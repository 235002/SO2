#!/bin/bash
zawartosc=`cat $1`
for plik in zawartosc
do
	if [[ -f $plik ]]
	then
		echo "Plik $plik: " >> $1
		cat $plik >> $1
	fi
rm $1 -f
done
