/********************************************************************************************
 * @brief   GoogleTest基础断言(assertion)记录
 * 
 * @details GoogleTest提供的断言可以用于函数、表达式等测试
 * 
 * @ref     https://google.github.io/googletest/reference/assertions.html
********************************************************************************************/
#include "sample.h"
#include "gtest/gtest.h"

/********************************************************************************************
 * @brief   单元测试样例
 * 
 * @details
 * (1) 注意Gtest需要调用RUN_ALL_TESTS运行测试用例。
 *     当前RUN_ALL_TESTS在main函数中调用
********************************************************************************************/
#if 0
TEST(oddEvenJudgeSuite, oddEvenJudgeTestCase) {
    EXPECT_EQ(1, oddEvenJudge(-10));
    EXPECT_EQ(1, oddEvenJudge(-1));
    EXPECT_EQ(0, oddEvenJudge(0));
    EXPECT_EQ(1, oddEvenJudge(1));
    EXPECT_EQ(0, oddEvenJudge(10));
}
#endif

/********************************************************************************************
 * @brief   testing::AssertionResult的使用
 * 
 * @details
 * 使用testing::AssertionResult可以自定义函数，一般在此函数中指出详细的错误信息。
 * 就像通常的函数一样，它也可以声明到.h文件中。
 * 不过尽量把它声明和定义在测试文件中，保证测试用例代码不影响源代码。
 * testing::AssertionResult定义的函数必须要有返回值。
 * 返回值类型类似bool，但不是bool，而是Gtest中特有的，返回其它类型编译会报错
 * 
 * testing::AssertionResult定义的函数返回值类型如下：
 * (1) testing::AssertionSuccess()
 *     类似于bool中的true(1), std::cout结果是1
 * (2) testing::AssertionFailure()
 *     类似于bool中的false(0), std::cout结果是0
********************************************************************************************/
#if 0
// testing::AssertionResult定义的函数和正常函数一样，形参可以修改，并且可以定义在其它文件
testing::AssertionResult elemChange(int *num) {
    *num = (*num) + 10;
    return testing::AssertionSuccess();
}
TEST(elemChangeSuite, elemChangeTestCase) {
    int num = 5;
    std::cout << "Before testing::AssertionSuccess elemChange() function num = " << num << std::endl;
    EXPECT_TRUE(elemChange(&num));
    std::cout << "After testing::AssertionSuccess elemChange() function num = " << num << std::endl;
}

// 判断是否是偶数，偶数返回testing::AssertionSuccess()；奇数返回testing::AssertionFailure()
testing::AssertionResult IsEven(int n) {
    if ((n % 2) == 0) {
        return testing::AssertionSuccess();                     // 正确时，一般不追加正确信息。
    }
    else {
        return testing::AssertionFailure() << n << " is odd";   // 出错时，可以使用 << 追加详细错误信息
    }
}
TEST(topicTest, TopicTest) {
    EXPECT_EQ(1, IsEven(6));
    EXPECT_TRUE(IsEven(6));
    EXPECT_TRUE(IsEven(sqrt(9)));   // 不通过测试，显示自定义失败的错误信息
/*
EXPECT_TRUE(IsEven(sqrt(9)))报错格式打印如下：
    Value of: IsEven(sqrt(9))
    Actual: false (3 is odd)
    Expected: true
*/
}
#endif

/********************************************************************************************
 * @brief   成功与失败的判断
 * 
 * @details
 * (1) SUCCEED()            产生成功，不产生输出，官方可能在未来改进此断言
 * (2) FAIL()               产生断言失败，并终止当前测试用例，其它测试用例和测试套件的执行不受影响
 * (3) ADD_FAILURE()        产生断言失败，不终止当前测试用例
 * (4) ADD_FAILURE_AT()     在特定的文件和行号产生失败，不终止测测试用例
 * (5) ASSERT_EQ()          ASSERT_*系列断言，失败时终止当前测试用例，其它测试用例和测试套件的执行不受影响
 * (6) EXPECT_EQ()          EXPECT_*系列断言，失败时不终止当前测试用例
********************************************************************************************/
#if 0
TEST(succeedAndFailSuite, succeedAndFailTestCase1) {
    switch(5) {
        case 1:
            SUCCEED() << "Success()";                   // 此断言没有任何作用，无论如何都没有任何输出
            break;
        case 2:
            FAIL() << "Fail(), stop";                   // 使用FAIL()出错后用例不会继续运行，相当于ASSERT_*
            break;    
        case 3:
            ADD_FAILURE() << "ADD_FAILURE(), continue"; // 使用ADD_FAILURE()出错后会继续运行，相当于EXPECT_*
            break;
        case 4:
            // 使./ut_test.cpp文件的的第3行出错。
            // 一般来说，如果判断某处发生错误是因为某文件某位置，可以用此断言
            ADD_FAILURE_AT(__FILE__, 3) << __FILE__ << " line 3 may have an error";
            break;
        case 5:
            ASSERT_EQ(0, oddEvenJudge(1)) << "ASSERT_EQ, stop";     // ASSERT_*类断言出错后将终止当前测试用例
            break;
        case 6:
            EXPECT_EQ(0, oddEvenJudge(1)) << "EXPECT_EQ, continue"; // EXPECT_*类断言出错后不会终止当前测试用例
            break;
    }

    FAIL() << "succeedAndFailTestCase1";    // 此断言用于判断同一测试用例内，前面的断言可能会影响后面言的执行
}

TEST(succeedAndFailSuite, succeedAndFailTestCase2) {
    FAIL() << "succeedAndFailTestCase2";    // 此断言用于证明不同测试用例，前面终止的测试用例不会影响其它测试套件以及测试用例
}
#endif

/********************************************************************************************
 * @brief   数值的大小判断与比较
 * 
 * @details
 * (1) EXPECT_TRUE()        为true通过 
 * (2) EXPECT_FALSE()       为false通过
 * (3) EXPECT_EQ(a, b)      a=b通过
 * (4) EXPECT_NE(a, b)      a≠b通过
 * (5) EXPECT_LT(a, b)      a<b通过 
 * (6) EXPECT_GT(a, b)      a>b通过
 * (7) EXPECT_LE(a, b)      a<=b通过
 * (8) EXPECT_GT(a, b)      a>=b通过
********************************************************************************************/
#if 0
TEST(numberCompareSuite, numberCompareTestCase) {
    int *arrMaxNumFindArr1      = nullptr;
    int arrMaxNumFindArr2[]     = {3, 0, 7, 1, -4};
    int max_res1;
    
    EXPECT_FALSE(arrMaxNumFind(arrMaxNumFindArr1, 1, &max_res1));
    EXPECT_FALSE(arrMaxNumFind(arrMaxNumFindArr2, 0, &max_res1));
    EXPECT_TRUE(arrMaxNumFind(arrMaxNumFindArr2, sizeof(arrMaxNumFindArr2) / sizeof(arrMaxNumFindArr2[0]), &max_res1));
    EXPECT_EQ(7, max_res1) << "Function arrMaxNumFind error";
}
#endif

/********************************************************************************************
 * @brief   字符串的比较
 * 
 * @details
 * (1) EXPECT_STREQ(str1, str2)         字符串str1=str2通过，不忽略大小写
 * (2) EXPECT_STRNE(str1, str2)         字符串str1≠str2通过，不忽略大小写
 * (3) EXPECT_STRCASEEQ(str1, str2)     字符串str1=str2通过，忽略大小写
 * (4) EXPECT_STRCASENE(str1, str2)     字符串str1≠str2通过，忽略大小写
********************************************************************************************/
#if 0
TEST(stringCompareSuite, stringCompareTestCase) {
    EXPECT_STREQ("UsadaYu", "usadayu");         // 不忽略大小写，字符串不相等，不通过
    EXPECT_STRCASEEQ("UsadaYu", "usadayu");     // 忽略大小写，字符串相等，通过
}
#endif

/********************************************************************************************
 * @brief   浮点数的比较
 * 
 * @details
 * (1) EXPECT_FLOAT_EQ(a, b)            float类a=b通过，浮点数判断是精度范围内，默认4 ULPs
 * (2) EXPECT_DOUBLE_EQ(a, b)           double类a=b通过，浮点数判断是精度范围内，默认4 ULPs
 * (3) EXPECT_NEAR(a, b, error)         a和b差值的绝对值小于error通过，error<0则必出错。a和b可以是整型或浮点
********************************************************************************************/
#if 0
TEST(floatCompareSuite, floatCompareTestCase) {
    EXPECT_DOUBLE_EQ(1.33333333333333333, 1.33333333333333334);     // 浮点数差值在误差范围内，通过
    EXPECT_DOUBLE_EQ(1.3333333, 1.3333334);                         // 浮点数差值超过误差范围，不通过
    EXPECT_NEAR(8, 5, 5);                                           // error为5，大于|8 - 5|，通过
    EXPECT_NEAR(3, 3, 0);                                           // 比较整型，error=0可以通过
    EXPECT_NEAR(3.1, 3.1, 0);                                       // 比较浮点，error=0可以通过
    EXPECT_NEAR(3, 3, -2);                                          // error设置为负必出错，不通过
}
#endif

/********************************************************************************************
 * @brief   异常处理判断。C++中特有的抛出错误类型，C语言中没有此特性
 * 
 * @details
 * (1) EXPECT_THROW(status1, status2)
 *     函数抛出异常，且status1=status2则通过；
 *     若函数不抛出异常，或抛出异常后status1≠status2则不通过
 * (2) EXPECT_NO_THROW(status)          只要抛出任何异常，就不通过；没有抛出异常通过
 * (3) EXPECT_ANY_THROW(status)         只要抛出任何异常，就通过；没有抛出异常不通过
********************************************************************************************/
#if C_OR_CXX & (0)
TEST(throwExceptionSuite, throwExceptionTestCase) {
    EXPECT_THROW(divide(10, 0), std::runtime_error);    // 抛出了指定的std::runtime_error异常，通过
    EXPECT_NO_THROW(divide(10, 1));                     // 没有抛出异常，通过
    EXPECT_NO_THROW(divide(10, 0));                     // 抛出了异常，不通过
    EXPECT_ANY_THROW(divide(10, 0));                    // 抛出了异常，通过
}
#endif

/********************************************************************************************
 * @brief   EXPECT_PRED。判断指定函数传入相应参数后的返回值是否为true，必须是外部函数，不能是testing::AssertionResult定义的函数
 * 
 * @details
 * (1) EXPECT_PRED1(function, var1)         为true通过，1表示function有一个形参，var1为参数
 * (2) EXPECT_PRED2(function, var1, var2)   为true通过，2表示function有两个形参，var1和var2为参数
 * (3) 以此类推
********************************************************************************************/
#if 0
TEST(predicateSuite, predicateTestCase1) {
    int mutualPrimeArr[] = {3, 4, 8};

    EXPECT_PRED2(mutualPrime, mutualPrimeArr[0], mutualPrimeArr[1]);    // 3和4互为质数，通过
    EXPECT_TRUE(mutualPrime(mutualPrimeArr[1], mutualPrimeArr[2]));     // 4和8不互为质数，不通过，提供简略的错误信息
    EXPECT_PRED2(mutualPrime, mutualPrimeArr[1], mutualPrimeArr[2]);    // 4和8不互为质数，不通过，提供详细的错误信息

/*
EXPECT_TRUE报错格式打印如下：
Value of: mutualPrime(mutualPrimeArr[1], mutualPrimeArr[2])
  Actual: false
Expected: true

EXPECT_PRED报错格式打印如下：
mutualPrime(mutualPrimeArr[1], mutualPrimeArr[2]) evaluates to false, where
mutualPrimeArr[1] evaluates to 4
mutualPrimeArr[2] evaluates to 8
*/
}
#endif

/********************************************************************************************
 * @brief   EXPECT_TRUE和EXPECT_PRED的异同
 * 
 * @details
 * 相同点：
 * (1) 两个断言都提供了对括号内情况的判断。都是以bool类型作为评判标准
 * (2) 两个断言都是true通过，false不通过
 * 不同点：
 * (1) EXPECT_TRUE在出错时提供的错误信息比较简略
 * (2) EXPECT_PRED在出错时提供的错误信息比较详细
 * (3) EXPECT_TRUE中可以使用Gtest testing::AssertionResult定义的函数
 * (4) EXPECT_PRED不可以使用Gtest testing::AssertionResult定义的函数
 * (5) EXPECT_TRUE测试的函数(非testing::AssertionResult定义)可以涉及形参的修改，参数可读可写
 * (6) EXPECT_PRED测试的函数(非testing::AssertionResult定义)不能涉及形参的修改，参数是只读的
********************************************************************************************/
#if 0
TEST(predicateSuite, predicateTestCase2) {
    int arrMaxNumFindArr3[] = {3, 4, 8};
    int max_res2;
    #if 1
        // 编译会报错，EXPECT_PRED后max_res2涉及形参修改
        EXPECT_PRED3(arrMaxNumFind, arrMaxNumFindArr3, sizeof(arrMaxNumFindArr3) / sizeof(arrMaxNumFindArr3[0]), &max_res2);
    #else
        // 编译不会报错
        EXPECT_TRUE(arrMaxNumFind(arrMaxNumFindArr3, sizeof(arrMaxNumFindArr3) / sizeof(arrMaxNumFindArr3[0]), &max_res2));
    #endif
}
#endif

/********************************************************************************************
 * @brief   EXPECT_PRED_FORMAT。判断指定函数传入相应参数后的返回值是否为true，必须是testing::AssertionResult定义的函数，不能是外部函数
 * 
 * @details
 * (1) EXPECT_PRED_FORMAT1(gtest_function, var1)
 *     为testing::AssertionSuccess()通过，1表示gtest_function有一个形参，var1为参数
 * (2) EXPECT_PRED_FORMAT2(gtest_function, var1, var2)
 *     为testing::AssertionSuccess()通过，2表示gtest_function有两个形参，var1和var2为参数
 * (3) 以此类推
********************************************************************************************/
#if 0
testing::AssertionResult primeJug(const char *m_expr, const char *n_expr, int m, int n) {
    if(mutualPrime(m, n)) {
        return testing::AssertionSuccess();
    }
    else {
        return testing::AssertionFailure() << m_expr << " and " << n_expr
        << " (" << m << " and " << n << ") are not mutually prime, "
        << "as they have a common divisor " << smallestPrime(m, n);
    }
}
TEST(predicateFormatSuite, predicateFormatTestCase1) {
    int primeJugArr1[] = {3, 4, 8};

    EXPECT_PRED_FORMAT2(primeJug, primeJugArr1[0], primeJugArr1[1]);    // 通过
    EXPECT_PRED_FORMAT2(primeJug, primeJugArr1[1], primeJugArr1[2]);    // 不通过，并打印自定义错误信息

/*
上述EXPECT_PRED_FORMAT报错格式如下：
primeJugArr1[1] and primeJugArr1[2] (4 and 8) are not mutually prime, as they have a common divisor 2
*/
}
#endif

/********************************************************************************************
 * @brief   关于EXPECT_PRED_FORMAT、EXPECT_PRED、EXPECT_TRUE
 * 
 * @details
 * EXPECT_PRED_FORMAT使用注意事项：
 * (1) EXPECT_PRED_FORMAT测试函数时，函数必须定义变量名称，
 *     如testing::AssertionResult exam(const char *elem_name, int elem)
 *     const char *elem_name不能遗漏，否则会报错
 * (2) EXPECT_PRED_FORMAT测试的函数只能是用testing::AssertionResult定义的，
 *     如果测试外部非testing::AssertionResult定义函数，即使返回值是bool，也会报错。
 *     testing::AssertionSuccess()打印值是1，但不等同于bool的true
 * 
 * EXPECT_PRED和EXPECT_PRED_FORMAT的异同
 * 相同点：
 * (1) 两个断言都是根据提供的函数和形参测试错误
 * (2) 两个断言都可以根据函数参数数量动态地扩展
 * 不同点：
 * (1) EXPECT_PRED只能用于非testing::AssertionResult定义的外部函数测试检验
 * (2) EXPECT_PRED_FORMAT只能用于testing::AssertionResult定义的内部函数测试检验
 * (3) EXPECT_PRED不能修改函数(非testing::AssertionResult定义)形参
 * (4) EXPECT_PRED_FORMAT可以修改函数(testing::AssertionResult定义)形参
 * 
 * EXPECT_TRUE和EXPECT_PRED_FORMAT的异同
 * 相同点：
 * (1) 两个断言都可以修改函数(testing::AssertionResult定义)形参
 * 不同点：
 * (1) EXPECT_TRUE()不但可以用于testing::AssertionResult定义的函数，也可以用于非testing::AssertionResult定义的函数。
 * 并且无论是内部函数还是外部函数，EXPECT_TRUE()都可以修改函数形参
 * (2) EXPECT_PRED_FORMAT*()仅适用于testing::AssertionResult定义的函数
********************************************************************************************/
#if 0
testing::AssertionResult formatElemChange(const char *num_expr, int *num) {
    *num = (*num) + 10;
    std::cout << "**(" << num_expr << "): ";      // 输出字符串"**(&num): "
    return testing::AssertionSuccess();
}
TEST(predicateFormatSuite, predicateFormatTestCase2) {
    int num = 5;

    // EXPECT_PRED_FORMAT和EXPECT_TRUE都可以修改函数形参
    #if 1
        EXPECT_PRED_FORMAT1(formatElemChange, &num);
    #else
        EXPECT_TRUE(formatElemChange("&num", &num));
    #endif
    std::cout << num << std::endl;
}
#endif

/********************************************************************************************
 * @brief   死亡测试
 * 
 * @details
 * (1) EXPECT_DEATH(function, info)
 *     测试函数输出对应错误信息并引发进程异常终止退出则通过。
 *     捕获的信息需要是包含关系。如错误信息为abcd，那么info为abcd通过，为abc通过，为abd不通过
 * (2) EXPECT_DEATH_IF_SUPPORTED(function, info)
 *     先判断运行环境是否支持死亡测试，若支持，则效果和EXPECT_DEATH一样；若不支持，则跳过本次死亡测试
 * (3) EXPECT_DEBUG_DEATH(function, info)
 *     debug环境下，此断言效果和EXPECT_DEATH()断言一样；非debug环境，则只执行function，不做死亡测试
 * (4) EXPECT_EXIT(function, error_code, info)
 *     根据错误码error_code判断进程终止时是否符合退出码或信号，符合错误码则测试通过。
 *     官方提供testing::ExitedWithCode()和testing::KilledBySignal()两种error_code形式
********************************************************************************************/
#if 0
TEST(deathSuiteDeathTest, deathTestCase1) {
    EXPECT_DEATH(deathFunc(), "Death func");                // 函数调用exit()退出进程，并且有相关错误信息被捕获，通过
    EXPECT_DEATH_IF_SUPPORTED(deathFunc(), "Death func");   // 在支持死亡测试的环境下，效果和EXPECT_DEATH一样，通过
    EXPECT_DEBUG_DEATH(deathFunc(), "Death func");          // 在debug条件下触发死亡测试，通过
    EXPECT_EXIT(exit(0), testing::ExitedWithCode(0), ".*"); // 进程正常退出，且进程退出码符合指定退出码，错误信息也符合，通过
}
#endif

/********************************************************************************************
 * @brief   EXPECT_DEATH使用注意事项
 * 
 * @details
 * EXPECT_DEATH(function, info)，通过此断言需要满足以下条件：
 * (1) 需要满足被测试函数会引发进程终止，并且必须是错误终止而不是正常终止
 * (2) 此断言必须填写info，info表示测试函数中向错误输出输出的信息
 * 
 * 关于错误信息：
 * (1) C语言错误输出一般为stdout，可以用fputs、fprintf等实现；C++可以用std::cerr实现像错误输出输出信息
 * (2) 关于info信息，实际上并不需要完全匹配。只需要字符串是错误输出字符串的一部分即可。
 *     如错误信息为abcd，那么info为abcd可以通过，为abc可以通过，为abd不可以通过。
 *     info中可以使用通配符".*"匹配任意字符串
********************************************************************************************/
#if C_OR_CXX & (0)
void death_func_info() {
    switch(1) {
        case 1:
            std::cerr << "Death func information" << std::endl; // 信息匹配且是错误输出，通过
            exit(-1);
        case 2:
            std::cout << "Death func information" << std::endl; // 信息匹配，但不是错误输出，不通过
            exit(-1);
        case 3:
            std::cerr << "death func information" << std::endl; // 是错误输出，但错误信息不匹配，不通过
            exit(-1);
        case 4:
            std::cerr << "Death func information" << std::endl; // 信息匹配且是错误输出，但没有终止进程，不通过
            break;
        case 5:
            std::cerr << "Death func information" << std::endl; // 信息匹配且是错误输出，进程有终止但不是异常终止，不通过
            exit(0);
    }
}
TEST(deathSuiteDeathTest, deathTestCase2) {
    EXPECT_DEATH(death_func_info(), "D.*ath fu");   // 错误信息用通配符".*"匹配字符"a"，匹配后指定错误信息是原错误信息的一部分，通过
    EXPECT_DEATH(death_func_info(), "Death fu");    // 错误信息用普通字符串，指定错误信息是原错误信息的一部分，通过
}
#endif

/********************************************************************************************
 * @brief   死亡测试使用注意事项
 * 
 * @details
 * (1) 死亡测试应在单线程上下文中运行。否则可能会有警告
 * (2) 死亡测试套件名称末尾尽量使用DeathTest，以DeathTest结尾的测试套件会在所有其他套件之前运行测试。
 *     但不使用DeathTest结尾命名的测试套件也不会出错，只是会按正常顺序执行而不会先被执行。
 * 
 * 关于错误信息：
 * (1) C语言错误输出一般为stdout，可以用fputs、fprintf等实现；C++可以用std::cerr实现像错误输出输出信息
 * (2) 关于info信息，实际上并不需要完全匹配。只需要字符串是错误输出字符串的一部分即可。
 *     如错误信息为abcd，那么info为abcd可以通过，为abc可以通过，为abd不可以通过。
 *     info中可以使用通配符".*"匹配任意字符串
********************************************************************************************/
#if 0
// 如下，死亡测试因为测试套件名称以"DeathTest"结尾，所以会比deathSuiteNormalTest先运行，打印错误信息
TEST(deathSuiteNormalTest, deathNormalTestCase) {
    EXPECT_EQ(3, 5);                        // 不通过
}
TEST(deathSuiteDeathTest, deathTestCase3) {
    EXPECT_DEATH(exit(-1), "information");  // 错误信息不匹配，不通过
}
#endif

/********************************************************************************************
 * @brief   EXPECT_DEATH_IF_SUPPORTED使用注意事项 
 * 
 * @details
 * 假设某个嵌入式系统没有处理异常的能力，系统环境不满足死亡测试的条件。
 * 那么此断言在这个系统中将不会执行死亡测试。
 * 如果使用EXPECT_DEATH，那么无论环境如何，都会强执行死亡测试。
 * 显然EXPECT_DEATH_IF_SUPPORTED()相对温和。
 * 
 * 所以如果需要死亡测试，那么尽量使用EXPECT_DEATH_IF_SUPPORTED而不是EXPECT_DEATH。
 * 在环境允许时，EXPECT_DEATH_IF_SUPPORTED和EXPECT_DEATH完全相同，参考EXPECT_DEATH用法即可
********************************************************************************************/
#if 0
// 此断言效果演示需要特定条件，故跳过
#endif

/********************************************************************************************
 * @brief   关于EXPECT_EXIT通过testing::ExitedWithCode()指定错误码
 * 
 * @details
 * (1) 使用testing::ExitedWithCode()指定函数退出状态码，并且希望通过测试，必须确保状态码>= 0；
 *     否则无论退出状态码是否等于指定状态码，测试都不会通过
 * (2) 如果函数退出的状态是负数func_error，那么testing::ExitedWithCode()指定错误码时为256 + (func_error)；
 *     举例说明，若函数退出时错误码是-2，那么256 + (-2) = 254，那么就指定testing::ExitedWithCode(254)，
 *     这样死亡测试就能通过。
 * (3) 死亡测试的错误码默认隐式转换为int类型。
********************************************************************************************/
#if 0
TEST(deathSuiteDeathTest, deathTestCase3) {
    EXPECT_EXIT(exit(5), testing::ExitedWithCode(3), ".*");     // 退出状态码 > 0，但和error_code不符，不通过
    EXPECT_EXIT(exit(5), testing::ExitedWithCode(5), ".*");     // 退出状态码 > 0，且和error_code相等，通过
    EXPECT_EXIT(exit(0), testing::ExitedWithCode(0), ".*");     // 退出状态码 = 0，且和error_code相等，通过
    EXPECT_EXIT(exit(-1), testing::ExitedWithCode(-1), ".*");   // 退出状态码和error_code相等，但小于0，不通过

    EXPECT_EXIT(exit(-5), testing::ExitedWithCode(251), ".*");  // 退出状态码 = error_code - 256. 通过
}
#endif

/********************************************************************************************
 * @brief   关于EXPECT_EXIT通过testing::KilledBySignal()指定错误码
 * 
 * @details
 * (1) 使用testing::KilledBySignal()指定函数退出状态码，并且希望通过测试，必须保证进程是因为被给定的信号终止的。
 *     举例说明，指定testing::KilledBySignal(2)，那么需要函数是因为收到2信号，即SIGINT信号而终止。
********************************************************************************************/
#if 0
TEST(deathSuiteDeathTest, deathTestCase4) {
    EXPECT_EXIT(signalHandler(), testing::KilledBySignal(SIGKILL), ".*");   // 发送的信号和终止进程的信号不同，不通过
    EXPECT_EXIT(signalHandler(), testing::KilledBySignal(SIGINT), ".*");    // 发送的信号和终止进程的信号相同，通过
}
#endif

/********************************************************************************************
 * @brief   Gtest主函数
 * 
 * @details
 * 调用RUN_ALL_TESTS即表示运行所有测试用例。
 * 调用RUN_ALL_TESTS前必须调用testing::InitGoogleTest()初始化
********************************************************************************************/
GTEST_API_ int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
