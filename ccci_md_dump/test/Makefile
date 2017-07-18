CC=arm-linux-androideabi-gcc 
CFLAGS=-I. -std=c11 -fPIE -pie
DEPS=../dump_md.h
SRC=client.c
CP=adb push

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

client: $(SRC)
	$(CC) -o $@ $^ $(CFLAGS)

install: client
	$(CP) $< /data/local/tmp/

.PHONY: install
