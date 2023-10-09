#!/bin/bash

#./run.sh compile_flash prj01_cli_parser

if [ $1 == 'compile_flash' ]
then
mkdir -p build
cd build
cmake -DPROJECT_CORE_FILES=$2 -DDO_FLASH=YES ..
make -j11

cd ..

elif [ $1 == 'compile_only' ]
then
mkdir -p build
cd build
cmake -DPROJECT_CORE_FILES=$2 -DDO_FLASH=NO ..
make -j11

cd ..


elif [ $1 == 'clean' ]
then
mkdir -p build
cd build
rm -r *
echo 'cleaned successfully'
cd ..

elif [ $1 == 'DO_picocom' ]
then

   sudo picocom -b 115200 /dev/ttyACM0

cd ..
fi
