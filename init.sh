#!/bin/bash

# ######################################## #
# 仓库初始化脚本，运行前确保此脚本有可执行权限 #
# ######################################## #

set -e

pre_dir=$(pwd)
# GoogleTest临时目录
googletest_tmp="tmp-googletest"

# 错误处理 #
error_deal() {
    echo -e "\033[0;31mAn error occurred when the script was triggered manually, the script will exit...\033[0m"
    cd ${pre_dir}
    # 删除可能存在和python相关的临时目录
    find ./ -type d \( -name "dist" -o -name "*.egg-info" \) -exec rm -rfv {} +
    # 删除可能存在和GoogleTest相关的临时目录
    find ./ -type d -name ${googletest_tmp} -exec rm -rfv {} +
    exit 1
}
trap "error_deal" ERR
trap "error_deal" SIGINT
# 错误处理 #

echo -e "\033[0;32m====================================================================\033[0m"
# python自定义模块安装 #
# 模块默认安装在python路径的site-packages下；
# 无安装权限可在pip后添加--user选项或以sudo方式执行脚本
cd ${pre_dir}/Python/common/self-fileModule
if [[ $(uname -s) == "Linux" ]]; then
    if command -v python3 &>/dev/null; then
        python3 ./setup.py sdist
        pip3 install --upgrade ./dist/fileModule*.tar.gz
    elif command -v python &>/dev/null; then
        python ./setup.py sdist
        pip install --upgrade ./dist/fileModule*.tar.gz
    else
        echo -e "\033[0;31mThere is no python in the environment\033[0m"
    fi
else
    if [[ "" != $(python3 --version) ]]; then
        python3 ./setup.py sdist
        pip3 install --upgrade ./dist/fileModule*.tar.gz
    elif [[ "" != "$(python --version)" ]]; then
        python ./setup.py sdist
        pip install --upgrade ./dist/fileModule*.tar.gz
    else
        echo -e "\033[0;31mThere is no python in the environment\033[0m"
    fi
fi
find ./ -type d \( -name "dist" -o -name "*.egg-info" \) -exec rm -rfv {} +
cd -

echo -e "\033[32m====================================================================\033[0m"
# 引用GoogleTest头文件
cd ${pre_dir}/ToolKnowledge/GoogleTest
mkdir -p include
{
    git clone https://github.com/Usada-Yu/External.git -b 1-external-googletest ${googletest_tmp}
} || true
if [ -d ${googletest_tmp} ]; then
    rm ./include/gtest -rfv
    mv ${googletest_tmp}/include/gtest ./include -v
    rm ${googletest_tmp} -rfv
else
    echo -e "\033[0;31mThe installation of external headers for GoogleTest failed\033[0m"
fi
cd -
