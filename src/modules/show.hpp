/**@file       show.hpp
* @brief       easyVim显示模块头文件
* @details     定义了easyVim的GUI逻辑
* @author      Super@redhecker
* @copyright   Copyright (c) 2024
*/

#ifndef EASYVIM_SHOW_HPP
#define EASYVIM_SHOW_HPP
#include <vector>
#include <string>
#include <iostream>
#include "config.hpp"


namespace ev {

class window{
public:

    enum WindowStatus{
        NORMAL  = 0, ///< 正常模式
        INSERT  = 1, ///< 插入模式
        COVER   = 2, ///< 覆盖模式
        COMMAND = 3  ///< 命令模式
    };

    window(EVFile* f) : lineNumber(0), colNumber(0), status(NORMAL), file(f){}
    ~window(){
    }
    void init();
    void quit();
    int  getInput();

    /**@function   flushScreen
     * @brief 刷新整个屏幕
     * @todo 优化显示效果: 1. 行号显示 2. 高亮显示 3. 滚动条
     */
    void flushScreen();

    /**@function   flushLine
     * @brief 刷新当前行文本
     */
    void flushLine();

    /**@function   updateStatus
     * @brief 更新状态栏
     * @todo 优化显示效果: 1. 显示当前行号和列号
     */
    void updateStatus();

    std::string getCommand();

    void moveTo(size_t line, size_t col);
    bool moveCur();

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void moveHead();
    void moveEnd();
    void moveTop();
    void moveBottom();


    WindowStatus getStatus(){
        return status;
    }
    bool setStatus(WindowStatus s){
        status = s;
        return true;
    }
    void printWin(std::string str);


private:
    size_t          lineNumber; ///< 当前屏幕首行对应file vector的行号
    size_t          colNumber;  ///< 当前屏幕首列对应file vector的列号
    size_t          curRow, curCol; ///< 光标在文件中的位置，与lineNumber和colNumber无关
    WindowStatus    status;
    EVFile*         file;
};

}




#endif //EASYVIM_SHOW_HPP