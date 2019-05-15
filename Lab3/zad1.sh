#Wyświetlić pliki, które mają kontretne ustawienia i posortować, wybrać 5 ostatnich
#Wyświetlić, które są stworzone mniej niż 5 sekund temu i wyświetlić ścieżkę bezzwględną, zamienić / na \
#!/bin/bash

echo "Pliki o dostępie zapisu grupowego i odczytu dla others: ";

find $1 -perm -020 -a -perm -004 | sort | tail -n 5

echo "Pliki *.txt stworzone mniej niz 5 sekund temu: ";

find $1 -name "*.txt" -newermt '-5 seconds' | while read file
do
	echo `realpath $file` | tr '/' '\\'
done
