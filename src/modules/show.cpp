/**
 * @file show.cpp
 * @brief easyVim显示模块实现文件
 * @author Super redhecker@github
 * @modify 2024
 */

#include "show.hpp"
#include <ncurses.h>
#include <locale.h>
#include <math.h>
#define EV_SHOW_DEBUG 1
#if EV_SHOW_DEBUG
#include <stdio.h>
#endif

namespace ev {
// 注意：LINES和COLS是ncurses库中的变量，分别表示当前终端的行数和列数，其中LINES需要减1，因为最后一行是状态栏
    
void window::init() {
    setlocale(LC_ALL,"");
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    if (!has_colors()) {
        quit();
        exit(1);
    }
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    updateStatus();
    refresh();
    curRow = 0;
    curCol = 0;
    return;
}

void window::updateStatus(){
    int row, col;
    getyx(stdscr, row, col);
    attron(COLOR_PAIR(1));
    move(LINES-1, 0);
    clrtoeol(); // 清除当前行
    if (status == NORMAL) {
        printw("--NORMAL--");
    } else if (status == INSERT) {
        printw("--INSERT--");
    } else if (status == COVER) {
        printw("--COVER--");
    } else if (status == COMMAND) {
        printw(":");
    }
    attroff(COLOR_PAIR(1));
    move(row, col);
    refresh();
    return;
}

int window::getInput(){
    return getch();
}

void window::quit(){
    endwin();
    return;
}

void window::moveUp(){
    getyx(stdscr, y, x);
    if (y > INIT_LINE) {
        curRow = y + lineNumber - INIT_LINE - 1;
        if (moveCur()) {
            flushScreen();
        }
    } else if (y == INIT_LINE) {
        if (lineNumber > 0) {
            lineNumber --;
            curRow = y + lineNumber - INIT_LINE;
            moveCur();
            flushScreen();
        }
    }
    refresh();
    return;
}

void window::moveDown(){
    getyx(stdscr, y, x);
    if (y < (LINES - 1) - 1 && (size_t)y < file->fileContent.size() - lineNumber - 1) {
        curRow = y + lineNumber - INIT_LINE + 1;
        if (moveCur()) {
            flushScreen();
        }
    } else if (y == (LINES - 1) - 1) {
        if ((size_t)y < file->fileContent.size() - lineNumber - 1) {
            lineNumber ++;
            curRow = y + lineNumber - INIT_LINE;
            moveCur();
            flushScreen();
        } else {
            //todo 没有一次性导入所有文件的话有可能到这里
        }
    }
    refresh();
    return;
}

void window::moveLeft(){
    getyx(stdscr, y, x);
    if (x > INIT_COL) {
        curCol = x + colNumber - INIT_COL - 1;
        moveCur();
    } else if (colNumber > 0) {
        colNumber --;
        curCol = colNumber;
        flushScreen();
    }
    refresh();
    return;
}

void window::moveRight(){
    getyx(stdscr, y, x);
    if (x < COLS - 1 && (size_t)x < file->fileContent[curRow].length() + INIT_COL - colNumber) {
        curCol = x + colNumber - INIT_COL + 1;
        moveCur();
    } else if (x == COLS - 1) {
        if ((size_t)x < file->fileContent[curRow].length() + INIT_COL - colNumber) {
            colNumber ++;
            curCol = x + colNumber - INIT_COL;
            flushScreen();
        }
    }
    refresh();
    return;
}

void window::moveHead(){
    curCol = 0;
    if (moveCur()) {
        flushScreen();
    } else {
        refresh();
    }
    return;
}

void window::moveEnd(){
    curCol = file->fileContent[curRow].length();
    if (moveCur()) {
        flushScreen();
    } else {
        refresh();
    }
    return;
}

void window::moveTop(){
    // todo 如果文件被分块读取的话，需要有别的操作
    curRow = 0;
    curCol = 0;
    if (moveCur()) {
        flushScreen();
    } else {
        refresh();
    }
    return;
}

void window::moveBottom(){
    // todo 如果文件被分块读取的话，需要有别的操作
    curRow = file->fileContent.size() - 1;
    curCol = 0;
    if (moveCur()) {
        flushScreen();
    } else {
        refresh();
    }
    return;
}

//todo 不知道有没有办法能实现检测窗口尺寸变化并实时更新(不过应该问题不大，多调用一下这个函数)
void window::flushScreen(){
    updateStatus();
    // int row, col;
    // getyx(stdscr, row, col);
    move(0, 0);
    std::vector<std::string> content = file->fileContent;
    auto searchPosition = file->searchPosition;
    for (int i = 0; i < (LINES - 1); i++){
        if (lineNumber + i < content.size()) {
            attron(A_BOLD);
            // 打印行号
            int lineNum = (lineNumber + i + file->start + 1) % 10000;
            if (lineNum > 999) {
                printw("%d ", lineNum); 
            } else if (lineNum > 99) {
                printw("0%d ", lineNum); 
            } else if (lineNum > 9) {
                printw("00%d ", lineNum); 
            } else {
                printw("000%d ", lineNum); 
            }
            attroff(A_BOLD);

            //如果整列都不在显示范围内（或者是空的）
            if (colNumber >= content[lineNumber + i].length()) {
                printw("\n");
            } else {
                std::string lineContent = content[lineNumber + i];
                size_t lastPos = colNumber;  // 用于追踪上一个打印的位置, colNumber是当前显示的最前面的列号

                // 遍历搜索位置并打印高亮内容（只对一个字符进行高亮）
                for (const auto& pos : searchPosition) {
                    size_t matchLine = pos.first; // 匹配的行号
                    size_t matchCol = pos.second; // 匹配的列号

                    // 只处理当前行的匹配
                    if (matchLine == lineNumber + i) {
                        // 如果匹配列号在当前显示范围内
                        if (matchCol >= colNumber && matchCol < colNumber + COLS - 5) {
                            int offset = matchCol - colNumber; // 当前字符相对位置

                            // 输出从上次输出到当前匹配位置之间的未高亮部分
                            printw("%s", lineContent.substr(lastPos, offset - lastPos).c_str());

                            // 高亮当前匹配字符
                            attron(A_BOLD | COLOR_PAIR(1));
                            printw("%c", lineContent[offset]);
                            attroff(A_BOLD | COLOR_PAIR(1));

                            // 更新 lastPos 到当前匹配位置的下一个字符
                            lastPos = offset + 1;
                        }
                    }
                }

                // 输出剩余部分
                if (lastPos < lineContent.length()) {
                    if (COLS + colNumber - INIT_COL > lineContent.length())
                        printw("%s\n", lineContent.substr(lastPos).c_str());
                    else 
                        printw("%s", lineContent.substr(lastPos, COLS - lastPos + colNumber - INIT_COL).c_str());
                } else {
                    printw("\n");
                }
            }
        } else {
            attron(COLOR_PAIR(1));
            printw("~\n");
            attroff(COLOR_PAIR(1));
        }
    }
    // move(row, col);
    moveCur();
    refresh();
    return;
}

// todo 可能也需要根据curRow和curCol来刷新
void window::flushLine(){
    int row, col;
    getyx(stdscr, row, col);
    move(row, 5);
    std::string line = file->fileContent[lineNumber + row];
    // 打印行内对应内容
    if (line.length() > colNumber + COLS - 5) {
        printw("%s\n", line.substr(colNumber, colNumber + COLS - 5).c_str());
    } else {
        printw("%s\n", line.substr(colNumber).c_str());
    }
    move(row, col);
    refresh();
    return;
}

std::string window::getCommand(){
    if (status != COMMAND) {
        return "";
    }
    int row, col;
    getyx(stdscr, row, col);
    move(LINES - 1, 1);
    echo();
    char buf[1024] = {0};
    getstr(buf);
    noecho();
    move(row, col);
    return std::string(buf);
}

void window::moveTo(size_t line, size_t col){
    //todo 不安全的实现，尽量不要用
    move(line, col);
    return;
}

bool window::moveCur(){
    bool result = false;
    if (curRow < 0 || curCol < 0 || curRow >= file->fileContent.size()) {
        return false;
    }
    if (curRow < lineNumber) {
        lineNumber = curRow;
        result = true;
    } else if (curRow >= lineNumber + LINES - 1 - INIT_LINE) {
        lineNumber = curRow - (LINES - 1) + INIT_LINE + 1;
        result = true;
    }
    size_t cc = curCol;

    cc = std::min(cc, file->fileContent[curRow].length());
    if (cc < colNumber) {
        if (cc == 0) {
            colNumber = cc;
        } else {
            colNumber = cc - 1;
        }
        result = true;
    } else if (cc > colNumber + COLS - INIT_COL -1) {
        colNumber = cc - COLS + INIT_COL + 1;
        result = true;
    }
    
    move(curRow + INIT_LINE - lineNumber, cc + INIT_COL - colNumber);
    return result;
}

void window::getCuryx(int& x, int& y){
    getyx(stdscr, y, x);
    y -= INIT_LINE;
    x -= INIT_COL;
    y += lineNumber;
    x += colNumber;
}

void window::refreshCur(bool flush){
    int x, y;
    getyx(stdscr, y, x);
    y -= INIT_LINE;
    x -= INIT_COL;
    y += lineNumber;
    x += colNumber;
    curRow = (size_t)y;
    curCol = (size_t)x;
    if (flush)
        flushScreen();
}

void window::printWin(std::string str){
    printw("%s", str.c_str());
    return;
}


    
} // namespace ev