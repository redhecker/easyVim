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
std::vector<std::pair<size_t, size_t>> EVFile::searchRegex(const std::string& regexPattern) {
    std::vector<std::pair<size_t, size_t>> results;
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

// 有问题，不要用
bool EVFile::replaceRegex(const std::pair<size_t, size_t> pos, const std::string& replacePattern) {
    size_t lineIndex = pos.first;

    if (lineIndex < 0 || lineIndex >= fileContent.size()) {
        return false;  // 行索引无效
    }

    std::string& line = fileContent[lineIndex];
    std::regex pattern(".*");  // 用正则匹配整个行内容，替换整个匹配的部分，可以更细化正则
    line = std::regex_replace(line, pattern, replacePattern);

    return true;
}

EVFile::EVFileStatus EVFile::searchInFileRegex(const std::string regexPattern){
    if (fileContent.empty()) {
        return EVFILE_NO_MATCH_PATTERN;
    }
    searchPosition = searchRegex(regexPattern);
    if (searchPosition.empty()){
        return EVFILE_NO_MATCH_PATTERN;
    }
    return EVFILE_PATTERN_MATCH;
}

// 有问题，不要用
EVFile::EVFileStatus EVFile::searchReplaceRegex(const std::string regexPattern, const std::string replacePattern){
    if (fileContent.empty()) {
        return EVFILE_NO_MATCH_PATTERN;
    }
    searchPosition = searchRegex(regexPattern);
    if (searchPosition.empty()){
        return EVFILE_NO_MATCH_PATTERN;
    }
    
    for (size_t i = 0; i < searchPosition.size(); i++){
        bool replaceSuccess = replaceRegex(searchPosition[i], replacePattern);
        if (!replaceSuccess){ 
            // todo：是否需要全部重做
            return EVFILE_REPLACE_FAIL;
        }
    }

    // 清空searchPosition中的内容
    searchPosition.clear();

    return EVFILE_REPLACE_SUCCESS;
}

std::vector<std::pair<size_t, size_t>> EVFile::search(const std::string& content) {
    std::vector<std::pair<size_t, size_t>> results;
    const size_t len = content.size();
    for (size_t row = 0; row < fileContent.size(); row++) {
        const auto& line = fileContent[row];
        for (size_t col = 0; col + len <= line.size(); col++) {
            if (content == line.substr(col, len)) {
                for (size_t i = 0; i < len; i++) { // 将匹配的所有位置都加入结果
                    results.push_back(std::pair<size_t, size_t>(row, col + i));
                }
                col += len - 1; // 不允许overlap，譬如搜索“1101”，文件中存在“1101101”，只匹配第一个
                continue;
            }
        }
    }
    return results;
}


std::vector<std::pair<size_t, size_t>> EVFile::search_case_ins(const std::string& content) {
    std::vector<std::pair<size_t, size_t>> results;
    const size_t len = content.size();
    std::string lower_content = content;
    std::transform(lower_content.begin(), lower_content.end(), lower_content.begin(), [](unsigned char c) { return std::tolower(c); });

    for (size_t row = 0; row < fileContent.size(); row++) {
        const auto& line = fileContent[row];
        std::string lower_line = line;
        std::transform(lower_line.begin(), lower_line.end(), lower_line.begin(), [](unsigned char c) { return std::tolower(c); });
        for (size_t col = 0; col + len <= line.size(); col++) {
            if (lower_content == lower_line.substr(col, len)) {
                for (size_t i = 0; i < len; i++) { // 将匹配的所有位置都加入结果
                    results.push_back(std::pair<size_t, size_t>(row, col + i));
                }
                col += len - 1; // 不允许 overlap，只匹配第一个完整的子串
                continue;
            }
        }
    }
    return results;
}

EVFile::EVFileStatus EVFile::searchInFile(const std::string content, bool caseSensitive){
    if (fileContent.empty()) {
        return EVFILE_NO_MATCH_PATTERN;
    }

    if (caseSensitive) {
        searchPosition = search(content);
    } else {
        searchPosition = search_case_ins(content);
    }
    if (searchPosition.empty()) {
        return EVFILE_NO_MATCH_PATTERN;
    }
    return EVFILE_PATTERN_MATCH;
}

std::vector<std::pair<size_t, size_t>> EVFile::search_first(const std::string& content) {
    std::vector<std::pair<size_t, size_t>> results;
    const size_t len = content.size();
    for (size_t row = 0; row < fileContent.size(); row++) {
        const auto& line = fileContent[row];
        for (size_t col = 0; col + len <= line.size(); col++) {
            if (content == line.substr(col, len)) {
                results.push_back(std::pair<size_t, size_t>(row, col)); // 记录匹配的起始位置
                col += len - 1; // 跳过已匹配的部分，避免重叠匹配
                continue;
            }
        }
    }
    return results;
}

std::vector<std::pair<size_t, size_t>> EVFile::search_first_case_ins(const std::string& content) {
    std::vector<std::pair<size_t, size_t>> results;
    const size_t len = content.size();
    std::string content_lower = content;
    std::transform(content_lower.begin(), content_lower.end(), content_lower.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    for (size_t row = 0; row < fileContent.size(); row++) {
        const auto& line = fileContent[row];
        std::string line_lower = line;
        std::transform(line_lower.begin(), line_lower.end(), line_lower.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        for (size_t col = 0; col + len <= line.size(); col++) {
            if (content_lower == line_lower.substr(col, len)) {
                results.push_back(std::pair<size_t, size_t>(row, col));
                return results;  // 返回找到的第一个匹配位置
            }
        }
    }

    return results;
}

bool EVFile::replace(const std::pair<size_t, size_t> pos, int len, const std::string& replaceContent) {
    size_t lineIndex = pos.first;
    size_t colIndex = pos.second;
    if (lineIndex >= fileContent.size()) {
        return false;
    }

    std::string& line = fileContent[lineIndex];
    if (colIndex + replaceContent.size() > line.size()) { // 如果替换内容会超出行的当前长度，调整行的大小
        line.resize(colIndex + replaceContent.size(), ' ');  // 用空格填充扩展的部分
    }
    line.replace(colIndex, len, replaceContent);
    hasChange = true;
    return true;
}

EVFile::EVFileStatus EVFile::searchReplace
(const std::string searchContent, const std::string replaceContent, bool caseSensitive){
    if (fileContent.empty()) {
        return EVFILE_NO_MATCH_PATTERN;
    }
    if (caseSensitive) {
        searchPosition = search_first(searchContent);
    } else {
        searchPosition = search_first_case_ins(searchContent);
    }
    if (searchPosition.empty()){
        return EVFILE_NO_MATCH_PATTERN;
    }
    
    int len = searchContent.size();
    size_t replace_offset = 0;
    size_t last_row = -1;  // 用来存储上一个匹配的位置的行号，初始为无效行号
    for (size_t i = 0; i < searchPosition.size(); ++i) {
        size_t row = searchPosition[i].first;
        size_t col = searchPosition[i].second;
        if (row != last_row) { // 换行重置偏移量
            replace_offset = 0;
        }
        bool replaceSuccess = replace({row, col + replace_offset}, len, replaceContent);  // 使用调整后的列位置
        if (!replaceSuccess) {
            return EVFILE_REPLACE_FAIL;
        }
        replace_offset += replaceContent.size() - len;  // 偏移量 = 新内容长度 - 原内容长度
        last_row = row; // 更新上一个行号
    }

    searchPosition.clear();// 清空searchPosition中的内容
    return EVFILE_REPLACE_SUCCESS;
}

} // namespace ev
