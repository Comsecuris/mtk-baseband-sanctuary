CC=arm-none-eabi-gcc 
#LIBS=-lmm -lmml1_rf -lmrs
#LIBS=-l3g324m_tvt -las_semaphore_utility -lbtt_agent -lbytecopy -lcc -lche -lcipher -lciss -lcldmacore -lcldmadev -lcmux -ldata -ldhl -ldp_engine -ldsp_ram -ledsp -ledyn -lel1 -lel2 -lemm -lephy -lerac -lerrc -lesm -letc -letcm -letmr -leval -levent_info -lfdm -lflc2_v2 -lflc2_v2_sec -lfsm -lgas -lgl1 -lhmu_sec -limc -limcsms -limsp -lkal -ll2_lte_copro -ll4 -llbs -lll1 -lllc -llpp -lltecsr -lltecsr_src -lltm_multi -lmcd -lmm -lmml1_rf -lmrs -lmtkdebug -lnmu -lnucleus_v2 -lnucleus_v2_critical_data -lnucleus_v2_ctrl_code -lnucleus_v2_debug -lnucleus_v2_int -lnvram_sec -lnwsel -lqmu_bm -lratadp -lratcm -lratdm -lratdm_sec -lrfc2507 -lrohc -lrrlp -lrsva -lrtp -lscsi -lsdm -lsim -lsleep_drv -lsm -lsms -lsndcp -lsst -lsst_sec -lsys_svc_sec -ltdd_drv -ltftlib -ltft_pf -ltstm -luas -lul1_hs_plus -lul2 -lulcs -lupcm -lvdm -lwccifdev 
#lmcd and lscsi are free they dont pull in new deps
#lmrs and luas contain the asn parsing they are a must
LIBS=-lmm -lmcd -lmrs -lscsi -ldefined
LINKER1=--no-wchar-size-warning,--start-group
LINKER2=--end-group
LFLAGS=-Wl,$(LINKER1) $(LIBS) -Wl,$(LINKER2) -Wl,--start-group -lgcc -lc -lm -lrdimon -Wl,--end-group
#override inline macros so gcc wouldnt freak
DEFINE=-DINLINE=inline -DINLINE_MODIFIER=static
CFLAGS=$(DEFINE) -std=gnu99 -fPIC -nostartfiles# -nostdlib
#FLAGS=-static -marm -mthumb-interwork -mfpu=vfpv3-d16 -mfloat-abi=softfp -march=armv7-a #-mcpu=cortex-r4
FLAGS=-fshort-enums -fshort-wchar -static -mthumb -mfloat-abi=softfp -march=armv7-r -mcpu=cortex-r4 -mfpu=vfpv3-d16 
EXECUTABLE=wrap
CP=adb push

STATLIB=lib/libdefined.a
SRC=defined.c stub.c wrap_mm.c
HDR=libdefined.h
LOBJ=obj/defined.o obj/stub.o
EOBJ=obj/wrap_mm.o obj/asn_common.o obj/asn_memory.o
EXTOBJ=ext_obj/lcd_lqueue.obj ext_obj/mcd_table_l4.obj ext_obj/bitstream.obj
#%.o: %.c $(DEPS)
#	$(CC) -c -o $@ $< $(CFLAGS)
all: $(STATLIB) $(EXECUTABLE)

obj/%.o: src/%.c include/$(HDR)
	$(CC) -I./ext_include/ -I./include -c $(FLAGS) $(CFLAGS) -o $@ $<

obj/%.o: ext_src/%.c
	$(CC) -I./ext_include/ -I./include -c $(FLAGS) $(CFLAGS) -o $@ $<

$(STATLIB): $(LOBJ)
	ar rcs $@ $^

$(EXECUTABLE): $(EOBJ) $(STATLIB)
	$(CC) -L./lib/ $(FLAGS) -o $@ $^ $(EXTOBJ) $(LFLAGS) 

undefined: $(EOBJ) $(STATLIB)
	$(CC) -L./lib/ $(FLAGS) -o $(EXECUTABLE) $^ $(EXTOBJ) $(LFLAGS) 2>&1| ./define.sh


clean:
	rm -f $(EXECUTABLE)
	rm -f $(STATLIB)
	rm -f obj/*

.PHONY: clean
