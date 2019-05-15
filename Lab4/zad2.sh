#!/bin/bash

#A)
#ps aux | awk '{n=split($11,array,"/"); print "User: "$1" proc: "array[n]" CPU="$3" MEM="$3;}'

#B)
#ps aux | awk '{n=split($11,array,"/"); print $11" ---> "array[n];}'

#C)
#ps aux | awk '{cpu+=$3;mem+=$4;} END {print "CPU = "cpu" MEM = "mem;}'

#D)
ps aux | awk \
'
{
	tabcpu[$1]+=3;
	tabmem[$1]+=$4;
} 
END \
{
maxcpu=0;
maxmem=0;
for(key in tabmem)
{
	print key" - (CPU = "tabcpu[key]" MEM = "tabmem[key]")"
	if(tabmem[key]>maxmem)
	{
		maxmem=tabmem[key];
		maxmemkey=key;
	}
	if(tabcpu[key]>maxcpu)
	{
		maxcpu=tabcpu[key];
		maxcpukey=key;
	}
} 
print maxmemkey" - "maxmem;
print maxcpuekey" - "maxcpu
}
'


