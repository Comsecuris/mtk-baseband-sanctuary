#!/usr/bin/python2
import os
import struct
DBG = 0
try:
    import idaapi
    import idautils
    import idc
except:
    DBG = 1

FILE_MAGIC = "CATI"
FILE_NAME = "~/htcm9/logs/mtklog/mdlog1/MDLog1_2016_0912_110645/DbgInfo_LR9.W1423.MD.LWTG.MP_MT6795_HIAU_1_1506V24P21_2005_0505_HTW_2015_05_05_18_19_1_lwg_n"

THUMB = 1
ARM = 0

extr_func =[["huge_init", 0x3ea4, 0x46b6, ARM],["pre_h_init",0x3de8,0x3e64,ARM], ["smh1", 0x7988d8, 0x798990, ARM]]

data1 = [0x6f5ffc, 0x7988d8]


rename = True
named = 0
created = 0

def get_c_str(fin):
    buf = bytearray()
    while True:
        b = fin.read(1)
        if b is None or b == '\0':
            return str(buf)
        else:
            buf.append(b)

def dump_info(fin):
    print "[#] Dumping img info:"
    print "[#] Version: " + get_c_str(fin)
    print "[#] Sub: " + get_c_str(fin)
    print "[#] Build: " + get_c_str(fin)
    print "[#] Time: " + get_c_str(fin)

def get_symbol(fin):
    fname = get_c_str(fin)
    begin = struct.unpack("<I", fin.read(4))[0]
    end = struct.unpack("<I", fin.read(4))[0]
    if begin == end:
        curr = fin.tell()
        junk = get_c_str(fin)
        end = struct.unpack("<I", fin.read(4))[0]
        fin.seek(curr)
    if begin % 2 == 1:
        mode = THUMB
        begin -= 1
        end -= 1
    else:
        mode = ARM
    return fname, begin, end, mode

def rename_func(begin, fname):
    global named
    fname = fname.replace('~','__')
    fname = fname.replace('<','_')
    fname = fname.replace('>','_')
    try:
        ret = idc.MakeName(begin, fname)
        named += 1
    except:
        if ret == 0 and idc.MakeName(begin, '_'+fname +'1')  !=0:
            named += 1
        elif ret == 0 and idc.MakeName(begin, '_'+fname +'2')  !=0:
            named += 1

def create_function(fname, begin, end, mode):
    global rename, named, created
    addr = begin
    ## Making Code
    while addr < end:
        #if not idc.GetMnem(addr):
        ret = idc.MakeCode(addr)
        if ret != 0:
            addr += ret
        else:
            addr += 4 - (2 * mode)
    if not idc.GetFunctionName(begin):
        ret = idc.MakeFunction(begin, end);
        if ret == 0:
            print "[WARN] Failed to create function: "+fname+" at:"+hex(begin)+ " end:"+ hex(end) +" mode:"+str(mode)
            return
        else:
            created += 1
        rename_func(begin, fname)
    else:
        idc.SetFunctionEnd(begin, end)
        if rename:
            rename_func(begin, fname)

def print_stat():
    global created, named
    print "[#] Created "+str(created)+" functions"
    print "[#] Named "+str(named)+" functions"

def load_dbg_file(fn):
    with open(fn, "rb") as fin:
        magic = fin.read(4)
        if magic != FILE_MAGIC:
            print "[ERROR] File magic is incorrect: "+magic+ ", provide valid DBG file!"
            return -1
        junk = fin.read(8)
        dump_info(fin)
        junk = fin.read(8)
        i=0
        pMode = THUMB
        idc.SetReg(0x0, "T", THUMB)
        while i < 10:
            fname, begin, end, mode = get_symbol(fin)
            if "/" in fname:
                print "[#] End of symbol region is reached. We are done!"
                break
            if DBG:
                print "[*] Name: "+fname+" Start: "+hex(begin)+" End: "+hex(end) + " ARM mode: " + str(mode)
                i+=1
#            if pMode != mode:
#                ret = idc.SetReg(begin, "T", mode)
#                if not ret:
#                    print "[ERROR] Failed to set segment register"
#                    continue
#                else:
#                    pMode = mode
            ret = idc.SetReg(begin, "T", mode)
            if not ret:
                print "[ERROR] Failed to set segment register"
                continue
            create_function(fname, begin, end, mode)
        print_stat()

load_dbg_file(FILE_NAME)
