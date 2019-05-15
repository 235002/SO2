#!/usr/bin/python3

import sys
import os
import shutil

if len(sys.argv) != 3:
	print("Zla ilosc paramaterow")
	raise SystemExit()
	
dirDeleteFrom = sys.qrgv[1]
dirCopyTo = sys.argv[2]

for file in os.listdir(dirDeleteFrom):
		if os.path.isdir(dirDeleteFrom + "/" + file):
			for file2 in os.listdir(dirDeleteFrom + "/" + file):
				if file2.lower().endswith('.txt'):
					os.rename(dirDeleteFrom + "/" + file + "/" + file2, dirCopyTo + "/" + file2)
					print("Backup file: " + dirDeleteFrom + "/" + file + "/" + file2)
			os.removedirs(dirDeleteFrom + "/" + file)
			