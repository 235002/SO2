#!/usr/bin/python3

import sys
import os
import shutil

if len(sys.argv) != 4:
	print("Zla ilosc paramaterow")
	raise SystemExit()

dirFrom = sys.argv[1]
ext = sys.argv[2]
dirTo = sys.argv[3]

for file in os.listdir(dirFrom):
	if file.endswith(".txt"):
		os.remove(os.path.join(dirFrom, file))
	elif file.endswith(ext):
		shutil.copyfile(os.path.join(dirFrom, file), os.path.join(dirTo, file))