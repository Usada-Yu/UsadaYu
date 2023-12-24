#!/bin/bash

set +e

pre_dir=$(pwd)
user_os_dir=${pre_dir}/../user_os
lib_dir=${pre_dir}/lib
inc_dir=${pre_dir}/include/external

function build_and_copy() {
    local plat="$1"

    cmake -H. -Bbuild -Dplat="${plat}"
    if [ -d artifact/"${plat}" ]; then
        make -B -C build
        mkdir -p "${lib_dir}/${plat}"
        cp artifact/"${plat}"/lib/* "${lib_dir}/${plat}"
    fi
}

mkdir -p ${lib_dir}
mkdir -p ${inc_dir}
rm -rf ${lib_dir}/* ${inc_dir}/*

cd ${user_os_dir}
rm -rf build artifact
cp ./include/* ${inc_dir}

if [[ $(uname -s) == "Linux" ]]; then
    build_and_copy "x86"
    build_and_copy "hi3519dv500"
    build_and_copy "sd3403v100"
else
    cmake -H. -Bbuild -Dplat=win -G "MinGW Makefiles"
    if [ -d artifact/win ]; then
        mingw32-make -B -C build
        mkdir -p "${lib_dir}/win"
        cp artifact/"win"/lib/* "${lib_dir}/win"
    fi
fi

rm -rf build artifact

cd -
