#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

#define __NORMAL_EXIT__     (0)
#define __PTHREAD_EXIT__    (0)
#define __PTHREAD_JOIN__    (0)
#define __PTHREAD_CANCEL__  (0)
#define __PTHREAD_DETACH__  (1)

// typedef unsigned long int pthread_t;     // 线程id号，用%lu打印

/*
int pthread_create(
    pthread_t *restrict tidp,               // 指向线程标识符的指针，用pthread_t创建
    const pthread_attr_t *restrict attr,    // 设置线程属性，默认为NULL
    void *(*start_rtn)(void *),             // 线程运行函数的起始地址，线程被创建就会执行
    void *restrict arg                      // 运行函数的参数。必须强制转换为void类型进行传递；没有传递参数则使用NULL
);
成功返回0；失败返回非0

void pthread_exit(void *retval);            // 退出当前线程，不会影响子线程或父线程
*/

void yuThreadFunc(void *ptr) {

    usleep(2 * 1000 * 1000);        // 挂起2s

    int* utc_gap_sec = (int*)(ptr);

    if (*utc_gap_sec % 2 == 0)
        printf("UsadaYu\n");
    else
        printf("Rurudo\n");

    pthread_exit("Yu thread exit");
    int *pr = NULL; *pr = 10;       // 此段错误不会被执行
}

#if __NORMAL_EXIT__
/*-----------------------------------------------------------------------------------------------------------------*/
/*
以下情况，子线程yuThread被挂起的2s内，主线程通过return 0结束，
那么当整个进程终止的时候，所有的线程(即主线程和所有子线程)都会被强行结束。
所以这种情况下看不到yuThreadFunc函数的打印信息
*/
int main() {

    pthread_t   yuThread;
    struct      timeval utc_gap;
    gettimeofday(&utc_gap, NULL);

    pthread_create(&yuThread, NULL, (void*)yuThreadFunc, (void*)(&utc_gap.tv_sec));

    return 0;
}
/*-----------------------------------------------------------------------------------------------------------------*/
#endif  // __NORMAL_EXIT__

#if __PTHREAD_EXIT__
/*-----------------------------------------------------------------------------------------------------------------*/
/*
以下情况，子线程yuThread被挂起的2s内，主线程通过pthread_exit(NULL)结束，
此时进程并不会立即终止，而是等待子线程结束才会终止。
*/
int main() {

    pthread_t   yuThread;
    struct      timeval utc_gap;
    gettimeofday(&utc_gap, NULL);

    pthread_create(&yuThread, NULL, (void*)yuThreadFunc, (void*)(&utc_gap.tv_sec));

    pthread_exit(NULL);         // 仅结束当前线程，即主线程，子线程不受影响
}
/*-----------------------------------------------------------------------------------------------------------------*/
#endif

#if __PTHREAD_JOIN__
/*-----------------------------------------------------------------------------------------------------------------*/
/*
int pthread_join(pthread_t thread, void **retval);  // retval用于存储被等待线程的返回值。pthread_exit或return的值都能接收
阻塞当前线程，并等待一个线程的结束
成功返回0；失败返回非0
*/
int main() {

    pthread_t   yuThread;
    char*       thread_exit;
    struct      timeval utc_gap;
    gettimeofday(&utc_gap, NULL);

    pthread_create(&yuThread, NULL, (void*)yuThreadFunc, (void*)(&utc_gap.tv_sec));

    pthread_join(yuThread, (void**)&thread_exit);
    printf("%s\n", thread_exit);
}
/*-----------------------------------------------------------------------------------------------------------------*/
#endif  // __PTHREAD_JOIN__

#if __PTHREAD_CANCEL__
/*-----------------------------------------------------------------------------------------------------------------*/
/*
int pthread_cancel(pthread_t tid);
成功返回0；失败返回非0
向目标tid线程发送Cancel信号，此信号名为Cancel，但是对Cancel信号具体的处理方式由目标tid线程自行处理；
如果目标tid线程对Cancel信号不做处理，默认未终止tid线程。

以下情况，子线程yuThread被挂起的2s内，主线程只挂起了1s，并通过pthread_cancel(yuThread)强行结束了子线程，
所以这种情况下看不到yuThreadFunc函数的打印信息
*/
int main() {

    pthread_t   yuThread;
    struct      timeval utc_gap;
    gettimeofday(&utc_gap, NULL);

    pthread_create(&yuThread, NULL, (void*)yuThreadFunc, (void*)(&utc_gap.tv_sec));

    usleep(1 * 1000 * 1000);
    printf("%d\n", pthread_cancel(yuThread));
    return 0;
}
/*-----------------------------------------------------------------------------------------------------------------*/
#endif  // __PTHREAD_CANCEL__

#if __PTHREAD_DETACH__
/*-----------------------------------------------------------------------------------------------------------------*/
/*
int pthread_detach(pthread_t tid);
成功返回0；失败返回非0
将目标tid线程与主控线程分离(线程共享的资源依然是共享的，不要混淆)，使目标tid线程退出状态不由其它线程获取，
而变为目标tid线程结束后主动释放资源，因此，这样避免了僵尸线程的产生。
不过，因为目标tid线程和主控线程分离了，所以主控线程不可以再调用pthread_join()终止这个tid子线程，
否则会返回EINVAL(22)错误

实际上，通过pthread_create()函数中的第二个线程属性参数也可以设置线程分离
*/
int main() {

    pthread_t   yuThread;
    struct      timeval utc_gap;
    gettimeofday(&utc_gap, NULL);

    pthread_create(&yuThread, NULL, (void*)yuThreadFunc, (void*)(&utc_gap.tv_sec));
    pthread_detach(yuThread);

#if 0
    char*       thread_exit;
    printf("%d\n", pthread_join(yuThread, (void**)&thread_exit));   // 打印22
#endif

    pthread_exit(NULL);
}
/*-----------------------------------------------------------------------------------------------------------------*/
#endif  // __PTHREAD_DETACH__
