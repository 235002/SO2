#!/bin/bash
./zad3.sh
mkdir Lab2.1/f
cp Lab2.1/a/c/d/link_plik1 Lab2.1/f
cp -d Lab2.1/a/c/d/link_plikB_bez Lab2.1/f

for file in `ls Lab2.1/a/c/d`;
do
	if [ `readlink -ef $file` == `realpath Lab2.1/a/b/plik1` ];
	then
		echo $file
	fi
done
