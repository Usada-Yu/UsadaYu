'''
Author: huYiHua_UsadaYu

Date: 2023-02-19

Usage: python3 heapResMerge.py [plat] [dir_path]

Description:
将内存报告文件按文件名中数字从小到大排列，并将内容逐一追加写入一个文件，方便后续处理
'''
import os
import re
import sys

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("\nUsage: python3 heapResMerge.py [plat] [dir_path]\n")
        sys.exit(-1)

    plat        = sys.argv[1]
    file_dir    = sys.argv[2]

    file_report = f"{file_dir}/{plat}_report.txt"
    if os.path.isfile(file_report):
        os.remove(file_report)

    # 使用正则表达式匹配文件名中的数字部分，并按照数字从小到大排序
    file_list           = os.listdir(file_dir)
    sorted_file_names   = sorted(file_list, key=lambda x: int(re.findall(r'\d+', x)[0]))

    with open(file_report, "a") as output_file:
        for file in sorted_file_names:
            # 拼接文件的完整路径
            file_path = os.path.join(file_dir, file)
            print(file_path)

            # 读取文件内容，并追加写入{plat}_report.txt
            with open(file_path, "r") as input_file:
                content = input_file.read()
            output_file.write(content)
