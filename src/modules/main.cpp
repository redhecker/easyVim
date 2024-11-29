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
#include <string>

bool normal(ev::window* window_, ev::EVFile* file_){
    int ch;
    ch = window_->getInput();
    // todo 支持指令自定义
    switch (ch){
        case 'i':
            window_->setStatus(ev::window::WindowStatus::INSERT);
            window_->updateStatus();
            break;
        case ':':
            window_->setStatus(ev::window::WindowStatus::COMMAND);
            window_->updateStatus();
            break;
        case EV_UP:
            window_->moveUp();
            break;
        case EV_DOWN:
            window_->moveDown();
            break;
        case EV_LEFT:
            window_->moveLeft();
            break;
        case EV_RIGHT:
            window_->moveRight();
            break;
        default:
            break;
    }
    return false;
}

bool insert(ev::window* window_, ev::EVFile* file_){
    // todo insert 模式需要能对文本进行编辑
    int ch = window_->getInput();
    switch (ch){
        case EV_Esc:
            window_->setStatus(ev::window::WindowStatus::NORMAL);
            window_->updateStatus();
            break;
        case EV_LEFT:
            window_->moveLeft();
            break;
        case EV_RIGHT:
            window_->moveRight();
            break;
        case EV_UP:
            window_->moveUp();
            break;
        case EV_DOWN:
            window_->moveDown();
            break;
        default:
            // todo 文本插入相关逻辑
            break;
    }
    return false;
}

bool command(ev::window* window_, ev::EVFile* file_){
    std::string command = window_->getCommand();

    // todo 支持指令信息自定义，默认回到normal模式
    if (command == "q"){
        // todo 判断文件是否有修改
        return true;
    } else if (command == "wq"){
        file_->saveFile();
        return true;
    } else if (command == "q!"){
        return true;
    } else if (command == "w"){
        file_->saveFile();
    } else {
        //todo 执行命令
    }
    return false;
}


int main(int argc, char** argv){
    ev::Parser parser;
    // parser.addCommand("command", "add command list");
    // parser.addCommand("keyBind", "add key bind list");
    parser.addCommand("c", "add command list");
    parser.addCommand("k", "add key bind list");
    std::unordered_map<std::string, std::string> result = parser.parse(argc, argv);
    if        (result.find("v") != result.end()){
        version();
        return 0;
    } else if (result.find("a") != result.end()){
        author();
        return 0;
    } else if (result.find("h") != result.end()){
        std::cout << parser.help() << std::endl;
        return 0;
    }

    ev::window window;
    std::string fileName = argv[argc - 1];
    if (argv[argc - 1][0] == '-' || argv[argc - 2][0] == '-'){
        std::cout << "Usage: easyVim ([params]) [file]" << std::endl;
        return 0;
    }
    ev::EVFile file(fileName);
    file.loadFile();
    window.init();
    window.flushScreen(file.fileContent);
    bool exit = false;
    while (!exit){
        ev::window::WindowStatus status = window.getStatus();
        switch (status){
        case ev::window::WindowStatus::NORMAL:
            normal(&window, &file);
            break;
        case ev::window::WindowStatus::INSERT:
            insert(&window, &file);
            break;
        case ev::window::WindowStatus::COMMAND:
            exit = command(&window, &file);
            break;
        default:
            break;
        }
    }

    endwin();
    return 0;
}