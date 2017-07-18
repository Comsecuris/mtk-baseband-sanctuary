# MTK Ril Unsolicited Parser Fuzzer

To run dynamically linked binaries with qemu user-static the elf loaders and the libc for the target architecture are required.

Add to `/etc/qemu-binfmt.conf`:

```
EXTRA_OPTS="-L /usr/arm-linux-gnueabi"
```
