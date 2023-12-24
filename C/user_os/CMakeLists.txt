cmake_minimum_required(VERSION 3.5)

project(
	PROJECT-USER-OS
	VERSION "1.0.0"
	DESCRIPTION "user defined os library"
	LANGUAGES "C"
	HOMEPAGE_URL "https://github.com/Usada-Yu/UsadaYu/tree/master/C/user_os"
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
set(__ARTIFACT_DIR ${PROJECT_SOURCE_DIR}/artifact/${plat})
set(__TARGET user_os)

# user_os输出路径
set(LIBRARY_OUTPUT_PATH ${__ARTIFACT_DIR}/lib)

include_directories(${PROJECT_SOURCE_DIR}/include)

aux_source_directory(${__SRC_DIR} __SRC_LIST)

# 打包生成user_os静态库
add_library(${__TARGET} STATIC ${__SRC_LIST})
# 打包生成user_os动态库
# add_library(${__TARGET} SHARED ${__SRC_LIST})

# 将头文件添加到目标目录下
file(COPY ${PROJECT_SOURCE_DIR}/include DESTINATION ${__ARTIFACT_DIR})
