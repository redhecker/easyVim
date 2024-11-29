/**@file       show.hpp
* @brief       easyVim显示模块头文件
* @details     定义了easyVim的GUI逻辑
* @author      Super@redhecker
* @copyright   Copyright (c) 2024
*/

#ifndef EASYVIM_SHOW_HPP
#define EASYVIM_SHOW_HPP
#include <ncurses.h>
#include <vector>
#include <string>
#include <iostream>


namespace ev {

class window{
public:

    enum WindowStatus{
        NORMAL  = 0, ///< 正常模式
        INSERT  = 1, ///< 插入模式
        COMMAND = 2  ///< 命令模式
    };

    window() : lineNumber(0), colNumber(0), status(NORMAL){}
    ~window(){
        quit();
    }
    void init();
    void quit();
    int  getInput();

    /**@function   flushScreen
     * @brief 刷新整个屏幕
     * @param file 文本内容
     * @param x    屏幕左上文本行号
     * @param y    屏幕左上文本列号
     * @param start file的起始行号
     * @todo 优化显示效果: 1. 行号显示 2. 高亮显示 3. 滚动条
     */
    void flushScreen(const std::vector<std::string>& file, size_t start = 0);

    /**@function   flushLine
     * @brief 刷新一行文本
     * @param line 文本内容
     */
    void flushLine(const std::string& line);

    /**@function   updateStatus
     * @brief 更新状态栏
     * @todo 优化显示效果: 1. 显示当前行号和列号
     */
    void updateStatus();

    std::string getCommand();

    //todo 这几个类目前实现得不太对，比如上下的时候有可能会需要依据原先的形状来判断col的位置
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void moveHead();
    void moveTail();
    void moveBegin();
    void moveEnd();

    WindowStatus getStatus(){
        return status;
    }
    bool setStatus(WindowStatus s){
        status = s;
        return true;
    }


private:
    size_t          lineNumber; ///< 当前屏幕首行对应file vector的行号
    size_t          colNumber;  ///< 当前屏幕首列对应file vector的列号
    WindowStatus    status;
};

}




#endif //EASYVIM_SHOW_HPP