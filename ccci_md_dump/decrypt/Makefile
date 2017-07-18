CC=arm-linux-androideabi-gcc 
CFLAGS=-I. -std=c11 -fPIE -pie
DEPS=../dump_md.h
SRC=decrypt.c
CP=adb push

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

decrypt: $(SRC)
	$(CC) -o $@ $^ $(CFLAGS)

install: decrypt
	$(CP) $< /data/local/tmp/

.PHONY: install
