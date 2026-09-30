#include "FileParser.h"

// Don't forget to always include "std::ios::binary | std::ios::trunc" in fstreams

void newFile(fs::path file, std::string body) {
    std::ofstream fout(file.c_str(), std::ios::binary | std::ios::trunc);
    fout << "\x{FF}\x{FF}\x{FF}\x{FF}\x{FF}\x{FF}\x{FF}\x{FF}" << body;
}

//void FileParser::coutBlockLists() { // TESTING
//    for (size_t lineIndex = 0; lineIndex < this->blockTextList.size(); ++lineIndex) {
//        if (lineIndex != 0) {
//            std::cout << std::endl;
//        }
//        for (size_t elementIndex = 0; elementIndex < this->blockTextList.at(lineIndex).size(); ++elementIndex) {
//            std::cout << this->blockTextList.at(lineIndex).at(elementIndex) << '/' << this->blockAddressList.at(lineIndex).at(elementIndex) << ", ";
//        }
//    }
//}

FileParser::FileParser(bool startEmpty) {
    this->newInstance(startEmpty);
}
FileParser::FileParser(fs::path file, bool startEmpty) {
    this->newInstance(file, startEmpty);
}
FileParser::FileParser(std::vector<std::vector<std::string>> blockTextLists, std::vector<std::vector<size_t>> blockAddressLists, size_t topBlock) {
    this->newInstance(blockTextLists, blockAddressLists, topBlock);
}
FileParser::FileParser(fs::path file, std::vector<std::vector<std::string>> blockTextLists, std::vector<std::vector<size_t>> blockAddressLists, size_t topBlock) {
    this->newInstance(file, blockTextLists, blockAddressLists, topBlock);
}

FileParser::~FileParser() {
}

void FileParser::newInstance(bool startEmpty) {
    this->initialize(fs::path(), startEmpty);
}
void FileParser::newInstance(fs::path file, bool startEmpty) {
    this->initialize(file, startEmpty);
    this->update();
}
void FileParser::newInstance(std::vector<std::vector<std::string>> blockTextLists, std::vector<std::vector<size_t>> blockAddressLists, size_t topBlock) {
    this->initialize(fs::path(), blockTextLists, blockAddressLists, topBlock);
}
void FileParser::newInstance(fs::path file, std::vector<std::vector<std::string>> blockTextLists, std::vector<std::vector<size_t>> blockAddressLists, size_t topBlock) {
    this->initialize(file, blockTextLists, blockAddressLists, topBlock);
    this->save();
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

std::string FileParser::getNodeText(size_t blockIndex, size_t nodeIndex) {
    if (blockIndex < this->blockTextList.size() && nodeIndex < this->blockTextList.at(blockIndex).size()) {
        return this->blockTextList.at(blockIndex).at(nodeIndex);
    }
    return "";
}
size_t FileParser::getNodeAddress(size_t blockIndex, size_t nodeIndex) {
    if (blockIndex < this->blockAddressList.size() && nodeIndex < this->blockAddressList.at(blockIndex).size()) {
        return this->blockAddressList.at(blockIndex).at(nodeIndex);
    }
    return -1;
}

std::vector<std::string> FileParser::getBlockText(size_t blockIndex) {
    if (blockIndex < this->blockTextList.size()) {
        return this->blockTextList.at(blockIndex);
    }
    return {};
}
std::vector<size_t> FileParser::getBlockAddress(size_t blockIndex) {
    if (blockIndex < this->blockAddressList.size()) {
        return this->blockAddressList.at(blockIndex);
    }
    return {};
}

std::vector<std::vector<std::string>> FileParser::getBlockTextList() {
    return this->blockTextList;
}
std::vector<std::vector<size_t>> FileParser::getBlockAddressList() {
    return this->blockAddressList;
}

/*
======================================================

        Set functs

======================================================
*/

void FileParser::setBlockLists(std::vector<std::vector<std::string>> newBlockTextList, std::vector<std::vector<size_t>> newBlockAddressList) {
    this->blockTextList = newBlockTextList;
    this->blockAddressList = newBlockAddressList;
}

// Blocks

void FileParser::setFirstBlock(size_t blockIndex) {
    this->firstBlock = blockIndex;
}

void FileParser::addBlock(std::string body) {
    this->blockTextList.push_back( { { body } } );
    this->blockAddressList.push_back( { { } } );
}
void FileParser::addBlock(std::vector<std::string> blockTextList, std::vector<size_t> blockAddressList) {
    this->addBlock(blockTextList.at(0));
    size_t listSize = blockTextList.size();
    if (listSize > blockAddressList.size()) {
        listSize = blockAddressList.size();
    }
    for (size_t index = 1; index < listSize; ++index) {
        this->blockTextList.back().push_back(blockTextList.at(index));
        this->blockAddressList.back().push_back(blockAddressList.at(index));
    }
}
void FileParser::addBlock(std::string body, std::vector<std::string> blockTextList, std::vector<size_t> blockAddressList) {
    blockTextList.insert(blockTextList.begin(), body);
    this->addBlock(blockTextList, blockAddressList);
}
void FileParser::addMultipleBlocks(std::vector<std::vector<std::string>> blockTextLists, std::vector<std::vector<size_t>> blockAddressLists) {
    size_t listSize = blockTextLists.size();
    if (listSize > blockAddressLists.size()) {
        listSize = blockAddressLists.size();
    }
    for (size_t index = 0; index < listSize; ++index) {
        this->addBlock(blockTextLists.at(index), blockAddressLists.at(index));
    }
}

void FileParser::removeBlock(size_t blockIndex) {
    if (blockIndex < this->blockTextList.size()) {
        this->blockTextList.erase(this->blockTextList.begin() + blockIndex);
        this->blockAddressList.erase(this->blockAddressList.begin() + blockIndex);
    }
}
void FileParser::removeMultipleBlocks(std::vector<size_t> blockIndices) {
    std::sort(blockIndices.begin(), blockIndices.end(), std::greater<size_t>());
    if (blockIndices.at(0) < this->blockTextList.size()) {
        for (size_t blockIndex : blockIndices) {
            this->removeBlock(blockIndex);
        }
    }
}

void FileParser::duplicateBlock(size_t blockIndex) {
    if (blockIndex < this->blockTextList.size()) {
        this->addBlock(this->getBlockText(blockIndex), this->getBlockAddress(blockIndex));
    }
}
void FileParser::duplicateMultipleBlocks(std::vector<size_t> blockIndices) {
    for (size_t blockIndex : blockIndices) {
        this->duplicateBlock(blockIndex);
    }
}

// Nodes

void FileParser::addNode(size_t blockIndex, std::string nodeText, size_t nodeAddress) {
    if (blockIndex < this->blockTextList.size()) {
        this->blockTextList.at(blockIndex).push_back(nodeText);
        this->blockAddressList.at(blockIndex).push_back(nodeAddress);
    }
}
void FileParser::addMultipleNodes(size_t blockIndex, std::vector<std::string> nodeTextList, std::vector<size_t> nodeAddressList) {
    size_t listSize = nodeTextList.size();
    if (listSize > nodeAddressList.size()) {
        listSize = nodeAddressList.size();
    }
    for (size_t index = 0; index < listSize; ++index) {
        this->addNode(blockIndex, nodeTextList.at(index), nodeAddressList.at(index));
    }
}

void FileParser::removeNode(size_t blockIndex, size_t nodeIndex) {
    if (nodeIndex != 0 && blockIndex < this->blockTextList.size() && nodeIndex < this->blockTextList.at(blockIndex).size()) {
        this->blockTextList.at(blockIndex).erase(this->blockTextList.at(blockIndex).begin() + nodeIndex);
        this->blockAddressList.at(blockIndex).erase(this->blockAddressList.at(blockIndex).begin() + nodeIndex);
    }
}
void FileParser::removeMultipleNodes(size_t blockIndex, std::vector<size_t> nodeIndices) {
    std::sort(nodeIndices.begin(), nodeIndices.end(), std::greater<size_t>());
    if (nodeIndices.at(0) < this->blockTextList.at(blockIndex).size()) {
        for (size_t nodeIndex : nodeIndices) {
            this->removeNode(blockIndex, nodeIndex);
        }
    }
}
void FileParser::removeMultipleNodes(std::vector<size_t> blockIndices, std::vector<std::vector<size_t>> nodeIndices) {
    // Every block index in the blockIndices list has a corresponding vector of node indices.
    size_t listSize = blockIndices.size();
    if (listSize > nodeIndices.size()) {
        listSize = nodeIndices.size();
    }
    for (size_t index = 0; index < listSize; ++index) {
        this->removeMultipleNodes(blockIndices.at(index), nodeIndices.at(index));
    }
}

void FileParser::duplicateNode(size_t ogBlockIndex, size_t ogNodeIndex, size_t pasteBlockIndex) {
    if (ogBlockIndex < this->blockTextList.size() && ogNodeIndex < this->blockTextList.at(ogBlockIndex).size() && pasteBlockIndex < this->blockTextList.size()) {
        this->addNode(pasteBlockIndex, this->blockTextList.at(ogBlockIndex).at(ogNodeIndex), this->blockAddressList.at(ogBlockIndex).at(ogNodeIndex));
    }
}
void FileParser::duplicateMultipleNodes(std::vector<size_t> ogBlockIndex, std::vector<size_t> ogNodeIndex, size_t pasteBlockIndex) {
    // Every block index in the ogBlockIndices list has a corresponding node index, (requiring duplicates if multiple nodes in the same block).
    size_t listSize = ogBlockIndex.size();
    if (listSize > ogNodeIndex.size()) {
        listSize = ogNodeIndex.size();
    }
    for (size_t index = 0; index < listSize; ++index) {
        this->duplicateNode(ogBlockIndex.at(index), ogNodeIndex.at(index), pasteBlockIndex);
    }
}
void FileParser::duplicateMultipleNodes(std::vector<size_t> ogBlockIndex, std::vector<size_t> ogNodeIndex, std::vector<size_t> pasteBlockIndices) {
    for (size_t pasteBlockIndex : pasteBlockIndices) {
        this->duplicateMultipleNodes(ogBlockIndex, ogNodeIndex, pasteBlockIndex);
    }
}

// File-handling

void FileParser::setPath(fs::path file) {
    this->filePath = file;
}

void FileParser::save(fs::path file) {
    std::ofstream fout(file.c_str(), std::ios::binary | std::ios::trunc);
    for (size_t lineIndex = 0; lineIndex < this->blockTextList.size(); ++lineIndex) {
        if (lineIndex != 0) {
            fout << "\x{FF}\x{FF}\x{FF}\x{FF}\x{FF}\x{FF}\x{FF}\x{FF}";
        }
        if (lineIndex == this->firstBlock) {
            fout << '\x{01}';
        }
        fout << this->blockTextList.at(lineIndex).at(0);
        for (size_t elementIndex = 1; elementIndex < this->blockTextList.at(lineIndex).size(); ++elementIndex) {
            fout << '\t';
            this->writeSize_tToBinary(fout, this->blockAddressList.at(lineIndex).at(elementIndex));
            fout << this->blockTextList.at(lineIndex).at(elementIndex);
        }
    }
}
void FileParser::save() {
    this->save(this->getPath());
}

void FileParser::update() {
    std::vector<std::vector<std::string>> newBlockTextList;
    std::vector<std::vector<size_t>> newBlockAddressList;
    size_t counter = 0;
    std::string line;
    std::string fileContents;
    {
        std::ifstream fin(this->getPath(), std::ios::binary | std::ios::trunc);
        std::ostringstream sout;
        sout << fin.rdbuf();
        fileContents = sout.str();
    }

    for (size_t lineIndex = fileContents.find("\x{FF}\x{FF}\x{FF}\x{FF}\x{FF}\x{FF}\x{FF}\x{FF}"); lineIndex != string::npos; lineIndex = fileContents.find("\x{FF}\x{FF}\x{FF}\x{FF}\x{FF}\x{FF}\x{FF}\x{FF}")) {
        line = fileContents.substr(0, lineIndex);
        fileContents = fileContents.substr(lineIndex + 8);
        newBlockTextList.push_back( { { "" } } );
        newBlockAddressList.push_back( { { 0 } } );
        if (line.at(0) == '\x{01}' ) {
            this->firstBlock = counter;
            line = line.substr(1);
        }

//        size_t elementIndex = line.find('\t');
//        if (elementIndex == string::npos) {
//            newBlockTextList.at(0) = line;
//        }
//        else{
//            newBlockTextList.at(0) = line.substr(0,elementIndex);
//            line = line.substr(elementIndex + 1);
//            for (; elementIndex != string::npos; elementIndex = line.find('\t')) {
//                newBlockTextList
//            }
//        }

        std::istringstream sin(line);

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

//    while (std::getline(fin, line, '\x{04}')) {
//        newBlockTextList.push_back( { { "" } } );
//        newBlockAddressList.push_back( { { } } );
//        if (line.at(0) == '\x{01}' ) {
//            this->firstBlock = counter;
//        }
//        std::istringstream sin(line.substr((line.at(0) == '\x{01}')));
//
//        std::string element;
//        std::getline(sin, element, '\t');
//        newBlockTextList.back().at(0) = element;
//        while (sin.peek() != -1) {
//            newBlockAddressList.back().push_back(this->getSize_tFromBinary(sin));
//            if (std::getline(sin, element, '\t')) {
//                newBlockTextList.back().push_back(element);
//            }
//            else {
//                newBlockTextList.back().push_back("");
//            }
//        }
//        ++counter;
//    }

    this->setBlockLists(newBlockTextList, newBlockAddressList);
}

/*
======================================================

        Private

======================================================
*/

void FileParser::initialize(fs::path file, bool startEmpty) {
    this->filePath = file;
    if (startEmpty) {
        this->firstBlock = 0;
        this->blockTextList = {{}};
        this->blockAddressList = {{}};
    }
    if (!fs::exists(file)) {
        if (startEmpty) {
            newFile(file);
        }
        else {
            newFile(file, "Example body");
        }
    }
    else {
        this->update();
    }
}
void FileParser::initialize(fs::path file, std::vector<std::vector<std::string>> blockTextLists, std::vector<std::vector<size_t>> blockAddressLists, size_t topBlock) {
    this->filePath = file;
    this->firstBlock = topBlock;
    this->blockTextList = blockTextLists;
    this->blockAddressList = blockAddressLists;
}

// Streams

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
