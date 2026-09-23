#include "../include/FileParser.h"

// Don't forget to always include "std::ios::binary" in fstreams

void newFile(fs::path file) {
    std::ofstream fout(file.c_str());
    fout << "\x{01}Example body";
}

FileParser::FileParser(fs::path file) {
    this->filePath = file;
    if (!fs::exists(file)) {
        newFile(file);
    }
    this->update();
}

FileParser::~FileParser() {
}

void FileParser::coutBlockLists() {
    for (size_t lineIndex = 0; lineIndex < this->blockTextList.size(); ++lineIndex) {
        std::cout << std::endl;
        for (size_t elementIndex = 0; elementIndex < this->blockTextList.at(lineIndex).size(); ++elementIndex) {
            std::cout << this->blockTextList.at(lineIndex).at(elementIndex) << '/' << this->blockAddressList.at(lineIndex).at(elementIndex) << ", ";
        }
    }
}

/*
======================================================

        Get functs

======================================================
*/

fs::path FileParser::getPath() {
    return this->filePath;
}
size_t FileParser::getFirstBlock() {
    return this->firstBlock;
}

std::vector<std::vector<std::string>> FileParser::getBlockTextList() {
    return this->blockTextList;
}
std::vector<std::vector<size_t>> FileParser::getBlockAddressList() {
    return this->blockAddressList;
}

/*
======================================================

        Private

======================================================
*/

void FileParser::save() {}

size_t FileParser::getSize_tFromBinary(std::ifstream& fin) {
    size_t result;
    fin.read((char*)&result, sizeof(size_t));

    if (sizeof(size_t) == 4) {
        char temp;
        for (char i = 0; i < sizeof(size_t); ++i) {
            fin >> temp;
        }
    }

    return result;
}
size_t FileParser::getSize_tFromBinary(std::istringstream& sin) {
    size_t result;
    sin.read((char*)&result, sizeof(size_t));

    if (sizeof(size_t) == 4) {
        char temp;
        for (char i = 0; i < sizeof(size_t); ++i) {
            sin >> temp;
        }
    }

    return result;
}
void FileParser::writeSize_tToBinary(std::ofstream& fout, size_t input) {
    fout.write(reinterpret_cast<const char *>(&input), sizeof(size_t));
    if (sizeof(size_t) == 4) {
        int zero = 0;
        fout.write(reinterpret_cast<const char *>(&zero), sizeof(size_t));
    }
}
void FileParser::writeSize_tToBinary(std::ostringstream& sout, size_t input) {
    sout.write(reinterpret_cast<const char *>(&input), sizeof(size_t));
    if (sizeof(size_t) == 4) {
        int zero = 0;
        sout.write(reinterpret_cast<const char *>(&zero), sizeof(size_t));
    }
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
}
