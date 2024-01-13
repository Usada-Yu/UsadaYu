#ifndef __SAMPLE_H__
#define __SAMPLE_H__

#define C_OR_CXX        (1)             // 0：C；1：C++

#include <math.h>
#include <unistd.h>

#if C_OR_CXX
#include <iostream>
#include <stdexcept>
#include <string>
#include <csignal>
#endif

#if !C_OR_CXX
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#endif

bool oddEvenJudge(int num);

bool arrMaxNumFind(int *arr, int len, int *arr_max_num);

#if C_OR_CXX
int divide(int a, int b);
#endif

bool mutualPrime(int m, int n);
int smallestPrime(int m, int n);

void deathFunc();

void signalHandler();

#endif  // __SAMPLE_H__