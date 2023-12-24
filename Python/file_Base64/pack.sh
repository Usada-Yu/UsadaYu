#!/bin/bash

set -e

binary_file=file_Base64
source_file=file_Base64.py

rm -f ${binary_file}

pyinstaller -F --name="${binary_file}" --distpath="./" \
${source_file}

# 删除打包后产生的文件
rm -rf build ${binary_file}.spec

mkdir -p bin
mv ${binary_file} bin