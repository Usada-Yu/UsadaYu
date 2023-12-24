######################## @Title 当前目录的Cmake脚本样例 ########################
# 此目录工程省去main()函数，用于编译静态库/动态库
#[[ windows，MINGW64下，执行命令：
    mkdir -p build && cd build
    cmake -G "MinGW Makefiles" ..
    mingw32-make -B -j
	]]
##############################################################################

cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)

project(
	PROJECT-CMAKE-LIBRARIES-MAKE
	VERSION 		"1.0.0"
	DESCRIPTION 	"cmake libraries make"
	LANGUAGES 		"C" "CXX"
	HOMEPAGE_URL 	"https://github.com/Usada-Yu/UsadaYu/tree/master/ToolKnowledge/Cmake"
)

set(__SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(__ARTIFACT_DIR ${PROJECT_SOURCE_DIR}/artifact)
set(__TARGET cmakeDemoLibrariesMake)

#[[
	@brief
	指定库文件生成路径

	@description
	动态库有可执行权限，若需要指定动态库生成路径，可以用以下参数：
	CMAKE_RUNTIME_OUTPUT_DIRECTORY
	EXECUTABLE_OUTPUT_PATH
	CMAKE_LIBRARY_OUTPUT_DIRECTORY
	LIBRARY_OUTPUT_PATH；
	静态库没有可执行权限，若需要指定静态库生成路径，可以用以下参数：
	LIBRARY_OUTPUT_PATH。
	综上所述，要生成库文件，选择LIBRARY_OUTPUT_PATH参数比较好
	]]
set(LIBRARY_OUTPUT_PATH ${__ARTIFACT_DIR})

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB_RECURSE __SRC_LIST "${__SRC_DIR}/*.cpp" "${__SRC_DIR}/*.c")

#[[
	@brief
	生成静态库或动态库命令

	@usage
	add_library(<library_name> STATIC/SHARED <src_list>)
	library_name表示生成的库文件的文件名；
	STATIC表示生成静态库，SHARED表示生成动态库；
	src_list表示所有需要的源文件

	@notice
	(1) cmake是跨平台的，所以不需要指出库文件的文件后缀，cmake会自行处理。
	一般Linux的静态库后缀为.a，动态库后缀为.so；
	一般Windows的静态库后缀为.lib，动态库后缀为.dll。
	(2) Windows下生成动态库时，还可能伴随着一个*.dll.a的文件生成，
	这一般是在使用GNU工具链的情况下会看到，这个文件是为了与GNU工具链兼容而生成的
	(3) Linux/Windows等系统下生成的库文件固定前缀都为lib。
	library_name中库文件前缀和后缀都不需要显示指出，只需要指定文件名即可。
	]]
add_library(${__TARGET} STATIC ${__SRC_LIST})
# add_library(${__TARGET} SHARED ${__SRC_LIST})

# 将头文件添加到目标目录下
file(COPY ${PROJECT_SOURCE_DIR}/include DESTINATION ${__ARTIFACT_DIR})
