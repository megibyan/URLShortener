#!/bin/bash

# author: Mikayel Egibyan <megibyan@gmail.com>

if [ ! -d "../../Build" ]
then
	mkdir ../../Build
fi

cd ../../Build
cmake ../ && make -j12

exit
