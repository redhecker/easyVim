/**
 * @file search_replace.cpp
 * @brief easyVim文件搜索和替换模块
 * @author Super redhecker@github
 * @modify 2024
 */

#include "core.hpp"
#include <cstring>
#include <regex>

namespace ev
{
std::vector<std::pair<int, int>> EVFile::search(const std::string& regexPattern) {
    std::vector<std::pair<int, int>> results;
    std::regex pattern(regexPattern);

    for (size_t lineIndex = 0; lineIndex < fileContent.size(); ++lineIndex) {
        const std::string& line = fileContent[lineIndex];
        std::sregex_iterator begin(line.begin(), line.end(), pattern);
        std::sregex_iterator end;

        for (std::sregex_iterator it = begin; it != end; ++it) {
            int columnIndex = static_cast<int>(it->position());
            results.emplace_back(static_cast<int>(lineIndex), columnIndex);
        }
    }

    return results;
}

bool EVFile::replace(const std::pair<int, int> pos, const std::string& replacePattern) {
    size_t lineIndex = pos.first;

    if (lineIndex < 0 || lineIndex >= fileContent.size()) {
        return false;  // 行索引无效
    }

    std::string& line = fileContent[lineIndex];
    std::regex pattern(".*");  // 用正则匹配整个行内容，替换整个匹配的部分，可以更细化正则
    line = std::regex_replace(line, pattern, replacePattern);

    return true;
}

EVFile::EVFileStatus EVFile::searchInFile(const std::string regexPattern){
    if (fileContent.empty()) {
        return EVFILE_NO_MATCH_PATTERN;
    }
    searchPosition = search(regexPattern);
    if (searchPosition.empty()){
        return EVFILE_NO_MATCH_PATTERN;
    }
    return EVFILE_PATTERN_MATCH;
}

EVFile::EVFileStatus EVFile::searchReplace(const std::string regexPattern, const std::string replacePattern){
    if (fileContent.empty()) {
        return EVFILE_NO_MATCH_PATTERN;
    }
    searchPosition = search(regexPattern);
    if (searchPosition.empty()){
        return EVFILE_NO_MATCH_PATTERN;
    }
    
    for (size_t i = 0; i < searchPosition.size(); i++){
        bool replaceSuccess = replace(searchPosition[i], replacePattern);
        if (!replaceSuccess){ 
            // todo：是否需要全部重做
            return EVFILE_REPLACE_FAIL;
        }
    }

    return EVFILE_REPLACE_SUCCESS;
}


} // namespace ev
