#!/bin/sh
#input=`cat`
#echo $input
#echo $input | 
grep 'undefined reference to' |sed "s/.*undefined reference to //;s/\`//;s/'//"|sort|uniq|
sed 's/\(.*\)/void \1() { printf("\1 hit!");exit(1);}/'> undefined.c
