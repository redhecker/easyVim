#include "show.hpp"
#define EV_SHOW_DEBUG 1
#if EV_SHOW_DEBUG
#include <stdio.h>
#endif

namespace ev {
// 注意：LINES和COLS是ncurses库中的宏，分别表示当前终端的行数和列数，其中LINES需要减1，因为最后一行是状态栏
    
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
    // endwin();
    return;
}

void window::moveUp(){
    int x, y;
    getyx(stdscr, y, x);
    if (y > 0) {
        move(y - 1, x);
    } else {
        //todo scroll
    }
    refresh();
    return;
}

void window::moveDown(){
    int x, y;
    getyx(stdscr, y, x);
    if (y < (LINES - 1) - 1) {
        move(y + 1, x);
    } else {
        //todo scroll
    }
    refresh();
    return;
}

void window::moveLeft(){
    int x, y;
    getyx(stdscr, y, x);
    if (x > 0) {
        move(y, x - 1);
    } else {
        //todo scroll
    }
    refresh();
    return;
}

void window::moveRight(){
    int x, y;
    getyx(stdscr, y, x);
    if (x < COLS - 1) {
        move(y, x + 1);
    } else {
        //todo scroll
    }
    refresh();
    return;
}

void window::flushScreen(const std::vector<std::string>& file, size_t start){
    int row, col;
    getyx(stdscr, row, col);
    move(0, 0);
    for (int i = 0; i < (LINES - 1); i++){
        if (lineNumber + i < file.size()) {
            attron(A_BOLD);
            // 打印行号
            int lineNum = (lineNumber + i + start + 1) % 10000;
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
            if (colNumber >= file[lineNumber + i].length()) {
                printw("\n");
            } else if (file[lineNumber + i].length() > colNumber + COLS - 5) {
                printw("%s\n", file[lineNumber + i].substr(colNumber, colNumber + COLS - 5).c_str());
            } else {
                printw("%s\n", file[lineNumber + i].substr(colNumber).c_str());
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

void window::flushLine(const std::string& line){
    int row, col;
    getyx(stdscr, row, col);
    move(row, 5);
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


    
} // namespace ev