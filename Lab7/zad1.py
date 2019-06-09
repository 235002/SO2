#!/usr/bin/python
import sys
if len(sys.argv) !=2:
	print("Incorrect parameters")
	raise SystemExit()
	
for x in range(0, 10):
	file = open(sys.argv[1] + "/File" + str(x) + ".txt", "w")
	file.write("Conetnt of " + str(x) + " file.")
	
print("Created files in /" + str(sys.argv[1]))