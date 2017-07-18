#!/bin/bash
export AFL_PATH=$HOME/sources/afl-2.35b
echo "core" | sudo tee /proc/sys/kernel/core_pattern
echo "performance" | sudo tee /sys/devices/system/cpu/cpu[0123]/cpufreq/scaling_governor
afl-qfuzz -i in -o out -Q -m 4400 -x dict -- ../wrap_native
