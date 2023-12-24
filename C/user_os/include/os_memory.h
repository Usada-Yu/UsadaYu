/********************************************************************************************
 * @name    os_memory.h
 * 
 * @author  胡益华
 * 
 * @date    2024-04-03
 * 
 * @brief   堆区内存管理
********************************************************************************************/

#ifndef __OS_MEMORY_H__
#define __OS_MEMORY_H__

#include "os_info.h"

/********************************************************************************************
 * @brief   申请堆区内存
 * 
 * @param   ptr: 堆区内存的起始地址
 * @param   num: 堆区内存的数量
 * 
 * @note    ptr必须有正确的变量类型，为避免内存大小出错，尽量不要对ptr二次强转
********************************************************************************************/
#ifndef OS_MEMORY_ALLOC
#define OS_MEMORY_ALLOC(ptr, num)                                   \
    ptr = (typeof(ptr))malloc(sizeof(typeof(*ptr)) * (num));        \
    if (OS_isNull(ptr)) {                                           \
        OS_ERROR("Malloc fail\n");                                  \
        return OS_EMEMORY_ALLOC;                                    \
    }                                                               \
    memset(ptr, 0, sizeof(typeof(*ptr)) * (num));
#endif  // OS_MEMORY_ALLOC

/********************************************************************************************
 * @brief   堆区内存释放
 * 
 * @param   ptr: 堆区内存的起始地址
********************************************************************************************/
#ifndef OS_MEMORY_FREE
#define OS_MEMORY_FREE(ptr)                                         \
    if (OS_isNotNull(ptr)) {                                        \
        free(ptr);                                                  \
        ptr = NULL;                                                 \
    }
#endif  // OS_MEMORY_FREE

#endif  // __OS_MEMORY_H__
