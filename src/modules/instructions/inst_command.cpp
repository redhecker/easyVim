/**
 * @file inst_command.cpp
 * @brief easyVim指令模块实现文件
 * @author Super@redhecker
 * @modify 2024
 */

#include "inst_command.hpp"
#include <algorithm>

namespace ev{

EVFile::EVFileStatus EVCommand::loadConfig(){
    // 加载默认配置
    config["w"] = EVCommand::instType::INST_SAVE;
    config["wq"] = EVCommand::instType::INST_SAVE_QUIT;
    config["q"] = EVCommand::instType::INST_QUIT;
    config["q!"] = EVCommand::instType::INST_QUIT_F;
    config["wn"] = EVCommand::instType::INST_SAVE_NEW;
    config["j"] = EVCommand::instType::INST_JUMP;
    config["exit"] = EVCommand::instType::INST_ESC;

    config["reload"] = EVCommand::instType::INST_RELOAD;
    config["reload!"] = EVCommand::instType::INST_RELOAD_F;

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
        } else if (key == "reload"){
            config[value] = EVCommand::instType::INST_RELOAD;
        } else if (key == "reload!"){
            config[value] = EVCommand::instType::INST_RELOAD_F;
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
        } else if (key == "jump"){
            config[value] = EVCommand::instType::INST_JUMP;
        } else if (key == "esc"){
            config[value] = EVCommand::instType::INST_ESC;
        } else {
            continue;
        }
    }

    return EVFile::EVFileStatus::EVFILE_OK;
}


EVCommand::commandStatus EVCommand::execCommand(std::vector<std::string> params, ev::EVFile* file_){
    if (params.size() == 0) {
        return EVCommand::COMMAND_FAIL;
    }

    EVCommand::commandStatus res = commandStatus::COMMAND_FAIL;

    switch (config[params[0]]){
    case EVCommand::instType::INST_SAVE:{
        if (params.size() != 1){
            res = COMMAND_PARAM_ERROR;
            break;
        }
        if (file_->saveFile() != EVFile::EVFileStatus::EVFILE_OK){
            res = COMMAND_FAIL;
            break;
        }
        res = COMMAND_OK;
        break;
    }
    case EVCommand::instType::INST_RELOAD:{
        if (params.size() != 1){
            res = COMMAND_PARAM_ERROR;
            break;
        }
        if (file_->hasChange)
        {
            res = COMMAND_TRY_COVER_RELOAD;
            break;
        }
        if (file_->loadFile() != EVFile::EVFileStatus::EVFILE_OK)
        {
            res = COMMAND_FAIL;
            break;
        }
        res = COMMAND_OK;
        break;
    }
    case EVCommand::instType::INST_RELOAD_F:{
        if (params.size() != 1){
            res = COMMAND_PARAM_ERROR;
            break;
        }
        if (file_->loadFile() != EVFile::EVFileStatus::EVFILE_OK)
        {
            res = COMMAND_FAIL;
            break;
        }
        res = COMMAND_OK;
        break;
    }
    case EVCommand::instType::INST_SAVE_NEW:{
        if (params.size() != 2)
        {
            res = COMMAND_PARAM_ERROR;
            break;
        }
        const std::string& path = params[1];
        bool check_path = true;
        // todo 解析路径的正确性
        if (check_path == false){
            res = COMMAND_PARAM_ERROR;
            break;
        }

        if (file_->saveFileAs(path) != EVFile::EVFileStatus::EVFILE_OK){
            res = COMMAND_FAIL;
            break;
        }
        res = COMMAND_OK;
        break;
    }
    case EVCommand::instType::INST_QUIT:{
        if (params.size() != 1){
            res = COMMAND_PARAM_ERROR;
            break;
        }

        if (file_->hasChange){
            res = COMMAND_TRY_UNSAVE_EXIT;
            break;
        }
        if (file_->quitFile() != EVFile::EVFileStatus::EVFILE_OK){
            res = COMMAND_FAIL;
            break;
        }
        res = COMMAND_OK_EXIT;
        break;
    }
    case EVCommand::instType::INST_SAVE_QUIT:{
        if (params.size() != 1)
        {
            res = COMMAND_PARAM_ERROR;
            break;
        }

        if (file_->saveFile() != EVFile::EVFileStatus::EVFILE_OK){
            res = COMMAND_FAIL;
            break;
        }
        if (file_->quitFile() != EVFile::EVFileStatus::EVFILE_OK){
            res = COMMAND_FAIL;
            break;
        }
        res = COMMAND_OK_EXIT;
        break;
    }
    case EVCommand::instType::INST_QUIT_F:{
        if (params.size() != 1)
        {
            res = COMMAND_PARAM_ERROR;
            break;
        }
        
        if (file_->quitFile() != EVFile::EVFileStatus::EVFILE_OK){
            res = COMMAND_FAIL;
            break;
        }
        res = COMMAND_OK_EXIT;
        break;
    }
    case EVCommand::instType::INST_SEARCH:{
        if (params.size() != 2){
            res = COMMAND_PARAM_ERROR;
            break;
        }

        res = (file_->searchInFile(params[1]) == EVFile::EVFILE_NO_MATCH_PATTERN) ? 
            COMMAND_NO_MATCH_PATTERN : COMMAND_OK;
        break;
    }
    case EVCommand::instType::INST_SEARCH_REPLACE:{
        if (params.size() != 3){
            res = COMMAND_PARAM_ERROR;
            break;
        }
        
        auto fileStatus = file_->searchReplace(params[1], params[2]);
        if (fileStatus == EVFile::EVFILE_NO_MATCH_PATTERN){
            res = COMMAND_NO_MATCH_PATTERN;        
        }
        else if (fileStatus == EVFile::EVFILE_REPLACE_FAIL){
            res = COMMAND_FAIL;
        }
        else{
            res = COMMAND_OK;
        }
        break;
    }
    case EVCommand::instType::INST_JUMP:{
        if (params.size() != 2){
            res = COMMAND_PARAM_ERROR;
            break;
        }

        // todo 跳转
        int num = stoi(params[1], nullptr, 10);
        if (num == -1) {
            num = file_->fileContent.size() - 1;
        }
        if (num < 0 || (size_t)num >= file_->fileContent.size()){
            res = COMMAND_PARAM_ERROR;
            break;
        }
        file_->jumpTo = num;
        res = COMMAND_JUMP;
        break;
    }
    case EVCommand::instType::INST_ESC:
        res = COMMAND_BACK;
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
        res = commandStatus::COMMAND_NOT_EXIST;
    }

    return res;
}

} // namespace ev