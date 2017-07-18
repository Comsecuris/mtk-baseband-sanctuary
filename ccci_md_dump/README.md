# CCCI Info Dump Kernel Module

This is a kernel module used to interact with ECCCI kernel driver and retrieve modem information, such as different memory addresses. It is also used to disable the EMI MPU protection for the modem memory regions and to decrypt the firmware image. This kernel driver was only tested with the MT6795 chipset and HTC's Linux 3.10 Android kernel.

### Test 

It is a simple C client that uses this kernel driver to retrieve the modem addresses.

### Decrypt

This program is used to decrypt the firmware image file that's stored on the device.
