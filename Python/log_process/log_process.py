'''
Author: huYiHua_UsadaYu

Creation Date: 2023-11-22

Updated Date: 2024-03-05

Usage: python3 log_porcess.py [retain/remove]

Description:
处理日志，输入希望保留或删除的行所带的关键字，匹配的行会被保留或删除
(1) 输入文件名；
(2) 输入需要保留的关键字，多个关键字之间以空格分隔，如elem1 elem2 elem4
(3) 不同模式举例，关键词为elem1 elem2 elem4：
    若输入retain则为保留模式：
    elem1 elem2 elem3 elem4 elem5这样的行会被保留；
    elem1 elem2这样的行不会被保留
    若输入remove则为删除模式：
    elem1 elem2 elem3 elem4 elem5这样的行会被删除；
    elem1 elem2这样的行不会被删除

Notice:
处理日志时请注意日志的编码格式，脚本默认以utf-8格式读取日志文件，并以utf-8格式写入文件
'''

import os
import sys

import fileModule

'''
若行开头有空格，则去掉空格(解决excel分列时首空格识别错误问题)
其次，函数在去掉行开头空格的同时保持列按照原日志格式对齐
'''
def leading_blank_transfer(input_str):
    if input_str.startswith(" "):
        blank_length = len(input_str) - len(input_str.lstrip())
        no_blank_leading = input_str.lstrip()

        first_str_length = 0
        for char in no_blank_leading:
            if char != " ":
                first_str_length += 1
            else:
                break

        add_blank = " " * blank_length
        new_str = no_blank_leading[:first_str_length] + add_blank + no_blank_leading[first_str_length:]

        return new_str
    else:
        return input_str

def file_process(input_file, keyword_list, processing_mode):
    output_file = fileModule.FMcreateUniqueFile(input_file)

    with open(input_file, "r", encoding="utf-8") as infile, open(output_file, "w") as outfile:
        lines           = infile.readlines()

        for line in lines:
            line = leading_blank_transfer(line)

            for i in range(0, len(keyword_list)):
                if keyword_list[i] in line:
                    if "retain" == processing_mode:
                        # 保证每一个关键字都被匹配到
                        if i == len(keyword_list) - 1:
                            outfile.write(line)
                            break
                        else:
                            continue
                    elif "remove" == processing_mode:
                        if i == len(keyword_list) - 1:
                            break
                        else:
                            continue
                else:
                    if "retain" == processing_mode:
                        break
                    elif "remove" == processing_mode:
                        outfile.write(line)
                        break

if __name__ == "__main__":
    if len(sys.argv) != 2 or (sys.argv[1] != "retain" and sys.argv[1] != "remove"):
        print("\nUsage: python log_porcess.py [retain/remove]\n")
        sys.exit(-1)

    pro_type = sys.argv[1]

    print("Input the file name: ", end = "")
    log_file = input()
    if not os.path.isfile(log_file):
        print(f"File {log_file} does not exist!")
        sys.exit(-1)

    while True:
        print("Input key generic strings, separated by spaces: ", end = "")
        key_string  = input()
        key_array   = [s for s in key_string.split()]

        if 0 == len(key_array):
            print("Please input key string!")
        else:
            break

    file_process(log_file, key_array, pro_type)

    print("Log processing complete")
    sys.exit(0)
