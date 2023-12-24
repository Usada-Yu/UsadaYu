cmake_minimum_required(VERSION 3.5)

project(
	PROJECT-USER-ALG
	VERSION "1.0.0"
	DESCRIPTION "user defined alg library"
	LANGUAGES "C"
	HOMEPAGE_URL "https://github.com/Usada-Yu/UsadaYu/tree/master/C/user_alg"
)

# 通过 cmake -H. -Bbuild -Dplat= 指定平台，默认为Linux x86平台
# 如果用户通过命令设置了plat变量，则采用用户设置的平台
set(plat "x86" CACHE STRING "Platform type")
if(DEFINED plat)
	set(plat ${plat} CACHE STRING "Platform type" FORCE)
endif()

if(plat STREQUAL "x86")
	message("-- Building platform is ${plat}")
elseif(plat STREQUAL "hi3519dv500")
	message("-- Building platform is ${plat}")
	set(__CROSS aarch64-linux-gnu-hi3519dv500-v2-)
elseif(plat STREQUAL "sd3403v100")
	message("-- Building platform is ${plat}")
	set(__CROSS aarch64-himix210-linux-sd3403v100-v1-)
elseif(plat STREQUAL "win")
	message("-- Building platform is ${plat}")
else()
	message(WARNING " Unexpected plat: ${plat}")
	set(plat "x86")
	message(WARNING " Use default plat: ${plat}")
endif()

set(CMAKE_C_COMPILER "${__CROSS}gcc")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")

set(__SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(__LIB_DIR ${PROJECT_SOURCE_DIR}/lib/${plat})
set(__ARTIFACT_DIR ${PROJECT_SOURCE_DIR}/artifact/${plat})
set(__TARGET user_alg)

# 静态库文件路径
set(__STATIC_LIBRARIES_DIR ${__LIB_DIR})

# 所有需要的静态库文件
set(__STATIC_LIBRARIES user_os)

# user_alg输出路径
set(LIBRARY_OUTPUT_PATH ${__ARTIFACT_DIR}/lib)

include_directories(${PROJECT_SOURCE_DIR}/include/external)
include_directories(${PROJECT_SOURCE_DIR}/include/internal)

# 指定静态库搜索路径
link_directories(${__STATIC_LIBRARIES_DIR})

# 链接静态库
link_libraries(${__STATIC_LIBRARIES})

aux_source_directory(${__SRC_DIR} __SRC_LIST)

# 打包生成user_alg静态库
add_library(${__TARGET} STATIC ${__SRC_LIST})
# 打包生成user_alg动态库
# add_library(${__TARGET} SHARED ${__SRC_LIST})

# 将头文件添加到目标目录下
file(GLOB __HEADER_FILE ${PROJECT_SOURCE_DIR}/include/internal/*.h)
file(COPY ${__HEADER_FILE} DESTINATION ${__ARTIFACT_DIR}/include)
