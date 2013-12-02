#!/bin/bash

# Usage:
# $ ./build.sh ./hello-world

mkdir ./build -p
pushd build >& /dev/null

cmake ..

make

# Save the make command's result for later
BUILD_SUCCESS=$?

popd >& /dev/null

# If arguments are supplied to the build script, then this could mean
# that the user either wants to install the project or execute a program
if [ $# -gt 0 ]; then
    # The user wants to install the project
    if [ $1 == "install" ]; then
        make install
    else
        # The user wants to execute a script in the bin directory
        # Move the bin directory and pass the command to call
        # Example call: ./build.sh ./hello-world
        pushd ./bin >& /dev/null

        # Check the status of the make command
        if [ ${BUILD_SUCCESS} -ne 0 ]; then
            # The make command failed, remove the binary of the command
            # the user is trying to run
            rm $1
        else
            # Build was successful, execute the binary
            $1
        fi
        popd >& /dev/null
    fi
fi
