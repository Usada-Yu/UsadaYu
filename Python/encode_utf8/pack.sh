#!/bin/bash
: "  脚本通过pyinstaller对encode_utf8.py文件打包；并通过upx压缩可执行文件
打包完成后脚本会自动删除产生的.spec文件，build目录，如需保留可修改此脚本
"

# 出错后退出
set -e

binary_file=encode_utf8
source_file=encode_utf8.py

rm -rf ${binary_file}

# : " 打包过程中，typing-3.7.4.3.dist-info库会和pyinstaller出现不兼容情况；
# 重命名typing-3.7.4.3.dist-info库解决此问题
# "
# if [ ! -r /home/usadayu/.local/lib/python3.7/site-packages/typing-3.7.4.3.dist-info_temp_flag ]; then
#     mv /home/usadayu/.local/lib/python3.7/site-packages/typing-3.7.4.3.dist-info \
#     /home/usadayu/.local/lib/python3.7/site-packages/typing-3.7.4.3.dist-info_temp_flag
# fi

pyinstaller -F --name="${binary_file}" --distpath="./" \
${source_file}

# # 将typing-3.7.4.3.dist-info命名修改回来
# mv /home/usadayu/.local/lib/python3.7/site-packages/typing-3.7.4.3.dist-info_temp_flag \
# /home/usadayu/.local/lib/python3.7/site-packages/typing-3.7.4.3.dist-info

# 删除pyinstaller打包后产生的文件
rm -rf build ${binary_file}.spec

# 通过upx压缩可执行文件
set +e                              # 出错继续执行，保证不同环境下的压缩
upx -9 ${binary_file} --force       # Linux
upx -9 ${binary_file}.exe --force   # Windows
set -e

mkdir -p bin
mv -f ${binary_file} bin
