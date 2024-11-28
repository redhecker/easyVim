/**@file       inst.hpp
* @brief       easyVim指令模块
* @details     定义了指令模块的相关函数和类
* @author      Super@redhecker
* @copyright   Copyright (c) 2024
*/

#ifndef EASYVIM_INST_HPP
#define EASYVIM_INST_HPP

namespace ev {
    enum instType {
        INST_SAVE           = 0, ///< 保存
        INST_SAVE_NEW       = 1, ///< 另存为，需要参数指定新的文件名，如果文件已存在则失败，强制指令则覆盖
        INST_QUIT           = 2, ///< 退出，如果文件未保存且不是强制指令则失败
        INST_SAVE_QUIT      = 3, ///< 保存并退出

        INST_SEARCH         = 4, ///< 搜索，需要参数指定搜索内容
        INST_SEARCH_REPLACE = 5, ///< 搜索并替换，需要参数指定搜索内容和替换内容 //todo 增加参数指定替换范围
        INST_ENCRYPT        = 6, ///< 对称加密
        INST_DECRYPT        = 7, ///< 对称解密

        INST_CHANGE_CODEC   = 8, ///< 更改编码，需要参数指定新的编码
        // todo 增加更多指令，比如rsa加密解密
    };
}

#endif //EASYVIM_INST_HPP