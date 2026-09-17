#ifndef FILEPARSER_H
#define FILEPARSER_H

#include <iostream> // Remember to remove

#include <string>


class FileParser
{
    public:
        FileParser(std::string);
        virtual ~FileParser();

    private:
        std::string filePath;
};

#endif // FILEPARSER_H
