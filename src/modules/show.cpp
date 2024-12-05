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
    int x, y;
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
    int x, y;
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
    int x, y;
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

//todo 不知道有没有办法能实现检测窗口尺寸变化并实时更新(不过应该问题不大，多调用一下这个函数)
void window::flushScreen(){
    updateStatus();
    // int row, col;
    // getyx(stdscr, row, col);
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
            } else if (content[lineNumber + i].length() > colNumber + COLS - 6) {
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
    } else if (curRow > lineNumber + LINES - INIT_LINE - 1) {
        lineNumber = curRow - LINES + INIT_LINE + 1;
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

void window::printWin(std::string str){
    printw("%s", str.c_str());
    return;
}


    
} // namespace ev