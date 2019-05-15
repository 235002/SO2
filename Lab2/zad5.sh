#Usuwanie wszystkich podkatalogow zadanego katalogu (parametr wywołania skryptu)
#Zawartość tych podkatalogów należy przenieść do katalogu nadrzędnego
#Usuwanie dotyczy tylko jednego poziomu podkatalogów
#!/bin/bash

#sprawdzanie czy użytkownik podał właściwą liczbę parametrów - 1 (nazwa katalogu)
if [ "$#" != "1" ]
then
	echo "Nie podales wlasciwego parametru. Podaj nazwe katalogu, ktory chcesz wyczyscic"
	exit 1;
fi

#sprawdzenie czy istnieje katalog, który użyt. podał jako parametr
if [ ! -d $1 ]
then
	echo "Katalog nie istnieje";
	exit 1;
fi

#pętla usuwająca podkatalogi
for i in `ls $1`
do
	#w przypadku gdy istnieje podkatalog
	if [ -d $1/$1 ]
	then
		#przenosimy zawartosc do kat. nadrzednego
		mv $1/$i/* $1/
		#usuwamy pliki pierwotne
		rm -rf $1/$i
	fi
done
