#ifndef FILEPARSER_H
#define FILEPARSER_H

#include <iostream> // Remember to remove

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>


class FileParser
{
    public:
        FileParser(std::string);
        virtual ~FileParser();
        void update();
        std::vector<std::vector<std::string>> getBlockTextList();
        std::vector<std::vector<size_t>> getBlockAddressList();

    private:
        size_t firstBlock;
        std::string filePath;
        std::vector<std::vector<std::string>> blockTextList;
        std::vector<std::vector<size_t>> blockAddressList;

        size_t getSize_tFromBinary(std::ifstream&);
        size_t getSize_tFromBinary(std::istringstream&);
        void writeSize_tToBinary(std::ofstream&, size_t);
        void writeSize_tToBinary(std::ostringstream&, size_t);
};

#endif // FILEPARSER_H
