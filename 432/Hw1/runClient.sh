#!/bin/bash


for nbufs in 15 30 60
do
   let "bufsize= 1500 / $nbufs"
   echo "Buffer Size: $bufsize"
    for Type in 1 2 3
    do 
        echo "Nbufs: $nbufs \n Bufsize: $bufsize \n Type: $Type \n"
        ./client 8654 20000 uw1-320-11.uwb.edu $nbufs $bufsize $Type    

    done
done