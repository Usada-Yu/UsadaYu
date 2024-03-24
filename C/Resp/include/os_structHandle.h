/********************************************************************************************
 * @name    os_structHandle.h
 * 
 * @author  胡益华
 * 
 * @date    2024-02-28
 * 
 * @brief   结构体有关的宏
********************************************************************************************/

#ifndef __OS_STRUCT_HANDLE_H__
#define __OS_STRUCT_HANDLE_H__

#ifndef OS_container_of
/********************************************************************************************
 * @brief   获取结构体成员的地址偏移量
 * 
 * @param   TYPE: 结构体类型
 * @param   MEMBER: 结构体成员变量名
********************************************************************************************/
#ifndef OS_offsetof
#define OS_offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif  // OS_offsetof

/********************************************************************************************
 * @brief   通过结构体成员获取结构体首地址
 * 
 * @param   ptr: 结构体成员的地址
 * @param   type: 结构体类型
 * @param   member: 结构体成员变量名
********************************************************************************************/
#define OS_container_of(ptr, type, member) ({                           \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);            \
        (type *)( (char *)__mptr - offsetof(type, member) );})
#endif  // OS_container_of

#endif  // __OS_STRUCT_HANDLE_H__
