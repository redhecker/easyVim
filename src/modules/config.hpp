/**@file       config.hpp
* @brief       配置文件，头文件汇总
* @author      Super@redhecker
* @copyright   Copyright (c) 2024
*/

#ifndef EV_CONFIG_HPP
#define EV_CONFIG_HPP

#define EV_VERSION "1.0.0"

#include "core/core.hpp"
#include "encrypt/encrypt.hpp"
#include "instructions/inst.hpp"
#include "instructions/inst_command.hpp"
#include "instructions/inst_operation.hpp"
#include "utils/parser.hpp"

#include <vector>
#include <string>
#include <algorithm>


#define EV_F(n) n+264
#define EV_Esc 27
#define EV_Enter 10
#define EV_Tab 9
#define EV_Backspace 263
#define EV_Delete 330
#define EV_LEFT 260
#define EV_RIGHT 261
#define EV_UP 259
#define EV_DOWN 258

#define INIT_LINE 0
#define INIT_COL 5


#endif