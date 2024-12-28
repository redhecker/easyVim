<div align=center>

# easyVim

![img.png](https://github.com/redhecker/easyVim/blob/docs/images/ev_logo.png)

[中文](#项目介绍) /
[English](#Introduction)

a simple vim-like text editor

一个类似vim的代码编辑器

<!-- ![img.png](Publication%2FPic%2Fimg.png) -->

</div>

## 项目介绍

Vim是一个强大的文本编辑器，其可以追溯到 20 世纪 70 年代的 Vi，1991 年演变为 Vim（意为 “Vi IMproved”）。
这款工具以纯键盘操作为核心，让用户能够精准高效地掌控代码和文本。
尽管它以学习曲线陡峭著称，一旦你熟悉了它，你会发现它不仅提升了文本处理效率和控制力，还让操作过程看起来非常炫酷。

easyVim项目旨在打造一个简单好用的“阉割版”Vim，用户可以根据此项目学习vim以及c++。

本项目旨在提供如下贡献：
- 一个简单轻量的Vim文本编辑器
- 一个性能优越，接口简洁的文本文件处理库
- 一个轻量好用，便于快速构建启动的c++框架

> 本项目为南方科技大学`CS219 计算机高级程序设计`课程项目

## 文件结构
```
.
├── CMakeLists.txt
├── Doxyfile
├── README.md
├── docs
│   └── ...
├── src
│   ├── include.hpp
│   ├── modules
│   │   ├── CMakeLists.txt
│   │   ├── config.hpp
│   │   ├── lib.cpp
│   │   ├── main.cpp
│   │   ├── show.cpp
│   │   ├── show.hpp
│   │   └── ...
│   └── test
│       ├── CMakeLists.txt
│       ├── test.cpp
│       └── ...
├── third_party
│   ├── ...
│   └── googletest
└── tools
    └── ...
```

## 从源代码构建项目

**示例Linux版本：** 5.15.167.4-microsoft-standard-WSL2 x86_64 GNU/Linux (Ubuntu 22.04.4 LTS)

**示例编译配置：** gcc (GCC) 11.2.0, GNU ld (GNU Binutils) 2.37

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

    注意：
    
    1. 如果您希望运行测试文件，那么需要打开测试选项`-DTEST_OPTION=ON`


4. 运行
   
   在当前文件夹下运行如下指令：
    ```shell
    cd build/bin
    ./easyVim yourfile.txt
    ```

    对于测试，可以使用`make test`
    或者`./tests/tests`

5. 生成动态库
   
   使用如下命令后可以在`install`文件夹下找到对应的动态库链接
    ```shell
    make install
    ```

### :rocket: **尝试最新版本!**

我们在`beta`版本中提供了多种实用工具，我们已经进行了初步的测试，您可以通过以下步骤进行部署尝试：

- **中文补丁**
    1. 如果你希望能支持UTF-8文字，那么需要使用`ncursesw`库，则下载依赖：
    ```shell
    sudo apt install libncursesw5-dev
    ```
    2. 然后在`cmake`时您需要打开选项`-DUTF8_OPTION=ON`
       
    **注意：**

    :bomb: 由于中文字符的特殊性，目前读写中文字符都可能导致排版出现问题 :(

  

- **多文件读写工具**

    1. 首先您需要安装`gnome-terminal`依赖：
   ```shell
   sudo apt install gnome-terminal
   ```

   2. 然后在`cmake`时您需要打开选项`-DMWS_OPTION=ON`
   3. 接下来您可以在`build`文件夹下找到可执行文件`mevim`，使用`./mevim`运行即可体验！

    **注意：**

    1. 您有可能需要sudo权限才能正确运行该程序，例如`sudo ./mevim`
   
    2. 如果您正在使用wsl2并且希望多文件读写时能够显示中文字符，并且您的wsl已经配置了中文环境，那么可以尝试（windows11系统）：
    ```shell
    sudo mkdir -p /usr/share/fonts/windows11
    sudo cp /mnt/c/Windows/Fonts/* /usr/share/fonts/windows11
    ```

## 参与贡献
欢迎所有的issue和pull-request :heart:，我们提供了模板，但是请随意，不必拘泥于模板！

## 链接


## 致谢
项目中的部分代码来自互联网上的开源代码，相关协议以及链接已在对应代码中标识，还有一部分教程我们没有直接使用其代码，但是也帮助了我们许多。
由于太多了没有办法全部列举出链接，在此感谢所有开源创作者！


## Introduction
