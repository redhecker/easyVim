#include "inst_command.hpp"
#include <algorithm>

namespace ev{

EVFile::EVFileStatus EVConfig::loadConfig(){
    // 加载默认配置
    config["w"] = EVCommand::instType::INST_SAVE;
    config["wq"] = EVCommand::instType::INST_SAVE_QUIT;
    config["q"] = EVCommand::instType::INST_QUIT;
    config["q!"] = EVCommand::instType::INST_QUIT_F;
    config["wn"] = EVCommand::instType::INST_SAVE_NEW;

    config["/"] = EVCommand::instType::INST_SEARCH;
    config["s/"] = EVCommand::instType::INST_SEARCH_REPLACE;
    config["enc"] = EVCommand::instType::INST_ENCRYPT;
    config["dec"] = EVCommand::instType::INST_DECRYPT;

    if (instList.size() == 0){
        return EVFile::EVFileStatus::EVFILE_READ_FAIL;
    }

    for (auto& inst : instList){
        std::string key = inst.substr(0, inst.find(":"));
        std::string value = inst.substr(inst.find(":") + 1);
        std::transform(key.begin(), key.end(), key.begin(), ::tolower);
        if (key.size() == 0 || value.size() == 0){
            continue;
        } else if (key == "save"){
            config[value] = EVCommand::instType::INST_SAVE;
        } else if (key == "save and quit"){
            config[value] = EVCommand::instType::INST_SAVE_QUIT;
        } else if (key == "quit"){
            config[value] = EVCommand::instType::INST_QUIT;
        } else if (key == "quitf"){
            config[value] = EVCommand::instType::INST_QUIT_F;
        } else if (key == "search"){
            config[value] = EVCommand::instType::INST_SEARCH;
        } else if (key == "search and replace"){
            config[value] = EVCommand::instType::INST_SEARCH_REPLACE;
        } else if (key == "encrypt"){
            config[value] = EVCommand::instType::INST_ENCRYPT;
        } else if (key == "decrypt"){
            config[value] = EVCommand::instType::INST_DECRYPT;
        } else if (key == "change codec"){
            config[value] = EVCommand::instType::INST_CHANGE_CODEC;
        } else {
            continue;
        }
    }

    return EVFile::EVFileStatus::EVFILE_OK;
}


EVCommand::commandStatus EVCommand::execCommand(std::string inst, std::vector<std::string> params){
    switch (config[inst]){
    case EVCommand::instType::INST_SAVE:
        // todo 保存文件
        break;
    case EVCommand::instType::INST_SAVE_NEW:
        // todo 另存为
        break;
    case EVCommand::instType::INST_QUIT:
        // todo 退出
        break;
    case EVCommand::instType::INST_SAVE_QUIT:
        // todo 保存并退出
        break;
    case EVCommand::instType::INST_QUIT_F:
        // todo 强制退出
        break;
    case EVCommand::instType::INST_SEARCH:
        // todo 搜索
        break;
    case EVCommand::instType::INST_SEARCH_REPLACE:
        // todo 搜索并替换
        break;
    case EVCommand::instType::INST_ENCRYPT:
        // todo 加密
        break;
    case EVCommand::instType::INST_DECRYPT:
        // todo 解密
        break;
    case EVCommand::instType::INST_CHANGE_CODEC:
        // todo 更改编码
        break;
    default:
        return commandStatus::COMMAND_NOT_EXIST;
    }

    return commandStatus::COMMAND_OK;
}

} // namespace ev