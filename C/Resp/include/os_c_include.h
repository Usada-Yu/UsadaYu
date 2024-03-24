/********************************************************************************************
 * @name    os_c_include.h
 * 
 * @author  胡益华
 * 
 * @date    2024-02-28
 * 
 * @brief   标准库、系统库头文件
********************************************************************************************/

#ifndef __OS_C_INCLUDE_H__
#define __OS_C_INCLUDE_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef __linux__
#ifndef __OS_LINUX__
#define __OS_LINUX__
#endif  // __OS_LINUX__
#include <time.h>
#include <unistd.h>
        // __linux__
#elif defined(_WIN32) || defined(_WIN64)
#ifndef __OS_WINDOWS__
#define __OS_WINDOWS__
#endif  // __OS_WINDOWS__
#include <windows.h>
#endif  // (_WIN32) || (_WIN64)

#endif  // __OS_C_INCLUDE_H__
