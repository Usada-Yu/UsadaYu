/********************************************************************************************
 * @brief   不同位数系统下各类型所占内存大小不同。一般直接取决于编译器内部实现，基本规律如下
 * 
 * @details 
 * type                         32bit system(Byte)      64bit system(Byte)
 * char                         1                       1
 * short(short int)             2                       2
 * int                          4                       4
 * long(long int)               4                       8
 * long long(long long int)     8                       8
 * float                        4                       4
 * double                       8                       8
 * void*                        4                       8
 * 
 * 1. 实际上各类型占用的内存大小在根本上，由程序运行时CPU的寻址位数决定；
 * 不过编译器会根据目标环境的CPU寻址位数直接决定各类型的大小。
 * 比如交叉编译时，编译器无法获取目标环境的CPU寻址位数，但是编译器依然能够解析各类型的大小；
 * 当使用sizeof(var)时，sizeof(var)的大小在编译时就已经决定了，不需要等到程序运行时再获取
 * 
 * 2. 在16位系统中，一般short占2Byte，int占2Byte，long占4Byte，ptr占2Byte；
 * 不过在一个单片机都纷纷迈入32位的时代，16位系统基本可以不必关心了
********************************************************************************************/

/********************************************************************************************
 * @brief   关于size_t内存占用大小。一般直接取决于编译器内部实现，基本规律如下
 * 
 * @details
 * name                         32bit system(Byte)      64bit system(Byte)
 * size_t                       unsigned int            unsigned long int
 * 
 * size_t为size type的缩写，设计此类型宏可以提高代码的可读性、可以移植性等。
 * size_t一般取目标平台下任何对象可能达到的最大长度，是无符号的。
 * C库中，和内存操作相关的函数中经常能看到size_t类型。
 * 
 * sizeof()关键字的返回值类型是size_t，为某类型或变量占用的内存字节大小。
 * void *malloc(size_t size)函数，用size_t指定分配内存的的字节数大小。
 * void *memcpy(void *str1, const void *str2, size_t n)，n表示拷贝的字节数。
 * 不难看出，有关内存大小、字节数的统计计算，经常能看到size_t的身影。
 * 
 * 以memcpy()函数为例，无论传入的参数n是什么类型，这些参数n都会被隐式转化为size_t。
 * 比如用unsigned int代替size_t：void *memcpy(void *str1, const void *str2, unsigned int n);
 * 那么就代表最多可一次性拷贝65536Byte(64MB)。
 * 若将此函数移植到一个I16LP32(int 32bit，long 32bit，ptr 32bit)处理器上，
 * 这个处理器可以一次性拷贝大于64MB的数据，但是此时unsigned int类型的形参不能承载65536Byte的数据，
 * 显然处理器的性能不能被完美地发挥。
 * 
 * 想当然的，如果用尽可能大的类型声明形参是不是就能解决上述问题。
 * 比如用unsigned long代替size_t：void *memcpy(void *str1, const void *str2, unsigned long n);
 * 然而这样，在IP16L32(int 16bit，ptr 16bit，long 32bit)处理器上，此函数执行的效率会大打折扣。
 * 一般来说，这类处理器移动一个32bit的long需要两个机器指令，这使得移动的效率大大降低。
 * 
 * 所以为了兼具可移植性、高效性。size_t应运而生。
 * 
 * @ref
 * 原文：http://web.archive.org/web/20101209143037/http://www.eetimes.com/discussion/programming-pointers/4026076/Why-size-t-matters?
 * 译文：https://www.cnblogs.com/noble/p/4144051.html
********************************************************************************************/
