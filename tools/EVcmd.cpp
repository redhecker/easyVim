#include<bits/stdc++.h>

int main(){
    bool exit = false, refresh = true;
    int res;
    std::string params = "";

    while (!exit) {
        std::cout << ">>";
        getline(std::cin, params);
        if (params == "exit") {
            exit = true;
        } else {
            // exectute ../build/bin/easyVim params in a new terminal window
            // 现在这玩意需要gnome-terminal支持，可能需要 sudo apt install gnome-terminal
            // 并且在wsl上面运行的话需要sudo，其它linux还不清楚
            // todo 出问题的时候返回值应该要能打印到控制台中（现在会打印到新开的terminal上然后就看不到了）
            system(("gnome-terminal -- ../build/bin/easyVim " + params).c_str());
        }
    }

    // todo 需要关闭所有子进程
    

    return 0;
}