#!/bin/bash
: "  脚本通过pyinstaller对file_Base64.py文件打包；并通过upx压缩可执行文件
打包完成后脚本会自动删除产生的.spec文件，build目录，如需保留可修改此脚本
"

# 出错后退出
set -e

binary_file=file_Base64
source_file=file_Base64.py

rm -f ${binary_file}

pyinstaller -F --name="${binary_file}" --distpath="./" \
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
