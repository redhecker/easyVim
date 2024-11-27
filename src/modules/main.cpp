#define FMT_HEADER_ONLY 
#include <ncurses.h>
#include "../include.hpp"

/**@mainpage  easyVim
* <table>
* <tr><th>Project  <td>easyVim
* <tr><th>Author   <td>Super github@redhecker
* </table>
* @section   项目详细描述
* 这个项目是这样的 。。。
*
* @section   项目功能描述
* 它的功能是。。。
* 
* @section   用法描述 
* 可以这样那样用、
* 
* @copyright   Copyright (c) 2024
***************************************************
*/
 int main()
 {
    initscr(); /*初始化，进入NCURSES模式*/
    printw("version %s", getVersion()); /*在虚拟屏幕上打印Hello,World!!! */
    refresh(); /*将虚拟屏幕上的内容写到显示器上，并刷新*/
    getchar(); /*等待用户输入*/
    endwin(); /*退出NCURSES模式*/
    return 0;
 }