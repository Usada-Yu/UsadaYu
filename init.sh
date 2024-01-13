#!/bin/bash

pre_dir=$(pwd)

set +e
cd ${pre_dir}/Python/common/self-fileModule
if [[ "" != $(python3 --version) ]]; then
    python3 ./setup.py sdist
    pip3 install --upgrade ./dist/fileModule*.tar.gz
elif [[ "" != "$(python --version)" ]]; then
    python ./setup.py sdist
    pip install --upgrade ./dist/fileModule*.tar.gz
else
    echo "There is no python in the environment"
    exit 1
fi
set -e

find ./ -type d \( -name "dist" -o -name "*.egg-info" \) \
-exec rm -rfv {} +

cd -
