/********************************************************************************************
 * @name    os_info.c
 * 
 * @author  胡益华
 * 
 * @date    2024-01-09
 * 
 * @brief   常用的信息打印、错误打印等宏
********************************************************************************************/

#include "os_common.h"

#ifdef __OS_LINUX__
inline void _os_info_current_time(FILE *stream) {
    time_t      os_info_rawtime;
    char        os_info_time_buffer[9];
    struct tm   *os_info_timeinfo;

    time(&os_info_rawtime);
    os_info_timeinfo = localtime(&os_info_rawtime);
    strftime(os_info_time_buffer, sizeof(os_info_time_buffer), "%H:%M:%S", os_info_timeinfo);

    if (stderr == stream) { 
        fprintf(stderr, "%s", os_info_time_buffer);
    }
    else {
        fprintf(stdout, "%s", os_info_time_buffer); 
    }
}
    // __OS_LINUX__
#elif defined __OS_WINDOWS__
inline void _os_info_current_time(FILE *stream) {
    SYSTEMTIME  os_info_sys_time;
    char        os_info_time_buffer[9];

    GetLocalTime(&os_info_sys_time);
    sprintf(os_info_time_buffer, "%02d:%02d:%02d",
            os_info_sys_time.wHour, os_info_sys_time.wMinute, os_info_sys_time.wSecond);

    if (stderr == stream) { 
        fprintf(stderr, "%s", os_info_time_buffer);
    }
    else {
        fprintf(stdout, "%s", os_info_time_buffer); 
    }
}
#endif  // __OS_WINDOWS__
