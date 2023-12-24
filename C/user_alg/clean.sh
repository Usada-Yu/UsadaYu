#!/bin/bash

pre_dir=$(pwd)

rm -rfv                                                                 \
    ${pre_dir}/build ${pre_dir}/artifact                                \
    ${pre_dir}/include/external ${pre_dir}/lib
