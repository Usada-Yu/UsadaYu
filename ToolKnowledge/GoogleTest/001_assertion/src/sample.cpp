#include "sample.h"

// 偶数返回0，奇数返回1
bool oddEvenJudge(int num) {
    return (num % 2); 
}

// 找出数组中的最大值，成功返回true 1，失败返回false 0，结果返回arr_max_num
bool arrMaxNumFind(int *arr, int len, int *arr_max_num) {
    int i;
    int res = 0;

    if(1 > len || nullptr == arr) {
        return false;
    }

    res = arr[0];
    for(i = 1; i < len; ++i) {
        if(arr[i] > res) {
            res = arr[i];
        }
    }

    *arr_max_num = res;
    return true;
}

#if C_OR_CXX
int divide(int a, int b) {
    if (b == 0) {
        throw std::runtime_error("Division by zero");
    }
    return a / b;
}
#endif

// 判断互质数。即判断是否有除了1以外的公约数，没有则返回true
bool mutualPrime(int m, int n) {
    int i;
    for(i = 2; (i <= sqrt(n)) || (i <= sqrt(m)); ++i) {
        if((m % i == 0) && (m % i == 0)) {
            return false;
        }
    }
    return true;
}

// 找出除了1以外最小的公约数
int smallestPrime(int m, int n) {
    int i;
    for(i = 2; (i <= sqrt(n)) || (i <= sqrt(m)); ++i) {
        if((m % i == 0) && (m % i == 0)) {
            return i;
        }
    }
    return 1;
}

void deathFunc() {
#if C_OR_CXX
    std::cout << "The process will exit in 0.3 seconds" << std::endl;
    usleep(0.3 * 1000 * 1000);
    std::cerr << "Death func" << std::endl;
#else
    fputs("The process will exit in 0.3 seconds\n", stdout);
    usleep(0.3 * 1000 * 1000);
    fputs("Death func\n", stderr);
#endif

    exit(-1);    //非正常退出
}

// 函数给本进程发送一个SIGINT信号终止自己
void signalHandler() {
    std::cout << "The process pid[" << getpid() << "] will be killed in 1 second" << std::endl;
    usleep(1 * 1000 * 1000);

    kill(getpid(), SIGINT);
}
