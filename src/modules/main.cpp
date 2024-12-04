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
* @todo support utf-8 codec
*************************************************
*/

#include "show.hpp"
#include "config.hpp"
#include "../include.hpp"
#include <iostream>

enum NORMAL_MODE_FLAGS{
    EV_NOTHING = 0,
    EV_DELETE  = 1, ///< for delete operations, such as dd
    EV_COPY    = 2, ///< for copy, such as yy
    EV_NAVIG   = 3, ///< for navigation, such as gg
    EV_CHANGE  = 4  ///< for r[char] -> cover a single char
};

bool normal(ev::window* window_, ev::EVFile* file_){
    int ch;
    // todo 支持指令自定义
    // todo 指令不是单字符的情况？
    bool exit = false, refresh = true;
    NORMAL_MODE_FLAGS flag = EV_NOTHING;
    while (!exit)
    {
        ch = window_->getInput();
        if (refresh){
            flag = EV_NOTHING;
        }
        refresh = true;
        switch (ch){
            case 'i':
                window_->setStatus(ev::window::WindowStatus::INSERT);
                window_->updateStatus();
                exit = true;
                break;
            case 'K':
                window_->setStatus(ev::window::WindowStatus::COVER);
                window_->updateStatus();
                exit = true;
                break;
            case ':':
                window_->setStatus(ev::window::WindowStatus::COMMAND);
                window_->updateStatus();
                exit = true;
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
            case 'd':
                if (flag == EV_DELETE){
                    window_->printWin("delete\n");
                } else {
                    flag = EV_DELETE;
                    refresh = false;
                }
            default:
                break;
        }
    }
    return false;
}

bool insert(ev::window* window_, ev::EVFile* file_){
    // todo insert 模式需要能对文本进行编辑
    int ch;

    bool exit = false;
    while (!exit){
        ch = window_->getInput();
        switch (ch){
            case EV_Esc:
                window_->setStatus(ev::window::WindowStatus::NORMAL);
                window_->updateStatus();
                exit = true;
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
                if (ch >= 32 && ch <= 126){
                    // todo 插入文本
                    if (window_->getStatus() == ev::window::WindowStatus::INSERT){
                        
                    } else if (window_->getStatus() == ev::window::WindowStatus::COVER){

                    }
                }
                break;
        }
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
        ev::version();
        return 0;
    } else if (result.find("a") != result.end()){
        ev::author();
        return 0;
    } else if (result.find("h") != result.end()){
        std::cout << parser.help() << std::endl;
        return 0;
    }

    std::string fileName = argv[argc - 1];
    if (argv[argc - 1][0] == '-' || argc == 1 || argv[argc - 2][0] == '-'){
        std::cout << "ERROR: Invalid parameters"        << std::endl;
        std::cout << "Usage: easyVim ([params]) [file]" << std::endl;
        std::cout << "use -h to check the params"       << std::endl;
        return 0;
    }

    ev::EVFile file(fileName);
    file.loadFile();
    ev::window window(&file);
    window.init();
    window.moveTo(INIT_LINE, INIT_COL);
    window.flushScreen();
    bool exit = false;
    while (!exit){
        ev::window::WindowStatus status = window.getStatus();
        switch (status){
        case ev::window::WindowStatus::NORMAL:
            normal(&window, &file);
            break;
        case ev::window::WindowStatus::COVER:
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

    window.quit();
    return 0;
}