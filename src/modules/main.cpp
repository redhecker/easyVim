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

bool normal(ev::window* window_, ev::EVFile* file_, ev::EVOper* oper_){
    int ch;
    bool exit = false, refresh = true;
    NORMAL_MODE_FLAGS flag = EV_NOTHING;
    while (!exit)
    {
        ch = window_->getInput();
        ch = oper_->getOper(ch);
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
            case 'k':
            case EV_UP:
                window_->moveUp();
                break;
            case 'j':
            case EV_DOWN:
                window_->moveDown();
                break;
            case 'h':
            case EV_LEFT:
                window_->moveLeft();
                break;
            case 'l':
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

bool command(ev::window* window_, ev::EVFile* file_, ev::EVCommand* comm_){
    std::string command = window_->getCommand();

    std::vector<std::string> commands = std::vector<std::string>();
    Stringsplit(command, ' ', commands);

    ev::EVCommand::commandStatus re = comm_->execCommand(commands, file_);

    bool res = false;
    switch (re)
    {
    case ev::EVCommand::COMMAND_OK_EXIT:
        res = true;
        break;
    default:
        break;
    }

    return res;
}


int main(int argc, char** argv){
    ev::Parser parser;
    std::string commands = "", operations = "";
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

    if (result.find("c") != result.end()){
        commands = result.find("c")->second;
    }
    if (result.find("k") != result.end()){
        operations = result.find("k")->second;
    }

    std::string fileName = argv[argc - 1];
    if (argv[argc - 1][0] == '-' || argc == 1 || argv[argc - 2][0] == '-'){
        std::cout << "ERROR: Invalid parameters"        << std::endl;
        std::cout << "Usage: easyVim ([params]) [file]" << std::endl;
        std::cout << "use -h to check the params"       << std::endl;
        return 0;
    }

    ev::EVCommand commandCfg(commands);
    commandCfg.loadConfig();
    ev::EVOper operationCfg(operations);
    operationCfg.loadConfig();

    ev::EVFile file(fileName);
    if (file.loadFile() == ev::EVFile::EVFileStatus::EVFILE_OPEN_FAIL){
        std::cout << "ERROR: Open file failed" << std::endl;
        std::cout << "The file might not extist! if so, simply use 'touch fileName' to creat target file first" << std::endl;
        return 0;
    }
    if (file.fileContent.size() == 0){
        file.fileContent.push_back("");
    }
    ev::window window(&file);
    window.init();
    window.moveCur();
    window.flushScreen();
    bool exit = false;
    while (!exit){
        ev::window::WindowStatus status = window.getStatus();
        switch (status){
        case ev::window::WindowStatus::NORMAL:
            normal(&window, &file, &operationCfg);
            break;
        case ev::window::WindowStatus::COVER:
        case ev::window::WindowStatus::INSERT:
            insert(&window, &file);
            break;
        case ev::window::WindowStatus::COMMAND:
            exit = command(&window, &file, &commandCfg);
            break;
        default:
            break;
        }
    }

    window.quit();
    return 0;
}