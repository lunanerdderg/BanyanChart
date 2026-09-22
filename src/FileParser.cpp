#include "../include/FileParser.h"

// Don't forget to always include "std::ios::binary" in fstreams

FileParser::FileParser(std::string file) {
    this->filePath = file;
    this->update();
}

FileParser::~FileParser() {
}

void FileParser::update() {
    size_t counter = 0;
    std::string line;
    std::ifstream fin(this->filePath, std::ios::binary);
    std::vector<std::vector<std::string>> newBlockTextList;
    std::vector<std::vector<size_t>> newBlockAddressList;

    while(std::getline(fin, line)) {
        newBlockTextList.push_back( { { "" } } );
        newBlockAddressList.push_back( { { } } );
        if (line.at(0) == ( (char)1 ) ) {
            this->firstBlock = counter;
        }
        std::istringstream sin(line.substr((line.at(0) == ( (char)1 ))));

        std::string element;
        std::getline(sin, element, '\t');
        newBlockTextList.back().at(0) = element;
        while (sin.peek() != -1) {
            newBlockAddressList.back().push_back(this->getSize_tFromBinary(sin));
            if (std::getline(sin, element, '\t')) {
                newBlockAddressList.back().push_back(element); // BOOKMARK
            }
            else {
                newBlockAddressList.back().push_back("");
            }
        }
        ++counter;
    }

    this->blockTextList = newBlockTextList;
    this->blockAddressList newBlockAddressList;
}

std::vector<std::vector<std::string>> FileParser::getBlockTextList() {
    return this->blockTextList;
}
std::vector<std::vector<size_t>> FileParser::getBlockAddressList() {
    return this->blockAddressList;
}



size_t FileParser::getSize_tFromBinary(std::ifstream& fin) {
    size_t result;
    fin.read((char*)&result, 4);
    return result;
}
size_t FileParser::getSize_tFromBinary(std::istringstream& sin) {
    size_t result;
    sin.read((char*)&result, 4);
    return result;
}
void FileParser::writeSize_tToBinary(std::ofstream& fout, size_t input) {
    fout.write(reinterpret_cast<const char *>(&input), 4);
}
void FileParser::writeSize_tToBinary(std::ostringstream& sout, size_t input) {
    sout.write(reinterpret_cast<const char *>(&input), 4);
}
