#! /bin/bash

export BUILD_PATH=/tmp/src
mkdir -p $BUILD_PATH
find . -name "dep-*.sh" -type f -exec {} \;
