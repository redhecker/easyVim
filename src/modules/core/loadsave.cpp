/**
 * @file loadsave.cpp
 * @brief easyVim文件读写模块
 * @author Super redhecker@github
 * @author Liu Haoran Defect-sts@github
 * @author Zhong Yong OptimistiCompound@github
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

EVFile::EVFileStatus EVFile::insertChar(int row, int col, char x) {  
    if (row < 0 || (size_t)row >= fileContent.size() || col < 0 || (size_t)col > fileContent[row].size()) {  
        return EVFileStatus::EVFILE_OUT_OF_BOUND;  
    }

    if (x == '\n') {  
        std::string newLine = fileContent[row].substr(col);
        fileContent[row] = fileContent[row].substr(0, col); 
        fileContent.insert(fileContent.begin() + row + 1, newLine); 
    } else {  
        fileContent[row].insert(fileContent[row].begin() + col, x);  
    }  

    hasChange = true;
    return EVFileStatus::EVFILE_OK;  
}

EVFile::EVFileStatus EVFile::coverChar(int row, int col, char x) {
    if (row < 0 || row >= fileContent.size() || col < 0 || col > fileContent[row].size()) {  
        return EVFileStatus::EVFILE_OUT_OF_BOUND;  
    }

    fileContent[row][col] = x;  
    hasChange = true;   

    return EVFileStatus::EVFILE_OK;  
}

EVFile::EVFileStatus EVFile::deleteChar(int row, int col, bool isFront) {
    if (row < 0 || row >= fileContent.size() || col < 0 || col > fileContent[row].size()) {  
        return EVFileStatus::EVFILE_OUT_OF_BOUND;  
    }

    if (isFront) {  
        if (col > 0) {  
            fileContent[row].erase(fileContent[row].begin() + col - 1);  
        } else {  
            if (row > 0) {  
                size_t lastCol = fileContent[row - 1].size();  
                fileContent[row - 1].push_back(fileContent[row][0]); 
                fileContent.erase(fileContent.begin() + row); 
            }  
        }  
    } else {  
        if (col < fileContent[row].size() - 1) {  
            fileContent[row].erase(fileContent[row].begin() + col);  
        } else {  
            if (row < fileContent.size() - 1) {  
                fileContent[row] += fileContent[row + 1];  
                fileContent.erase(fileContent.begin() + row + 1); 
            }  
        }  
    }  

    hasChange = true; 
    return EVFileStatus::EVFILE_OK; 
}

EVFile::EVFileStatus EVFile::deleteLine(int rowB, int colB, int rowE, int colE) {
    if (rowE == -1) {  
        rowE = fileContent.size() - 1;
    }
    if (rowB < 0 || rowB > rowE || rowE >= fileContent.size()) {  
        return EVFileStatus::EVFILE_OUT_OF_BOUND; 
        return EVFileStatus::EVFILE_OUT_OF_BOUND; 
        return EVFileStatus::EVFILE_OUT_OF_BOUND;   
    }
    if (colB < 0 || colE < 0 || colB >= fileContent[rowB].size() || colE >= fileContent[rowE].size() || colB > colE) {  
        return EVFileStatus::EVFILE_OUT_OF_BOUND;  
    }

    for (int row = rowB; row <= rowE; ++row) {  
        if (row == rowB) {  
            fileContent[row].erase(fileContent[row].begin() + colB, fileContent[row].end());  
        } else if (row == rowE) {  
            fileContent[row].erase(fileContent[row].begin(), fileContent[row].begin() + colE + 2);  
        } else {  
            fileContent.erase(fileContent.begin() + row);  
            --rowE;  
            --row;   
        }  
    }  

    hasChange = true;  
    return EVFileStatus::EVFILE_OK;   
}

EVFile::EVFileStatus EVFile::copyLine(int rowB, int colB, int rowE, int colE) {  
    if (rowB < 0 || rowE < rowB || rowE >= fileContent.size()) {  
        return EVFileStatus::EVFILE_OUT_OF_BOUND;  
    }  

    copiedFile.clear();  
    for (int i = rowB; i <= rowE; ++i) { 
        std::string line = fileContent[i];  
        if (colB >= 0 && colB < line.size() && (colE == -1 || colE < line.size())) {  
            std::string toCopy = line.substr(colB, (colE == -1 ? std::string::npos : colE - colB + 1));  
            copiedFile.push_back(toCopy);  
        } else {  
            return EVFileStatus::EVFILE_OUT_OF_BOUND;   
        }  
    }  

    hasCopy = true;    
    return EVFileStatus::EVFILE_OK;  
}  

EVFile::EVFileStatus EVFile::pasteLine(int row, int col) {  
    if (!hasCopy) {  
        return EVFileStatus::EVFILE_OUT_OF_BOUND;  
    }  
    if (row < 0 || row >= fileContent.size()) {  
        return EVFileStatus::EVFILE_OUT_OF_BOUND;  
    }  

    for (const auto& line : copiedFile) {  
        fileContent.insert(fileContent.begin() + row, line);  
        row++; 
    }  

    hasChange = true;
    return EVFileStatus::EVFILE_OK;  
}


EVFile::~EVFile(){
    if (file != NULL){
        fclose(file);
    }
}

} //namespacec ev