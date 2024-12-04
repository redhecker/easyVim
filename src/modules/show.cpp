/**
 * @file show.cpp
 * @brief easyVim显示模块实现文件
 * @author Super redhecker@github
 * @modify 2024
 */

#include "show.hpp"
#include <ncurses.h>
#define EV_SHOW_DEBUG 1
#if EV_SHOW_DEBUG
#include <stdio.h>
#endif

namespace ev {
// 注意：LINES和COLS是ncurses库中的变量，分别表示当前终端的行数和列数，其中LINES需要减1，因为最后一行是状态栏
    
void window::init() {
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
    return;
}

void window::updateStatus(){
    int row, col;
    getyx(stdscr, row, col);
    attron(COLOR_PAIR(1));
    move(LINES-1, 0);
    if (status == NORMAL) {
        printw("--NORMAL--");
    } else if (status == INSERT) {
        printw("--INSERT--");
    } else if (status == COVER) {
        printw("--COVER-- ");
    } else if (status == COMMAND) {
        printw(":         ");
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
    int x, y;
    getyx(stdscr, y, x);
    if (y > INIT_LINE) {
        move(y - 1, x);
    } else if (y == INIT_LINE) {
        if (lineNumber > 0) {
            lineNumber --;
            flushScreen();
        }
    }
    refresh();
    return;
}

void window::moveDown(){
    int x, y;
    getyx(stdscr, y, x);
    if (y < (LINES - 1) - 1 && (size_t)y < file->fileContent.size() - lineNumber - 1) {
        move(y + 1, x);
    } else if (y == (LINES - 1) - 1) {
        if (y < file->fileContent.size() - lineNumber - 1) {
            lineNumber ++;
            flushScreen();
        } else {
            //todo 没有一次性导入所有文件的话有可能
        }
    }
    refresh();
    return;
}

void window::moveLeft(){
    int x, y;
    getyx(stdscr, y, x);
    if (x > INIT_COL) {
        move(y, x - 1);
    } else if (colNumber > 0) {
        colNumber --;
        flushScreen();
    }
    refresh();
    return;
}

void window::moveRight(){
    int x, y;
    getyx(stdscr, y, x);
    if (x < COLS - 1 && (size_t)x < file->fileContent[y + lineNumber].length() + INIT_COL - 1) {
        move(y, x + 1);
    } else if (x == COLS - 1) {
        if (x < file->fileContent[y + lineNumber].length() + INIT_COL - colNumber - 1) {
            colNumber ++;
            flushScreen();
        }
    }
    refresh();
    return;
}

//todo 不知道有没有办法能实现检测窗口尺寸变化并实时更新(不过应该问题不大，多调用一下这个函数)
void window::flushScreen(){
    updateStatus();
    int row, col;
    getyx(stdscr, row, col);
    move(0, 0);
    std::vector<std::string> content = file->fileContent;
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
            // 打印行内对应内容
            if (colNumber >= content[lineNumber + i].length()) {
                printw("\n");
            } else if (content[lineNumber + i].length() > colNumber + COLS - 5) {
                printw("%s", content[lineNumber + i].substr(colNumber, COLS - 5).c_str());
            } else {
                printw("%s\n", content[lineNumber + i].substr(colNumber).c_str());
            }
        } else {
            attron(COLOR_PAIR(1));
            printw("~\n");
            attroff(COLOR_PAIR(1));
        }
    }
    move(row, col);
    refresh();
    return;
}

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

void window::printWin(std::string str){
    printw(str.c_str());
    return;
}


    
} // namespace ev