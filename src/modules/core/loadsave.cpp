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
        if (fputs(line.c_str(), file) == EOF) {
            fclose(file);
            return EVFILE_WRITE_FAIL;
        }
        if (fputs("\n", file) == EOF) {
            fclose(file);
            return EVFILE_WRITE_FAIL;
        }
    }

    hasChange = false;
    if (fclose(file) != 0)  
    {
        return EVFILE_CLOSE_FAIL;
    }
    file = NULL;

    return EVFileStatus::EVFILE_OK;
}


EVFile::EVFileStatus EVFile::saveFileAs(const std::string& newFilePath) {
    FILE* newFile = fopen(newFilePath.c_str(), "w");
    if (!newFile) {
        return EVFILE_OPEN_FAIL;
    }

    for (const auto& line : fileContent) {
        if (fputs(line.c_str(), newFile) == EOF) {
            fclose(newFile);
            return EVFILE_WRITE_FAIL;
        }
        if (fputc('\n', newFile) == EOF) {
            fclose(newFile);
            return EVFILE_WRITE_FAIL;
        }
    }
    if (fclose(newFile) != 0) {
        return EVFILE_CLOSE_FAIL;
    }
    return EVFILE_OK;
}


EVFile::EVFileStatus EVFile::quitFile(){
    if (fclose(file) == EOF){
        return EVFileStatus::EVFILE_CLOSE_FAIL;
    }
    return EVFileStatus::EVFILE_OK;
}

EVFile::~EVFile(){
    if (file != NULL){
        fclose(file);
    }
}

} //namespacec ev