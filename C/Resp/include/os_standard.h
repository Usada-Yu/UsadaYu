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
// 通用错误
#ifndef OS_EFAIL
#define OS_EFAIL        (-1)
#endif  // OS_EFAIL

// 通用正确
#ifndef OS_SOK
#define OS_SOK          (0)
#endif  // OS_SOK

// 超时错误
#ifndef OS_TIMEOUT
#define OS_TIMEOUT      (1)
#endif  // OS_TIMEOUT

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
