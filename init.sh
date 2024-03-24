#!/bin/bash

pre_dir=$(pwd)

# 错误处理 #
error_deal() {
    echo -e "\e[31mAn error occurred when the script was triggered manually, the script will exit...\e[0m"
    cd ${pre_dir}
    find ./ -type d \( -name "dist" -o -name "*.egg-info" \) -exec rm -rfv {} +
    exit 1
}
trap "error_deal" ERR
trap "error_deal" SIGINT
# 错误处理 #

# python自定义模块安装 #
cd ${pre_dir}/Python/common/self-fileModule
if [[ $(uname -s) == "Linux" ]]; then
    if command -v python3 &>/dev/null; then
        python3 ./setup.py sdist
        pip3 install --upgrade ./dist/fileModule*.tar.gz
    elif command -v python &>/dev/null; then
        python ./setup.py sdist
        pip install --upgrade ./dist/fileModule*.tar.gz
    else
        echo "There is no python in the environment"
        exit 1
    fi
else
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
fi

find ./ -type d \( -name "dist" -o -name "*.egg-info" \) -exec rm -rfv {} +
cd -
# python自定义模块安装 #
