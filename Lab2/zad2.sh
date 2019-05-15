#stworzyć skrypt, który odpali pierwszy skrypt
#przekopiować plik wykorzystując dowiązanie symboliczne
#przekopiować dowiązanie symboliczne
#sprawdzić czy dowiązania wskazują na ten sam plik
#!/bin/bash

./zad1.sh

p1=`realpath Lab2/a/b/plik1`
p2=`realpath Lab2/c/d/plikA`

for file in `ls Lab2/a/e`
do
	if [ -h Lab2/a/e/$file ]
	then
		link=`readlink -f Lab2/a/e/$file`
		if [ $p1 = $link ] || [ $p2 = $link ]
		then
			echo $link
		fi
	fi
done

mkdir Lab2/f
cp -d Lab2/a/e/link_plikB_bez Lab2/f
cp Lab2/a/e/link_plikA Lab2/f
