/********************************************************************************************
 * 1. 关于CPU
 * @ref https://www.ruanyifeng.com/blog/2018/01/assembly-language-primer.html
 * 
 * 即使是C语言如此底层的语言，CPU也是无法理解的。
 * 真正能被CPU直接识别的是机器语言，也就是0和1，但是0和1对于人类来说可读性极差。
 * 最早期的编程还真是手搓0和1，这在今天看来不过是一种玩笑罢了。
 * 后来，工程师们将这些二进制的0和1指令写成了八进制，但是这种单纯的数字还是不太友好；
 * 因此汇编语言应运而生，它基本和机器语言一一对应，但是作为一种助记符，对于人类又相对友好
********************************************************************************************/

/********************************************************************************************
 * 不同的CPU指令集通常是不一样的。指令集不单指汇编语言，也包括算数运算、逻辑运算、数据传输等规范。
 * 通俗来讲，指令集定义了软件控制CPU的方式。
 * 
 * arm和x86架构占据着多少市场份额不言而喻。
 * x86架构的CPU多被用于计算机，Intel和AMD是耳熟能详的代表公司。
 * 而作为一名嵌入式工程师，平日工作接触到更多的肯定是arm架构。
 * 工作中经常接触到的有armv7架构，它是32bit的，如海思的hi3516dv300芯片；
 * 也有armv8架构，它是64bit的，兼容32bit的指令，如海思的hi3516dv500芯片、海思的sd3403v100芯片等。
********************************************************************************************/

/********************************************************************************************
 * CPU只负责数据的运算，不负责数据的存储。
 * CPU会从负责存储数据的内存中读取数据，不过读取内存的速度终究是有些慢的，大大拖慢了CPU运行的速度。
 * 所以CPU一般自带一、二级缓存，这些缓存还是慢了一些，所以CPU还有寄存器，寄存器拥有极致的读写速度，
 * 所以被人们称为零级缓存。CPU优先读取寄存器，然后寄存器又和内存等交换数据。
 * 读写最频繁的数据一般会被存放在寄存器中，如循环变量，经过编译器的优化，一般会放在寄存器中。
 * 
 * 寄存器不像内存依靠地址区分，而是依靠名称区分，每个寄存器都有自己的名称，
 * 通过寄存器的名称可以告诉CPU去哪个寄存器读写数据，这样速度是极快的。
********************************************************************************************/

/********************************************************************************************
 * 数据交换流程简化图
 * 
 * CPU registers        CPU寄存器
 *  ↓
 * Cache                缓存
 *  ↓
 * RAM                  内存
 *  ↓
 * Hard disk            硬盘
 * 
 * 越上级，读写速度越快，但是容量越小
********************************************************************************************/

/********************************************************************************************
 * 2. 关于内存
 * 因为CPU的寄存器和缓存能存放的数据很少，一般CPU要只会寄存器和内存进行数据交换。
 * 因此对内存的基本模型也要有所了解。
 * 
 * 进程运行时，操作系统会为其分配一段内存，用于存储程序本身和进程运行时产生的数据。
 * 这段内存有起始地址和结束地址，大致模型如下(假设内存地址为0x1000~0x8000)：
 * 
 *      Memory
 * ----------------------------→结束地址(高位，0x8000)
 * |                    |
 * |    Stack frame     |
 * |     (main)         |
 * |--------------------|
 * |                    |
 * |    Stack frame1    |------→栈区内存，由高位(地址)向低位(地址)分配。
 * |--------------------|       函数被调用时，会在栈区建立一个栈帧，函数内部的变量都会保存在整个帧里。
 * |                    |       函数执行结束后，函数帧会被回收，内部所有的变量都会被释放，不再占用空间。
 * |                    |       函数内：int a; const int a; const int a = 10;等一般存放在stack
 * |                    |
 * |    Stack frame1    |------→函数中调用其它函数，那么会建立一个新的栈帧，依次类推。
 * |--------------------|       一般地，调用栈有多少层，就有多少帧。
 * |                    |       当此函数结束后，那么进程会回到调用处，继续在之前中断地地方往下执行。
 * |                    |       由此，可见数据结构算法中的入栈(pop)出栈(push)非常类似
 * |                    |
 * |    ......          |
 * |--------------------|
 * |    Heap            |------→堆区内存，由低位(地址)向高位(地址)分配，堆区内存不会自动消失，必须手动释放。
 * |                    |       malloc申请的内存通常存放在heap
 * |                    |
 * |--------------------|
 * |    Bss Segment     |------→未初始化数据段，用于存放程序中未初始化的全局变量和静态变量。
 * |                    |       使用时，数据会被自动初始化。初始化为0和NULL等。
 * |                    |       函数内：static int a;
 * |                    |       全局：int a; const int a; static int a;等一般存放在bss
 * |--------------------|
 * |    Data Segment    |------→已初始化数据段，用于存放程序中已初始化的全局变量和静态变量。
 * |                    |       函数内：static int a = 10;
 * |                    |       全局：int a = 10; static int a = 10;等一般存放在data
 * |--------------------|
 * |    Text Segment    |------→文本段，用于存放程序执行的代码和一些只读文本。
 * |                    |       多数平台架构下此区域为只读的，少部分架构允许可写。
 * |                    |       函数内：static const int a;
 * |                    |       全局：const int a = 10; static const int a;等一般存放在text
 * |                    |
 * ----------------------------→起始地址(低位，0x1000)。从起始地址开始有一小段静态数据，这里忽略
********************************************************************************************/

/********************************************************************************************
 * 上述关于内存地址实际上都是虚拟地址。
 * 将两个相同的源文件编译后反汇编，可以看到它们的反汇编结果是一样的，包括虚拟地址。
 * 如果将基于相同源文件编译的两个程序同时运行，或者将一个可执行文件复制粘贴后运行它和它的副本，
 * 即使虚拟地址相同，也不会出问题。
 * 操作系统使用内存管理单元(MMU)来实现虚拟地址映射到物理地址，每个进程都有自己独立的映射页表。
 * 所以即使程序的虚拟地址是相同的，它的物理地址也可以相互隔离，互不干扰。
********************************************************************************************/