/**@mainpage  easyVim
* <table>
* <tr><th>Author   <td>Zhu Chao      redhecker@github
* <tr><th>Author   <td>Zhong Yong    OptimistiCompound@github
* <tr><th>Author   <td>Liu Haoran    Defect-sts@github
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
    int ch, x, y;
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
        if (flag == EV_CHANGE){
            // cover
            if (ch >= 32 && ch <= 126){
                int x, y;
                window_->getCuryx(x, y);
                // file_->deleteChar(y, x, false);
                // file_->insertChar(y, x, ch);
                file_->coverChar(y, x, ch);
                window_->refreshCur();
            }
            continue;
        }
        switch (ch) {
            case 'i':
                window_->setStatus(ev::window::WindowStatus::INSERT);
                exit = true;
                break;
            case 'K':
                window_->setStatus(ev::window::WindowStatus::COVER);
                exit = true;
                break;
            case ':':
                window_->setStatus(ev::window::WindowStatus::COMMAND);
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
            case '0':
                window_->moveHead();
                break;
            case '$':
                window_->moveEnd();
                break;
            case 'G':
                window_->moveBottom();
                break;
            case EV_Enter:
                window_->moveDown();
                window_->moveHead();
                break;
            case EV_Backspace:
                if (window_->getCurCol() > 0){
                    window_->moveLeft();
                } else if (window_->getCurRow() > 0){
                    window_->moveUp();
                    window_->moveEnd();
                }
                break;
            case 'D':
            case EV_Delete:
                // 删除当前字符
                window_->getCuryx(x, y);
                file_->deleteChar(y, x, false);
                window_->refreshCur();
                break;
            case 'd':
                if (flag == EV_DELETE){
                    window_->getCuryx(x, y);
                    file_->deleteLine(y);
                    window_->moveHead();
                } else {
                    flag = EV_DELETE;
                    refresh = false;
                }
                break;
            case 'g':
                if (flag == EV_NAVIG){
                    // gg
                    window_->moveTop();
                } else {
                    flag = EV_NAVIG;
                    refresh = false;
                }
                break;
            case 'r':
                if (flag != EV_CHANGE){
                    flag = EV_CHANGE;
                    refresh = false;
                }
                break;
            default:
                // //only for debugging
                // printf("ch: %d\n", ch);
                break;
        }
        window_->flushScreen();
    }
    return false;
}

bool insert(ev::window* window_, ev::EVFile* file_){
    // todo insert 模式需要能对文本进行编辑
    int ch;

    bool exit = false;
    int x, y;
    while (!exit){
        ch = window_->getInput();
        switch (ch) {
            case EV_Esc:
                window_->setStatus(ev::window::WindowStatus::NORMAL);
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
            case EV_Backspace:
                window_->getCuryx(x, y);
                file_->deleteChar(y, x, true);
                window_->refreshCur(false);
                if (window_->getCurCol() > 0){
                    window_->moveLeft();
                } else if (window_->getCurRow() > 0){
                    window_->moveUp();
                    window_->moveEnd();
                }
                break;
            case EV_Delete:
                // 删除当前字符
                window_->getCuryx(x, y);
                file_->deleteChar(y, x, false);
                window_->refreshCur();
                break;
            case EV_Enter:
                window_->getCuryx(x, y);
                file_->insertChar(y, x, '\n');
                window_->moveDown();
                window_->moveHead();
                break;
            case EV_Tab:
                //todo
                break;
            default:
                if (ch >= 32 && ch <= 126){
                    // 插入或者替换文本
                    window_->getCuryx(x, y);
                    if (window_->getStatus() == ev::window::WindowStatus::INSERT){
                        file_->insertChar(y, x, ch);
                        window_->refreshCur(false);
                        window_->moveRight();
                    } else if (window_->getStatus() == ev::window::WindowStatus::COVER){
                        file_->coverChar(y, x, ch);
                        window_->refreshCur(false);
                        window_->moveRight();
                    }
                }
                break;
        }
        window_->flushScreen();
    }
    return false;
}

bool command(ev::window* window_, ev::EVFile* file_, ev::EVCommand* comm_){
    std::string command = window_->getCommand();

    std::vector<std::string> commands = std::vector<std::string>();
    Stringsplit(command, ' ', commands);

    ev::EVCommand::commandStatus re = comm_->execCommand(commands, file_);

    bool res = false;
    switch (re) {
        case ev::EVCommand::COMMAND_OK_EXIT:
            res = true;
            break;
        case ev::EVCommand::COMMAND_OK:
            window_->flushScreen();
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
    if (file.loadFile() == ev::EVFile::EVFileStatus::EVFILE_READ_FAIL){
        std::cout << "ERROR: Open file failed" << std::endl;
        std::cout << 
        "What a pity! The file is too long to read, please try to open a smaller file." 
        << std::endl;
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
        window.updateStatus();
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