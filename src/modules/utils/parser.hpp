/**
 * @file parser.hpp
 * @brief 解析命令行参数
 * @author Super redhecker@github
 * @modify 2024
 */

#ifndef UTILS_PARSER_HPP
#define UTILS_PARSER_HPP

#include <string>
#include <vector>
#include <unordered_map>

namespace ev {

/**
 * @class Parser
 * @brief easyVim 解析器类
 * @details 用于解析用户输入的指令
 */
class Parser{
public:
    Parser();
    ~Parser(){}

    /**
     * @brief 解析指令
     * @param input 输入指令
     * @return 解析结果
     */
    std::unordered_map<std::string, std::string> parse(int argc, char** argv);

    /**
     * @brief 添加指令
     * @param command 指令
     * @param help 指令帮助信息
     */
    void addCommand(std::string command, std::string help = ""){
        commands.push_back(command);
        helps.push_back(help);
    }

    /**
     * @brief 获取指令列表
     * @return 帮助信息
     */
    std::string help(){
        std::string result = "";
        for (size_t i = 0; i < commands.size(); i++){
            if (commands[i].size() > 1){
                result += "--" + commands[i] + "\t" + helps[i] + "\n";
            } else {
                result += "-" + commands[i] + "\t" + helps[i] + "\n";
            }
        }
        return result;
    }

private:
    std::vector<std::string> commands;
    std::vector<std::string> helps;
};

}



#endif //UTILS_PARSER_HPP