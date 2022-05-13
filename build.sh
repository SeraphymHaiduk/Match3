#!/bin/bash
mainDir="$PWD"
echo "mainDir = $PWD"
pluginsPath="Plugins/ModelPlugin"
scriptDir=$(dirname $0)
cd $scriptDir
cd $pluginsPath
cmake -B build/
cd build 
make
cd $mainDir
cmake -B build/ -S $scriptDir/
mkdir -p build/$pluginsPath
cp $scriptDir/$pluginsPath/build/qmldir  build/$pluginsPath/qmldir
cp $scriptDir/$pluginsPath/build/libModelPlugin.so build/$pluginsPath/libModelPlugin.so
cd build
make 
cd ..
./build/Match3

