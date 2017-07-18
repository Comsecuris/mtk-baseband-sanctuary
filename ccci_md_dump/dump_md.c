#include <linux/mm.h>
#include <linux/miscdevice.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/mman.h>
#include <linux/random.h>
#include <linux/init.h>
#include <linux/raw.h>
#include <linux/tty.h>
#include <linux/capability.h>
#include <linux/ptrace.h>
#include <linux/spinlock.h>
#include <linux/device.h>
#include <linux/highmem.h>
#include <linux/backing-dev.h>
#include <linux/shmem_fs.h>
#include <linux/splice.h>
#include <linux/pfn.h>
#include <linux/export.h>
#include <linux/io.h>
#include <linux/uio.h>

#include <linux/uaccess.h>

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/wait.h>
#include <linux/interrupt.h>
#include <linux/syscalls.h>
#include <linux/file.h>

#include <linux/types.h>   // for dev_t typedef
#include <linux/kdev_t.h>  // for format_dev_t
#include <linux/fs.h>      // for alloc_chrdev_region()
#include <linux/string.h>
#include <linux/kallsyms.h>

#include <asm/io.h> //for debug purposes


#define LKM_MD_DUMP
#include "dump_md.h"

#include "includes/ccci_core.h"
#include "includes/ccci_tty.h"

#define DEVICE_NAME "md_dump"
#define DEVICE_CLASS "mddump"

#define FIND_SYM(fname, fptr) \
if (strcmp(name, fname) == 0)\
{\
    if (fptr != NULL)\
    {\
        printk(KERN_INFO "[md_dump] found two "fname", terminating\n");\
        return -EFAULT;\
    }\
    printk(KERN_INFO "[md_dump] found "fname" at %lx \n", addr);\
    fptr = (typeof(fptr))addr;\
    return 0;\
}
//#define VM_VM_AREA      0x04
typedef struct
{
    int            m_md_id;
    int            count;
    int            ready;
    int            need_reset;
    int            reset_handle;
    int            channel;
    int            uart_tx;
    int            uart_rx_ack;
    int            idx;
    struct wake_lock        wake_lock;
    char                wakelock_name[16];
    wait_queue_head_t        write_waitq;
    wait_queue_head_t        read_waitq;
    wait_queue_head_t        poll_waitq_r;
    wait_queue_head_t        poll_waitq_w;
    spinlock_t                poll_lock;
    shared_mem_tty_t        *shared_mem;
    struct mutex            ccci_tty_mutex;
    int                        has_pending_read;
    rwlock_t                ccci_tty_rwlock; 
    struct timer_list        timer;
    struct tasklet_struct    ccci_tty_tasklet;
} tty_instance_t;

MODULE_AUTHOR("gym");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Provides interaction with the MTK CCCI driver");
MODULE_VERSION("0.1");

static int majorNum;
static struct class* mddumpClass = NULL;
static struct device* mddumpDev = NULL;
static struct ccci_modem* md0;

char* (*md_info_str_p)(int)=NULL;
size_t (*ccci_version_show_p)(char *)=NULL;
struct ccci_modem* (*md_get_by_id)(int)=NULL;
void (*ap_clear_protection_p)(struct ccci_modem*)=NULL;
ssize_t (*emi_mpu_show_p)(struct device_driver*, char*)=NULL;
int (*sys_open_p)(const char __user *filename, int flags, umode_t mode);
int (*sec_aes_init_p)(void);
int (*lib_aes_dec_p)(unsigned char*, unsigned, unsigned char*, unsigned);

static long ioctl_dump(struct file *file, unsigned int ioctl_num, unsigned long ioctl_param)
{ 
    int fd, ret, i = 0;
    mm_segment_t old_fs;
    char buf[1024];
    char *buf2;
    struct modem_mem_region_info mdi;
    struct file* fl;
    tty_instance_t* tty_instance;
    struct tty_info ttyi;

    printk(KERN_INFO "[md_dump]  ioctl called %x\n", ioctl_num);
    // possibly useful md_2_ap_phy_addr_offset_fixed
    switch(ioctl_num)
    {
        case IOCTL_GET_MD_INFO_STR:
        {
            for (buf2=buf;i < 6;i++)
            {
                printk(KERN_INFO "[md_dump] modem %d info: %s\n", i,md_info_str_p(i));
                buf2 += sprintf(buf2, "[md_dump] modem %d info %s\n", i, md_info_str_p(i));
            }
            ret = copy_to_user((char*)ioctl_param, buf, strlen(buf));
            if (ret)
                printk(KERN_ALERT "[md_dump] failed to copy all the bytes to user\n");

        }
        break;
        case IOCTL_GET_DRV_VERSION:
        {
            ccci_version_show_p(buf);
            if(strcmp(buf, "3"))
            {
                printk(KERN_INFO "[md_dump] modem using ECCI driver\n");
                sprintf(buf, "ECCI");
            }
            else
            {
                printk(KERN_INFO "[md_dump] modem using DSDA driver\n");
                sprintf(buf, "DSDA");
            }
            ret = copy_to_user((char*)ioctl_param, buf, strlen(buf));
            if (ret)
                printk(KERN_ALERT "[md_dump] failed to copy all the bytes to user\n");

        }
        break;
        case IOCTL_GET_MODEM:
        {
            memset(&mdi, 0, sizeof(struct modem_mem_region_info));
            /*
            printk(KERN_INFO "[md_dump] modem 0 at: %p\n", md0);
            printk(KERN_INFO "[md_dump] md mem: %p size: %x\n", md0->mem_layout.md_region_vir, md0->mem_layout.md_region_size);
            printk(KERN_INFO "[md_dump] md phys mem: %llx\n", md0->mem_layout.md_region_phy);
            printk(KERN_INFO "[md_dump] dsp mem: %p size: %x\n", md0->mem_layout.dsp_region_vir, md0->mem_layout.dsp_region_size);
            printk(KERN_INFO "[md_dump] smem mem: %p size: %x offset AP to MD: %x\n", md0->mem_layout.smem_region_vir, md0->mem_layout.smem_region_size, md0->mem_layout.smem_offset_AP_to_MD);
            printk(KERN_INFO "[md_dump] smem base: %p size: %x \n", md0->smem_layout.ccci_exp_smem_base_vir, md0->smem_layout.ccci_exp_smem_size);
            printk(KERN_INFO "[md_dump] smem phy base: %llx\n", md0->smem_layout.ccci_exp_smem_base_phy);
            printk(KERN_INFO "[md_dump] smem dbg base: %p size: %p \n", md0->smem_layout.ccci_exp_smem_ccci_debug_vir, md0->smem_layout.ccci_exp_smem_ccci_debug_vir);
            printk(KERN_INFO "[md_dump] sim type: %x\n",md0->sim_type);
            */
            mdi.modem = (long long unsigned)md0;
            mdi.rom_phy = md0->mem_layout.md_region_phy;
            mdi.rom_virt = (long long unsigned)md0->mem_layout.md_region_vir;
            mdi.rom_size = md0->img_info[0].size;

            mdi.ram_phy = ((mdi.rom_phy + mdi.rom_size + 0xFFFF)&(~0xFFFF));
            mdi.ram_virt = ((mdi.rom_virt + mdi.rom_size + 0xFFFF)&(~0xFFFF));
            mdi.ram_size = md0->mem_layout.md_region_size - (mdi.ram_phy - mdi.rom_phy);
            
            mdi.shm_phy = md0->mem_layout.smem_region_phy;
            mdi.shm_virt = (long long unsigned)md0->mem_layout.smem_region_vir;
            mdi.shm_size = md0->mem_layout.smem_region_size;
            mdi.shm_offset = md0->mem_layout.smem_offset_AP_to_MD;
            mdi.md_address = md0->img_info[0].address;
            mdi.md_virt_addr = phys_to_virt(md0->img_info[0].address);

            mdi.sim_type = md0->sim_type;
            //mdi.ccif_base = (struct md_cd_ctrl*)md->private
            dump_mdi(&mdi);
            ret = copy_to_user((char*)ioctl_param, &mdi, sizeof(struct modem_mem_region_info));
            if (ret)
                printk(KERN_ALERT "[md_dump] failed to copy all the bytes to user\n");

            

        }
        break;
        case IOCTL_REMOVE_PROTECTION:
        {
            ap_clear_protection_p(md0);
            printk(KERN_INFO "[md_dump] trying to clear MD rom/ram protection\n");
        }
        break;
        case IOCTL_GET_MPU_INFO:
        {
            /*
             * THIS KILLS THE KERNEL
            buf2 = kmalloc(8096, GFP_ATOMIC);
            ret = emi_mpu_show_p(mddumpDev->driver, buf);
            printk(KERN_INFO "[md_dump] priv info size %d\n", ret);
            kfree(buf2);
            */
        }
        break;
        case IOCTL_GET_TTYC0_INFO:
        {
            memset(&ttyi, 0, sizeof(struct tty_info));
            old_fs = get_fs();
            set_fs(KERNEL_DS);
            // There are probably 1000 better ways to do this
            fd = sys_open_p("/dev/ttyC0", O_RDONLY, 0);
            if (fd < 0)
            {
                printk(KERN_INFO "[md_dump] failed to open /dev/ttyC0 %d:%x\n", fd, fd);
                return fd;
            }
            fl = fdget(fd).file;
            if (!fl)
            {
                printk(KERN_INFO "[md_dump] failed to get file handler\n");
                goto error_close;
            }
            tty_instance = (tty_instance_t*)fl->private_data;
            if (!tty_instance)
            {
                printk(KERN_INFO "[md_dump] failed to steal file private data\n");
                goto error_close;
            }
            sys_close(fd);
            set_fs(old_fs);
            
            ttyi.channel = (long long int)tty_instance->channel;
            ttyi.uart_tx = (long long int)tty_instance->uart_tx;
            ttyi.uart_rx_ack = (long long int)tty_instance->uart_rx_ack;
            ttyi.idx = (long long int)tty_instance->idx;
            ttyi.rx_ctrl_read = (long long unsigned)tty_instance->shared_mem->rx_control.read;
            ttyi.rx_ctrl_write = (long long unsigned)tty_instance->shared_mem->rx_control.write;
            ttyi.rx_ctrl_length = (long long unsigned)tty_instance->shared_mem->rx_control.length;
            ttyi.tx_ctrl_read = (long long unsigned)tty_instance->shared_mem->tx_control.read;
            ttyi.tx_ctrl_write = (long long unsigned)tty_instance->shared_mem->tx_control.write;
            ttyi.tx_ctrl_length = (long long unsigned)tty_instance->shared_mem->tx_control.length;

            ttyi.buffer_loc = (long long unsigned)tty_instance->shared_mem->buffer;

            ret = copy_to_user((char*)ioctl_param, &ttyi, sizeof(struct tty_info));
            if (ret)
            {
                printk(KERN_ALERT "[md_dump] failed to copy all the bytes to user\n");
                return -EFAULT;
            }
            printk(KERN_INFO "[md_dump] %lu bytes copied to user\n", sizeof(struct tty_info));
            return 0;
        
error_close:
            sys_close(fd);
            set_fs(old_fs);
            return -EFAULT;            
        }
        break;
        case IOCTL_DECRYPT_BUFFER:
        {
            struct todecrypt td;
            unsigned offset = 0;
            char tmp[16];
            char out[16];

            ret = copy_from_user(&td, (char*)ioctl_param, sizeof(struct todecrypt));
            if (ret)
            {
                printk(KERN_ALERT "[md_dump] failed to copy from user\n");
                return -EFAULT;
            }
            printk(KERN_INFO "[md_dump] decrypting %llx bytes\n", td.size);

            // calling the key init
            ret = sec_aes_init_p();
            if (ret)
            {
                printk(KERN_ALERT "[md_dump] sec key init failed\n");
                return -EFAULT;
            }
            
            while(offset < td.size)
            {
                ret = copy_from_user(tmp, td.data+offset, 16);
                if (ret)
                {
                    printk(KERN_ALERT "[md_dump] failed to copy from user at %x\n", offset);
                    return -EFAULT;
                }
                // actual decrypt func
                ret = lib_aes_dec_p(tmp, 16, out, 16);
                if (ret)
                {
                    printk(KERN_ALERT "[md_dump] failed to decrypt data at %x\n", offset);
                    return -EFAULT;
                }
                ret = copy_to_user(td.data+offset, out, 16);
                if (ret)
                {
                    printk(KERN_ALERT "[md_dump] failed to copy to user at %x\n", offset);
                    return -EFAULT;
                }
                offset +=16;
            }
            printk(KERN_INFO "[md_dump] decrypted %x bytes\n", offset);
            return 0;
        }
        break;
        default:
            return -EFAULT;

    }
    return 0;
}

static ssize_t
write_dump(struct file *file, const char __user * buffer, size_t length, loff_t * offset)
{
    printk(KERN_INFO "[md_dump] write is called\n");
    return 0;
}

static ssize_t read_dump(struct file *file, char __user *buffer, size_t length, loff_t *offset)
{
    
    printk(KERN_INFO "[md_dump] read is called\n");
    return 0;
}

static int open_dump(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "[md_dump] Ioctl num: %lx\n", IOCTL_GET_MD_INFO_STR);
    printk(KERN_INFO "[md_dump] Ioctl num: %lx\n", IOCTL_GET_DRV_VERSION);
    printk(KERN_INFO "[md_dump] Ioctl num: %lx\n", IOCTL_GET_MODEM);
    printk(KERN_INFO "[md_dump] Ioctl num: %lx\n", IOCTL_REMOVE_PROTECTION);
    printk(KERN_INFO "[md_dump] Ioctl num: %lx\n", IOCTL_GET_MPU_INFO);
    //file->f_op->unlocked_ioctl(file, IOCTL_GET_MD_INFO_STR, 0);
    //printk(KERN_INFO "[md_dump] ioctl call %p\n", file->f_op->unlocked_ioctl);

    return  0;
}

static const struct file_operations mddump_fops = {
	.read	    	= read_dump,
	.write	    	= write_dump,
//    .unlocked_ioctl = ioctl_dump,
    .compat_ioctl   = ioctl_dump,
	.open	    	= open_dump,
};


// Used to retrieve unexported symbols
static int symwalk_cb(void *data, const char *name, struct module *mod, unsigned long addr)
{
    //if (mod != NULL)
    //    return 0;
    FIND_SYM("ccci_get_md_info_str", md_info_str_p)
    FIND_SYM("ccci_version_show", ccci_version_show_p)
    FIND_SYM("ccci_get_modem_by_id", md_get_by_id)
    FIND_SYM("ccci_clear_md_region_protection", ap_clear_protection_p);
    FIND_SYM("emi_mpu_show", emi_mpu_show_p);
    FIND_SYM("sys_open", sys_open_p);
    FIND_SYM("sec_aes_init", sec_aes_init_p);
    FIND_SYM("lib_aes_dec", lib_aes_dec_p);
    return 0;
}

static int __init chr_dev_init(void)
{

    int ret;
	printk(KERN_INFO "[md_dump] is loading\n");
    ret = kallsyms_on_each_symbol(symwalk_cb, NULL);
    if (ret)
        return ret;

    md0 = md_get_by_id(0);
    if (!md0)
    {
        printk(KERN_ALERT "[md_dump] failed to acquire modem handler\n");
        return -EFAULT;
    }
    
	majorNum = register_chrdev(DEV_MD_MAJOR, DEVICE_NAME, &mddump_fops);
	if (majorNum < 0){
		printk(KERN_ALERT "[md_dump] unable to get major\n");
		return majorNum;
	}
#if DEV_MD_MAJOR > 0
    majorNum = DEV_MD_MAJOR;
#endif

	mddumpClass = class_create(THIS_MODULE, DEVICE_CLASS);
	if (IS_ERR(mddumpClass)){
		unregister_chrdev(majorNum, DEVICE_NAME);
		printk(KERN_ALERT "[md_dump] Failed to register class\n");
		return PTR_ERR(mddumpClass);
	}

	mddumpDev = device_create(mddumpClass, NULL, MKDEV(majorNum, 0), NULL, DEVICE_NAME);
	if (IS_ERR(mddumpDev)){
        class_destroy(mddumpClass);
		unregister_chrdev(majorNum, DEVICE_NAME);
		printk(KERN_ALERT "[md_dump] Failed to create device\n");
		return PTR_ERR(mddumpDev);
	}
    printk(KERN_INFO "[md_dump] device created\n");
    return 0;
}

static void __exit mddump_exit(void){
   device_destroy(mddumpClass, MKDEV(majorNum, 0));     // remove the device
   class_unregister(mddumpClass);                          // unregister the device class
   class_destroy(mddumpClass);                             // remove the device class
   unregister_chrdev(majorNum, DEVICE_NAME);             // unregister the major number
   printk(KERN_INFO "[md_dump] Goodbye from the LKM!\n");
}

module_init(chr_dev_init);
module_exit(mddump_exit);
