#include "../include.hpp"
#include "config.hpp"
#include <iostream>

void version(){
    std::cout << "easyVim version: " << EV_VERSION << std::endl;
}

const char* getVersion(){
    return EV_VERSION;
}