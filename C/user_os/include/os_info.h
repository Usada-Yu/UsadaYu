/********************************************************************************************
 * @name    os_info.h
 * 
 * @author  胡益华
 * 
 * @date    2024-01-09
 * 
 * @brief   常用的信息打印、错误打印等宏
********************************************************************************************/

#ifndef __OS_INFO_H__
#define __OS_INFO_H__

#include "os_c_include.h"
#include "os_standard.h"

#ifdef __OS_LINUX__
#ifndef __OS_FILE__
#define __OS_FILE__                                                 \
    (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif  // __OS_FILE__
        // __OS_LINUX__
#elif defined __OS_WINDOWS__
#define __OS_FILE__                                                 \
    (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#endif  // __OS_WINDOWS__

/********************************************************************************************
 * @brief   向标准输出打印当前时间，格式为hour:minute:second
 * 
 * @param   stream: 输出流。指定向标准输出或标准错误打印信息，传入NULL表示向标准输出打印信息
********************************************************************************************/
void _os_info_current_time(FILE *stream);

#ifndef OS_CURRENT_TIME
#define OS_CURRENT_TIME(stream)     _os_info_current_time(stream)
#endif  // OS_CURRENT_TIME

/********************************************************************************************
 * @brief   向标准输出打印信息
 * 
 * @param   format: 打印信息
********************************************************************************************/
#ifndef OS_INFO
#define OS_INFO(format, ...)                                        \
    do {                                                            \
        fprintf(stdout, "[");                                       \
        OS_CURRENT_TIME(stdout);                                    \
        fprintf(stdout,                                             \
        " INFO File: %s Line: %d Function: %s()] " format,          \
        __OS_FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__);        \
    } while(0)
#endif  // OS_INFO

/********************************************************************************************
 * @brief   向标准错误打印警告
 * 
 * @param   format: 打印信息
********************************************************************************************/
#ifndef OS_WARN
#define OS_WARN(format, ...)                                        \
    do {                                                            \
        fprintf(stderr, "[");                                       \
        OS_CURRENT_TIME(stderr);                                    \
        fprintf(stderr,                                             \
        " WARN File: %s Line: %d Function: %s()] " format,          \
        __OS_FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__);        \
    } while(0)
#endif  // OS_WARN

/********************************************************************************************
 * @brief   向标准错误打印错误
 * 
 * @param   format: 打印信息
********************************************************************************************/
#ifndef OS_ERROR
#define OS_ERROR(format, ...)                                       \
    do {                                                            \
        fprintf(stderr, "[");                                       \
        OS_CURRENT_TIME(stderr);                                    \
        fprintf(stderr,                                             \
        " ERROR File: %s Line: %d Function: %s()] " format,         \
        __OS_FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__);        \
    } while(0)
#endif // OS_ERROR

/********************************************************************************************
 * @brief   判断函数返回状态，成功后打印信息到标准输出，并返回
 * 
 * @param   ret: 函数返回值
 * @param   func: 函数名称
********************************************************************************************/
#ifndef OS_isSUC_INFO_RE
#define OS_isSUC_INFO_RE(ret, func)                                 \
    if (OS_isSuc(ret)) {                                            \
        OS_INFO(                                                    \
        "The function "#func"() call was successful, return\n");    \
        return ret;                                                 \
    }
#endif  // OS_isSUCCESS_INFO_RE

/********************************************************************************************
 * @brief   判断函数返回状态，成功后仅打印信息到标准输出，不返回
 * 
 * @param   ret: 函数返回值
 * @param   func: 函数名称
********************************************************************************************/
#ifndef OS_isSUC_INFO_IF
#define OS_isSUC_INFO_IF(ret, func)                                 \
    if (OS_isSuc(ret)) {                                            \
        OS_INFO(                                                    \
        "The function "#func"() call was successful, "              \
        "print only\n");                                            \
    }
#endif  // OS_isSUC_INFO_IF

/********************************************************************************************
 * @brief   判断函数返回状态，成功后仅打印信息到标准输出，并二次循环
 * 
 * @param   ret: 函数返回值
 * @param   func: 函数名称
 * 
 * @note    此宏必须在循环中调用
********************************************************************************************/
#ifndef OS_isSUC_INFO_CT
#define OS_isSUC_INFO_CT(ret, func)                                 \
    if (OS_isSuc(ret)) {                                            \
        OS_INFO(                                                    \
        "The function "#func"() call was successful, continue\n");  \
        continue;                                                   \
    }
#endif  // OS_isSUC_INFO_CT

/********************************************************************************************
 * @brief   判断函数返回状态，失败后仅打印错误信息到标准错误，并返回
 * 
 * @param   ret: 函数返回值
 * @param   func: 函数名称
********************************************************************************************/
#ifndef OS_isFAIL_ERROR_RE
#define OS_isFAIL_ERROR_RE(ret, func)                               \
    if (OS_isFail(ret)) {                                           \
        OS_ERROR(                                                   \
        "The function "#func"() call failed with [%d], return\n",   \
        ret);                                                       \
        return ret;                                                 \
    }
#endif  // OS_isFAIL_ERROR_RE

/********************************************************************************************
 * @brief   判断函数返回状态，失败后仅打印错误信息到标准错误，不返回
 * 
 * @param   ret: 函数返回值
 * @param   func: 函数名称
********************************************************************************************/
#ifndef OS_isFAIL_ERROR_IF
#define OS_isFAIL_ERROR_IF(ret, func)                               \
    if (OS_isFail(ret)) {                                           \
        OS_ERROR(                                                   \
        "The function "#func"() call failed with [%d], "            \
        "print only\n",                                             \
        ret);                                                       \
    }
#endif  // OS_isFAIL_ERROR_IF

/********************************************************************************************
 * @brief   判断函数返回状态，失败后仅打印错误信息到标准错误，并跳转
 * 
 * @param   ret: 函数返回值
 * @param   func: 函数名称
 * @param   label: goto标签
 * 
 * @note    此宏调用前必须设置goto处理标签
********************************************************************************************/
#ifndef OS_isFAIL_ERROR_GT
#define OS_isFAIL_ERROR_GT(ret, func, label)                        \
    if (OS_isFail(ret)) {                                           \
        OS_ERROR(                                                   \
        "The function "#func"() call failed with [%d], "            \
        "goto "#label"\n", ret);                                    \
        goto label;                                                 \
    }
#endif  // OS_isFAIL_ERROR_GT

/********************************************************************************************
 * @brief   判断函数返回状态，失败后仅打印错误信息到标准错误，并二次循环
 * 
 * @param   ret: 函数返回值
 * @param   func: 函数名称
 * 
 * @note    此宏必须在循环中调用
********************************************************************************************/
#ifndef OS_isFAIL_ERROR_CT
#define OS_isFAIL_ERROR_CT(ret, func)                               \
    if (OS_isFail(ret)) {                                           \
        OS_ERROR(                                                   \
        "The function "#func"() call failed with [%d], continue\n", \
        ret);                                                       \
        continue;                                                   \
    }
#endif  // OS_isFAIL_ERROR_CT

/********************************************************************************************
 * @brief   判断函数返回状态，失败后仅打印警告信息到标准错误，并返回
 * 
 * @param   ret: 函数返回值
 * @param   func: 函数名称
********************************************************************************************/
#ifndef OS_isFAIL_WARN_RE
#define OS_isFAIL_WARN_RE(ret, func)                                \
    if (OS_isFail(ret)) {                                           \
        OS_WARN(                                                    \
        "The function "#func"() call failed with [%d], return\n",   \
        ret);                                                       \
        return ret;                                                 \
    }
#endif  // OS_isFAIL_WARN_RE

/********************************************************************************************
 * @brief   判断函数返回状态，失败后仅打印警告信息到标准错误，不返回
 * 
 * @param   ret: 函数返回值
 * @param   func: 函数名称
********************************************************************************************/
#ifndef OS_isFAIL_WARN_IF
#define OS_isFAIL_WARN_IF(ret, func)                                \
    if (OS_isFail(ret)) {                                           \
        OS_WARN(                                                    \
        "The function "#func"() call failed with [%d], "            \
        "print only\n",                                             \
        ret);                                                       \
    }
#endif  // OS_isFAIL_WARN_IF

/********************************************************************************************
 * @brief   判断函数返回状态，失败后仅打印警告信息到标准错误，并跳转
 * 
 * @param   ret: 函数返回值
 * @param   func: 函数名称
 * @param   label: goto标签
 * 
 * @note    此宏调用前必须设置goto处理标签
********************************************************************************************/
#ifndef OS_isFAIL_WARN_GT
#define OS_isFAIL_WARN_GT(ret, func, label)                         \
    if (OS_isFail(ret)) {                                           \
        OS_WARN(                                                    \
        "The function "#func"() call failed with [%d], "            \
        "goto "#label"\n", ret);                                    \
        goto label;                                                 \
    }
#endif  // OS_isFAIL_WARN_GT

/********************************************************************************************
 * @brief   判断函数返回状态，失败后仅打印警告信息到标准错误，并二次循环
 * 
 * @param   ret: 函数返回值
 * @param   func: 函数名称
 * 
 * @note    此宏必须在循环中调用
********************************************************************************************/
#ifndef OS_isFAIL_WARN_CT
#define OS_isFAIL_WARN_CT(ret, func)                                \
    if (OS_isFail(ret)) {                                           \
        OS_WARN(                                                    \
        "The function "#func"() call failed with [%d], continue\n", \
        ret);                                                       \
        continue;                                                   \
    }
#endif  // OS_isFAIL_WARN_CT

#endif  // __OS_INFO_H__
