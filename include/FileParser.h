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

        size_t getSize_tFromBinaryFile(std::ifstream&);
        void writeSize_tToBinaryFile(std::ofstream&, size_t);

    private:

        std::string filePath;
        std::vector<std::vector<std::string>> blockTextList;
        std::vector<std::vector<size_t>> blockAddressList;
};

#endif // FILEPARSER_H
