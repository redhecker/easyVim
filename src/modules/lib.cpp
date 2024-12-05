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

// 版权声明：此函数遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。                  
// 原文链接：https://blog.csdn.net/m0_58086930/article/details/122759927
void Stringsplit(const std::string& str, const char split, std::vector<std::string>& res)
{
	if (str == "")		return;
	//在字符串末尾也加入分隔符，方便截取最后一段
	std::string strs = str + split;
	size_t pos = strs.find(split);
 
	// 若找不到内容则字符串搜索函数返回 npos
	while (pos != strs.npos)
	{
		std::string temp = strs.substr(0, pos);
		res.push_back(temp);
		//去掉已分割的字符串,在剩下的字符串中进行分割
		strs = strs.substr(pos + 1, strs.size());
		pos = strs.find(split);
	}
}
