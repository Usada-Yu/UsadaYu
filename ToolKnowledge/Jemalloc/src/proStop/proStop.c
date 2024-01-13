/*
1.
此用例中，malloc函数为ptr分配内存后，ptr并没有被释放。
这个程序执行完成后会直接return，这种情况下使用jemalloc定位内存问题会相对容易。

2. 
(1) 以如下方式执行命令：
make clean
mkdir -p ./memAnlys/x86
chmod 777 ./memAnlys/x86
make mtype=stop -B
MALLOC_CONF=prof:true,prof_leak:true,lg_prof_sample:0,prof_final:true,\
prof_prefix:./memAnlys/x86/x86 ./bin/x86/lovely
(2) 上述环境变量中：
prof:true           开启后，剖析进程的内存申请操作
prof_leak:true      开启后，生成转储后的内存报告文件
lg_prof_sample:0    内存分配采样的间隔，2^0字节
prof_final:true     基于atexit函数转储进程结束时的内存情况
prof_prefix:./memAnlys/x86/x86  转储的heap文件前缀

3.
在./memAnlys/x86目录下会生成相应的.heap文件
ls ./memAnlys/x86
jeprof --show_bytes ./bin/x86/lovely ./memAnlys/x86/x86.*.0.f.heap --text --cum

4. 
(1) 若释放堆区内存，即HEAP_FREE_FLAG为1，那么打印如下：
Using local file ./bin/x86/lovely.
Using local file ./memAnlys/x86/x86.1757.0.f.heap.
Total: 81920 B
       0   0.0%   0.0%    81920 100.0% _GLOBAL__sub_I_eh_alloc.cc
   81920 100.0% 100.0%    81920 100.0% _GLOBAL__sub_I_eh_alloc.cc (inline)
       0   0.0% 100.0%    81920 100.0% __do_global_ctors_aux
       0   0.0% 100.0%    81920 100.0% __static_initialization_and_destruction_0 (inline)
这意味着内存是被完全释放的。
(2) 若不释放堆区内存，即HEAP_FREE_FLAG为0，那么打印如下：
Using local file ./bin/x86/lovely.
Using local file ./memAnlys/x86/x86.1858.0.f.heap.
Total: 110592 B
       0   0.0%   0.0%    81920  74.1% _GLOBAL__sub_I_eh_alloc.cc
   81920  74.1%  74.1%    81920  74.1% _GLOBAL__sub_I_eh_alloc.cc (inline)
       0   0.0%  74.1%    81920  74.1% __do_global_ctors_aux
       0   0.0%  74.1%    81920  74.1% __static_initialization_and_destruction_0 (inline)
       0   0.0%  74.1%    28672  25.9% __libc_start_main
       0   0.0%  74.1%    28672  25.9% _start
   28672  25.9% 100.0%    28672  25.9% fun_alloc
       0   0.0% 100.0%    28672  25.9% main
可以看到，main函数有残留的内存没有被释放，进一步可以定位到fun_alloc函数中；
说明fun_alloc函数中申请的内存没有被释放。
*/

#include "common.h"

#define HEAP_MEM_NUM        (6666)
#define HEAP_FREE_FLAG      (0)     // 堆区内存完全释放标志。0：不释放；1：释放

int main() {
    int i       = 0;
    int *ptr    = NULL;

    ptr = (int*)fun_alloc(sizeof(int) * HEAP_MEM_NUM);
    if (NULL == ptr) {
        exit(-1);
    }

    for (i = 0; i < HEAP_MEM_NUM; i++) {
        ptr[i] = i;
    }

#if HEAP_FREE_FLAG
    free(ptr);
    ptr = NULL;
#endif

    return 0;
}
