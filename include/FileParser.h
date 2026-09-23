#ifndef FILEPARSER_H
#define FILEPARSER_H

//#include <iostream> // TESTING

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <filesystem>
namespace fs = std::filesystem;

void newFile(fs::path, std::string="Example body");

class FileParser
{
    public:
//        void coutBlockLists(); // TESTING
        FileParser(fs::path, bool=false); FileParser(fs::path, std::vector<std::vector<std::string>>, std::vector<std::vector<size_t>>, size_t=0);
        virtual ~FileParser();
        // Get
        fs::path getPath();
        size_t getFirstBlock();
        std::string getNodeText(size_t, size_t);
        size_t getNodeAddress(size_t, size_t);
        std::vector<std::string> getBlockText(size_t);
        std::vector<size_t> getBlockAddress(size_t);
        std::vector<std::vector<std::string>> getBlockTextList();
        std::vector<std::vector<size_t>> getBlockAddressList();
        // Set
        void setBlockLists(std::vector<std::vector<std::string>>, std::vector<std::vector<size_t>>);
          // Block editing
        void setFirstBlock(size_t);
        void addBlock(std::string=""); void addBlock(std::vector<std::string>, std::vector<size_t>); void addBlock(std::string, std::vector<std::string>, std::vector<size_t>);
        void addMultipleBlocks(std::vector<std::vector<std::string>>, std::vector<std::vector<size_t>>);
        void removeBlock(size_t);
        void removeMultipleBlocks(std::vector<size_t>);
        void duplicateBlock(size_t);
        void duplicateMultipleBlocks(std::vector<size_t>);
          // Node editing
        void addNode(size_t, std::string, size_t);
        void addMultipleNodes(size_t, std::vector<std::string>, std::vector<size_t>);
        void removeNode(size_t, size_t);
        void removeMultipleNodes(size_t, std::vector<size_t>); void removeMultipleNodes(std::vector<size_t>, std::vector<std::vector<size_t>>);
        void duplicateNode(size_t, size_t, size_t);
        void duplicateMultipleNodes(std::vector<size_t>, std::vector<size_t>, size_t); void duplicateMultipleNodes(std::vector<size_t>, std::vector<size_t>, std::vector<size_t>);
          // File-handling
        void save();
        void save(fs::path);
        void update();

    private:
        size_t firstBlock;
        fs::path filePath;
        std::vector<std::vector<std::string>> blockTextList;
        std::vector<std::vector<size_t>> blockAddressList;
        // Streams
        size_t getSize_tFromBinary(std::ifstream&); size_t getSize_tFromBinary(std::istringstream&);
        void writeSize_tToBinary(std::ofstream&, size_t); void writeSize_tToBinary(std::ostringstream&, size_t);
};

#endif // FILEPARSER_H
