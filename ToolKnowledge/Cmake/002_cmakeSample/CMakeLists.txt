######################## @Title 当前目录的Cmake脚本样例 ########################
#[[ windows，MINGW64下，执行命令：
    mkdir -p build && cd build
    cmake -G "MinGW Makefiles" ..
    mingw32-make -B -j
	]]
##############################################################################

############################# Cmake自带的常用变量 #############################
#[[
	PROJECT_SOURCE_DIR			工程的根目录，即调用project()的CMakeLists.txt所在的绝对路径
	PROJECT_BINARY_DIR			运行cmake命令的目录，通常为${PROJECT_SOURCE_DIR}/build
	PROJECT_NAME				通过project()命令定义的项目名称

	CMAKE_SOURCE_DIR			顶层CMakeLists.txt所在的绝对路径
	CMAKE_BINARY_DIR			顶层构建目录的绝对路径

	CMAKE_CURRENT_SOURCE_DIR	当前CMakeLists.txt所在的绝对路径
	CMAKE_CURRENT_BINARY_DIR	当前脚本构建目录的绝对路径
	CMAKE_CURRENT_LIST_DIR		当前正在处理的CMakeLists.txt的绝对路径

	CMAKE_MODULE_PATH				用于指定额外的cmake模块(.cmake文件)的搜索路径的列表
	CMAKE_RUNTIME_OUTPUT_DIRECTORY	可执行文件的输出目录，不指定默认在PROJECT_BINARY_DIR下
	CMAKE_LIBRARY_OUTPUT_DIRECTORY	库文件的输出目录，不指定默认在PROJECT_BINARY_DIR下
	EXECUTABLE_OUTPUT_PATH			可执行文件的输出目录，不指定默认在PROJECT_BINARY_DIR下
	LIBRARY_OUTPUT_PATH				库文件的输出目录，不指定默认在PROJECT_BINARY_DIR下
	]]

#[[
	1. 无论顶层CMakeLists.txt路径是怎样的，都有：
	(1) PROJECT_SOURCE_DIR和CMAKE_SOURCE_DIR始终是一致的；
	(2) PROJECT_BINARY_DIR和CMAKE_BINARY_DIR始终是一致的。

	2. CMAKE_RUNTIME_OUTPUT_DIRECTORY和EXECUTABLE_OUTPUT_PATH作用是一样的，
	EXECUTABLE_OUTPUT_PATH多在旧版cmake中使用，新版建议使用CMAKE_RUNTIME_OUTPUT_DIRECTORY。
	若CMAKE_RUNTIME_OUTPUT_DIRECTORY和EXECUTABLE_OUTPUT_PATH都被指定，
	那么CMAKE_RUNTIME_OUTPUT_DIRECTORY优先级大于EXECUTABLE_OUTPUT_PATH

	3. 关于库文件输出目录变量CMAKE_LIBRARY_OUTPUT_DIRECTORY和LIBRARY_OUTPUT_PATH，
	具体参考../003_Library
	]]
##############################################################################

#[[ 
	@brief
	指定当前CMakeList.txt脚本使用的cmake最低版本为3.5

	@description
	新版本的cmake可能有一些新的命令，旧版本不支持，
	所以需要指定执行当前CMakeList.txt脚本的最低版本cmake

	@notice
	此命令不是必须的，但是建议写上
	]]
cmake_minimum_required(VERSION 3.5)

#[[
	@brief
	设置c++标准为c++11，即-std=c++11；同理有set(CMAKE_CXX_STANDARD 14)等

	@description
	在执行cmake命令时也可以指定c++标准，但是建议在cmake脚本中配置CMAKE_CXX_STANDARD。
	如果希望执行cmake命令时指定c++标准，命令为：cmake .. -DCMAKE_CXX_STANDARD=11
	-D表示指定变量，此时，CMAKE_CXX_STANDARD会被写入Makefile中。
	当CMakeList.txt中指定了CMAKE_CXX_STANDARD，执行cmake命令时指定的CMAKE_CXX_STANDARD将不起作用

	@notice
	若不指定c++标准，默认使用c++98标准(也有说默认使用c++11标准)。
	我在windows下使用mingw32-make 4.4.1版本，发现默认使用的是c++98标准；
	当然其它环境可能情况不同，所以最好将CMAKE_CXX_STANDARD变量显示地配置。
	]]
set(CMAKE_CXX_STANDARD 11)

#[[
	@brief
	配置工程信息

	@notice
	一般整个工程可以有多个CMakeLists.txt，但只能顶层CMakeLists.txt能调用project
	]]
project(
	PROJECT-CMAKE-SAMPLE		# 构建项目时指定的工程名称。可选参数，但建议写上
	VERSION "1.0.0"				# 项目的版本号。可选参数
	DESCRIPTION "cmake sample"	# 项目的描述信息。可选参数
	LANGUAGES "C" "CXX"			# 项目的编写语言，主流语言如C、CXX、OBJC等cmake一般都支持。可选参数

	# 工程主页的URL。可选参数
	HOMEPAGE_URL "https://github.com/Usada-Yu/UsadaYu/tree/master/ToolKnowledge/Cmake"
)
message(${PROJECT_NAME})		# 打印信息：PROJECT-CMAKE_SAMPLE

#[[
	@brief
	设置变量，多个变量之间以空格或符号;分隔。变量默认是string类型

	@usage
	set(<VARIABLE> <variable_contents>)
	将variable_contents用VARIABLE变量代替

	@notice
	使用变量时以${}的方式引用；类似shell的引用，区别于Makefile的$()
	]]
set(__SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(__BINARY_DIR ${PROJECT_SOURCE_DIR}/bin)
set(__TARGET cmakeDemoSample)

#[[
	@brief
	设置可执行文件的输出目录。

	@notice
	如果目录不存在，cmake会自动创建这个目录。即构建Makefile时就创建这个bin目录。
	若目录层级是多层的，那么将会递归地创建目录，即相当于：mkdir -p dir_path
	]]
# 创建可执行文件的输出目录；因为指定CMAKE_RUNTIME_OUTPUT_DIRECTORY后会自动创建，所以可不写
# file(MAKE_DIRECTORY ${__BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${__BINARY_DIR})
message(${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

#[[
	@brief
	指定头文件路径
	]]
include_directories(${PROJECT_SOURCE_DIR}/include)

#[[
	@brief
	添加源文件到变量方式1，使用file命令

	@usage
	file(GLOB/GLOB_RECURSE <VARIABLE> <dir_path/*.file_format>)
	GLOB表示搜索符合dir_path/*.file_format的文件；
	GLOB_RECURSE表示递归地搜索符合dir_path/*.file_format的文件。
	搜索后将符合指定类型的文件添加到VARIABLE变量中

	@notice
	(1) GLOB参数下，源文件的搜索深度固定是1，没有递归搜索，
	类似shell的find命令：find <dir_path> -maxdepth 1 -name "*.c"
	(2) GLOB_RECURSE参数下，源文件的搜索是递归的，无视目录深度，
	类似shell的find命令：find <dir_path> -name "*.c"
	]]
# Method 1 for adding source files: file(GLOB ...)
file(GLOB __SRC_LIST "${__SRC_DIR}/*.cpp" "${__SRC_DIR}/C/*.c" "${__SRC_DIR}/CXX/*.cpp")
# Method 2 for adding source files: file(GLOB_RECURSE ...)
# file(GLOB_RECURSE __SRC_LIST "${__SRC_DIR}/*.cpp" "${__SRC_DIR}/*.c")

#[[
	@brief
	添加源文件到变量方式2，使用aux_source_directory命令

	@usage
	aux_source_directory(<dir_path> <VARIABLE>)
	搜索dir_path目录下的源文件(.c/.cpp/.cc等)，将其添加到VARIABLE变量中

	@notice
	源文件的搜索深度固定是1，没有递归搜索，
	类似shell的find命令：find <dir_path> -maxdepth 1 -name "*.c"
	]]
# Method 3 for adding source files: aux_source_directory(...)
# aux_source_directory(${__SRC_DIR} __SRC_LIST)
# aux_source_directory(${__SRC_DIR}/C __SRC_LIST)
# aux_source_directory(${__SRC_DIR}/CXX __SRC_LIST)

#[[
	@brief
	基于源文件为${__SRC_LIST}，生成名为${__TARGET}的可执行文件

	@usage
	add_executable(<executable_name> <src_list>)
	executable_name表示生成的可执行文件的文件名；
	src_list表示所有需要的源文件
	]]
add_executable(${__TARGET} ${__SRC_LIST})
