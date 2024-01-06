#ifndef __COMMON_H__
#define __COMMON_H__

#if defined(__linux__)
#define __ENV_OS__      (1)
#elif defined(_WIN32)
#define __ENV_OS__      (0)
#endif

#if __ENV_OS__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#else
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#endif

#endif