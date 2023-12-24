#ifndef __CONTAINEROF_H__
#define __CONTAINEROF_H__

#ifndef OS_container_of
/********************************************************************************************
 * @brief   获取结构体成员的地址偏移量
 * 
 * @param   TYPE: 结构体类型
 * @param   MEMBER: 结构体成员变量名
********************************************************************************************/
#ifndef offsetof
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif  // offsetof

/********************************************************************************************
 * @brief   通过结构体成员获取结构体首地址
 * 
 * @param   ptr: 结构体成员的地址
 * @param   type: 结构体类型
 * @param   member: 结构体成员变量名
********************************************************************************************/
#define container_of(ptr, type, member) ({                              \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);            \
        (type *)( (char *)__mptr - offsetof(type, member) );})
#endif  // container_of

#endif  // __CONTAINEROF_H__
