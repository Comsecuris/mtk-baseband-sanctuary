#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <errno.h>
//#include <libexplain/ioctl.h>

#include "../dump_md.h"

void do_ioctl(int fd, unsigned int cmd, char* buf)
{
    int data, ret;
    
    cmd+=0x40000;
    printf("Sending ioctl: %lx\n", cmd);
    ret = ioctl(fd, cmd, buf);
    if (ret < 0)
    {
        printf("Failed to send ioctl: %d\n", ret);
        printf("Reason: %s\n", strerror(errno));
        printf("Errno: %d\n", errno);
    }

}

void dump_area(int device, char* filename, long long unsigned address, unsigned length)
{
    printf("Trying to dump  %x bytes at %llx to %s\n", length, address, filename);
    FILE* fo = fopen(filename, "wb");
    if (!fo)
    {
        printf("Failed to open out file: %s\n", filename);
        return;
    }

    char* buf= (char*)malloc(length);
    if (!buf)
    {
        printf("Failed to allocate memory %x\n", length);
        fclose(fo);
        return;
    }
    lseek64(device, address, SEEK_SET);
    read(device, buf, length);
    fwrite(buf, 1, length, fo);
    free(buf);
    fclose(fo);

}


int main(int argc, char** argv)
{
    int ret;
    int fd, fdmem;
    int fdtty;

    fd = open("/dev/md_dump", O_RDWR| O_NONBLOCK);
    if (fd < 0)
    {
        printf("Failed to open device\n");
        return 0;
    }
    fdmem = open("/dev/kmem", O_RDWR| O_LARGEFILE);
    if (fdmem < 0)
    {
        printf("Failed to open /dev/kmem\n");
        return 0;
    }
    char info[1024];
    char drv_version[128];
    struct modem_mem_region_info mdi;
    struct tty_info ttyi;

    do_ioctl(fd, IOCTL_GET_MD_INFO_STR, info);
    puts(info);
    do_ioctl(fd, IOCTL_GET_DRV_VERSION, drv_version);
    printf("[md_dump] driver used by modem: %s\n", drv_version);
    do_ioctl(fd, IOCTL_GET_MODEM, (char*)&mdi);
    dump_mdi(&mdi);
    //do_ioctl(fd, IOCTL_GET_TTYC0_INFO, (char*) &ttyi);
    //dump_ttyi(&ttyi);
    //printf("Size of ttyi: %lu\n", sizeof(struct tty_info));
    //do_ioctl(fd, IOCTL_REMOVE_PROTECTION, info);
    //do_ioctl(fd, IOCTL_GET_MPU_INFO);
    
    dump_area(fdmem, "rom.dump", mdi.rom_virt, 0x1000);
    close(fdmem);
    close(fd);

    return 0;
}
