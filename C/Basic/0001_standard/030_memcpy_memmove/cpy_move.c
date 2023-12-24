/********************************************************************************************
 * @brief   关于memcpy与memmove的差异与使用
 * 
 * @details
 * (1)  memcpy与memmove都是用于内存拷贝。
 *      memcpy使用时，一般不要对同一块内存进行操作；
 *      memmove是允许对同一块内存进行拷贝操作的。
 *      何为对同一块内存操作，举个例子：
 *      char str[] = "0123456789";
 *      memcpy(str + 2, str + 0, 4);
 *      显然，memcpy内将str[0]赋值给str[2]后，后续会有str[2]赋值给str[4]的操作。
 *      这样多少有些歧义了，当gcc开启-Wall与-Werror选项后，这样的代码是不被允许通过的
 * 
 * (2)  写出上述代码，一般本意都是希望将"0123"字符串拷贝到[str + 2, str + 6)区间中，
 *      即拷贝后的结果为：0101236789
 *      所以赋值从后往前进行即可，即先将str[3]赋值给str[5]，再将str[2]赋值给str[4]，依此类推。
 *      memmove就提供了这个功能，使用memmove代替上述的memcpy，编译器便不再发出警告
 * 
 * (3)  实际上，glibc发展至今，这些小问题在标准库的源代码中早已解决。
 *      上述例子中，即使使用memcpy，运行后的结果和使用memmove还是一样的。
 *      不过开启了gcc的-Wall与-Werror选项后，报错依然会出现的。
 *      所以规范而言，遇到上述情况还是使用memmove更为妥当
********************************************************************************************/

#include <stdio.h>
#include <string.h>

#ifndef W_ERROR
#define W_ERROR (1)
#endif

int main()
{
    char str1[32] = "0123456789";
    char str2[32] = "0123456789";

#if W_ERROR
#pragma GCC diagnostic error "-Wall"
#endif
    memcpy(str1 + 2, str1 + 0, 4);
#if W_ERROR
#pragma GCC diagnostic pop
#endif
    printf("Copied string using memcpy:\t%s\n", str1);

#pragma GCC diagnostic error "-Wall"
    memmove(str2 + 2, str2 + 0, 4);
#pragma GCC diagnostic pop
    printf("Copied string using memmove:\t%s\n", str2);

    return 0;
}
