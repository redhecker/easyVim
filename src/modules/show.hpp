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
        COMMAND = 3, ///< 命令模式

        WARNING_TRY_UNSAVE_QUIT = 11, ///< 尝试不保存退出
        WARNING_NO_MATCH_PATTERN = 12, ///< 未查找到匹配样式
        WARNING_COMMAND_NOT_EXIST = 13, ///< 指令不存在
        WARNING_COMMAND_PARAM_ERROR = 14, ///< 指令参数错误
        WARNING_COMMAND_FAIL = 15, ///< 指令执行失败
        WARNING_TRY_COVER_RELOAD = 16, ///< 尝试覆盖内容
    };

    window(EVFile* f) : lineNumber(0), colNumber(0), status(NORMAL), file(f){}
    ~window(){
    }
    void init();
    void quit();

    /**@function   getInput
     * @brief 获取用户输入，用户一旦输入就立即返回
     * @return 用户输入的ASCII码
     */
    int  getInput();

    /**@function   getCommand
     * @brief 获取命令行输入，遇到'\n'返回输入字符串
     * @return 命令行输入字符串
     */
    std::string getCommand();

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

    void moveTo(size_t line, size_t col);

    /**@function   moveCur
     * @brief 移动光标到当前行，列
     * @details 根据当前光标位置，判断是否需要刷新屏幕
     * @note 内部方法，理论上不应该被外部调用
     * @return 是否需要刷新屏幕
     */
    bool moveCur();

    /**@function   moveUp
     * @brief 光标上移
     */
    void moveUp();

    /**@function   moveDown
     * @brief 光标下移
     */
    void moveDown();

    /**@function   moveLeft
     * @brief 光标左移
     */
    void moveLeft();

    /**@function   moveRight
     * @brief 光标右移
     */
    void moveRight();

    /**@function   moveHead
     * @brief 光标移动到行首
     */
    void moveHead();

    /**@function   moveEnd
     * @brief 光标移动到行尾
     */
    void moveEnd();

    /**@function   moveTop
     * @brief 光标移动到文件首行
     */
    void moveTop();

    /**@function   moveBottom
     * @brief 光标移动到文件末行
     */
    void moveBottom();


    WindowStatus getStatus(){
        return status;
    }
    bool setStatus(WindowStatus s){
        status = s;
        return true;
    }
    void printWin(std::string str);

    void getCuryx(int& x, int& y);

    void refreshCur(bool flush = true);

    size_t getCurRow(){
        return curRow;
    }

    size_t getCurCol(){
        return curCol;
    }

    void setCurRow(size_t row){
        curRow = row;
        return;
    }


private:
    size_t          lineNumber; ///< 当前屏幕首行对应file vector的行号
    size_t          colNumber;  ///< 当前屏幕首列对应file vector的列号
    size_t          curRow, curCol; ///< 光标在文件中的位置，与lineNumber和colNumber无关
    WindowStatus    status;
    EVFile*         file;
    int             x, y;
};

}




#endif //EASYVIM_SHOW_HPP