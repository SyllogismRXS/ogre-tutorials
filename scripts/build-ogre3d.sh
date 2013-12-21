#!/bin/bash

##############################################
# Build OpenCV
##############################################

if [ ! -d ../third-party-build ];
then
    mkdir ../third-party-build
fi

if [ ! -d ../third-party-build/ogre ]; then
    echo "Downloading ogre 1.8 repo..."
    
    pushd ../third-party-build >& /dev/null
    hg clone http://bitbucket.org/sinbad/ogre/ -u v1-8
    popd >& /dev/null
fi

pushd ../third-party-build/ogre >& /dev/null

if [ ! -d build ];
then
    mkdir build
fi

pushd build

cmake ..
make $@

popd >& /dev/null # build

popd >& /dev/null # ogre

