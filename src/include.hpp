/**@file       include.hpp
* @brief       easyVim动态库头文件
* @details     打包成动态库时引用的头文件，定义了相应的函数
* @author      Super@redhecker
* @copyright   Copyright (c) 2024
*/

#ifndef EV_HPP
#define EV_HPP

/**
 * @brief 测试接口，用于打印当前版本号
 */
void version();

/**
 * @brief 用于打印作者信息
 */
void author();

/**
 * @return 返回当前版本号
 */
const char* getVersion();

#endif