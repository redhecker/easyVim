/**@file       core.hpp
* @brief       easyVim核心模块头文件
* @details     定义了easyVim的核心模块相关函数和类，比如文件操作、文本操作等
* @author      Super@redhecker
* @copyright   Copyright (c) 2024
*/

#ifndef EASYVIM_CORE_HPP
#define EASYVIM_CORE_HPP
#include <vector>
#include <string>

namespace ev {

/**
 * @class evFile
 * @brief easyVim 基础文件类
 * @details 用于存储文件内容，提供文件操作接口
 */
class evFile{
public:
    enum class evFileStatus{
        OK,         ///< 文件正常
        NOT_EXIST,  ///< 文件不存在
        OPEN_FAIL,  ///< 文件打开失败
        READ_FAIL,  ///< 文件读取失败
        WRITE_FAIL, ///< 文件写入失败
        CLOSE_FAIL  ///< 文件关闭失败
    };

    evFile(const std::string& fileName) : fileName(fileName){}
    ~evFile();

    /**
     * @brief 读取文件
     * @return evFileStatus 文件状态
     */
    evFileStatus loadFile();

private:
    std::string                  fileName;     ///< 文件名
    std::vector<std::string>     fileContent;  ///< 文件内容
    size_t                       start;        ///< 文件起始行号（由于文件可能很大，不能一次性把所有文件内容都load进来）
};
    
}

#endif //EASYVIM_CORE_HPP