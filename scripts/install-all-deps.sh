#!/bin/bash
usage()
{
cat << EOF
usage: sudo $0 <linux-variant>
This script installs all dependencies for opencv-workbench

EOF
}

#Require the script to be run as root
if [[ $(/usr/bin/id -u) -ne 0 ]]; then
    echo "This script must be run as root because libraries will be installed."
    usage
    exit
fi

# Grab username of caller for later
ORIGINAL_USER=$(who am i | awk '{print $1}')

if [ ! -d ../third-party-build ];
then
su $ORIGINAL_USER -m -c 'mkdir ../third-party-build'
fi

# Install dependencies through the package manager first:
./install-bin-deps.sh

# -----------------------------------------------------------------------------
# Build OGRE 3D
# -----------------------------------------------------------------------------
su $ORIGINAL_USER -m -c './build-ogre3d.sh'
./build-ogre3d.sh install
ldconfig
