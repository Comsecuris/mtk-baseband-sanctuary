#ifndef DUMP_MODEM_HEADER
#define DUMP_MODEM_HEADER

#include <linux/ioctl.h>

#define DEV_MD_MAJOR 210 //0 for dynamic
// IOCTL Commands
//#define MD_DUMP_IOCTL_BASE 0x10
#define MD_DUMP_IOCTL_BASE 210


#ifdef LKM_MD_DUMP
#define MYPRINT printk
#else
#define MYPRINT printf
#define KERN_INFO
#endif

struct modem_mem_region_info
{
    long long unsigned modem;
    
    long long unsigned rom_phy;
    long long unsigned rom_virt;
    long long unsigned rom_size;

    long long unsigned ram_phy;
    long long unsigned ram_virt;
    long long unsigned ram_size;

    long long unsigned shm_phy;
    long long unsigned shm_virt;
    long long unsigned shm_size;
    long long unsigned shm_offset;

    long long unsigned sim_type;

    long long unsigned ccif_base;
    long long unsigned md_address;
    long long unsigned md_virt_addr;

};

struct tty_info
{
    long long int channel;
    long long int uart_tx;
    long long int uart_rx_ack;
    long long int idx;

    long long unsigned rx_ctrl_read;
    long long unsigned rx_ctrl_write;
    long long unsigned rx_ctrl_length;
    
    long long unsigned tx_ctrl_read;
    long long unsigned tx_ctrl_write;
    long long unsigned tx_ctrl_length;

    long long unsigned buffer_loc;

};

struct todecrypt
{
    long long unsigned size;
    char * data;
};

void dump_ttyi(struct tty_info* ttyi)
{
    MYPRINT(KERN_INFO "[md_dump]-----dumping ttyC0 info----\n");
    MYPRINT(KERN_INFO "[md_dump] channel: %llx:%lld\n", ttyi->channel, ttyi->channel);
    MYPRINT(KERN_INFO "[md_dump] uart_tx: %llx:%lld\n", ttyi->uart_tx, ttyi->uart_tx);
    MYPRINT(KERN_INFO "[md_dump] uart_rx_ack: %llx:%lld\n", ttyi->uart_rx_ack, ttyi->uart_rx_ack);
    MYPRINT(KERN_INFO "[md_dump] idx: %llx:%lld\n", ttyi->idx, ttyi->idx);
    MYPRINT(KERN_INFO "[md_dump] RX CTRL:\n");
    MYPRINT(KERN_INFO "[md_dump] \tread: %llx:%lld\n", ttyi->rx_ctrl_read, ttyi->rx_ctrl_read);
    MYPRINT(KERN_INFO "[md_dump] \twrite: %llx:%lld\n", ttyi->rx_ctrl_write, ttyi->rx_ctrl_write);
    MYPRINT(KERN_INFO "[md_dump] \tlength: %llx:%lld\n", ttyi->rx_ctrl_length, ttyi->rx_ctrl_length);

    MYPRINT(KERN_INFO "[md_dump] TX CTRL:\n");
    MYPRINT(KERN_INFO "[md_dump] \tread: %llx:%lld\n", ttyi->tx_ctrl_read, ttyi->tx_ctrl_read);
    MYPRINT(KERN_INFO "[md_dump] \twrite: %llx:%lld\n", ttyi->tx_ctrl_write, ttyi->tx_ctrl_write);
    MYPRINT(KERN_INFO "[md_dump] \tlength: %llx:%lld\n", ttyi->tx_ctrl_length, ttyi->tx_ctrl_length);

    MYPRINT(KERN_INFO "[md_dump] Buffer: %llx\n", ttyi->buffer_loc);
    MYPRINT(KERN_INFO "[md_dump] -----End of Dump------\n");
}

void dump_mdi(struct modem_mem_region_info* mdi)
{
    MYPRINT(KERN_INFO "[md_dump]----dumping modem info----\n");
    MYPRINT(KERN_INFO "[md_dump] Modem 0 at: %llx\n", mdi->modem);
    MYPRINT(KERN_INFO "[md_dump] Rom:\n");
    MYPRINT(KERN_INFO "[md_dump] \tPhys start: %llx\n", mdi->rom_phy);
    MYPRINT(KERN_INFO "[md_dump] \tVirt start: %llx\n", mdi->rom_virt);
    MYPRINT(KERN_INFO "[md_dump] \tsize: %llx\n", mdi->rom_size);
    
    MYPRINT(KERN_INFO "[md_dump] Ram:\n");
    MYPRINT(KERN_INFO "[md_dump] \tPhys start: %llx\n", mdi->ram_phy);
    MYPRINT(KERN_INFO "[md_dump] \tVirt start: %llx\n", mdi->ram_virt);
    MYPRINT(KERN_INFO "[md_dump] \tsize: %llx\n", mdi->ram_size);
    
    MYPRINT(KERN_INFO "[md_dump] Shm:\n");
    MYPRINT(KERN_INFO "[md_dump] \tPhys start: %llx\n", mdi->shm_phy);
    MYPRINT(KERN_INFO "[md_dump] \tVirt start: %llx\n", mdi->shm_virt);
    MYPRINT(KERN_INFO "[md_dump] \tsize: %llx\n", mdi->shm_size);
    MYPRINT(KERN_INFO "[md_dump] \toffset: %llx\n", mdi->shm_offset);

    MYPRINT(KERN_INFO "[md_dump] CCIF base: %llx\n", mdi->ccif_base);

    MYPRINT(KERN_INFO "[md_dump] SIM type: %llx\n", mdi->sim_type);
    MYPRINT(KERN_INFO "[md_dump] Modem img address: %llx\n", mdi->md_address);
    MYPRINT(KERN_INFO "[md_dump] Modem virt  img address: %llx\n", mdi->md_virt_addr);
    MYPRINT(KERN_INFO "[md_dump]----End of Dump----\n");

    
}

#define IOCTL_GET_MD_INFO_STR _IOR(MD_DUMP_IOCTL_BASE, 0, char*)
#define IOCTL_GET_DRV_VERSION _IOR(MD_DUMP_IOCTL_BASE, 1, char*)
#define IOCTL_GET_MODEM _IOR(MD_DUMP_IOCTL_BASE, 2, char*)
#define IOCTL_REMOVE_PROTECTION _IOR(MD_DUMP_IOCTL_BASE, 3, char*)
#define IOCTL_GET_MPU_INFO _IOR(MD_DUMP_IOCTL_BASE, 4, char*)
#define IOCTL_GET_TTYC0_INFO _IOR(MD_DUMP_IOCTL_BASE, 5, char*)
#define IOCTL_DECRYPT_BUFFER _IOWR(MD_DUMP_IOCTL_BASE, 6, char*)

#define DRV_ECCI 3
#define DRV_DSDA 5


#endif
