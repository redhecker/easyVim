<div align=center>


![img.png](https://github.com/redhecker/easyVim/blob/docs/images/logo.png)

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

## 项目框架
![img.png](https://github.com/redhecker/easyVim/blob/docs/images/struct.png)

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
  
    🤯 同时，由于未知原因（代码限制了utf-8的输入识别以避免一些奇怪的问题），我们目前并不支持输入，仅支持显示。

  

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

[用户手册](https://github.com/redhecker/easyVim/wiki/%E7%94%A8%E6%88%B7%E6%89%8B%E5%86%8C-%E2%80%90-users'-manual)

[开发手册](https://github.com/redhecker/easyVim/wiki/%E5%BC%80%E5%8F%91%E6%89%8B%E5%86%8C)

[推荐语](https://github.com/redhecker/easyVim/wiki/%E6%8E%A8%E8%8D%90%E8%AF%AD)

## 致谢
项目中的部分代码来自互联网上的开源代码，相关协议以及链接已在对应代码中标识，还有一部分教程我们没有直接使用其代码，但是也帮助了我们许多。
由于太多了没有办法全部列举出链接，在此感谢所有开源创作者！


## Introduction

Vim is a powerful text editor, which can be traced back to Vi in the 1970s and evolved into Vim (meaning "Vi IMproved") in 1991. This tool focuses on pure keyboard operation, enabling users to precisely and efficiently control code and text. Although it is known for its steep learning curve, once you get familiar with it, you will find that it not only improves the efficiency and control of text processing but also makes the operation process look really cool.

The easyVim project aims to create a simple and user-friendly "lite version" of Vim. Users can learn vim and C++ through this project.

This project intends to make the following contributions:
- A simple and lightweight Vim text editor.
- A text file processing library with superior performance and a concise interface.
- A lightweight and handy C++ framework that is convenient for quick construction and startup.

> This project is the course project for the "CS219 Advanced Computer Programming" course at Southern University of Science and Technology.

## File Structure
```
.
├── CMakeLists.txt
├── Doxyfile
├── README.md
├── docs
│   └──...
├── src
│   ├── include.hpp
│   ├── modules
│   │   ├── CMakeLists.txt
│   │   ├── config.hpp
│   │   ├── lib.cpp
│   │   ├── main.cpp
│   │   ├── show.cpp
│   │   ├── show.hpp
│   │   └──...
│   └── test
│       ├── CMakeLists.txt
│       ├── test.cpp
│       └──...
├── third_party
│   ├──...
│   └── googletest
└── tools
    └──...
```

## Building the Project from Source Code

**Example Linux Version**: 5.15.167.4-microsoft-standard-WSL2 x86_64 GNU/Linux (Ubuntu 22.04.4 LTS)

**Example Compilation Configuration**: gcc (GCC) 11.2.0, GNU ld (GNU Binutils) 2.37

1. Download Relevant Dependencies

The `easyVim` strongly depends on the `ncurses` library, so you need to download the dependencies:
```shell
sudo apt install libncurses5-dev
```

If you want to use `googletest` for testing, then you need to use the following dependencies:
```shell
git submodule update --init --recursive
```

2. Compilation

Run the following commands in the current folder:
```shell
mkdir build && cd build 
cmake.. -DTEST_OPTION=OFF 
make -j4
```

**Note**:

1. If you want to run the test files, you need to turn on the test option `-DTEST_OPTION=ON`.

3. Running

Run the following commands in the current folder:
```shell
cd build/bin
./easyVim yourfile.txt
```

For testing, you can use `make test` or `./tests/tests`.

4. Generating Dynamic Libraries

After using the following command, you can find the corresponding dynamic library links in the `install` folder:
```shell
make install
```

### :rocket: **Try the Latest Version!**

We have provided several practical tools in the `beta` version, and we have already conducted preliminary tests. You can deploy and try them through the following steps:

- **UTF-8 Support**
    1. If you want to support UTF-8 characters, you need to use the `ncursesw` library, and then download the dependencies:
    ```shell
    sudo apt install libncursesw5-dev
    ```
    2. Then, when using `cmake`, you need to turn on the option `-DUTF8_OPTION=ON`.

    **Note**:

    :bomb: Due to the particularity of Chinese characters, there may be layout problems when reading and writing Chinese characters at present. :(

- **Multi-file Reading and Writing Tools**

    1. First, you need to install the `gnome-terminal` dependency:
    ```shell
    sudo apt install gnome-terminal
    ```
    2. Then, when using `cmake`, you need to turn on the option `-DMWS_OPTION=ON`.
    3. Next, you can find the executable file `mevim` in the `build` folder and run it using `./mevim` to experience it!

    **Note**:

    1. You may need `sudo` privileges to run the program correctly, for example, `sudo./mevim`.
    2. If you are using WSL2 and want to display Chinese characters when reading and writing multiple files, and your WSL has been configured with a Chinese environment, you can try (for Windows 11 system):
    ```shell
    sudo mkdir -p /usr/share/fonts/windows11
    sudo cp /mnt/c/Windows/Fonts/* /usr/share/fonts/windows11
    ```

## Contributing

All issues and pull-requests are welcome :heart:. We have provided templates, but feel free to contribute without being restricted by the templates!

## Links

[Users' Manual](https://github.com/redhecker/easyVim/wiki/%E7%94%A8%E6%88%B7%E6%89%8B%E5%86%8C-%E2%80%90-users'-manual)

[Recommendation](https://github.com/redhecker/easyVim/wiki/%E6%8E%A8%E8%8D%90%E8%AF%AD)

## Acknowledgments

Some of the code in this project comes from open-source code on the Internet. The relevant agreements and links have been marked in the corresponding code. There is also a part of the tutorials that we didn't directly use their code but were also of great help to us. Since there are too many to list all the links, we would like to thank all open-source creators here! 
