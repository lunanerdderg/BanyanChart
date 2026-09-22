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
        std::cout << counter << std::endl; // TESTING
        newBlockTextList.push_back( { { "" } } );
        newBlockAddressList.push_back( { { } } );
        if (line.at(0) == ( (char)1 ) ) {
            this->firstBlock = counter;
        }
        std::istringstream sin(line.substr((line.at(0) == ( (char)1 ))));

        std::string element;
        std::getline(sin, element, '\t');
        newBlockTextList.back().at(0) = element;
        std::cout << newBlockTextList.back().at(0) << std::endl; // TESTING
        while (sin.peek() != -1) {
            newBlockAddressList.back().push_back(this->getSize_tFromBinary(sin));
            if (std::getline(sin, element, '\t')) {
                newBlockTextList.back().push_back(element);
            }
            else {
                newBlockTextList.back().push_back("");
            }
        }
        ++counter;
    }

    this->blockTextList = newBlockTextList;
    this->blockAddressList = newBlockAddressList;
    for (size_t lineIndex; lineIndex < this->blockTextList.size(); ++lineIndex) {
        std::cout << std::endl;
        for (size_t elementIndex; elementIndex < this->blockTextList.at(lineIndex).size(); ++elementIndex) {
            std::cout << this->blockTextList.at(lineIndex).at(elementIndex) << '/' << this->blockAddressList.at(lineIndex).at(elementIndex) << ", ";
        }
    }
}

std::vector<std::vector<std::string>> FileParser::getBlockTextList() {
    return this->blockTextList;
}
std::vector<std::vector<size_t>> FileParser::getBlockAddressList() {
    return this->blockAddressList;
}



size_t FileParser::getSize_tFromBinary(std::ifstream& fin) {
    unsigned long long int result;
    fin.read((char*)&result, 4);
    return result;
}
size_t FileParser::getSize_tFromBinary(std::istringstream& sin) {
    unsigned int result;
    sin.read((char*)&result, 4);
    std::cout << result; // TESTING
    return result;
}
void FileParser::writeSize_tToBinary(std::ofstream& fout, size_t input) {
    fout.write(reinterpret_cast<const char *>(&input), 4);
}
void FileParser::writeSize_tToBinary(std::ostringstream& sout, size_t input) {
    sout.write(reinterpret_cast<const char *>(&input), 4);
}
