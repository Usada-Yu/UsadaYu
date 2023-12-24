# 可执行文件file_Base64.exe使用说明

### 1. Update:

###### 	version: 1.0.0

​	Last Updated: 2023-12-25 (Merry Christmas)

​	Update Details: 初始化程序，添加基础功能



### 2. Author:

​	Name: 胡益华

​	Email: UsadaYu.yh@gmail.com



### 3. Usage:

​	Environment: Windows Linux

​	Usage: 

​	(1) Windows: cd bin && file_Base64.exe [encode|decode] input_file [output_file]

​	(2) Linux: ./pack.sh && cd bin && ./file_Base64 [encode|decode] input_file [output_file]



### 4. Description:

​	(1) ./file_Base64 encode input_file [output_file]

​		将文件input_file通过Base64编码为文本格式

​	(2) ./file_Base64 decode input_file [output_file]

​		将文本文件input_file通过Base64解码为原来的文件

​	(3) output_file是可选参数，可自行指定输出文件或不指定，若不指定程序会为你自动创建一个新的文件



### 5. Notice:

​	(1) 如果是编码(encode)，不指定output_file则会自动创建一个txt格式文件

​	(2) 如果是解码(decode)，不指定output_file则会自动创建一个txt格式文件，

​		但可能需要将解码后的文件后缀修改为原来正确的文件后缀，所以解码时尽量指定output_file参数