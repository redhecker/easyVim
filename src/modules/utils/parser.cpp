#include "parser.hpp"
#include <algorithm>

namespace ev {
    Parser::Parser() {
        // addCommand("version", "Show version information");
        addCommand("v", "Show version information");
        // addCommand("author", "Show author information");
        addCommand("a", "Show author information");
        // addCommand("help", "Show help information");
        addCommand("h", "Show help information");
    }

    std::unordered_map<std::string, std::string> Parser::parse(int argc, char** argv) {
        std::unordered_map<std::string, std::string> result;
        for (int i = 1; i < argc; i++) {
            if (argv[i][0] == '-') {
                if (i + 1 < argc && argv[i + 1][0] != '-') {
                    if (argv[i][1] == '-' 
                    && std::find(commands.begin(), commands.end(), argv[i] + 2) != commands.end()) {
                        result[argv[i] + 2] = argv[i + 1];
                    } else if (std::find(commands.begin(), commands.end(), argv[i] + 1) != commands.end()) {
                        result[argv[i] + 1] = argv[i + 1];
                    }
                    i++;
                } else if (std::find(commands.begin(), commands.end(), argv[i] + 1) != commands.end()) {
                    result[argv[i] + 1] = "";
                }
            }
        }
        return result;
    }

} // namespace ev