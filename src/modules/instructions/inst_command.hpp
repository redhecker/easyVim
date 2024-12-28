/**
 * @file inst_command.hpp
 * @brief easyVim指令模块头文件
 * @author Super@redhecker
 * @modify 2024
 */

#ifndef EV_INST_COMMAND_HPP
#define EV_INST_COMMAND_HPP

#include "inst.hpp"

namespace ev{

/**
 * @class EVCommand
 * @brief easyVim 指令类
 * @details 定义了easyVim的指令类，包括保存、退出、搜索、替换、加密、解密等指令
 */
class EVCommand : public EVConfig{
public:
    enum instType {
        INST_SAVE           = 0, ///< 保存
        INST_SAVE_NEW       = 1, ///< 另存为，需要参数指定新的文件名，如果文件已存在则失败，强制指令则覆盖
        INST_QUIT           = 2, ///< 退出，如果文件未保存且不是强制指令则失败
        INST_SAVE_QUIT      = 3, ///< 保存并退出
        INST_QUIT_F         = 4, ///< 强制退出

        INST_RELOAD         = 10, ///< 重新加载，在打开多个文件的时候用于同步更改
        INST_RELOAD_F       = 11, ///< 强制重新加载

        INST_SEARCH         = 32, ///< 搜索，需要参数指定搜索内容
        INST_SEARCH_REPLACE = 33, ///< 搜索并替换，需要参数指定搜索内容和替换内容 //todo 增加参数指定替换范围
        INST_ENCRYPT        = 34, ///< 对称加密
        INST_DECRYPT        = 35, ///< 对称解密

        INST_JUMP           = 61, ///< 跳转，需要参数指定跳转位置
        INST_ESC            = 62, ///< 回到正常模式
        INST_CHANGE_CODEC   = 63, ///< 更改编码，需要参数指定新的编码
        // todo 增加更多指令，比如rsa加密解密
    };

    enum commandStatus {
        COMMAND_OK          = 0, ///< 指令执行成功
        COMMAND_FAIL        = 1, ///< 指令执行失败
        COMMAND_PARAM_ERROR = 2, ///< 参数错误
        COMMAND_NOT_EXIST   = 3, ///< 指令不存在

        COMMAND_TRY_COVER_RELOAD  = 11, ///< 文件中有更改，试图进行覆盖式的重新加载

        COMMAND_TRY_UNSAVE_EXIT   = 21, ///< 试图不保存文件退出
        
        COMMAND_NO_MATCH_PATTERN  = 31, ///< 查找不到匹配结果

        COMMAND_OK_EXIT           = 41, ///< 指令执行成功并且退出程序

        COMMAND_JUMP              = 51, ///< 跳转
        COMMAND_BACK              = 52, ///< 退出
    };

    EVCommand(std::string f = "") : EVConfig(f){}
    ~EVCommand(){}

    /**
     * @brief 读取配置文件
     * @return evFileStatus 文件状态
     */
    EVFile::EVFileStatus loadConfig();

    /**
     * @brief 执行指令
     * @param inst 指令, params 参数列表
     * @return 指令执行结果
     */
    commandStatus execCommand(std::vector<std::string> params, ev::EVFile* file_);

    std::unordered_map<std::string, int> config;    ///< 配置信息
};

} // namespace ev

#endif //EV_INST_COMMAND_HPP