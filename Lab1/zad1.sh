#!/bin/bash
for file in "$1"/*;
do
	if [ ! -x $file ]
	then
		rm $file -f
	fi
done
