/**@file       inst.hpp
* @brief       easyVim指令模块
* @details     定义了指令模块的相关函数和类
* @author      Super@redhecker
* @copyright   Copyright (c) 2024
*/

#ifndef EASYVIM_INST_HPP
#define EASYVIM_INST_HPP

#include <string>
#include <unordered_map>
#include <cstring>
#include <vector>
#include <fstream>
#include "../core/core.hpp"

namespace ev {
/**
 * @class EVConfig
 * @brief easyVim 指令配置类
 * @details 用于存储指令信息以及拓展指令，支持从配置文件读取指令信息
 */
class EVConfig{
public:
    EVConfig(std::string f = ""){
        fileName = f;
        FILE* file = fopen(fileName.c_str(), "r");
        instList = std::vector<std::string>();
        if (file != NULL){
            char buf[128] = {0};
            while(fgets(buf, 128, file) != NULL){
                if (buf[0] == '#'){
                    continue;
                }
                if (buf[strlen(buf) - 1] == '\n'){
                    buf[strlen(buf) - 1] = '\0';
                }
                instList.push_back(buf);
            }
            fclose(file);
        }
    }
    ~EVConfig(){}

    std::string fileName;                           ///< 配置文件名
    std::vector<std::string> instList;              ///< 指令列表
};
    
}

#endif //EASYVIM_INST_HPP