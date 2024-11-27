#define FMT_HEADER_ONLY 
#include <fmt/core.h>
#include "config.hpp"


/**@mainpage  temp_main
* <table>
* <tr><th>Project  <td>temp name
* <tr><th>Author   <td>Super github@redhecker
* </table>
* @section   项目详细描述
* 这个项目是这样的 。。。
*
* @section   项目功能描述
* 它的功能是。。。
* 
* @section   用法描述 
* 可以这样那样用
* 
* @section   更新信息 
* <table>
* <tr><th>Date        <th>H_Version  <th>S_Version  <th>Author    <th>Description  </tr>
* <tr><td>2024/10/20  <td>1.0    <td>S02010041808171   <td>1234  <td>initial version </tr>
* <tr><td>2025/20/30  <td>1.1    <td>S02010041906241   <td>5678  <td>
* </tr>
* </table>
**********************************************************************************
*/
int main(){
    // fmt demo
    fmt::print("Hello, {}!\n", "world");
    fmt::print("Version: {}\n", TEMP_VERSION);

    // + 代表正数加+号，负数加-号
    fmt::print("{:+f}; {:+f}\n", 3.14, -3.14); 
    // 空格正数加空格，负数加-号
    fmt::print("{: f}; {: f}\n", 3.14, -3.14); 
    // -号代表正数不变，负数加-号 same as '{:f}; {:f}' 相当于是默认行为
    fmt::print("{:-f}; {:-f}\n", 3.14, -3.14);

    fmt::print("{:+}; {:+}\n", 3, -3);
    fmt::print("{:-}; {:-}\n", 3, -3);
    fmt::print("{: }; {: }\n", 3, -3);
    fmt::print("{:}; {:}\n", 3, -3);

    int a = 9, b = 3;

    fmt::print("{} + {} = {}\n", a, b, add(a, b));
    fmt::print("{} - {} = {}\n", a, b, sub(a, b));
    fmt::print("{} * {} = {}\n", a, b, mul(a, b));
    fmt::print("{} / {} = {}\n", a, b, di(a, b));
    return 0;
}