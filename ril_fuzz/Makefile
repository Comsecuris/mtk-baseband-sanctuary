CC=arm-linux-androideabi-gcc 
CFLAGS=-I. -std=c11 -fPIE -pie -ldl -pthread -static
SRC=wrap.c
CP=adb push
SYSROOT=/home/gym/dev/comsec/toolchain5.0.2/sysroot/

wrap: $(SRC)
	$(CC) -L$(SYSROOT)usr/lib/ -I$(SYSROOT)usr/include/  -o $@ $^ $(CFLAGS) 

install: wrap
	$(CP) $< /data/local/tmp/

.PHONY: install
