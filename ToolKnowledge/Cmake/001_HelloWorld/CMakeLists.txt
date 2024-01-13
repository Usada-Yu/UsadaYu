######################## @Title 当前目录的Cmake脚本样例 ########################
#[[ windows，MINGW64下，执行命令：
    mkdir -p build && cd build
    cmake -G "MinGW Makefiles" ..
    mingw32-make -B -j
	./cmakeDemoHelloWorld
	]]
##############################################################################
# 注释方式说明
	# (1). 符号#可以用于单行注释
	# (2). 符号#[[ ]]可以用于多行注释
	#[[
		Hello Cmake!
		]]

project(HELLO)
add_executable(cmakeDemoHelloWorld ./main.c)

# cd ../ && rm -rf ./build/*
