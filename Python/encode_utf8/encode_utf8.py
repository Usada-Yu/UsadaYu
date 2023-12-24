'''
Author: Hu_Yihua_UsadaYu

Creation Date: 2024-01-01

Updated Date: 2024-01-01

Usage:
python encode_utf8.py directory_path [file_extensions]
python encode_utf8.py [file_path]

Description:
(1) 运行此脚本时指定directory_path目录或file_path文件
(2) 若输入的是directory_path目录：
    脚本会将输入目录下所有非utf-8格式的且后缀为file_extensions文件全部修改为utf-8编码格式；
    不输入file_extensions参数则对file_path目录下所有的文件生效
(3) 若输入的是file_path文件：
    脚本会将所有指定文件全部修改为utf-8编码格式
(4) 使用样例：
    python encode_utf8.py directory_path
    python encode_utf8.py directory_path .h .cpp
    python encode_utf8.py directory_path .py .c .cpp
    python encode_utf8.py file_path1 file_path2

Notice: 
(1) 不要将文件和目录混合输入
(2) 脚本基于chardet判断文件编码格式；
    chardet判断编码格式以置信度给出，所以判断结果并非100%准确
(3) 不要保持对此脚本的信任，如果没有git等管理工具，使用脚本前请备份文件
'''

import os
import sys
import chardet

def convert_to_utf8(file_path):
    with open(file_path, "rb") as file:
        content = file.read()
        result = chardet.detect(content)
        encoding = result["encoding"]

    if encoding and encoding.lower() not in ["utf-8", "ascii"]:
        with open(file_path, "r", encoding=encoding, errors="replace") as file:
            content = file.read()

        with open(file_path, "w", encoding="utf-8") as file:
            file.write(content)
        print(f"Converted {file_path} to UTF-8.")

def process_files(directory, extensions=None):
    for root, dirs, files in os.walk(directory):
        for file in files:
            if not extensions or file.endswith(tuple(extensions)):
                file_path = os.path.join(root, file)
                convert_to_utf8(file_path)

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("\nUsage: python encode_utf8.py file_path [file_extensions]\n")
        sys.exit(1)

    file_path = sys.argv[1]
    file_extensions = sys.argv[2:] if len(sys.argv) > 2 else None

    if os.path.isdir(file_path):
        process_files(file_path, file_extensions)
    elif os.path.isfile(file_path):
        for file in sys.argv[1:]:
            convert_to_utf8(file)
    else:
        print("\nThe file or directory is incorrectly entered\n")
        sys.exit(1)
    
    sys.exit(0)
