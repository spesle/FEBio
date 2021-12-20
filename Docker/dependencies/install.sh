#! /bin/bash
set -o errexit
set -o verbose

export BUILD_PATH=/tmp/src
mkdir -p $BUILD_PATH

find . -name "dep-*.sh" -type f -exec {} \;
