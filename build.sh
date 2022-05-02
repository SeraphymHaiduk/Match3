#!/bin/bash
mainDir="$PWD"
echo "mainDir = $PWD"
pluginsPath="Plugins/ModelPlugin"
cd $pluginsPath
cmake -B build/
cd build 
make
cd $mainDir
cmake -B build/
mkdir -p build/$pluginsPath
cp $pluginsPath/build/qmldir  build/$pluginsPath/qmldir
cp $pluginsPath/build/libModelPlugin.so build/$pluginsPath/libModelPlugin.so
cd build
make 
cd ..
./build/Match3

