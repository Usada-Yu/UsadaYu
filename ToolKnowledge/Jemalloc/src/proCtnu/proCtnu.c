/*
1.
此用例中，ptr_rise堆内存被分配后，释放时有部分没有被释放，因此会产生内存碎片。
进程中开启了两个线程，增加一些定位内存碎片的难度。
这个程序模拟不会退出的进程，所以jemalloc MALLOC_CONF环境变量中的prof_final参数不起作用。

2. 
(1) 以如下方式执行命令：
make clean
mkdir -p ./memAnlys/x86
chmod 777 ./memAnlys/x86
make mtype=ctnu -B
MALLOC_CONF=prof:true,prof_leak:true,lg_prof_interval:18,lg_prof_sample:16,\
prof_prefix:./memAnlys/x86/x86 ./bin/x86/lovely
(2) 上述环境变量中：
prof:true           开启后，剖析进程的内存申请操作
prof_leak:true      开启后，生成转储后的内存报告文件
lg_prof_interval:18 生成转储文件的间隔，2^18字节
lg_prof_sample:16   内存分配采样的间隔，2^16字节
prof_prefix:./memAnlys/x86/x86  转储的heap文件前缀

3.
在./memAnlys/x86目录下会生成相应的.heap文件，因为进程无法退出，所以.heap文件会持续生成。
ls ./memAnlys/x86
./script/jeHeapToTxt.sh x86
python3 ./script/log_porcess.py [retain/remove]

4.
结果报告总体来看因为内存有申请也有释放，所以统计结果中内存分配的大小也在上下浮动，
此时通过excel作图可以更直观地反映内存问题。
通过脚本和作图对内存报告针对性地处理后做分析：
(1) jemalloc统计的总内存消耗(Total)有上下浮动，但总体呈上升趋势，说明进程总体存在内存泄漏；
    实际上，总体内存上涨的情况使用Linux的top命令也可以发现；
(2) main函数的内存上涨趋势和Total趋势相似；
(3) fun_alloc函数的内存上涨趋势和main函数趋势相似；
(4) 调用fun_alloc的函数有main和fun_heap_stack；
(5) fun_heap_stack函数内存消耗比较稳定，总体趋势没有呈现上涨

5.
初步得出结论：
main函数调用fun_alloc后，可能没有将堆区内存归还，需要检查main中内存释放情况
*/

#include <pthread.h>
#include "common.h"

#define HEAP_MEM_SIZE       (6666)
#define HEAP_MEM_NUM        (5)
#define HEAP_FREE_FLAG      (1)     // 堆区内存完全释放标志。1：不完全释放；0：完全释放

/*
计算得str_arr结构体大小为：
sizeof(int) * HEAP_MEM_SIZE = 26664(B)
每次泄露的结构体内存数量为1，根据采样间隔公式有：
2 ^ x = 26664 * 1
进一步有：
x = log2 ^ 26664 ≈ 14.703
所以采样间隔lg_prof_sample设置为15或16比较合适。

此处因为已经知晓内存泄露时的涨幅，所以可以直接计算并决定lg_prof_sample的大小；
实际定位内存问题时，可以先用Linux的top命令统计内存的每一次涨幅，再决定lg_prof_sample
*/
typedef struct {
    int elem[HEAP_MEM_SIZE];
} str_arr;

void fun_heap_stack(int *threadFreeFlag) {
    int     i           = 0;
    int     stack[3]    = {0};
    int     *thrdFlag   = threadFreeFlag;
    str_arr *ptr        = NULL;

    while (*thrdFlag) {
        printf("%s\n", __FUNCTION__);

        ptr = fun_alloc(1 * sizeof(str_arr));
        if (NULL == ptr) {
                exit(-1);
        }
        usleep(1 * 1000 * 1000);

        for (i = 0; i < 3; i++) {
            stack[i] = i;
            usleep(stack[i] * 1000 * 1000);
        }

        free(ptr);
        ptr = NULL;
    }
}

int main() {
    int         i                           = 3600;
    int         j                           = 0;
    pthread_t   tid;
    str_arr     *ptr_rise[HEAP_MEM_NUM]     = {NULL};
    str_arr     *ptr_steady[HEAP_MEM_NUM]   = {NULL};

    int globalThreadFlag = 1;

    (void)pthread_create(&tid, NULL, (void*)fun_heap_stack, &globalThreadFlag);

    while (i--) {
        for (j = 0; j < HEAP_MEM_NUM; ++j) {
            ptr_rise[j] = fun_alloc(1 * sizeof(str_arr));
            if (NULL == ptr_rise[j]) {
                 exit(-1);
            }
            printf("%p\n", ptr_rise[j]);
            usleep(1 * 1000 * 1000);
        }

        for (j = 0; j < HEAP_MEM_NUM; ++j) {
            ptr_steady[j] = fun_alloc(1 * sizeof(str_arr));
            if (NULL == ptr_steady[j]) {
                 exit(-1);
            }
            printf("%p\n", ptr_steady[j]);
            usleep(1 * 1000 * 1000);
        }

        // ptr_rise: HEAP_FREE_FLAG为1时少释放一块内存
        for (j = 0; j < (HEAP_MEM_NUM - HEAP_FREE_FLAG); ++j) {
            if (ptr_rise[j] != NULL) {
                free(ptr_rise[j]);
                ptr_rise[j] = NULL;
            }
        }

        // ptr_steady: 正常释放
        for (j = 0; j < HEAP_MEM_NUM; ++j) {
            if (ptr_steady[j] != NULL) {
                free(ptr_steady[j]);
                ptr_steady[j] = NULL;
            }
        }
    }

    globalThreadFlag = 0;
    (void)pthread_join(tid, NULL);

    printf("%s finished\n", __FUNCTION__);
    return 0;
}
