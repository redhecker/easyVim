/**@file       core.hpp
* @brief       easyVim核心模块
* @details     定义了easyVim的核心模块相关函数和类，比如文件操作、文本操作等
* @author      Super@redhecker
* @copyright   Copyright (c) 2024
*/

#ifndef EASYVIM_CORE_HPP
#define EASYVIM_CORE_HPP
#include <vector>
#include <string>
#include <fstream>

namespace ev {

/**
 * @class evFile
 * @brief easyVim 基础文件类
 * @details 用于存储文件内容，提供文件操作接口
 * @todo 未来可以考虑文件特别大的情况，拓展分块读取文件的功能
 */
class EVFile{
public:
    enum EVFileStatus{
        EVFILE_OK           = 0,         ///< 文件正常
        EVFILE_NOT_EXIST    = 1,         ///< 文件不存在 -> 创建文件
        EVFILE_OPEN_FAIL    = 2,         ///< 文件打开失败
        EVFILE_READ_FAIL    = 3,         ///< 文件读取失败
        EVFILE_WRITE_FAIL   = 4,         ///< 文件写入失败
        EVFILE_CLOSE_FAIL   = 5,          ///< 文件关闭失败
        EVFILE_OUT_OF_BOUND =6
    };

    EVFile(const std::string fileName) : fileName(fileName){
        hasChange = false;
        start = 0;
        offset = 0;
        hasCopy = false;
    }
    ~EVFile();

    /**
     * @brief 读取文件
     * @return evFileStatus 文件状态
     */
    EVFileStatus loadFile();

    /**
     * @brief 写入文件
     * @return evFileStatus 文件状态
     */
    EVFileStatus saveFile();

    EVFileStatus insertChar(int row, int col, char x);
    EVFileStatus coverChar(int row, int col, char x);
    EVFileStatus deleteChar(int row, int col, bool isFront);

    EVFileStatus deleteLine(int rowB, int colB, int rowE = -1, int colE = -1);
    EVFileStatus copyLine(int rowB, int colB, int rowE = -1, int colE = -1);
    EVFileStatus pasteLine(int row, int col);

    std::string                  fileName;     ///< 文件名
    std::vector<std::string>     fileContent;  ///< 文件内容
    bool                         hasChange;    ///< 文件是否有改动
    size_t                       start;        ///< 文件起始行号（由于文件可能很大，不能一次性把所有文件内容都load进来）
    size_t                       offset;       ///< 文件偏移量（由于文件可能很大，不能一次性把所有文件内容都load进来）

private:
    FILE* file;                          ///< 文件指针
    std::vector<std::string> copiedFile; ///< 复制的文件内容
    bool hasCopy;                        ///< 复制内容是否有效
};
} // namespace ev

#endif //EASYVIM_CORE_HPP