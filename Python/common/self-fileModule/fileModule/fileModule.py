'''
Author: Hu_Yihua_UsadaYu

Creation Date: 2024-02-23

Updated Date: 2024-02-23

Description: 基于python的文件处理函数
'''

import os
import inspect

# INTERNAL
'''
 @brief         确定输入文件名已经存在时，获取一个独一无二的文件名
 @param         file_name: 文件名称或文件路径
 @return        获取文件名成功返回文件名
                获取文件名失败返回False
'''  
def _fm_create_unique_file(file_path):
    count = 1
    new_file_base, new_file_extension = os.path.splitext(file_path)
    new_file_path = f"{new_file_base}_{count}{new_file_extension}"

    while os.path.exists(new_file_path):
        count += 1
        if count == 100000:
            print("There are too many conflicting files")
            return False
        new_file_path = f"{new_file_base}_{count}{new_file_extension}"

    return new_file_path

# EXTERNAL
'''
 @brief         获取文件的绝对路径
 @description   若输入参数已经是文件的绝对路径，那么直接返回
 @notice        此处输入的相对路径时相对于调用者的，而不是fileModule模块
 @param         relative_path: 相对路径
 @return        文件的绝对路径字符串
'''
def FMgetAbsolutePath(file_path):
    # 获取调用者的相对路径
    caller_frame    = inspect.currentframe().f_back
    caller_path     = inspect.getframeinfo(caller_frame).filename
    caller_dir      = os.path.dirname(caller_path)
    return os.path.abspath(os.path.join(caller_dir, file_path))

'''
 @brief         输入文件名或文件路径，创建一个独一无二的文件
 @description   文件命名方式为<file_num.suffix>
                如，传入文件名为file.txt，若此file.txt已存在，则创建名为file_1.txt的文件；
                若file_1.txt也已存在，则创建名为file_2.txt的文件；以此类推。
                此函数创建的文件索引至多到99999
 @notice        此函数调用后新文件会被自动创建
 @param         file_name: 文件名称或文件路径
 @return        创建文件成功返回文件名
                创建文件失败返回False
'''
def FMcreateUniqueFile(file_path):
    if not os.path.exists(file_path):
        with open(file_path, "w") as _:
            print(f"File '{file_path}' is created")
            return file_path
    else:
        new_file_path = _fm_create_unique_file(file_path)
        if not new_file_path:
            return False

        with open(new_file_path, "w") as _:
            print(f"File '{new_file_path}' is created")
            return new_file_path

'''
 @brief         输入文件名或文件路径，获取一个独一无二的文件名
 @description   文件命名方式为<file_num.suffix>
                如，传入文件名为file.txt，若此file.txt已存在，则获取名为file_1.txt的文件；
                若file_1.txt也已存在，则获取名为file_2.txt的文件；以此类推。
                此函数获取的文件名索引至多到99999
 @notice        此函数调用后新文件不被自动创建
 @param         file_name: 文件名称或文件路径
 @return        获取文件名成功返回文件名
                获取文件名失败返回False
'''
def FMcreateUniqueFileName(file_path):
    if not os.path.exists(file_path):
        return file_path
    else:
        new_file_path = _fm_create_unique_file(file_path)
        if not new_file_path:
            return False

        return new_file_path
