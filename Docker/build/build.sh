#! /bin/bash
set -o errexit
set -o verbose

main() {
	mkdir -p cmbuild
	pushd cmbuild
	cmake .. -B .
	make -j "$(nproc)"
	popd || exit 1
}

main
