#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define __CLOCK__           (0)
#define __TIMES__           (0)
#define __CLOCK_GETTIME__   (0)
#define __GETTIMEOFDAY__    (1)

// typedef long clock_t;
// typedef long int time_t;
// typedef long int suseconds_t;

#if __CLOCK__
/*-----------------------------------------------------------------------------------------------------------------*/
#include <time.h>
/*
clock_t clock(void);

(1) system()函数会开启一个子进程，但是clock()函数只会计算自身进程时间，无法计算子进程时间
(2) CLOCKS_PER_SEC是系统定义的宏，由GNU标准库定义为1000000.
(3) clock()函数不能区分用户态(user)和内核态(sys)
*/
int main() {

    long i = 2000;

    clock_t start_time, end_time;
    start_time = clock();

    while (i--) {
        system("cd");
    }

    end_time = clock();
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Total time of the parent process = %lf seconds\n", elapsed_time);

    return 0;
}
/*-----------------------------------------------------------------------------------------------------------------*/
#endif  // __CLOCK__

#if __TIMES__
/*-----------------------------------------------------------------------------------------------------------------*/
#include <sys/times.h>      // times()函数头文件
#include <unistd.h>         // sysconf(_SC_CLK_TCK); 获取内核计时频率
/*
clock_t times(struct tms *buf);

struct tms {

    clock_t tms_utime;      // 进程执行用户代码的时间
    clock_t tms_stime;      // 进程执行内核代码的时间
    clock_t tms_cutime;     // 子进程执行用户代码的时间
    clock_t tms_cstime;     // 子进程执行内核代码的时间
}
*/
int main() {

    long i = 2000;

    struct tms start_time, end_time;
    times(&start_time);

    while (i--) {
        system("cd");
    }

    times(&end_time);
    double elapsed_time = ((end_time.tms_utime + end_time.tms_stime + end_time.tms_cutime + end_time.tms_cstime) - 
                          (start_time.tms_utime + start_time.tms_stime + start_time.tms_cutime + start_time.tms_cstime)) /
                          (double)sysconf(_SC_CLK_TCK);

    printf("Total time = %lf seconds\n", elapsed_time);

    return 0;
}
/*-----------------------------------------------------------------------------------------------------------------*/
#endif  // __TIMES__

#if __CLOCK_GETTIME__
/*-----------------------------------------------------------------------------------------------------------------*/
#include <time.h>
/*
int clock_gettime(clockid_t clk_id, struct timespec *tp);

clockid_t clk_id:
(1) CLOCK_REALTIME: 标准POSIX实时时钟
(2) CLOCK_MONOTONIC: POSIX时钟，以恒定速率运行，不会复位和调整，取值和CLOCK_REALTIME一样
(3) CLOCK_PROCESS_CPUTIME_ID、CLOCK_THREAD_CPUTIME_ID: CPU中的硬件计时器中实现

struct timespec {

    time_t tv_sec;  // 秒
    long tv_nsec;   // 纳秒
};
*/
int main() {

    long i = 2000;

    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    while (i--) {
        system("cd");
    }

    clock_gettime(CLOCK_MONOTONIC, &end_time);
    double elapsed_time = (end_time.tv_sec - start_time.tv_sec) +
                          (end_time.tv_nsec - start_time.tv_nsec) / 1e9;

    printf("Total time = %lf seconds\n", elapsed_time);

    return 0;
}
/*-----------------------------------------------------------------------------------------------------------------*/
#endif  // __CLOCK_GETTIME__

#if __GETTIMEOFDAY__
/*-----------------------------------------------------------------------------------------------------------------*/
#include <sys/time.h>       // 区别于<sys/times.h>
/*
int gettimeofday(struct timeval *tv, struct timezone *tz);  // 第二个参数填NULL即可，不会用到
从1970年1月1号00:00(UTC)到当前的时间跨度

struct timeval {

    time_t      tv_sec;     // 秒
    suseconds_t tv_usec;    // 微秒
};
*/
int main() {

    long i = 2000;

    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);

    while (i--) {
        system("cd");
    }

    gettimeofday(&end_time, NULL);
    double elapsed_time = (end_time.tv_sec - start_time.tv_sec) +
                          (end_time.tv_usec - start_time.tv_usec) / 1e6;

    printf("Total time = %lf seconds\n", elapsed_time);

    return 0;
}
/*-----------------------------------------------------------------------------------------------------------------*/
#endif  // __GETTIMEOFDAY__