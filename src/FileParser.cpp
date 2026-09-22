#include "../include/FileParser.h"

// Don't forget to always include "std::ios::binary" in fstreams

FileParser::FileParser(std::string file) {
    this->filePath = file;
}

FileParser::~FileParser() {
}

void FileParser::update() {
    std::string line;
    std::ifstream fin(this->filePath, std::ios::binary);
    std::vector<std::vector<std::string>> newBlockTextList;
    std::vector<std::vector<size_t>> newBlockAddressList;

    while(std::getline(fin, line)) {
        newBlockTextList.push_back( { { "" } } );
        newBlockAddressList.push_back( { { 0 } } );
        if (line.at(0) == ( (char)1 ) ) {
            newBlockAddressList.back().at(0) = 1;
        }
        std::istringstream sin(line.substr(newBlockAddressList.back().at(0)));

        std::string element;
        while (std::getline(sin, element, '\t')) { // BOOKMARK, Get text and address in each element
        }


//        size_t prevIndex = newBlockAddressList.back().at(0);
//        for (size_t index = prevIndex; index < line.size(); ++index) {
//            if (line.at(index) == '\t') {
//                index += 5;
//                prevIndex = index;
//            }
//        }
    }
}

std::vector<std::vector<std::string>> FileParser::getBlockTextList() {
    return this->blockTextList;
}
std::vector<std::vector<size_t>> FileParser::getBlockAddressList() {
    return this->blockAddressList;
}


size_t FileParser::getSize_tFromBinaryFile(std::ifstream& fin) {
    size_t result;
    fin.read((char*)&result, 4);
    return result;
}
void FileParser::writeSize_tToBinaryFile(std::ofstream& fout, size_t input) {
    fout.write(reinterpret_cast<const char *>(&input), 4);
}
