#!/bin/bash
FILES="./crashes/*"
#OUTPUT="crash_trace"
ELF="../wrap_native"
for dir in $FILES
do
    DIR="${dir}/*"
    for f in $DIR
    do
        OUTPUT="${dir##*/}_trace"
        echo "Processing $f"

        echo -e "\n##############################################\n" >> $OUTPUT
        echo $f >> $OUTPUT
        qemu-arm -g 1234 $ELF < $f &
        arm-linux-gnueabihf-gdb -q --se=$ELF -nh -batch -ex 'target remote localhost:1234' -ex 'c' -ex 'bt' -ex 'i r' >> $OUTPUT
    done
done
    
