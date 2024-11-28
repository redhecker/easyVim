#include "show.hpp"
#define EV_SHOW_DEBUG 1
#if EV_SHOW_DEBUG
#include <stdio.h>
#endif

namespace ev {
// 提示：LINES和COLS是ncurses库中的宏，分别表示当前终端的行数和列数，其中LINES需要减1，因为最后一行是状态栏
    
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
    refresh();
    attron(COLOR_PAIR(1));
    move(LINES-1, 0);
    printw("initialize the window\n");
    move(0, 0);
    attroff(COLOR_PAIR(1));
    return;
}

int window::getInput(){
    return getch();
}

void window::quit(){
    endwin();
    return;
}

void window::moveCursor(int row, int col){
    move(row, col);
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

void window::flushScreen(const std::vector<std::string>& file, size_t x, size_t y, size_t start){
    int row, col;
    getyx(stdscr, row, col);
    move(0, 0);
    for (int i = 0; i < (LINES - 1); i++){
        if (x + i < file.size()) {
            attron(A_BOLD);
            // 打印行号
            int lineNum = (x+i+start+1) % 10000;
            if (lineNum > 999) {
                printw("%ld ", x+i+start+1); 
            } else if (lineNum > 99) {
                printw("0%ld ", x+i+start+1); 
            } else if (lineNum > 9) {
                printw("00%ld ", x+i+start+1); 
            } else {
                printw("000%ld ", x+i+start+1); 
            }
            attroff(A_BOLD);
            // 打印行内对应内容
            if (y >= file[x+i].length()) {
                printw("\n");
            } else if (file[x+i].length() > y + COLS - 5) {
                printw("%s\n", file[x+i].substr(y, y + COLS - 5).c_str());
            } else {
                printw("%s\n", file[x+i].substr(y).c_str());
            }
        } else {
            attron(COLOR_PAIR(1));
            printw("~\n");
            attroff(COLOR_PAIR(1));
        }
    }
    move(row, col);
    return;
}

void window::flushLine(const std::string& line, size_t y){
    int row, col;
    getyx(stdscr, row, col);
    move(row, 5);
    // 打印行内对应内容
    if (line.length() > y + COLS - 5) {
        printw("%s\n", line.substr(y, y + COLS - 5).c_str());
    } else {
        printw("%s\n", line.substr(y).c_str());
    }
    move(row, col);
    return;
}


    
} // namespace ev