/********************************************************************************************
 * @name    os_math.c
 * 
 * @author  胡益华
 * 
 * @date    2024-03-29
 * 
 * @brief   常用的基础计算
********************************************************************************************/

#include "os_common.h"

/********************************************************************************************
 * @brief   返回若干个整型数字中的最大值
 * 
 * @param   args_num: 整型数字的总个数
 * @param   ...: 若干的整型数字
 * 
 * @note    (1) args_num为必填项
 *          (2) 举例：若传入整型数字总数为8，那么args_num填写8即可；
 *          args_num填写大于8，如10，那么会比较8个整型数字；
 *          args_num填写小于8，如6，那么会比较前6个整型数字
 *          (3) 函数基于可变参数列表编写。
 *          va_arg宏读取参数时会根据传入参数类型大小的偏移读取，故传参时必须传递整型类型
********************************************************************************************/
int _os_math_max_int(unsigned int args_num, ...) {
    unsigned int i = 0;
    va_list args;
    va_start(args, args_num);               // 将可变参数列表初始化为从第二个参数开始，第一个参数为args_num

    int max_val = INT_MIN;                  // 设置初始值为整型的最小值
    for (i = 0; i < args_num; i++) {
        int arg = va_arg(args, int);        // 以整型类型获取可变参数列表的中的元素
        max_val = arg > max_val ? arg : max_val;
    }

    va_end(args);                           // 结束对可变参数列表的访问
    return max_val;
}

/********************************************************************************************
 * @brief   返回若干个整型数字中的最小值
 * 
 * @param   args_num: 整型数字的总个数
 * @param   ...: 若干的整型数字
 * 
 * @note    (1) args_num为必填项
 *          (2) 举例：若传入整型数字总数为8，那么args_num填写8即可；
 *          args_num填写大于8，如10，那么会比较8个整型数字；
 *          args_num填写小于8，如6，那么会比较前6个整型数字
 *          (3) 函数基于可变参数列表编写。
 *          va_arg宏读取参数时会根据传入参数类型大小的偏移读取，故传参时必须传递整型
********************************************************************************************/
int _os_math_min_int(unsigned int args_num, ...) {
    unsigned int i = 0;
    va_list args;
    va_start(args, args_num);               // 将可变参数列表初始化为从第二个参数开始，第一个参数为args_num

    int min_val = INT_MAX;                  // 设置初始值为整型的最大值
    for (i = 0; i < args_num; i++) {
        int arg = va_arg(args, int);        // 以整型类型获取可变参数列表的中的元素
        min_val = arg < min_val ? arg : min_val;
    }

    va_end(args);                           // 结束对可变参数列表的访问
    return min_val;
}

/********************************************************************************************
 * @brief   返回若干个双精度浮点型数字中的最大值
 * 
 * @param   args_num: 双精度浮点型数字的总个数
 * @param   ...: 若干的双精度浮点型数字
 * 
 * @note    (1) args_num为必填项；
 *          (2) 举例：若传入双精度浮点型数字总数为8，那么args_num填写8即可；
 *          args_num填写大于8，如10，那么会比较8个双精度浮点型数字；
 *          args_num填写小于8，如6，那么会比较前6个双精度浮点型数字
 *          (3) 函数基于可变参数列表编写。
 *          对于浮点型，va_arg宏只能以double类型读取而不能以float类型读取；
 *          va_arg宏读取参数时会根据传入参数类型大小的偏移读取，故传参时必须传递浮点型
********************************************************************************************/
double _os_math_max_dbl(unsigned int args_num, ...) {
    unsigned int i = 0;
    va_list args;
    va_start(args, args_num);               // 将可变参数列表初始化为从第二个参数开始，第一个参数为args_num

    double max_val = DBL_MIN;               // 设置初始值为双精度浮点型的最小值
    for (i = 0; i < args_num; i++) {
        double arg = va_arg(args, double);  // 以双精度浮点型获取可变参数列表的中的元素
        max_val = arg > max_val ? arg : max_val;
    }

    va_end(args);                           // 结束对可变参数列表的访问
    return max_val;
}

/********************************************************************************************
 * @brief   返回若干个双精度浮点型数字中的最小值
 * 
 * @param   args_num: 双精度浮点型数字的总个数
 * @param   ...: 若干的双精度浮点型数字
 * 
 * @note    (1) args_num为必填项；
 *          (2) 举例：若传入双精度浮点型数字总数为8，那么args_num填写8即可；
 *          args_num填写大于8，如10，那么会比较8个双精度浮点型数字；
 *          args_num填写小于8，如6，那么会比较前6个双精度浮点型数字
 *          (3) 函数基于可变参数列表编写。
 *          对于浮点型，va_arg宏只能以double类型读取而不能以float类型读取；
 *          va_arg宏读取参数时会根据传入参数类型大小的偏移读取，故传参时必须传递浮点型
********************************************************************************************/
double _os_math_min_dbl(unsigned int args_num, ...) {
    unsigned int i = 0;
    va_list args;
    va_start(args, args_num);               // 将可变参数列表初始化为从第二个参数开始，第一个参数为args_num

    double min_val = DBL_MAX;               // 设置初始值为双精度浮点型的最大值
    for (i = 0; i < args_num; i++) {
        double arg = va_arg(args, double);  // 以双精度浮点型获取可变参数列表的中的元素
        printf("%lf\n", arg);
        min_val = arg < min_val ? arg : min_val;
    }

    va_end(args);                           // 结束对可变参数列表的访问
    return min_val;
}
