#VERSION = 3
#PATCHLEVEL = 10
#SUBLEVEL = 61
#EXTRAVERSION = -gea92418

#KERNELVERSION = $(VERSION)$(if $(PATCHLEVEL),.$(PATCHLEVEL)$(if $(SUBLEVEL),.$(SUBLEVEL)))$(EXTRAVERSION)
#export VERSION PATCHLEVEL SUBLEVEL KERNELVERSION

KERNEL_DIR_X86=/lib/modules/$(shell uname -r)/build
KERNEL_DIR_ARM=htc_source/KERNEL_OBJ
TOOLCHAIN=android-ndk-r12b/toolchains/aarch64-linux-android-4.9/prebuilt/linux-x86_64/bin/aarch64-linux-android-
ARCHI=arm64
CP=adb push


obj-m+=dump_md.o

all:
	$(MAKE) ARCH=$(ARCHI) CROSS_COMPILE=$(TOOLCHAIN) -C $(KERNEL_DIR_ARM) M=$(PWD) modules
clean:
	$(MAKE) -C $(KERNEL_DIR_ARM) M=$(PWD) clean
	$(RM) Module.markers modules.order
install: dump_md.ko
	$(CP) $< /data/local/tmp/

.PHONY: install
