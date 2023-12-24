######################## @Title 当前目录的Cmake脚本样例 ########################
# 此目录工程演示链接静态库/动态库的方式.
# 这里，将003演示中制作的静态库/动态库和头文件拷贝到当前工程根目录下；
# 并且，将002演示中的主函数拷贝到当前工程中，用于调用库文件中的函数
#[[ windows，MINGW64下，执行命令：
    mkdir -p build && cd build
    cmake -G "MinGW Makefiles" ..
    mingw32-make -B -j
	]]
##############################################################################

cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)

project(
	PROJECT-CMAKE-LIBRARIES-LINK
	VERSION 		"1.0.0"
	DESCRIPTION 	"cmake libraries link"
	LANGUAGES 		"C" "CXX"
	HOMEPAGE_URL 	"https://github.com/Usada-Yu/UsadaYu/tree/master/ToolKnowledge/Cmake"
)

set(__SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(__BINARY_DIR ${PROJECT_SOURCE_DIR}/bin)
set(__TARGET cmakeDemoLibrariesLink)
# 静态库文件路径
set(__STATIC_LIBRARIES_DIR ${PROJECT_SOURCE_DIR}/lib/static)
# 动态库文件路径
set(__SHARE_LIBRARIES_DIR ${PROJECT_SOURCE_DIR}/lib/share)

# 所有需要的静态库文件
set(__STATIC_LIBRARIES cmakeDemoLibrariesMake)
# 所有需要的动态库文件
set(__SHARE_LIBRARIES cmakeDemoLibrariesMake)

#[[
	@brief
	指定库文件的搜索路径

	@usage
	link_directories(<library_path> [...])
	library_path表示库文件的搜索路径
	[...]表示如果需要指定多个库文件搜索路径，可以继续将其它路径在后续追加

	@notice
	(1) 此命令既可以指出静态库的搜索路径；也可以指出动态库的搜索路径
	(2) 
	]]
link_directories(${__STATIC_LIBRARIES_DIR})
# link_directories(${__SHARE_LIBRARIES_DIR})

include_directories(${PROJECT_SOURCE_DIR}/include/external)
include_directories(${PROJECT_SOURCE_DIR}/include/internal)

aux_source_directory(${__SRC_DIR} __SRC_LIST)

#[[
	@brief
	链接静态库命令

	@usage
	link_libraries(<static_library> [...])
	static_library表示需要链接的静态库名称；
	[...]表示如果需要链接多个静态库，可以继续将其它静态库名称在后续追加

	@notice
	(1) 此命令只适用于链接一个或多个静态库，不适用于动态库
	(2) 指定静态库名称时可以使用静态库库文件的全名，也可以使用去除前缀和后缀的库名称；
	如，一个静态库为libexample.a。那么使用link_libraries指定静态库链接时，
	link_libraries(libexample.a)是对的；
	link_libraries(example)也是对的。
	(3) 如果直接用link_libraries指定完整的静态库文件路径，那么就不能使用去除前缀和后缀的库名称了；
	如，一个静态库为libexample.a。那么使用link_libraries指定静态库链接时，
	link_libraries($HOME/cmakeDemo/lib/libexample.a)是对的；
	link_libraries($HOME/cmakeDemo/lib/example)是错的。
	所以此命令一般配合使用link_directories命令指出静态库文件的搜索目录
	]]
link_libraries(${__STATIC_LIBRARIES})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${__BINARY_DIR})
add_executable(${__TARGET} ${__SRC_LIST})
