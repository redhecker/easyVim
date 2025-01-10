/**@file       encrypt.cpp
* @brief       easyVim加密解密模块
* @author      Super@redhecker
* @copyright   Copyright (c) 2024
*/

#include "encrypt.hpp"

namespace ev
{
    
    bool encrypt(std::vector<std::string> *input, 
                 std::vector<std::string> *output, 
                 std::string key, EV_ENCRYPT_TYPE evType){

        if (evType == EV_ENCRYPT_AES_BEGIN) {
            aes_encrypt(input, output, key);
            std::string key_md5 = md5(key);
            output->insert(output->begin(), key_md5);
        } 
        else if (evType == EV_ENCRYPT_AES_NBEGIN) {
            aes_encrypt(input, output, key);
        }
        else {
            return false;
        }

        return true;
    }


    bool decrypt(std::vector<std::string> *input, 
                 std::vector<std::string> *output, 
                 std::string key, EV_DECRYPT_TYPE evType){
    
        if (evType == EV_DECRYPT_AES_BEGIN){
            std::string key_md5 = md5(key);
            std::string real_md5 = input->front();
            if (key_md5 == real_md5){
                input->erase(input->begin());
            } else {
                return false;
            }
            aes_decrypt(input, output, key);
        } 
        else if (evType == EV_DECRYPT_AES_NBEGIN) {
            // 保证对方如果是用正常的加密方式加密的，那么这里也能解密（只要密码正确就是正确解密）
            std::string key_md5 = md5(key);
            std::string real_md5 = input->front();
            if (key_md5 == real_md5){
                input->erase(input->begin());
            }
            aes_decrypt(input, output, key);
        }
        else {
            return false;
        }

        return true;
    }

} // namespace ev
