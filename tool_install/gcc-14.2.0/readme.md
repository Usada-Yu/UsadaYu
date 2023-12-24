# gcc源码安装

## 环境

Linux，centos7



## 源码地址

gcc 官方指定的依赖库

```
https://gcc.gnu.org/install/prerequisites.html
```

### gmp-6.3.0

```
https://gmplib.org/
```

### mpfr-4.2.1

要求 gmp 版本大于5.0

```
https://www.mpfr.org/mpfr-current/
```

### mpc-1.3.1

要求 gmp 版本大于5.0，mpfr 版本大于4.1.0

```
https://www.multiprecision.org/mpc/download.html
```

### gcc-14.2.0

gcc 源码镜像地址，官方似乎只提供了 mirrors

```
https://gcc.gnu.org/mirrors.html
```

任意选取镜像中的 release 下载

```
https://ftp.tsukuba.wide.ad.jp/software/gcc/releases/gcc-14.2.0/
```



## 安装流程

```
tar -xvf gmp-6.3.0.tar.xz 
cd gmp-6.3.0/
./configure --prefix=$HOME/.local/x86/gnu/gmp-6.3.0/
make -j
make install
```

```
tar -xvf mpfr-4.2.1.tar.xz 
cd mpfr-4.2.1/
./configure --prefix=$HOME/.local/x86/gnu/mpfr-4.2.1/ \
--with-gmp=$HOME/.local/x86/gnu/gmp-6.3.0/
make -j
make install
```

```
tar -zxvf mpc-1.3.1.tar.gz
cd mpc-1.3.1/
./configure --prefix=$HOME/.local/x86/gnu/mpc-1.3.1/ \
--with-gmp=$HOME/.local/x86/gnu/gmp-6.3.0/ \
--with-mpfr=$HOME/.local/x86/gnu/mpfr-4.2.1/
make -j
make install
```



安装 gcc 时，我遇到 libmpfr.so.6 动态库无法打开，所以这里先添加环境变量

```
vim ~/.bash_profile
export LD_LIBRARY_PATH=$HOME/.local/x86/gnu/mpfr-4.2.1/lib:$LD_LIBRARY_PATH
source ~/.bash_profile
```

接下来安装 gcc

```
tar -xf gcc-14.2.0.tar.xz
cd gcc-14.2.0/
./configure --prefix=$HOME/.local/x86/gnu/gcc-14.2.0/ \
--with-gmp=$HOME/.local/x86/gnu/gmp-6.3.0/ \
--with-mpfr=$HOME/.local/x86/gnu/mpfr-4.2.1/ \
--with-mpc=$HOME/.local/x86/gnu/mpc-1.3.1/
make -j
make install
```



### 添加环境变量

```
vim ~/.bash_profile
export LD_LIBRARY_PATH=$HOME/.local/x86/gnu/gcc-14.2.0/lib64:$LD_LIBRARY_PATH
export PATH=$HOME/.local/x86/gnu/gcc-14.2.0/bin:$PATH

# 这里 `CC` 和 `CXX` 环境变量可选择性添加，保证一些工具搜索编译器时默认使用自安装的 gnuc
export CC=$HOME/.local/x86/gnu/gcc-14.2.0/bin/gcc
export CXX=$HOME/.local/x86/gnu/gcc-14.2.0/bin/g++

source ~/.bash_profile
gcc --version
```



## gdb安装

### gdb-15.1

```
https://sourceware.org/pub/gdb/releases/?C=M;O=D
```



### 安装流程

```
tar -xf gdb-15.1.tar.xz 
./configure --prefix=$HOME/.local/x86/gnu/gdb-15.1 \
--with-gmp=$HOME/.local/x86/gnu/gmp-6.3.0/ \
--with-mpfr=$HOME/.local/x86/gnu/mpfr-4.2.1/ \
--with-mpc=$HOME/.local/x86/gnu/mpc-1.3.1/
make -j
make install
```



### 添加环境变量

```
vim ~/.bash_profile
export PATH=$HOME/.local/x86/gnu/gdb-15.1/bin:$PATH
source ~/.bash_profile
gdb --version
gdbserver --version
```



## gnu基础配套工具

### binutils-2.43

```
https://sourceware.org/pub/binutils/releases/
```



### 安装流程

```
tar -xf binutils-2.43.tar.xz 
./configure --prefix=$HOME/.local/x86/gnu/binutils-2.43
make -j
make install
```



### 添加环境变量

```
vim ~/.bash_profile
export PATH=$HOME/.local/x86/gnu/binutils-2.43/bin:$PATH
source ~/.bash_profile
ld -v
```
