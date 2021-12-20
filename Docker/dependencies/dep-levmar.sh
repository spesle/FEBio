#! /bin/bash
set -o errexit
set -o verbose

. ./common-functions.sh

LEVMAR_SOURCE=http://users.ics.forth.gr/~lourakis/levmar/levmar-2.6.tgz
LEVMAR_ARCHIVE=$(basename $LEVMAR_SOURCE)
LEVMAR_PATH="${LEVMAR_ARCHIVE%.*}"

build_and_install() {
	local source=$1
	local patchfile=$2
	local build_dir=cmake-build
	pushd "$source" || exit 1
	dos2unix CMakeLists.txt CMakeLists.txt
	patch --ignore-whitespace -p0 < $patchfile
	mkdir -p $build_dir
	pushd $build_dir || exit 1
	cmake -DBUILD_DEMO:BOOLEAN=false .. -B .
	make -j "$(nproc)"
	make install
	popd || exit 1
	popd || exit 1
}

main() {
	local patchfile="$(pwd)/levmar-install.patch"
	pwd
	pushd "$BUILD_PATH" || exit 1
	download_source "$LEVMAR_SOURCE"
	tar xzf "$LEVMAR_ARCHIVE"
	build_and_install "$LEVMAR_PATH" "$patchfile"
	popd || exit 1
}

main
