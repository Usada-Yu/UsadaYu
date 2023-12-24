######################## @Title 当前目录的Cmake脚本样例 ########################
#[[ windows，MINGW64下，执行命令：
    cmake -H. -Bbuild -G "MinGW Makefiles"
    mingw32-make -C build -B -j
	./build/cmakeDemoHelloWorld
	]]
##############################################################################
# 注释方式说明
	# (1). 符号#可以用于单行注释
	# (2). 符号#[[ ]]可以用于多行注释
	#[[
		Hello Cmake!
		]]

project(HELLO-WORLD)
add_executable(cmakeDemoHelloWorld ./main.c)
