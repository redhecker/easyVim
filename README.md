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


## project-introduction
