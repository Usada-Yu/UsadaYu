#include <stdio.h>

#define __STRING_MERGE__    (1)

#if __STRING_MERGE__
/*-----------------------------------------------------------------------------------------------------------------*/
/*
宏定义实现字符串的拼接
不同宏定义方式拼接后的参数类型可能是不同的，注意区分
*/
#define __STRING_MERGE_NONE__       (0)
#define __STRING_MERGE_INT__        (0)
#define __STRING_MERGE_INT_CROSS__  (1)
#define __STRING_MERGE_STR__        (0)

#define ELEM_VAR_ABC   (1)
#define ELEM_VAR_DEF   (2)
#define ELEM_VAR_GHI   (3)

#if __STRING_MERGE_NONE__
// 假设有如下代码，结构十分规律，完全可用宏定义改写它
int main() {

    if (ELEM_VAR_ABC)
        printf("Suffix: (ABC), definition number: (%d)\n", ELEM_VAR_ABC);
    if (ELEM_VAR_DEF)
        printf("Suffix: (DEF), definition number: (%d)\n", ELEM_VAR_DEF);
    if (ELEM_VAR_GHI)
        printf("Suffix: (GHI), definition number: (%d)\n", ELEM_VAR_GHI);
}
#elif __STRING_MERGE_INT__
/*
若希望拼接后的字符串是整形%d形式，那么可以选择"var1##var2"的形式。
当然，可以用空格将欲拼接的字符串分割开来，使看起来更加清晰。
写成"var1##var2"/"var1 ##var2"/"var1## var2"/"var1 ## var2"等等都是正确的。
一般来说，两个#，表示仅作形式上的替换；单个#，表示以字符串形式替换。
*/

#define STRING_MERGE(var1, var2) (var1##var2)
#define STRING_MERGE_PRINT_ELEM(elem)   \
    if (STRING_MERGE(ELEM_VAR_, elem))  \
        printf("Suffix: ("#elem"), definition number: (%d)\n", STRING_MERGE(ELEM_VAR_, elem));

int main() {

    STRING_MERGE_PRINT_ELEM(ABC);
    STRING_MERGE_PRINT_ELEM(DEF);
    STRING_MERGE_PRINT_ELEM(GHI);
}
#elif __STRING_MERGE_INT_CROSS__
/*
实际上，在类似的宏用法中，对于编译器也是有一定要求的。
尤其是一些旧版本的gcc编译器，可能在字符串拼接时对拼接的内容都有要求。
如不能出现var1_和var2这样拼接，因为var1_是以下划线结尾的；
类似的，某些编译器中不能出现以.结尾的宏拼接。
甚至对于分隔符是空格/逗号/点号(" "/","/".")等都有要求。
如果出现：does not give a valid preprocessing token这样的报错，
很有可能就是编译器对当前宏定义写法不支持导致的。

更头疼的是对于相同的宏，编译器编译时不报错，但产生了不同的结果；
这就好比 i + i++ + ++i 这种老生常谈的话题。
所以实际使用时，没有把握的情况下应尽量避免。

这里举个例子仅作参考，实际情况会更加复杂。
假如某编译器不支持以下划线结尾的宏拼接，那么可以使用如下方式代替。
宏展开时先展开里层的宏，即STRING_MERGE(ELEM_VAR, _##elem)，
展开后为ELEM_VAR_##elem，接着展开外层宏，##elem会被elem所替代。
*/
#define STRING_MERGE(var1, var2) (var1##var2)
#define STRING_MERGE_PRINT_ELEM(elem)   \
    if (STRING_MERGE(ELEM_VAR_, elem))  \
        printf("Suffix: ("#elem"), definition number: (%d)\n", STRING_MERGE(ELEM_VAR, _##elem));

int main() {

    STRING_MERGE_PRINT_ELEM(ABC);
    STRING_MERGE_PRINT_ELEM(DEF);
    STRING_MERGE_PRINT_ELEM(GHI);
}
#elif __STRING_MERGE_STR__
/*
若希望拼接后的字符串是字符串%s形式，那么可以选择"#var1#var2"的形式，
单个#一般表示将变量作为字符串处理
此时，需要用%s来格式化输出，因为拼接后ELEM_VAR_*形式的参数不再是宏定义，而是一个字符串。
使用%d格式化输出可能发生段错误等。
*/

#define STRING_MERGE(var1, var2) (#var1#var2)
#define STRING_MERGE_PRINT_ELEM(elem)   \
    if (STRING_MERGE(ELEM_VAR_, elem))  \
        printf("Suffix: ("#elem"), definition number: (%s)\n", STRING_MERGE(ELEM_VAR_, elem));

int main() {

    STRING_MERGE_PRINT_ELEM(ABC);
    STRING_MERGE_PRINT_ELEM(DEF);
    STRING_MERGE_PRINT_ELEM(GHI);
}
#endif
/*-----------------------------------------------------------------------------------------------------------------*/
#endif
