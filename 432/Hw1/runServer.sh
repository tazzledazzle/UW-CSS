#!/bin/bash


for nbufs in 15 30 60
do
    bufsize='expr 1500 / $nbufs'
    for Type in 1 2 3
    do 
        echo "Nbufs: $nbufs \n Bufsize: $bufsize \n Type: $Type \n"
        ./server 8654 20000 
        
    done
done