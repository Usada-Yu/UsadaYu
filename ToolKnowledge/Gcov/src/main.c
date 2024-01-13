/*
要生成覆盖率html格式报告，可以运行如下命令：
make clean
make -B
./bin/x86/lovely
gcovr -r ./ \
--gcov-ignore-parse-errors \
--exclude-unreachable-branches \
--print-summary \
--html-details=./coverage_report/x86_coverage_repoet.html
*/

#include <stdio.h>

#define __LOOP_NUM          (8)
#define INFO_PRINT(var)     printf("Line: %d, "#var" = %d\n", __LINE__, var);

// 调用此函数
void func_valid() {
    int var = 10;
    INFO_PRINT(var);
}

// 不调用此函数
void func_invalid() {
    int var = 10;
    INFO_PRINT(var);
}

int main() {
    int i = 0;

    for (i = 0; i < __LOOP_NUM; i++) {
        switch (i) {
            case 1:
                INFO_PRINT(i);
                break;
            case 4:
                INFO_PRINT(i);
                break;
            case 10:
                INFO_PRINT(i);
                break;  
            default:
                break;
        }

        if (i == __LOOP_NUM + 1) {
            INFO_PRINT(i);
        }
        else {
            INFO_PRINT(i);
        }

        // 此类if模块不会被覆盖率检测，覆盖率报告对此类模块呈现为白色
        if (0 == 1) {
            INFO_PRINT(i);
        }
    }

    func_valid();

    return 0;
}
