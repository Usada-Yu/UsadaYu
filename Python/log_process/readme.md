# 可执行文件log_porcess使用说明

### 1. Update:

​	Creation Date: 2023-11-22

###### 	version: 1.0.0

​	Updated Date: 2023-11-22

​	Update Details: 可执行文件可根据关键字对日志文件做匹配保留

###### version: 1.0.1

​	Updated Date: 2024-03-05

​	Update Details: 添加对关键字匹配做去除处理



### 2. Author:

​	Name: 胡益华

​	Email: UsadaYu.yh@gmail.com



### 3. Usage:

​	Environment: Windows Linux

​	Usage Command: 

​	(1) Windows: cd bin && log_porcess.exe [retain/remove]

​	(2) Linux: cd bin && ./log_porcess [retain/remove]



### 4. Description:

​	处理日志，输入希望保留或删除的行所带的关键字，匹配的行会被保留或删除

​	(1) 输入文件名；

​	(2) 输入需要保留的关键字，多个关键字之间以空格分隔，如elem1 elem2 elem4

​	(3) 不同模式举例，关键词为elem1 elem2 elem4：

​		若输入retain则为保留模式：

​		elem1 elem2 elem3 elem4 elem5这样的行会被保留；

​		elem1 elem2这样的行不会被保留

​		若输入remove则为删除模式：

​		elem1 elem2 elem3 elem4 elem5这样的行会被删除；

​		elem1 elem2这样的行不会被删除



### 5. Notice:

​	处理日志时请注意日志的编码格式，脚本默认以utf-8格式读取日志文件，并以utf-8格式写入文件