/**@file       core.hpp
* @brief       easyVim核心模块
* @details     定义了easyVim的核心模块相关函数和类，比如文件操作、文本操作等
* @author      Super@redhecker
* @copyright   Copyright (c) 2024
*/

#ifndef EASYVIM_CORE_HPP
#define EASYVIM_CORE_HPP
#include <vector>
#include <utility>
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
        EVFILE_OK               = 0,         ///< 文件正常
        EVFILE_NOT_EXIST        = 1,         ///< 文件不存在 -> 创建文件
        EVFILE_OPEN_FAIL        = 2,         ///< 文件打开失败
        EVFILE_READ_FAIL        = 3,         ///< 文件读取失败
        EVFILE_WRITE_FAIL       = 4,         ///< 文件写入失败
        EVFILE_CLOSE_FAIL       = 5,         ///< 文件关闭失败
        EVFILE_OUT_OF_BOUND     = 6          ///< 指针超出文本位置

        EVFILE_DIR_DOSE_NOT_EXIST  = 10,         ///< 路径不存在 -> 创建路径
        EVFILE_NO_MATCH_PATTERN    = 11,         ///< 找不到匹配的内容
        EVFILE_PATTERN_MATCH       = 12,         ///< 找不到匹配的内容
        EVFILE_REPLACE_SUCCESS     = 13,         ///< 成功替换
        EVFILE_REPLACE_FAIL        = 14,         ///< 替换失败

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

    /**
     * @brief 文件另存为，还没有实现创建文件夹得功能，如果目录不存在直接返回错误
     * @param 新文件名称
     * @return evFileStatus 文件状态
     */
    EVFileStatus saveFileAs(const std::string& newFilePath);

    /**
     * @brief 退出文件
     * @return evFileStatus 文件状态
     */
    EVFileStatus quitFile();    

    /**
     * @brief 在文件中查找匹配正则表达式的内容
     * @return evFileStatus 文件状态
     */
    EVFileStatus searchInFile(const std::string regexPattern); 

    /**
     * @brief 在文件中查找匹配正则表达式的内容并替换
     * @return evFileStatus 文件状态
     */
    EVFileStatus searchReplace(const std::string regexPattern, const std::string replacePattern); 

    EVFileStatus insertChar(int row, int col, char x);
    EVFileStatus coverChar(int row, int col, char x);
    EVFileStatus deleteChar(int row, int col, bool isFront);

    EVFileStatus deleteLine(int rowB, int colB, int rowE = -1, int colE = -1);
    EVFileStatus copyLine(int rowB, int colB, int rowE = -1, int colE = -1);
    EVFileStatus pasteLine(int row, int col);

    std::string                  fileName;     ///< 文件名
    std::vector<std::string>     fileContent;  ///< 文件内容
    std::vector<std::string>     copiedFile;   ///< 复制的文件内容
    bool                         hasCopy;      ///< 复制内容是否有效
    bool                         hasChange;    ///< 文件是否有改动
    size_t                       start;        ///< 文件起始行号（由于文件可能很大，不能一次性把所有文件内容都load进来）
    size_t                       offset;       ///< 文件偏移量（由于文件可能很大，不能一次性把所有文件内容都load进来）

private:
    FILE* file;                          ///< 文件指针
    std::vector<std::pair<int,int>> searchPosition;   ///< 查找结果在文件中的位置

    /**
     * @brief 查找的辅助函数
     * @param regexPattern 正则表达式
     * @return evFileStatus 文件状态
     */
    std::vector<std::pair<int, int>> search(const std::string& regexPattern); 

    /**
     * @brief searchReplace的辅助函数
     * @param pos替换的起始位置，replacePattern用于替换的正则表达式
     * @return evFileStatus 文件状态
     */
    bool replace(const std::pair<int,int> pos, const std::string& replacePattern); 
};
} // namespace ev

#endif //EASYVIM_CORE_HPP