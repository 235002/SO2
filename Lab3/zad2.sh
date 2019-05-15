#Wyświetlić sciężkę bezzwględną, datę, godzinę
#Jednym poleceniem wrzucić do pliku i na ekran
#!/bin/bash

echo "Pliki *.txt stworzone mniej niż 50000 sekund temu: ";
#-maxdepth 3
find $1 -name "*.txt" -newermt '-50000 seconds' | while read file
do
	echo `realpath $file`"|"`date -r $file +%Y-%m-%d`"|"`date -r $file +%H:%M:%S` | tr '/' '\\'
done | tee result.txt



for file in `cat result.txt`
do
	echo $file | cut -d"|" -f1;
done
