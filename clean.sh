#!/bin/bash

rm -rf ./build
rm -rf ./lib
rm -rf ./bin
rm -rf ./include

pushd ./src/game-of-life >& /dev/null
./clean.sh
popd >& /dev/null

