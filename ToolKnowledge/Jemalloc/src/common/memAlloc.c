#include "common.h"

/********************************************************************************************
 * @brief   申请堆区内存，类似calloc函数
 * @param   size: 申请内存的大小(字节)
********************************************************************************************/
void* fun_alloc(int size) {
    void *ptr;

    ptr = (void*)malloc(size);
    if (NULL == ptr) {
        printf("Malloc fail\n");
        return NULL;
    }

    memset(ptr, 0, size);
    return ptr;
}
