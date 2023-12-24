/********************************************************************************************
 * @brief  关于宏定义container_of解析
********************************************************************************************/
#include <stdio.h>
#include "containerOf.h"

#define __COA_INFO(format, ...)                             \
    do {                                                    \
        fprintf(stdout,                                     \
        "[Line: %d]: " format, __LINE__, ##__VA_ARGS__);    \
    } while(0);

/*-----------------------------------------------------------------------------------------------------------------*/
/*
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

#define container_of(ptr, type, member) ({			            \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
        (type *)( (char *)__mptr - offsetof(type, member) );})
*/

/*-----------------------------------------------------------------------------------------------------------------*/
int main() {
    /*
    1. 最外层({})符号的作用：
    若符号中有多条语句，那么返回最后一条语句的值
    */
    int elem1   = 10;
    int elem2   = 10;
    int status1 = 0;
    status1 = ({elem1; elem1 + elem2; elem1 == elem2;});
    __COA_INFO("[status: %d]\n", status1);

    /*
    2. typeof的作用：
    获取变量的类型
    */
    char *str1 = "Hello";
    typeof(str1) str2 = "World";
    __COA_INFO("%s %s\n", str1, str2);

    /*
    3. ((type *)0)->member的作用：
    以0为结构体的地址，获取结构体中的member成员
    */
    typedef struct {
        int member1;
        int member2;
    } st_box1;
    __COA_INFO("[member1 address: %p] [member2 address: %p]\n", &((st_box1 *)0)->member1, &((st_box1 *)0)->member2);

    /*
    4. const typeof( ((type *)0)->member ) *__mptr = (ptr);的作用：
    表示以member的类型声明一个指针__mptr，将其赋值为ptr，即传入的menber成员的地址。
    可以看出这里实际上重点是获取结构体成员member的类型，所以即使使用(type *)4或(type *)10等等效果都是一样的
    */
    __COA_INFO("[member1 address: %p] [member2 address: %p]\n", &((st_box1 *)2)->member1, &((st_box1 *)2)->member2);

    /*
    5. ((size_t) &((TYPE *)0)->MEMBER)的作用：
    size_t：在当前系统可以达到的最大偏移地址，一般在stddef.h头文件按中，用最大的无符号整型表示，
    一般64位系统下为long unsigned int(64bit)；32位系统下为unsigned int(32bit)。
    这个表达式表示获取结构体member成员相对于结构体首地址的偏移地址
    */

    /*
    6. (char *)__mptr - offsetof(type, member)的作用：
    表示结构体成员member的地址减去member相对于结构体首地址的偏移地址，这样就获得了结构体的首地址。
    此处用(char *)强转__mptr是为了在减去offsetof时，固定减去sizeof(char) * offsetof(type, member)长度；
    如果使用(int *)强转__mptr，那么减去偏移量时就会减去sizeof(int) * offsetof(type, member)长度
    */
    #pragma pack(push, 1)
    typedef struct {
        char                placeholder[128];   // 64位系统下：128Byte  offset address: nil
        char                member1;            // 64位系统下：8bit     offset address: 0x80
        int                 member2;            // 64位系统下：32bit    offset address: 0x81
        unsigned long int   member3;            // 64位系统下：64bit    offset address: 0x85
        float               member4;            // 64位系统下：32bit    offset address: 0x8d
        double              member5;            // 64位系统下：64bit    offset address: 0x91
        char*               member6;            // 64位系统下：64bit    offset address: 0x99
    } st_box2;
    #pragma pack(4)

    // 0x91 - 3 * sizeof(short) = 0x91 - 0x06 = 0x8b
    __COA_INFO("[offset address: %p]\n", (short *)(&((st_box2 *)0)->member5) - 3);

    // 0x91 - 3 * sizeof(int) = 0x91 - 0x0c = 0x85
    __COA_INFO("[offset address: %p]\n", (int *)(&((st_box2 *)0)->member5) - 3);

    // 0x91 - 3 * sizeof(char) = 0x91 - 0x03 = 0x8e
    __COA_INFO("[offset address: %p]\n", (char *)(&((st_box2 *)0)->member5) - 3);

    return 0;
}
