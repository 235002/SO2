#!/usr/bin/python
import sys
import os


import sys
if len(sys.argv) !=3:
	print("Incorrect parameters.")
	raise SystemExit()
	
dirFrom = sys.argv[1]
dirTo = sys.argv[2]
	
for file in os.listdir(dirFrom):
	if os.access(dirFrom + "/" + file, os.X_OK):
		os.rename(dirFrom + "/" + file, dirTo + "/" +file)
		print(file + " moved to /" + dirTo)