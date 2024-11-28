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


namespace ev {

class window{
public:
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
    void flushScreen(const std::vector<std::string>& file, size_t x, size_t y, size_t start = 0);

    /**@function   flushLine
     * @brief 刷新一行文本
     * @param line 文本内容
     * @param y    屏幕看得到的起始列号 //todo 把这个参数做成window的成员变量
     */
    void flushLine(const std::string& line, size_t y);

    //todo 这几个类目前实现得不太对，比如上下的时候有可能会需要依据原先的形状来判断col的位置
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void moveHead();
    void moveTail();
    void moveBegin();
    void moveEnd();


private:
    int lineNumber;

    void moveCursor(int row, int col);
};

}




#endif //EASYVIM_SHOW_HPP