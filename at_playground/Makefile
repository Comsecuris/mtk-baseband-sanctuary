CC=arm-linux-androideabi-gcc 
CFLAGS=-I. -std=c11 -fPIE -pie -pthread
SRC=mitm.c
CP=adb push

mitm: $(SRC)
	$(CC) -o $@ $^ $(CFLAGS)

install: mitm
	$(CP) $< /data/local/tmp/

.PHONY: install
