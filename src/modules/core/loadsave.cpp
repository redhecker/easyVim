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
        }
        fileContent.push_back(buf);
    }
    
    fclose(file);
    file = NULL;

    hasChange = false;
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

EVFile::EVFileStatus EVFile::insertChar(int row, int col, char x) {  
    if (row < 0 || (size_t)row >= fileContent.size() 
    ||  col < 0 || (size_t)col >  fileContent[row].size()) { 
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
    if (row < 0 || (size_t)row >= fileContent.size() 
    ||  col < 0 || (size_t)col >  fileContent[row].size()) {  
        return EVFileStatus::EVFILE_OUT_OF_BOUND;  
    }

    fileContent[row][col] = x;  
    hasChange = true;   

    return EVFileStatus::EVFILE_OK;  
}

EVFile::EVFileStatus EVFile::deleteChar(int row, int col, bool isFront) {
    if (row < 0 || (size_t)row >= fileContent.size() 
    ||  col < 0 || (size_t)col >  fileContent[row].size()) {
        return EVFileStatus::EVFILE_OUT_OF_BOUND;  
    }

    if (isFront) {
        if (col > 0) {
            fileContent[row].erase(fileContent[row].begin() + col - 1);  
        } else {
            // 这个目前的问题在于对光标的掌控不足
            if (row > 0) {
                // size_t lastCol = fileContent[row - 1].size();
                fileContent[row - 1] += fileContent[row];
                fileContent.erase(fileContent.begin() + row); 
            }
        }  
    } else {  
        if ((size_t)col < fileContent[row].size()) {
            fileContent[row].erase(fileContent[row].begin() + col);  
        } else if ((size_t)row < fileContent.size() - 1) {  
            fileContent[row] += fileContent[row + 1];  
            fileContent.erase(fileContent.begin() + row + 1);   
        }  
    }  

    hasChange = true; 
    return EVFileStatus::EVFILE_OK; 
}

EVFile::EVFileStatus EVFile::deleteLine(int rowB, int colB, int rowE, int colE) {
    if (rowE == -1) {  
        rowE = fileContent.size() - 1;
    } else if (rowE == 0) {
        rowE = rowB;
    }
    if (colE == -1) {  
        colE = fileContent[rowE].size() - 1; 
    }
    if (rowB < 0 || rowE < rowB || colB < 0 || colE < colB) {  
        return EVFileStatus::EVFILE_OUT_OF_BOUND;  
    }
    if ((size_t)colB >= fileContent[rowB].size() 
    ||  (size_t)colE >= fileContent[rowE].size()) {
        return EVFileStatus::EVFILE_OUT_OF_BOUND;  
    }

    if (rowB == rowE) {
        std::string line = fileContent[rowB];
        fileContent.erase(fileContent.begin() + rowB);
        if (colB > 0 || (size_t)colE < line.size() - 1) {
            fileContent.insert(fileContent.begin() + rowB, line.substr(0, colB) + line.substr(colE + 1));
        } 
    } else {
        // todo 这里的实现目前还是有问题的，（考虑全部都不是默认值的情况）
        for (int row = rowB; row <= rowE; ) {  
            if (row == rowB) { 
                std::string line = fileContent[row];
                fileContent.erase(fileContent.begin() + row);
                if (colB > 0) {
                    fileContent.insert(fileContent.begin() + row, line.substr(0, colB));
                    row++;
                } else {
                    rowE--;
                }
            } else if (row == rowE) {
                std::string line = fileContent[row];
                fileContent.erase(fileContent.begin() + row);
                if ((size_t)colE < line.size() - 1) {
                    fileContent.insert(fileContent.begin() + row, line.substr(colE + 1));
                    row++;
                } else {
                    rowE--;
                }
            } else {  
                fileContent.erase(fileContent.begin() + row);  
                --rowE; 
            }
        }
    }

    if (fileContent.size() == 0) {
        fileContent.push_back("");
    }

    hasChange = true;  
    return EVFileStatus::EVFILE_OK;   
}

// todo 这里的实现是有问题的，但是目前无所谓，之后可能要改
EVFile::EVFileStatus EVFile::copyLine(int rowB, int colB, int rowE, int colE) {
    if (rowE == 0) {  
        rowE = rowB;
    }
    if (colE == -1) {  
        colE = fileContent[rowE].size() - 1; 
    }
    if (rowB < 0 || rowE < rowB || (size_t)rowE >= fileContent.size()) {  
        return EVFileStatus::EVFILE_OUT_OF_BOUND;  
    }  

    copiedFile.clear();  
    for (int i = rowB; i <= rowE; ++i) { 
        std::string line = fileContent[i];  
        if (colB >= 0 && (size_t)colB < line.size() && (colE == -1 || (size_t)colE < line.size())) {  
            std::string toCopy = line.substr(colB, (colE == -1 ? std::string::npos : colE - colB + 1));  
            copiedFile.push_back(toCopy);  
        } else {  
            return EVFileStatus::EVFILE_OUT_OF_BOUND;   
        } 
    }  

    hasCopy = true;
    return EVFileStatus::EVFILE_OK;  
}  

EVFile::EVFileStatus EVFile::pasteLine(int row) {  
    if (!hasCopy) {  
        return EVFileStatus::EVFILE_COPY_NOTEXIST;  
    }  
    if (row < 0 || (size_t)row >= fileContent.size()) {  
        return EVFileStatus::EVFILE_OUT_OF_BOUND;  
    }  

    for (const auto& line : copiedFile) {
        fileContent.insert(fileContent.begin() + row, line);
        row++;
    }

    hasChange = true;
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
    if (file != NULL && fclose(file) == EOF){
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