/**
 * @file loadsave.cpp
 * @brief easyVim文件读写模块
 * @author Super redhecker@github
 * @modify 2024
 */

#include "core.hpp"
#include <cstring>

namespace ev {

EVFile::EVFileStatus EVFile::loadFile(){
    file = fopen(fileName.c_str(), "r");
    if (file == NULL){
        return EVFileStatus::EVFILE_OPEN_FAIL;
    }
    

    char buf[8192] = {0};

    start = 0;
    offset = 0;
    fileContent = std::vector<std::string>();
    while(fgets(buf, 8192, file) != NULL){
        // 如果末尾有换行符需要去掉
        if (buf[strlen(buf) - 1] == '\n'){
            buf[strlen(buf) - 1] = '\0';
        }
        fileContent.push_back(buf);
    }
    
    fclose(file);
    file = NULL;

    return EVFileStatus::EVFILE_OK;
}

EVFile::EVFileStatus EVFile::saveFile(){
    file = fopen(fileName.c_str(), "w");

    if (file == NULL){
        return EVFileStatus::EVFILE_OPEN_FAIL;
    }

    for (auto& line : fileContent){
        fputs(line.c_str(), file);
        fputs("\n", file);
    }

    fclose(file);
    file = NULL;

    return EVFileStatus::EVFILE_OK;
}


EVFile::~EVFile(){
    if (file != NULL){
        fclose(file);
    }
}

} //namespacec ev