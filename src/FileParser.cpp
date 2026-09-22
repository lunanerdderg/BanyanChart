#include "../include/FileParser.h"

FileParser::FileParser(std::string file) {
    this->filePath = file;
}

FileParser::~FileParser() {
}

void FileParser::update() {
    std::string line;
    std::ifstream fin(this->filePath);
    std::vector<std::vector<std::string>> newBlockTextList;
    std::vector<std::vector<size_t>> newBlockAddressList;

    while(std::getline(fin, line)) {
        newBlockTextList.push_back( { { "" } } );
        newBlockAddressList.push_back( { { 0 } } );
        if (line.at(0) == '') {
            newBlockAddressList.back().at(0) = 1;
        }

        size_t counter = 0;
        for (size_t index = 0; index < line.size(); ++index) {
            if (line.at(index) == '\t') {
                ++counter;
            }
        }
    }
}

std::vector<std::vector<std::string>> FileParser::getBlockTextList() {
    return this->blockTextList;
}
std::vector<std::vector<size_t>> FileParser::getBlockAddressList() {
    return this->blockAddressList;
}
