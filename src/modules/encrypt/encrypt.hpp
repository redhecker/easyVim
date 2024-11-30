/**@file       encrypt.hpp
* @brief       easyVim加密解密模块
* @details     定义了easyVim用于加密解密的相关函数和类
* @author      Super@redhecker
* @copyright   Copyright (c) 2024
*/

#ifndef EASYVIM_ENCRYPT_HPP
#define EASYVIM_ENCRYPT_HPP
#include<string>
#include<vector>

namespace ev {
    
    /**
     * @function md5加密算法
     */
    std::string md5(std::string input);

    /**
     * @function aes128位加密算法
     */
    void aes_encrypt(std::vector<std::string> *input, std::vector<std::string> *output, std::string key);
    void aes_decrypt(std::vector<std::string> *input, std::vector<std::string> *output, std::string key);

} // namespace ev

#endif //EASYVIM_ENCRYPT_HPP