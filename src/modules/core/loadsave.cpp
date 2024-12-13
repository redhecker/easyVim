/**
 * @file loadsave.cpp
 * @brief easyVim文件读写模块
 * @author Super redhecker@github
 * @modify 2024
 */

#include "core.hpp"
#include <cstring>
#include <sys/stat.h>

// --------------------- getFileSize ---------------------
// getFileSize函数来自于csdn文章：https://blog.csdn.net/cpp_learner/article/details/123018360
// 通过stat结构体 获得文件大小，单位字节
size_t getFileSize(const char *fileName) {

	if (fileName == NULL) {
		return 0;
	}
	
	// 这是一个存储文件(夹)信息的结构体，其中有文件大小和创建时间、访问时间、修改时间等
	struct stat statbuf;

	// 提供文件名字符串，获得文件属性结构体
	stat(fileName, &statbuf);
	
	// 获取文件大小
	size_t filesize = statbuf.st_size;

	return filesize;
}
// --------------------- getFileSize ---------------------


namespace ev {

EVFile::EVFileStatus EVFile::loadFile(){
    file = fopen(fileName.c_str(), "r");
    if (file == NULL){
        return EVFileStatus::EVFILE_NOT_EXIST;
    }

    size_t fileSize = getFileSize(fileName.c_str());
    if (fileSize > 1024 * 1024 * 1024){ // 1GB
        return EVFileStatus::EVFILE_READ_FAIL; // 文件读取失败，文件过大
    }
    

    char buf[8192] = {0};

    start = 0;
    offset = 0;
    fileContent = std::vector<std::string>();
    while(fgets(buf, 8192, file) != NULL){
        // 如果末尾有换行符需要去掉
        if (buf[strlen(buf) - 1] == '\n'){
            buf[strlen(buf) - 1] = '\0';
        } else {
            return EVFileStatus::EVFILE_READ_FAIL; // 文件读取失败，文件单行太长（超过8191个字符）
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