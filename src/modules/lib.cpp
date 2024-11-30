#include "../include.hpp"
#include "config.hpp"
#include <iostream>

namespace ev
{

void version(){
    std::cout << "easyVim version: " << EV_VERSION << std::endl;
}

const char* getVersion(){
    return EV_VERSION;
}

void author(){
    std::cout << "Author: Super github@redhecker" << std::endl;
}

bool EVencrypt(std::vector<std::string> *input, 
                std::vector<std::string> *output, 
                std::string key, EV_ENCRYPT_TYPE evType){
                    return encrypt(input, output, key, evType);
                }

/**
 * @function 解密接口
 */
bool EVdecrypt(std::vector<std::string> *input, 
             std::vector<std::string> *output, 
             std::string key, EV_DECRYPT_TYPE evType){
                return decrypt(input, output, key, evType);
            }

} // namespace ev


