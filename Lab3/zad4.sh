#Wyświetlić "*.exe", wielkość plików do 64 bajtów na ekranie i do pliku
#ścieżka kanoniczna | data | czas
#!/bin/bash

find . -maxdepth 10 -name "*.exe" -size -64c -perm -100 | head -5 | while read file
do
	echo `realpath $file`"|"`date -r $file +%Y-%m-%d`"|"`date -r $file +%H:%M:%S` | tr '/' '\\'
done | tee result2.txt
