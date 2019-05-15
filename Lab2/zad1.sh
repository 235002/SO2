#Tworzymy nowy folder i kalatogi z pliakmi
#Tworzymy dowiązania symboliczne do plików tekstowych
#Komenda ln -s arg1 arg2 - tworzy dowiązanie symobliczne
# -s -tworzenie dowiązań symbolicznych zamiast zwykłych
# arg1 - ścieżka do celu(pliku,folderu)
# arg2 - ścieżka, w którym ma zostać utworzony link
# realpath - przekształca podaną ścieżkę na kanoniczą
#!/bin/bash

rm -rf Lab2

mkdir Lab2
mkdir Lab2/a
mkdir Lab2/c
mkdir Lab2/a/b
mkdir Lab2/a/e
mkdir Lab2/c/d

echo "test1" > Lab2/a/b/plik1
echo "test2" > Lab2/a/b/plik2
echo "testA" > Lab2/c/d/plikA
echo "testB" > Lab2/c/d/plikB

#tworzenie dowiązań względnych
ln -s ../b/plik1 Lab2/a/e/link_plik1
ln -s ../../c/d/plikA Lab2/a/e/link_plikA
ln -s ../b/plik2 Lab2/a/e/link_plik2
ln -s ../../c/d/ Lab2/a/e/link_do_d

#tworzenie dowiązań bezwzględnych
ln -s `realpath Lab2/a/b/plik1` Lab2/a/e/linik_plik1_bez
ln -s `realpath Lab2/c/d/plikB` Lab2/a/e/linik_plikB_bez
