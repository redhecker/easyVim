/**@file       include.hpp
* @brief       easyVim动态库头文件
* @details     打包成动态库时引用的头文件，定义了相应的函数
* @author      Super@redhecker
* @copyright   Copyright (c) 2024
*/

#ifndef EV_HPP
#define EV_HPP
#include "modules/config.hpp"

namespace ev{

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

/**
 * @function 加密接口
 */
bool EVencrypt(std::vector<std::string> *input, 
                std::vector<std::string> *output, 
                std::string key, EV_ENCRYPT_TYPE evType=EV_ENCRYPT_AES_BEGIN);

/**
 * @function 解密接口
 */
bool EVdecrypt(std::vector<std::string> *input, 
             std::vector<std::string> *output, 
             std::string key, EV_DECRYPT_TYPE evType=EV_DECRYPT_AES_BEGIN);


} // namespace ev



// 版权声明：此函数遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。                  
// 原文链接：https://blog.csdn.net/m0_58086930/article/details/122759927
void Stringsplit(const std::string& str, const char split, std::vector<std::string>& res);

#endif