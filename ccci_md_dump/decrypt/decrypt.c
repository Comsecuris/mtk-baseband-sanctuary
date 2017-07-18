#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#include "../dump_md.h"

#define FWIMG_PATH "/etc/firmware/modem_1_lwg_n.img"
#define OUT_FILE "./modem_raw.img"

typedef struct _SEC_CIPHER_IMG_HEADER
{
    unsigned int magic_number;

    unsigned char cust_name [32];
    unsigned int image_version;
    unsigned int image_length;
    unsigned int image_offset;

    unsigned int cipher_offset;
    unsigned int cipher_length;

    /*
     * v0 : legacy
     * v1 : standard operations
     */
    unsigned int aes_version;
    unsigned char dummy[68];

}CIPHER_HEADER;



typedef struct _SEC_IMG_HEADER_V2
{
    unsigned int magic_number;
    unsigned char cust_name [32];
    unsigned int image_version;
    unsigned int image_length;
    unsigned int image_offset;

    unsigned int sign_offset;
    unsigned int sign_length;
    unsigned int signature_offset;
    unsigned int signature_length;
} SEC_IMG_HEADER_V2, SEC_IMG_HEADER_V3, SEC_IMG_HEADER;

typedef struct _SEC_IMG_HEADER_V4
{
    unsigned int magic_number;

    unsigned char cust_name [32];
    unsigned int image_version;
    unsigned int signature_length;
    unsigned int image_offset;

    unsigned int ext_magic;
    unsigned int ext_hdr_length;

    unsigned int image_length_high;
    unsigned int image_length_low;
} SEC_IMG_HEADER_V4;


typedef struct _SEC_EXTENSTION_CRYPTO
{
    unsigned int magic;
    unsigned int ext_type;
    unsigned char hash_type;
    unsigned char sig_type;
    unsigned char enc_type;
    unsigned char reserved;
} SEC_EXTENSTION_CRYPTO;

typedef struct _SEC_FRAGMENT_CFG
{
    unsigned int magic;
    unsigned int ext_type;
    unsigned int chunk_size;
    unsigned int frag_count;
} SEC_FRAGMENT_CFG;
typedef struct _SEC_EXTENSTION_HASH_ONLY
{
    unsigned int magic;
    unsigned int ext_type;
    unsigned int sub_type;  /* hash type */
    unsigned int hash_offset;
    unsigned int hash_len;
    unsigned char hash_data[];
} SEC_EXTENSTION_HASH_ONLY;


typedef struct _SEC_EXTENSTION_HASH_ONLY_64
{
    unsigned int magic;
    unsigned int ext_type;
    unsigned int sub_type;  /* hash type */
    unsigned int padding;
    unsigned long long hash_offset_64;
    unsigned long long hash_len_64;
    unsigned char hash_data[];
} SEC_EXTENSTION_HASH_ONLY_64;

typedef struct _SEC_EXTENSTION_HASH_SIG
{
    unsigned int magic;
    unsigned int ext_type;
    unsigned int sig_type;  /* sig type */
    unsigned int hash_type; /* hash type */
    unsigned int auth_offset;
    unsigned int auth_len;
    unsigned char auth_data[];  /* sig + hash */
} SEC_EXTENSTION_HASH_SIG;

typedef struct _SEC_EXTENSTION_END_MARK
{
    unsigned int magic;
    unsigned int ext_type;
} SEC_EXTENSTION_END_MARK;

typedef struct _SEC_IMG_EXTENSTION_SET
{
    SEC_EXTENSTION_CRYPTO *crypto;
    SEC_FRAGMENT_CFG *frag;
    SEC_EXTENSTION_END_MARK *end;
    SEC_EXTENSTION_HASH_ONLY **hash_only;
    SEC_EXTENSTION_HASH_ONLY_64 **hash_only_64;
} SEC_IMG_EXTENSTION_SET;

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
int main(int argc, char ** argv)
{
    FILE * fw;
    CIPHER_HEADER ch;
	SEC_IMG_HEADER_V4 simh;
	SEC_IMG_EXTENSTION_SET sies;
	fw = fopen(FWIMG_PATH, "rb");
    if(!fw)
	{
		printf("[ERROR] Failed to open file\n");
        exit(0);
	}
    fread(&simh, sizeof(SEC_IMG_HEADER_V4), 1, fw);
    if (simh.magic_number != 0x53535353 || simh.ext_magic != 0x7b797b79)
    {
        printf("[ERROR] wrong img format\n");
        exit(0);
    }
    printf("[INFO] IMG HDR img ver: %x img offset: %x\n", simh.image_version, simh.image_offset);
    fseek(fw, 0, SEEK_END);
    long long unsigned file_size = ftell(fw);
    long long unsigned img_len = (((long long unsigned)simh.image_length_high<<32) & 0xffffffff00000000) + simh.image_length_low;
    long long unsigned img_sign_offset = img_len + simh.image_offset;
    long long unsigned ext_headers_offset = img_sign_offset + simh.signature_length;
    unsigned ext_hdr_length = (file_size - ext_headers_offset) & 0xffffffff;
    printf("[INFO] img_len: %llx file size: %llx sign offset: %llx\n", img_len, file_size, img_sign_offset);
    
    fseek(fw, sizeof(SEC_IMG_HEADER_V4), SEEK_SET);
    fread(&ch, sizeof(CIPHER_HEADER), 1, fw);
    if (ch.magic_number != 0x63636363)
    {
        printf("[ERROR] wrong cipher format\n");
        exit(0);
    }
    printf("[INFO] CH img version: %x img len: %x img offset: %x cipher off: %x cipher len: %x cipher type %s\n", 
            ch.image_version, ch.image_length, ch.image_offset, ch.cipher_offset, ch.cipher_length, ch.aes_version ? "STD":"LEGACY");
    
    struct todecrypt td;
    td.size = ch.cipher_length;
    td.data = (char*) malloc(td.size);
    if (!td.data)
    {
        printf("[ERROR] Failed to allocate buffer\n");
        exit(0);
    }
    
    int ret = fread(td.data, td.size, 1, fw);
    if (ret != 1)
    {
        printf("[ERROR] Failed to read cipher data %x\n", ret);
        exit(0);
    }
    //decrypt data ioctl
    int fd = open("/dev/md_dump", O_RDWR| O_NONBLOCK);
    if (fd < 0)
    {
        printf("Failed to open ioctl device\n");
        return 0;
    }
    do_ioctl(fd, IOCTL_DECRYPT_BUFFER, (char*)&td);

    char * plain = malloc(ch.image_length);
    if (!plain)
    {
        printf("[ERROR] Failed to allocate memory\n");
        exit(0);
    }
    memcpy(plain, td.data, td.size);
    ret = fread(plain+td.size, ch.image_length - td.size, 1, fw);
    if (ret != 1)
    {
        printf("[ERROR] Failed to read rest of data %x\n", ret);
        exit(0);
    }
    FILE* fout = fopen(OUT_FILE, "wb");
    if(!fout)
    {
        printf("[ERROR] Failed to open out file\n");
        exit(0);
    }
    fwrite(plain, ch.image_length, 1, fout);
    return 0;
}
