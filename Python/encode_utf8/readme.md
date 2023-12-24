# 可执行文件encode_utf8使用说明

### 1. Update:

​	Creation Date: 2024-01-01

###### 	version: 1.0.0

​	Updated Date: 2024-01-01

​	Update Details: 可执行文件可对指定目录中的文件进行编码格式的统一



### 2. Author:

​	Name: 胡益华

​	Email: UsadaYu.yh@gmail.com



### 3. Usage:

​	Environment: Windows Linux

​	Usage Command: 

​	(1) Windows: 

​		cd bin && encode_utf8.exe directory_path [file_extensions]

​		cd bin && encode_utf8.exe [file_path]

​	(2) Linux: 

​		cd bin && ./file_Base64 directory_path [file_extensions]

​		cd bin && ./file_Base64 [file_path]



### 4. Description:

​	(1) 运行此程序时指定directory_path目录或file_path文件

​	(2) 若输入的是directory_path目录：

​		程序会将输入目录下所有非utf-8格式的且后缀为file_extensions文件全部修改为utf-8编码格式；

​		不输入file_extensions参数则对file_path目录下所有的文件生效

​	(3) 若输入的是file_path文件：

​		程序会将所有指定文件全部修改为utf-8编码格式

​	(4) 使用样例：

​		./encode_utf8 directory_path

​		./encode_utf8 directory_path .h .cpp

​		./encode_utf8 directory_path .py .c .cpp

​		./encode_utf8 file_path1 file_path2



### 5. Notice:

​	(1) 不要将文件和目录混合输入

​	(2) 程序基于chardet判断文件编码格式；

​		chardet判断编码格式以置信度给出，所以判断结果并非100%准确

​	(3) 不要保持对此程序的信任，如果没有git等管理工具，执行程序前请备份文件

