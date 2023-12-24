/********************************************************************************************
 * @name    os_standard.h
 * 
 * @author  胡益华
 * 
 * @date    2024-01-09
 * 
 * @brief   规范标准的宏
********************************************************************************************/

#ifndef __OS_STANDARD_H_
#define __OS_STANDARD_H_

/********************************************************************************************
 * @brief   状态码
********************************************************************************************/
#ifndef OS_SOK
// 通用正确
#define OS_SOK              (0)
#endif  // OS_SOK

#ifndef OS_EFAIL
// 通用错误
#define OS_EFAIL            (-1)
#endif  // OS_EFAIL

#ifndef OS_ETIMEOUT
// 超时错误
#define OS_ETIMEOUT         (-2)
#endif  // OS_ETIMEOUT

#ifndef OS_EMEMORY_ALLOC
// 内存分配失败
#define OS_EMEMORY_ALLOC    (-3)
#endif  // OS_EMEMORY_ALLOC

#ifndef OS_ECACHE_OVER
// 自定义缓存溢出
#define OS_ECACHE_OVER      (-4)
#endif  // OS_ECACHE_OVER

#ifndef OS_EFUNC_PARAM
// 函数实参错误
#define OS_EFUNC_ARGUMENT   (-5)
#endif  // OS_EFUNC_PARAM

#ifndef OS_EPTR_NULL
// 指针为空
#define OS_EPTR_NULL        (-6)
#endif  // OS_EPTR_NULL

#ifndef OS_EMATCH
// 参数或结果等匹配错误
#define OS_EMATCH           (-7)
#endif  // OS_EMATCH

/********************************************************************************************
 * @brief   空指针判断
 * 
 * @param   ptr: 指针变量
********************************************************************************************/
#ifndef OS_isNull
#define OS_isNull(ptr)          (((void*)(0)) == (ptr))
#endif  // OS_isNull

#ifndef OS_isNotNull
#define OS_isNotNull(ptr)       (((void*)(0)) != (ptr))
#endif  // OS_isNotNull

/********************************************************************************************
 * @brief   状态判断
 * 
 * @param   status: 状态变量
********************************************************************************************/
#ifndef OS_isSuc
#define OS_isSuc(status)        (OS_SOK == (status))
#endif  // OS_isSuc

#ifndef OS_isFail
#define OS_isFail(status)       (OS_SOK != (status))
#endif  // OS_isFail

#endif  // __OS_STANDARD_H_
