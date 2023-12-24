/********************************************************************************************
 * @brief   GoogleTest的一些高级用法
 * 
 * @details 主要是fixture、错误定位、参数化测试等方面的一些记录
 * 
 * @ref     https://google.github.io/googletest/advanced.html
********************************************************************************************/
#include <vector>
#include <set>
#include <tuple>
#include <thread>
#include "sample.h"
#include "gtest/gtest.h"
#include "gtest/gtest-spi.h"

#define CLASS_SET_TEAR_COUNT()                                  \
    void SetUp() override {                                     \
        static int setUpCount = 1;                              \
        std::cout << __FUNCTION__ << " count: "                 \
        << setUpCount++ << std::endl;                           \
    }                                                           \
    void TearDown() override {                                  \
        static int tearDownCount = 1;                           \
        std::cout << __FUNCTION__ << " count: "                 \
        << tearDownCount++ << std::endl;                        \
    }

/********************************************************************************************
 * @brief   testing::StaticAssertTypeEq<T1, T2>()的类型检测
 * 
 * @details
 * (1) C++中，可能会用到模板特性。如果需要对变量类型做判断，可以使用此函数判断T1和T2类型是否相同。
 * (2) 对于C语言而言，此函数可能实用性不高，不过它对C语言是支持的。
 * (3) 如过判断T1和T2类型不同，会在编译阶段直接报错，而不是在程序运行时打印错误。
 * (4) testing::StaticAssertTypeEq<T1, T2>()是一个函数而不是宏定义，不可以在后续用符号<<追加错误信息。
********************************************************************************************/
#if 0
template <typename T>
class assertTypeEqual {
    public:
        static void typeEq() {
            testing::StaticAssertTypeEq<int, T>();  // 测试模板类型是否为int类型
        }

        static void infoPrt() {
            std::cout << __FUNCTION__ << std::endl;
        }
};

class assertTypeEqualFunction {
    public:
        void assertTypeEqualTestFunc1() {
            assertTypeEqual<bool>::infoPrt();   // bool类型，不调用类型判断，即使类型错误编译也不会报错
        }

        void assertTypeEqualTestFunc2() {
            assertTypeEqual<int>::typeEq();     // int类型，调用类型判断，类型匹配，编译不会报错
        }

        #if 0
        void assertTypeEqualTestFunc3() {
            assertTypeEqual<bool>::typeEq();    // bool类型，调用类型判断，类型不匹配，编译报错
        }
        #endif
};

// C语言中，如果某变量类型不确定或函数返回类型不确定也可以通过此函数测试，不过一般实用性不高
static int assertTypeEqualCFunction() {
    return 0;
}
void assertTypeEqualCTest() {
    int     var1;
    double  var2;

    assertTypeEqual<typeof(var1)>::typeEq();                        // 编译不会报错
    assertTypeEqual<typeof(assertTypeEqualCFunction())>::typeEq();  // 编译不会报错
    #if 0
    assertTypeEqual<typeof(var2)>::typeEq();                        // 编译报错
    #endif
}
#endif

/********************************************************************************************
 * @brief   多线程测试
 * 
 * @details
 * (1) 一般来说，仅凭Gtest提供的宏与函数很难做到被测函数内部线程同步或异步的控制。
 *     通常Gtest会按照代码编写的顺序去执行每一条测试用例，每一条测试用例入口实际上都是在Gtest的主线程中的。
 *     如果测试用例内启用了新的线程，Gtest主线程并不会因此而自动阻塞
 * (2) 通常测试用例中新线程都是被测函数中启动的，所以在测试用例中也可能并不能控制线程的回收。
 *     这种设计其实没有问题，因为如果新的线程是一个死循环，那么阻塞测试用例会变得极其不合理
 * (3) 假设被测试的函数存在异步关系，比如函数A处于线程1，函数B处于线程2；
 *     函数A依赖于函数B的运行结果，如果函数B没有运行完，函数A就必须等待。
 *     如果存在上述情况，通常解决的方式是在测试用例中，调用函数A前适当添加延时，除此之外暂时没有更好的办法
********************************************************************************************/
#if 0
// 以下这个例子证明了在多线程情况下，测试用例不会因为新的线程而阻塞。
// 测试用例mulThrdTestCase1中，通过线程改变了mulThrdSourceVar的值；
// 但是mulThrdSourceVar的改变存在0.5秒的延时。
// 在延时时，测试用例直接来到了mulThrdTestCase2，所以测试用例mulThrdTestCase2不通过。
class mulThrdSource {
    public:
        int mulThrdSourceVar = 10;
        std::thread mulThrdSourceThread;

        static void mulThrdSourceFunc1(int *var) {
            usleep(0.5 * 1000 * 1000);
            *var = 20;
        }
};
mulThrdSource mulThrdSource;

TEST(mulThrdSuite, mulThrdTestCase1) {
    EXPECT_EQ(mulThrdSource.mulThrdSourceVar, 10);

    mulThrdSource.mulThrdSourceThread =               \
    std::thread(mulThrdSource::mulThrdSourceFunc1,    \
    &mulThrdSource.mulThrdSourceVar);

    // 若此处回收子线程，那么后续测试用例就可以通过。但是被测函数可能是一个死循环，没有暴露的强制回收线程接口
}
TEST(mulThrdSuite, mulThrdTestCase2) {
    // 在此处添加延时处理，那么测试用例可以通过
    // usleep(1 * 1000 * 1000);

    EXPECT_EQ(mulThrdSource.mulThrdSourceVar, 20);
    mulThrdSource.mulThrdSourceThread.join();
}
#endif

/********************************************************************************************
 * @brief   fixture(测试夹具)
 * 
 * @details
 * (1) 如果多个测试用例的编写有相似指出，那么可以使用Gtest提供的fixture，
 *     定义一个类，他需要继承自testing::Test。
 *     后续定义测试用例时，用TEST_F代替TEST，并且测试套件名称必须是上述这个类的名称
 * (2) 在下一个fixture创建前，前一个fixture会被删除以保证TEST_F有效。
 * (3) fixture中，有一些特殊的函数：
 *     1) SetUp()：在每个测试用例执行前，SetUp()都会被调用，
 *        在其中可以执行一些准备工作，如初始化共享资源、创建对象实例等
 *     2) TearDown()：在每个测试用例执行后，TearDown()都会被调用，
 *        在其中可以进行清理工作，如释放资源、销毁对象实例等
 *     3) SetUpTestSuite()：在当前fixture运行所有测试用例前SetUpTestSuite()会被调用，
 *        不同于SetUp()，不管有多少TEST_F，SetUpTestSuite()都只会被调用一次。
 *        此函数一般用于fixture共享资源的创建等
 *     4) TearDownTestSuite()：在当前fixture运行所有测试用例后TearDownTestSuite()会被调用，
 *        不同于TearDown()，不管有多少TEST_F，TearDownTestSuite()都只会被调用一次。
 *        此函数一般用于fixture共享资源的销毁等
********************************************************************************************/
#if 0
class fixtureSuite : public testing::Test {
    protected:
        static void SetUpTestSuite() {
            std::cout << ">>>>>>>>>>>> " << __FUNCTION__ << ", start! <<<<<<<<<<<<" << std::endl;   // 打印1次
        }

        CLASS_SET_TEAR_COUNT();                                                                     // 打印多次   

        static void TearDownTestSuite() {
            std::cout << ">>>>>>>>>>>> " << __FUNCTION__ << ", stop! <<<<<<<<<<<<" << std::endl;    // 打印1次
        }
};
TEST_F(fixtureSuite, fixtureTestCase1) {
    EXPECT_EQ(2, 2);
}
TEST_F(fixtureSuite, fixtureTestCase2) {
    EXPECT_EQ(3, 3);
}
#endif

/********************************************************************************************
 * @brief   GTEST_SKIP，此断言调用后会跳过本测试用例内后续所有的代码
 * 
 * @details
 * (1) GTEST_SKIP不影响当前测试用例内前面的代码
 * (2) GTEST_SKIP不影响其它测试用例
********************************************************************************************/
#if 0
TEST(gtestSkipSuite, gtestSkipTestCase1) {
    EXPECT_EQ(0, 1);                                // 不通过
    if(1) {
        GTEST_SKIP() << "Skipping single test";     // 跳过当前测试用例内后续所有代码，显示SKIPPED
    }
    EXPECT_EQ(0, 1);                                // 跳过
    std::cout << "Information not to be printed" << std::endl;
}
TEST(gtestSkipSuite, gtestSkipTestCase2) {
    EXPECT_EQ(0, 1);                                // 不通过
    std::cout << "Printed information" << std::endl;
}
#endif

/********************************************************************************************
 * @brief   SCOPED_TRACE，追踪内部测试函数的具体出错位置
 * 
 * @details
 * (1) 如果一个自定义的测试函数被多次调用，并且测试错误发生在测试函数内部，那么报错位置也在对应的函数内部而不是调用处。
 *     这导致了如果希望发现是哪个地方调用后出错，就需要去逐一检查。
 *     SCOPED_TRACE解决了上述问题，它可以定位发生错误的调用源，从文件到行号
 * (2) 用符号{}表示定位要追踪的调用源，同个{}内使用多次SCOPED_TRACE则会把两个定位字符串全部输出，实际上没有意义
 * (3) SCOPED_TRACE既可以追踪普通类型的函数，也可以追踪testing::AssertionResult定义的函数
********************************************************************************************/
#if 0
// 假设internalTestFunction是一个自定义的测试函数
void internalTestFunction(int n) {
    EXPECT_EQ(1, n) << n << "is not equal to 1";
}
TEST(scopedTraceSuite, scopedTraceTestCase) {
    #if 1
        {
            // 测试通过，追踪到这个调用点的字符串"internalTestFunction flag 1"会被忽略
            SCOPED_TRACE("internalTestFunction flag 1");
            internalTestFunction(1);    // 测试通过
        }
        {
            // 测试不通过，报错定位在internalTestFunction函数内，
            // 但会用字符串"internalTestFunction flag 2"追踪到这个调用地点
            SCOPED_TRACE("internalTestFunction flag 2");
            internalTestFunction(2);    // 测试不通过
        }
        {
            SCOPED_TRACE("internalTestFunction flag 3");
            internalTestFunction(3);    // 测试不通过
        }
    #else
        // 测试不通过，报错定位都在internalTestFunction函数内，容易发生混淆
        internalTestFunction(1);
        internalTestFunction(2);
        internalTestFunction(3);
    #endif
}
#endif

/********************************************************************************************
 * @brief   HasFailure和HasFatalFailure
 * 
 * @details
 * (1) HasFailure()：bool类型的函数。
 *     此函数用于判断当前用例，调用HasFailure()之前是否存在断言错误，
 *     若存在错误，则返回true，否则返回false。
 *     此函数既可以判断是否产生非致命错误，也可以判断是否产生致命错误
 * (2) HasFatalFailure()：bool类型的函数。
 *     此函数作用类似于类似与HasFailure()，不过仅用于判断是否产生致命错误，忽略非致命错误
 * (3) 上述函数调用前都需要先继承testing::Test
********************************************************************************************/
#if 0
class isHasFailureSuite : public testing::Test {
    protected:
        // SetUp()和TearDown()不受HasFailure或AESSERT_*等影响
        CLASS_SET_TEAR_COUNT();
};

TEST_F(isHasFailureSuite, isHasFailureTestCase1) {
    EXPECT_EQ(15, 10);
    if(HasFailure()) {
        std::cout << "There is assertion error before" << std::endl;
        return;
    }
    std::cout << "Information not to be printed" << std::endl;
}

void fatalFailureFunction() {
    ASSERT_EQ(15, 10);
}
TEST_F(isHasFailureSuite, isHasFailureTestCase2) {
    fatalFailureFunction();
    if(HasFatalFailure()) {
        // 此字符串将会被打印
        std::cout << "There is fatal assertion error before" << std::endl;
        return;
    }
    std::cout << "Information not to be printed" << std::endl;
}

// 致命错误一般由AEESRT_*等断言产生；非致命错误一般由EXPECT_*等断言产生。
// 非致命错误不会使当前测试用例中断，所以在产生非致命错误后调用HasFailure是没有什么问题的。
// 但是产生致命错误后，测试用例就会被直接终止，那么为什么还有HasFatalFailure()函数用来判断是否产生致命错误呢？
// 显然上述isHasFailureTestCase2测试用例已经回答了这个问题。
// 如果测试用例中直接产生了致命错误，那么测试用例会被终止；但如果测试用例调用的函数产生了致命错误，测试用例不会被终止。
// 此时便可以用HasFatalFailure()判断是否存在间接的致命错误了
TEST_F(isHasFailureSuite, isHasFailureTestCase3) {
    ASSERT_EQ(15, 10);                                              // 测试用例内直接的致命错误，将导致整个测试用例终止
    if(HasFatalFailure()) {
        std::cout << "Information not to be printed" << std::endl;  // 此字符串将不会被打印，因为测试用例已被ASSERT_终止
    }
}
#endif

/********************************************************************************************
 * @brief   参数化测试
 * 
 * @details
 * (1) 如果希望重复性地对某种同类参数进行测试，那么可以考虑使用参数化测试
 * (2) 使用参数化测试前，需要继承testing::TestWithParam<T>，继承testing::Test的类不支持参数化测试
 * (3) 参数化测试提供了一系列参数生成器，用于生成不同形式的同类参数。
 *     一般用INSTANTIATE_TEST_SUITE_P宏提前声明要被测试的参数具体值。此宏的用法说明后续有记录。
 * (4) 如果希望实现参数化测试，那么测试用例用TEST_P定义而不是TEST_F
 * (5) 继承自testing::TestWithParam<T>的类中定义了GetParam()函数，
 *     此函数用于逐一访问INSTANTIATE_TEST_SUITE_P中声明的测试参数
 * (6) 一个继承自testing::TestWithParam<T>的类也可以实现普通的fixture，即用TEST_F定义测试用例，
 *     但是此时不能使用GetParam()函数访问测试参数。
 *     一般地，TEST_F定义的测试用例会比TEST_P定义的参数化测试用例先运行
********************************************************************************************/
#if 0
class withParamSuite : public testing::TestWithParam<int> {
    protected:
        CLASS_SET_TEAR_COUNT();
};

// 此处表示用7，17，25重复地代入测试用例进行测试
INSTANTIATE_TEST_SUITE_P(withParamExample, withParamSuite, testing::Values(7, 17, 25));

TEST_P(withParamSuite, withParamTestCase1) {
    EXPECT_TRUE(isPrime(GetParam())) << GetParam() << " is not a prime";
}

TEST_F(withParamSuite, withParamTestCase2) {
    EXPECT_TRUE(0);
}
#endif

/********************************************************************************************
 * @brief   关于testing::TestWithParam
 * 
 * @details
 * (1) 所有的值参数化测试都是从testing::WithParamInterface<T>继承的，它是一个纯接口类，
 *     testing::TestWithParam同时继承了testing::Test和testing::WithParamInterface<T>
 * (2) 如果在参数化测试中，希望向测试夹具中预先添加一些参数或函数，可以采用上述方式；
 *     继承testing::Test后再继承testing::WithParamInterface<T>
********************************************************************************************/
#if 0
// 向基类新增自定义成员
class testCustom : public testing::Test {
    protected:
        void testCustomFunction(int count) {
            std::cout << __FUNCTION__ << "count: " << count << std::endl;
        }
};
// 继承参数化测试类
class testWithParamCustomSuite : public testCustom, public testing::WithParamInterface<int> {
    protected:
        void testWithParamCustomFunction(int count) {
            testCustomFunction(count);
        }
};

INSTANTIATE_TEST_SUITE_P(testWithParamCustomExample, testWithParamCustomSuite, testing::Values(1, 2));
TEST_P(testWithParamCustomSuite, testWithParamCustomTestCase) {
    testCustomFunction(GetParam());
}
#endif

/********************************************************************************************
 * @brief   参数化测试的参数生成器，INSTANTIATE_TEST_SUITE_P
 * 
 * @details
 * (1) INSTANTIATE_TEST_SUITE_P(InstantiationName, TestSuiteName, param_generator)
 *     InstantiationName表示测试套件实例的唯一名称；
 *     TestSuiteName是继承自testing::TestWithParam<T>的类名称，即测试套件名称；
 *     param_generator表示参数生成器，参数生成器用于生成类型相似的一系列参数
 * (2) 用INSTANTIATE_TEST_SUITE_P声明测试参数时，必须放在全局而不能放在函数或类内
 * 
 * @ref     https://google.github.io/googletest/reference/testing.html#INSTANTIATE_TEST_SUITE_P
********************************************************************************************/
#if 0   // INSTANTIATE_TEST_SUITE_P
#if 0   // testing::Range(begin, end [, step])
        //      * begin表示测试参数的起始值(测试参数大于等于起始值begin)；
        //      * end表示测试参数的终止值(测试参数小于终止值end)；
        //      * step表示步长，可不填，默认为1
class testWithParamGeneratorSuite1 : public testing::TestWithParam<int> {
    protected:
        CLASS_SET_TEAR_COUNT();
};

// 0，2，4
INSTANTIATE_TEST_SUITE_P(testWithParamGeneratorExample1, testWithParamGeneratorSuite1, testing::Range(0, 5, 2));
// 0，2，4，不包括6
INSTANTIATE_TEST_SUITE_P(testWithParamGeneratorExample2, testWithParamGeneratorSuite1, testing::Range(0, 6, 2));

TEST_P(testWithParamGeneratorSuite1, testWithParamGeneratorTestCase1) {
    std::cout << "Parameter: " << GetParam() << std::endl;
}

class testWithParamGeneratorSuite2 : public testing::TestWithParam<double> {
    protected:
        CLASS_SET_TEAR_COUNT();
};
// 使用浮点数时模板类型必须用double而不能用float，并且有整数的情况下也必须使用浮点类型，如6.0
INSTANTIATE_TEST_SUITE_P(testWithParamGeneratorExample1, testWithParamGeneratorSuite2, testing::Range(1.5, 6.0, 1.5));
TEST_P(testWithParamGeneratorSuite2, testWithParamGeneratorTestCase1) {
    std::cout << "Parameter: " << GetParam() << std::endl;
}
#endif  // testing::Range(begin, end [, step])

#if 0   // testing::Values(v1, v2, ..., vN)
        //      * 测试参数为{v1, v2, ..., vN}
class testWithParamGeneratorSuite3 : public testing::TestWithParam<std::string> {
    protected:
        CLASS_SET_TEAR_COUNT();
};

INSTANTIATE_TEST_SUITE_P(testWithParamGeneratorExample1, testWithParamGeneratorSuite3, testing::Values("string1", "string2", "string3"));

TEST_P(testWithParamGeneratorSuite3, testWithParamGeneratorTestCase1) {
    std::cout << "Parameter: " << GetParam() << std::endl;
}
#endif  // testing::Values(v1, v2, ..., vN)

#if 0   // testing::ValuesIn(container) or testing::ValuesIn(begin,end)
        //      * 将数组或容器中的元素作为测试参数，可以以迭代器范围形式传入测试参数
class testWithParamGeneratorSuite4 : public testing::TestWithParam<float> {
    protected:
        CLASS_SET_TEAR_COUNT();
    public:
        static std::vector <float> testWithParamGeneratorContainer1;
        static std::set <float> testWithParamGeneratorContainer2;
        static float testWithParamGeneratorArray1[2];
};

std::vector <float> testWithParamGeneratorSuite4::testWithParamGeneratorContainer1 = {1.1, 2.2};
std::set <float> testWithParamGeneratorSuite4::testWithParamGeneratorContainer2 = {4.4, 3.3};
float testWithParamGeneratorSuite4::testWithParamGeneratorArray1[2] = {5.5, 6.6};

INSTANTIATE_TEST_SUITE_P(testWithParamGeneratorExample1,                                        \
                        testWithParamGeneratorSuite4,                                           \
                        testing::ValuesIn(                                                      \
                        testWithParamGeneratorSuite4::testWithParamGeneratorContainer1.begin(), \
                        testWithParamGeneratorSuite4::testWithParamGeneratorContainer1.end()));
INSTANTIATE_TEST_SUITE_P(testWithParamGeneratorExample2,                                        \
                        testWithParamGeneratorSuite4,                                           \
                        testing::ValuesIn(                                                      \
                        testWithParamGeneratorSuite4::testWithParamGeneratorContainer2));
INSTANTIATE_TEST_SUITE_P(testWithParamGeneratorExample3,                                        \
                        testWithParamGeneratorSuite4,                                           \
                        testing::ValuesIn(
                        testWithParamGeneratorSuite4::testWithParamGeneratorArray1));

TEST_P(testWithParamGeneratorSuite4, testWithParamGeneratorTestCase1) {
    std::cout << "Parameter: " << GetParam() << std::endl;
}
#endif  // testing::ValuesIn(container) or testing::ValuesIn(begin,end)

#if 0   // testing::Bool()
        //      * 测试参数为{false, true}
class testWithParamGeneratorSuite5 : public testing::TestWithParam<bool> {
    protected:
        CLASS_SET_TEAR_COUNT();
};

INSTANTIATE_TEST_SUITE_P(testWithParamGeneratorExample1, testWithParamGeneratorSuite5, testing::Bool());

TEST_P(testWithParamGeneratorSuite5, testWithParamGeneratorTestCase1) {
    if (GetParam()) {
        std::cout << "True" << std::endl;
    }
    else {
        std::cout << "False" << std::endl;
    }
}
#endif  // testing::Bool()

#if (1) // testing::Combine(g1, g2, ..., gN)
        //      * 可将类参数生成器联合使用，GetParam()函数会把传入参数排列组合作为测试参数
#if 0   //          * 排列组合
class testWithParamGeneratorSuite6 : public testing::TestWithParam<std::tuple<int, std::string>> {
    protected:
        CLASS_SET_TEAR_COUNT();
};

INSTANTIATE_TEST_SUITE_P(testWithParamGeneratorExample1,                \
                        testWithParamGeneratorSuite6,                   \
                        testing::Combine(                               \
                        testing::Range(1, 3),                           \
                        testing::Values("string1", "string2")));

TEST_P(testWithParamGeneratorSuite6, testWithParamGeneratorTestCase1) {
    auto    parameter       = GetParam();
    auto    integerParam    = std::get<0>(parameter);
    auto    stringParam     = std::get<1>(parameter);

    std::cout << "Parameter: "              \
    << "[interger: " << integerParam << "]" \
    << "[string: " << stringParam << "]"    \
    << std::endl;
}
#endif  //          * 排列组合

#if 0   //          * 非排列组合
        //          希望测试参数一一对应不是排列组合，可以使用如下方式
typedef struct {
    int         integerParam;
    std::string stringParam;
} testWithParamGeneratorStruct;

std::vector <testWithParamGeneratorStruct> testWithParamGeneratorStruct1 {
    {1, "string1"}, {2, "string2"}, {3, "string3"}
};

class testWithParamGeneratorSuite7 : public testing::TestWithParam<testWithParamGeneratorStruct> {
    protected:
        CLASS_SET_TEAR_COUNT();
};

INSTANTIATE_TEST_SUITE_P(testWithParamGeneratorExample1,\
                        testWithParamGeneratorSuite7, \
                        testing::ValuesIn(testWithParamGeneratorStruct1.begin(), testWithParamGeneratorStruct1.end()));

TEST_P(testWithParamGeneratorSuite7, testWithParamGeneratorTestCase1) {
    std::cout << GetParam().integerParam << ". " << GetParam().stringParam << std::endl;
}
#endif  //          * 非排列组合
#endif  // testing::Combine(g1, g2, ..., gN)
#endif  // INSTANTIATE_TEST_SUITE_P

/********************************************************************************************
 * @brief   类型参数化测试
 * 
 * @details
 * (1) gtest提供了参数化测试、类型化测试，类型参数化测试三种测试方式(类型化测试这里不做记录)。
 *     类型化测试注重对参数类型的测试，C++存在auto、模板等特性，所以对类型的测试有时是有必要的。
 *     至此，类型参数化测试也不难理解，即既注重对类型的测试，也注重对参数的测试
 * 
 * @ref     https://google.github.io/googletest/advanced.html#type-parameterized-tests
********************************************************************************************/
#if 0
template <typename T>
class withParamTypeSuite1 {
    public:
        withParamTypeSuite1(T value) : value_(value) {}             // 构造函数，将私有变量value_赋值为value

        T GetPrivateValue() const {
            return value_;
        }
    private:
        T value_;
};

template <typename T>
class withParamTypeSuite2 : public testing::Test {
    protected:
        CLASS_SET_TEAR_COUNT();
        withParamTypeSuite1<T> withParamTypeBuild1;
    public:
        withParamTypeSuite2() : withParamTypeBuild1(25) {}          // 构造函数，将25传递给withParamTypeBuild1成员变量的构造函数
};

// 通过TYPED_TEST_SUITE_P声明一个类型参数化测试套件
TYPED_TEST_SUITE_P(withParamTypeSuite2);

TYPED_TEST_P(withParamTypeSuite2, withParamTypeTestCase1) {
    TypeParam expected = 25;                                        // 类型化测试中的一个特殊用法，通过TypeParam可获取变量类型
    TypeParam actual = this->withParamTypeBuild1.GetPrivateValue(); // 通过this引用fixture中的成员

    EXPECT_EQ(expected, actual);
}

// 通过测试用例名称注册测试用例，每个测试用例都必须注册，不注册那么编译会报错
#if 0   // 如下，withParamTypeTestCase2没有被注册，编译报错：You forgot to list test withParamTypeTestCase2
TYPED_TEST_P(withParamTypeSuite2, withParamTypeTestCase2) {}
#endif
REGISTER_TYPED_TEST_SUITE_P(withParamTypeSuite2, withParamTypeTestCase1);

// using用于定义类型别名，包含int，double。表示用同一测试用例测试int类型和double类型
using withParamTypeTypes = testing::Types<int, double>;

// 使用withParamTypeTypes中的数据类型实例化withParamTypeSuite2测试套件，用于测试运行
INSTANTIATE_TYPED_TEST_SUITE_P(withParamTypeExample, withParamTypeSuite2, withParamTypeTypes);
#endif

/********************************************************************************************
 * @brief   线程错误捕获
 * 
 * @details
 * (1) EXPECT_NONFATAL_FAILURE(statement, substring)
 *     检测当前线程是否发生断言错误，若发生，则报错时输出substring字符串；
 *     若当前线程没有发生断言错误，无论其它线程是否发生错误，报错时substring字符串都不显示。
 * (2) EXPECT_NONFATAL_FAILURE_ON_ALL_THREADS(statement, substring)
 *     检测所有线程是否发生断言错误，若有一个线程发生断言错误，则报错时输出substring字符串；
 *     若所有线程都没有发生断言错误，报错时result_str字符串不显示
 * (3) 使用上述两种断言时，若发生了错误。
 *     错误区别在于是否有substring字符串被打印，而不是是否发生了断言错误
 * (4) 经测试，若发生多个测试错误，无论哪个断言，substring都不会被打印，而是以以下形式打印错误：
 *     Expected: 1 non-fatal failure
 *     Actual: 2 failures
********************************************************************************************/
#if 0
#define THREAD_SOLE_MUL_FLAG (0)        // 1表示单线程检测，0表示多线程检测

#if THREAD_SOLE_MUL_FLAG
// 单线程检测断言测试函数
void soleSubThread() {
    EXPECT_EQ(3, 5) << "Son thread has a failure";   
}
void soleFaterThread() {
    EXPECT_EQ(3, 5) << "Father thread has a failure";

    std::thread subThread(soleSubThread);
    subThread.join();
}
#else
// 多线程检测断言测试函数
void mulSubThread() {
    EXPECT_EQ(3, 5) << "Son thread has a normal failure";   
}
void mulFatherThread() {
    EXPECT_EQ(3, 5) << "Father thread has a normal failure";

    std::thread sonThread(mulSubThread);
    sonThread.join();
}
#endif  // THREAD_SOLE_MUL_FLAG

TEST(threadErrorCatchSuite, threadErrorCatchTestCase) {
#if THREAD_SOLE_MUL_FLAG 
    // 此断言只检测当前线程，而不检测其它线程
    EXPECT_NONFATAL_FAILURE(soleFaterThread(), "There is an error in the current thread");
#else  
    // 此断言检测所有线程
    EXPECT_NONFATAL_FAILURE_ON_ALL_THREADS(mulFatherThread(), "At least one error in all threads");
#endif  // THREAD_SOLE_MUL_FLAG
}
#endif

GTEST_API_ int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
