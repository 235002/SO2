#!/bin/bash

echo "A"
ps aux | awk '{user="Uzytkownik = "$1" - proces "$11" (CPU = "$3", MEM = "$4")"; print user;}'

echo "B"
ps aux | awk '{proc=split($11,array,"/");b="Uzytkownik = "$1" - proces "array[proc]" (CPU = "$3", MEM = "$4")"; print b;}'

echo "C"
ps aux | awk 'BEGIN {cup=0;mem=0;} {cpu+=$3;mem+=$4} END {print "Suma CPU = "cpu" Suma MEMORY = "mem}'

echo "D"
ps aux | awk 'BEGIN{cpu[$1]=0;mem[$1]=0;} {if(NR>1){cpu[$1]+=$3;mem[$1]+=$4;}}END {for(user in cpu){print "Uzytkownik = "user" CPU = "cpu[user]" MEM = "mem[user]}}'

echo "E"
ps aux | awk \
'{
    if(NR>1){
        cpu[$1]+=$3;
        mem[$1]+=$4;
    }   
} END {
    for(user in cpu) {
        if(max_cpu<cpu[user]){
            max_cpu=cpu[user];
            user_max_cpu=user;
        }
        if(max_mem<mem[user]){
            max_mem=mem[user];
            user_max_mem=user;
        }
    }
    print "Uzytkownik = "user_max_cpu" - maxCPU"max_cpu;
    print "Uzytkownik = "user_max_mem" - maxMEM"max_mem;
}'
