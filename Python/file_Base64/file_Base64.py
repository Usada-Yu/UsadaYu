'''
Author: Hu_Yihua_UsadaYu

Creation Date: 2023-12-25

Updated Date: 2023-12-25

Usage: python file_Base64.py [encode|decode] input_file [output_file]

Description:
(1) python file_Base64.py encode input_file [output_file]
将文件input_file通过Base64编码为文本格式
(2) python file_Base64.py decode input_file [output_file]
将文本文件input_file通过Base64解码为原来的文件
(3) output_file是可选参数，可自行指定输出文件或不指定，若不指定程序会为你自动创建一个新的文件

Notice:
(1) 如果是编码(encode)，不指定output_file则会自动创建一个txt格式文件
​(2) 如果是解码(decode)，不指定output_file则会自动创建一个txt格式文件，
    但可能需要将解码后的文件后缀修改为原来正确的文件后缀，所以解码时尽量指定output_file参数
(3) 此脚本不能对目录进行编解码，如有需要，请先对目录进行压缩
'''

import os
import sys
import base64

import fileModule

'''分割文件名和后缀
无论文件是否有后缀，后缀是什么，都将新后缀更改为.txt
如果origin_file_name是txt格式，提醒用户解码情况下可能需要自行更改正确的后缀
'''
def file_and_extension(origin_file_name):
    origin_file_base, origin_file_extension = os.path.splitext(origin_file_name)
    if origin_file_extension == ".txt":
        print(f"Note that '{origin_file_name}' is a file in txt format")
        print(f"If it's decoding, you may need to manually change the file extension")
    
    file_name = origin_file_base + ".txt"
    return fileModule.FMcreateUniqueFile(file_name)

def encode(input_file, output_file):
    with open(input_file, "rb") as f:
        content = f.read()
        encoded_content = base64.b64encode(content).decode("utf-8")

    with open(output_file, "w") as f:
        f.write(encoded_content)

def decode(input_file, output_file):
    with open(input_file, "r") as f:
        encoded_content = f.read()
        decoded_content = base64.b64decode(encoded_content)

    with open(output_file, "wb") as f:
        f.write(decoded_content)

if __name__ == "__main__":
    if len(sys.argv) not in [3, 4]:
        print("Usage: python file_Base64.py [encode|decode] input_file [output_file]")
        sys.exit(1)

    action      = sys.argv[1]
    input_file  = sys.argv[2]
    if not os.path.exists(input_file):
        print(f"No such file: '{input_file}'")
        sys.exit(1)
    
    '''
    输入参数为4且output_file不存在: 将sys.argv[3]正常复制给output_file
    输入参数为4但output_file已存在: 在output_file后添加数字后缀用于区分
    输入参数为3: 创建一个唯一的.txt格式的output_file
    '''
    if len(sys.argv) == 4:
        output_file = sys.argv[3]
    if len(sys.argv) == 4 and os.path.exists(output_file):
        output_file = fileModule.FMcreateUniqueFile(output_file)
    if len(sys.argv) == 3:
        output_file = file_and_extension(input_file)

    if not output_file:
        sys.exit(1)

    if action not in ["encode", "decode"]:
        print("Invalid action. Please use 'encode' or 'decode'")
        sys.exit(1)

    if action == "encode":
        encode(input_file, output_file)
        print(f"'{input_file}' encoded and saved as '{output_file}'")
    elif action == "decode":
        decode(input_file, output_file)
        print(f"'{input_file}' decoded and saved as '{output_file}'")
    
    sys.exit(0)
