#!/bin/bash
cnum=`grep -c ^processor /proc/cpuinfo`
grep ^model\ name /proc/cpuinfo | head -n 1 | cut -f 2 1>&2
for (( c=1; c<=cnum; c++ ))
do
	echo -e "N = $1 \nc = $c" 1>&2
	time ./matrix $1 $c >> /dev/null 
	echo -e "\n\n\n\n" 1>&2
done
