<div align=center>

# easyVim

[中文](#项目介绍) /
[English](#project-introduction)

a simple vim-like text editor

一个类似vim的代码编辑器

<!-- ![img.png](Publication%2FPic%2Fimg.png) -->

</div>

## 项目介绍

## 从源代码构建项目

**示例Linux版本：** 5.15.167.4-microsoft-standard-WSL2 x86_64 GNU/Linux (Ubuntu 22.04.4 LTS)

**示例编译器：** gcc (GCC) 11.2.0, GNU ld (GNU Binutils) 2.37

1. 下载相关依赖

    本项目强依赖于`ncurses`库，因此需要下载依赖：
    ```shell
    sudo apt install libfmt-dev
    ```

2. 编译


3. 运行




## project-introduction

how to build (on ubuntu):

step one: add dependency
```
sudo apt install libfmt-dev
```
step two: build

if you want to build with google test:
```
git submodule update --init --recursive
```
```
mkdir build && cd build 
cmake .. -DTEST_OPTION=ON 
make -j4
```

if you do not want to build with google test:
```
mkdir build && cd build 
cmake .. -DTEST_OPTION=OFF 
make -j4
```

step three: run the program

`./main` at build/bin to run main program.

`./tests` at build/tests to run tests.

you can also run `make test` to run tests.

you can use `make install` to get dynamic link library at install.
