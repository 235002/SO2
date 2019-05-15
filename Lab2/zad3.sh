#!/bin/bash
rm -rf Lab2.1

mkdir Lab2.1
mkdir Lab2.1/a
mkdir Lab2.1/e
mkdir Lab2.1/a/b
mkdir Lab2.1/a/c
mkdir Lab2.1/a/c/d

touch Lab2.1/a/b/plik1
touch Lab2.1/a/b/plik2
touch Lab2.1/e/plikA
touch Lab2.1/e/plikB

echo "test plik1" >> Lab2.1/a/b/plik1
echo "test plik2" >> Lab2.1/a/b/plik2
echo "test plikA" >> Lab2.1/e/plikA
echo "test plikB" >> Lab2.1/e/plikB

ln -s ../../b/plik1 Lab2.1/a/c/d/link_plik1
ln -s ../../../e/plikA Lab2.1/a/c/d/link_plikA
ln -s ../../b Lab2.1/a/c/d/link_kat_b

ln -s `realpath Lab2.1/a/b/plik2` Lab2.1/a/c/d/link_plik2_bez
ln -s `realpath Lab2.1/e/plikB` Lab2.1/a/c/d/link_plikB_bez
ln -s `realpath Lab2.1/a/b/plik1` Lab2.1/a/c/d/linik_plik1_bez

