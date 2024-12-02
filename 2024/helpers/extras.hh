#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

void stripString(std::string &line)
{
    if (line.length() == 0) return; // nothing to do...

    auto start_it = line.begin();
    auto end_it = line.rbegin();

    const char s = ' ';
    const char n = '\n';
    const char r = '\r';
    const char t = '\t';

    while (*start_it == s || *start_it == n || *start_it == r || *start_it == t)
        ++start_it;
    while (*end_it == s || *end_it == n || *end_it == r || *end_it == t)
        ++end_it;
    line = std::string(start_it, end_it.base());
}

std::vector<std::string> splitString(const std::string &line, const std::string &delimiter)
{
    std::vector<std::string> sLine;

    // Find first instance of the delimiter
    size_t foundIndex = line.find(delimiter);
    size_t curIndex = 0;

    while (foundIndex != std::string::npos) {
        std::string curLine = std::string(line.begin() + curIndex, line.begin() + foundIndex);
        sLine.push_back(curLine);
        curIndex = foundIndex + delimiter.size();
        foundIndex = line.find(delimiter, curIndex);
    }

    if (curIndex != line.size()) {
        sLine.push_back(std::string(line.begin()+curIndex, line.end()));
    }

    return sLine;
}
