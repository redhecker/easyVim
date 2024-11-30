<div align=center>

# easyVim

![img.png](https://github.com/redhecker/easyVim/blob/main/docs/ev_logo.png)

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

    `easyVim`强依赖于`ncurses`库，因此需要下载依赖：
    ```shell
    sudo apt install libncurses5-dev
    ```

    如果你希望使用`googletest`进行测试，那么需要使用依赖：
    ```shell
    git submodule update --init --recursive
    ```

3. 编译
   
   在当前文件夹下运行如下指令：
    ```shell
    mkdir build && cd build 
    cmake .. -DTEST_OPTION=OFF 
    make -j4
    ```

    注意：如果您希望运行测试文件，那么需要打开测试选项`-DTEST_OPTION=ON`

4. 运行
   
   在当前文件夹下运行如下指令：
    ```shell
    cd build/bin
    ./easyVim yourfile.txt
    ```

    对于测试，可以使用`make test`
    或者`./tests./tests`

5. 生成动态库
   
   使用如下命令后可以在`install`文件夹下找到对应的动态库链接
    ```shell
    make install
    ```


## project-introduction
