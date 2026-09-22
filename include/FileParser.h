#ifndef FILEPARSER_H
#define FILEPARSER_H

#include <iostream> // Remember to remove

#include <string>
#include <vector>
#include <fstream>


class FileParser
{
    public:
        FileParser(std::string);
        virtual ~FileParser();
        void update();
        std::vector<std::vector<std::string>> getBlockTextList();
        std::vector<std::vector<size_t>> getBlockAddressList();

    private:
        std::string filePath;
        std::vector<std::vector<std::string>> blockTextList;
        std::vector<std::vector<size_t>> blockAddressList;
};

#endif // FILEPARSER_H
