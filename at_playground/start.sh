#!/system/bin/sh
echo "Starting mitm proxy">/data/local/tmp/boot.log
mitm_fs &
sleep 1
echo "Starting real muxd">>/data/local/tmp/boot.log
/data/local/tmp/ccci_fsd 0
