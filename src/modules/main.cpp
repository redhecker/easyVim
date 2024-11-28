/**@mainpage  easyVim
* <table>
* <tr><th>Project  <td>easyVim
* <tr><th>Author   <td>Super github@redhecker
* </table>
* @section   项目描述
* easyVim 是一款类似vim的文本编辑器。
*
* @section   项目功能描述
* easyVim功能描述。
* 
* @section   用法描述 
* 可以这样那样用。
* 
* @copyright   Copyright (c) 2024
*************************************************
*/

#include "show.hpp"
#include "config.hpp"
#include "../include.hpp"
#include <iostream>
int main(){
    ev::window window;
    ev::EVFile file("test.txt");
    file.loadFile();
    window.init();
    window.flushScreen(file.fileContent, 0, 0);
    int ch;
    bool exit = false;
    while (!exit) {
        ch = window.getInput();

        switch (ch){
            case EV_Esc:
                exit = true;
                break;
            case EV_UP:
                window.moveUp();
                break;
            case EV_DOWN:
                window.moveDown();
                break;
            case EV_LEFT:
                window.moveLeft();
                break;
            case EV_RIGHT:
                window.moveRight();
                break;
            default:
                printw("%d ", ch);
                break;
        }
    }
    window.quit();
    file.fileContent.push_back("hello world");
    file.saveFile();

    return 0;
}