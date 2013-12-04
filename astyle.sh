#!/bin/bash

if [ -z "$1" ]; then
    echo "usage: astyle.sh dir";
    exit 0;
fi

for i in $(find $1 -name '*.*pp'); do 
    astyle --style=allman -C -S -N -K -Y $i $i;
done
