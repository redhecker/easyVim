/**
 * @file inst_command.hpp
 * @brief easyVim Normal模式下指令模块头文件
 * @author Super@redhecker
 * @modify 2024
 */

#ifndef EV_INST_OPER_HPP
#define EV_INST_OPER_HPP

#include "inst.hpp"

namespace ev{

/**
 * @class EVCommand
 * @brief easyVim 指令类
 * @details 定义了easyVim的指令类，包括保存、退出、搜索、替换、加密、解密等指令
 */
class EVOper : public EVConfig{
public:

    EVOper(std::string f = "") : EVConfig(f){}
    ~EVOper(){}

    /**
     * @brief 读取配置文件
     * @return evFileStatus 文件状态
     */
    EVFile::EVFileStatus loadConfig();

    /**
     * @brief 获取指令
     * @param oper 操作符
     * @return 操作符
     */
    int getOper(int oper);

    std::unordered_map<int, int> config;    ///< 配置信息
};

} // namespace ev

#endif //EV_INST_OPER_HPP