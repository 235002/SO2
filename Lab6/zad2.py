#!/usr/bin/python3

import sys

if len(sys.argv) != 4:
	print("Zla ilosc paramaterow")
	raise SystemExit()

fileFrom = sys.argv[1]
dirTo = sys.argv[2]
counter = int(sys.argv[3])

file = open(fileFrom, 'r')
data = file.read()
file.close()

for x in range(0, counter)
	file = open(dirTo + "/File" + str(x) + ".txt". "w")
	file.write(data)
	file.close()
	
print("Skopiowano " + str(counter) + " razy")
