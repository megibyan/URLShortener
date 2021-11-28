#!/bin/bash

# author: Mikayel Egibyan <megibyan@gmail.com>

cd ../../Build
cmake ../ && make -j12
make Test -j12
./Test

exit
