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

    enum EV_ENCRYPT_TYPE {
        EV_ENCRYPT_AES_BEGIN  = 0, ///< 使用aes加密算法，并且在第一行增加密钥MD5进行识别
        EV_ENCRYPT_AES_NBEGIN = 1  ///< 使用aes加密算法，但是不保存密钥MD5
    };

    enum EV_DECRYPT_TYPE {
        EV_DECRYPT_AES_BEGIN  = 0, ///< 使用aes解密算法，并且识别第一行的MD5，若识别失败则不解密
        EV_DECRYPT_AES_NBEGIN = 1  ///< 直接使用aes解密算法
    };

    /**
     * @function 加密接口
     */
    bool encrypt(std::vector<std::string> *input, 
                 std::vector<std::string> *output, 
                 std::string key, EV_ENCRYPT_TYPE evType=EV_ENCRYPT_AES_BEGIN);

    /**
     * @function 解密接口
     */
    bool decrypt(std::vector<std::string> *input, 
    std::vector<std::string> *output, 
    std::string key, EV_DECRYPT_TYPE evType=EV_DECRYPT_AES_BEGIN);
    
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