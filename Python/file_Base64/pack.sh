#!/bin/bash

set -e

binary_file="file_Base64"
source_file="file_Base64.py"

rm -f ${binary_file}

pyinstaller -F --clean --name="${binary_file}" --distpath="./" \
${source_file}

# 删除pyinstaller打包后产生的文件
rm -rf build ${binary_file}.spec

# 通过upx压缩可执行文件
set +e                              # 出错继续执行，保证不同环境下的压缩
upx -9 ${binary_file} --force       # Linux
upx -9 ${binary_file}.exe --force   # Windows
set -e

mkdir -p bin
mv ${binary_file} bin
