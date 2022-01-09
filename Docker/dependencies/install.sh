#! /bin/bash
set -o errexit
set -o verbose

export BUILD_PATH=/tmp/src
mkdir -p $BUILD_PATH

installers=(dep-hypre dep-levmar dep-mmg)
for installer in ${installers[@]}; do
	./${installer}.sh
done
