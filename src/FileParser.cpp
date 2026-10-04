#include "FileParser.h"

// Don't forget to always include "std::ios::binary | std::ios::trunc" in fstreams

void newFile(std::string file, std::string body) {
    std::ofstream fout(file.c_str(), std::ios::binary | std::ios::trunc);
    fout << '\x{01}' << body;
}

//void FileParser::coutBlockLists() { // TESTING
//    for (size_t lineIndex = 0; lineIndex < this->blockTextList.size() && lineIndex < this->blockAddressList.size(); ++lineIndex) {
//        if (lineIndex != 0) {
//            std::cout << std::endl;
//        }
//        for (size_t elementIndex = 0; elementIndex < this->blockTextList.at(lineIndex).size() && lineIndex < this->blockAddressList.at(lineIndex).size(); ++elementIndex) {
//            std::cout << this->blockTextList.at(lineIndex).at(elementIndex) << '/' << this->blockAddressList.at(lineIndex).at(elementIndex) << ", ";
//        }
//    }
//}

FileParser::FileParser() {
    this->newInstance();
}
FileParser::FileParser(bool startEmpty) {this->newInstance(startEmpty);}
FileParser::FileParser(wxString file) {this->newInstance(file);}
FileParser::FileParser(std::string file) {this->newInstance(file);}
FileParser::FileParser(const char file[]) {this->newInstance(file);}
FileParser::FileParser(std::vector<std::vector<std::string>> blockTextLists, std::vector<std::vector<size_t>> blockAddressLists, size_t topBlock) {this->newInstance(blockTextLists, blockAddressLists, topBlock);}
FileParser::FileParser(const char file[], std::vector<std::vector<std::string>> blockTextLists, std::vector<std::vector<size_t>> blockAddressLists, size_t topBlock) {this->newInstance(file, blockTextLists, blockAddressLists, topBlock);}
FileParser::FileParser(wxString file, std::vector<std::vector<std::string>> blockTextLists, std::vector<std::vector<size_t>> blockAddressLists, size_t topBlock) {this->newInstance(file, blockTextLists, blockAddressLists, topBlock);}
FileParser::FileParser(std::string file, std::vector<std::vector<std::string>> blockTextLists, std::vector<std::vector<size_t>> blockAddressLists, size_t topBlock) {this->newInstance(file, blockTextLists, blockAddressLists, topBlock);}

FileParser::~FileParser() {
}

void FileParser::newInstance(bool startEmpty) {
    this->initialize("", startEmpty);
}
void FileParser::newInstance(std::string file) {
    this->initialize(file, false);
    this->update();
}
void FileParser::newInstance(const char file[]) {
    this->newInstance((std::string)file);
}
void FileParser::newInstance(wxString file) {
    this->newInstance(file.ToStdString());
}
void FileParser::newInstance(std::vector<std::vector<std::string>> blockTextLists, std::vector<std::vector<size_t>> blockAddressLists, size_t topBlock) {
    this->initialize("", blockTextLists, blockAddressLists, topBlock);
}
void FileParser::newInstance(std::string file, std::vector<std::vector<std::string>> blockTextLists, std::vector<std::vector<size_t>> blockAddressLists, size_t topBlock) {
    this->initialize(file, blockTextLists, blockAddressLists, topBlock);
    this->save();
}
void FileParser::newInstance(const char file[], std::vector<std::vector<std::string>> blockTextLists, std::vector<std::vector<size_t>> blockAddressLists, size_t topBlock) {
    this->newInstance((std::string)file, blockTextLists, blockAddressLists, topBlock);
}
void FileParser::newInstance(wxString file, std::vector<std::vector<std::string>> blockTextLists, std::vector<std::vector<size_t>> blockAddressLists, size_t topBlock) {
    this->newInstance(file.ToStdString(), blockTextLists, blockAddressLists, topBlock);
}

/*
======================================================

        Get functs

======================================================
*/

std::string FileParser::getPath() {
    return this->filePath;
}
size_t FileParser::getFirstBlock() {
    return this->firstBlock;
}

size_t FileParser::getNumBlocks() {
    size_t listSize = this->blockTextList.size();
    if (listSize > this->blockAddressList.size()) {
        listSize = this->blockAddressList.size();
    }
    return listSize;
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

std::string FileParser::getBlockBody(size_t blockIndex) {
    if (blockIndex < this->blockTextList.size() && this->blockTextList.at(blockIndex).size() > 0) {
        return this->blockTextList.at(blockIndex).at(0);
    }
    return "";
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

void FileParser::setText(std::string text, size_t blockIndex, size_t nodeIndex) {
    if (blockIndex < this->blockTextList.size() && nodeIndex < this->blockTextList.at(blockIndex).size()) {
        this->blockTextList.at(blockIndex).at(nodeIndex) = text;
    }
}
void FileParser::setText(const char text[], size_t blockIndex, size_t nodeIndex) {
    this->setText(text, blockIndex, nodeIndex);
}
void FileParser::setNodeAddress(size_t address, size_t blockIndex, size_t nodeIndex) {
    if (nodeIndex != 0 && blockIndex < this->blockTextList.size() && nodeIndex < this->blockTextList.at(blockIndex).size()) {
        this->blockAddressList.at(blockIndex).at(nodeIndex) = address;
    }
}
void FileParser::setFirstBlock(size_t blockIndex) {
    this->firstBlock = blockIndex;
}

void FileParser::addBlock(std::string body) {
    this->blockTextList.push_back( { { body } } );
    this->blockAddressList.push_back( { { 0 } } );
}
void FileParser::addBlock(std::vector<std::string> blockTexts, std::vector<size_t> blockAddresses) {
    this->blockTextList.push_back(blockTexts);
    this->blockAddressList.push_back(blockAddresses);
}
void FileParser::addBlock(std::string body, std::vector<std::string> blockTexts, std::vector<size_t> blockAddresses) {
    blockTexts.insert(blockTexts.begin(), body);
    blockAddresses.insert(blockAddresses.begin(), 0);
    this->addBlock(blockTexts, blockAddresses);
}
void FileParser::addMultipleBlocks(std::vector<std::vector<std::string>> blockTextLists, std::vector<std::vector<size_t>> blockAddressLists) {
    for (size_t index = 0; index < this->getNumBlocks(); ++index) {
        this->addBlock(blockTextLists.at(index), blockAddressLists.at(index));
    }
}

void FileParser::removeBlock(size_t blockIndex) {
    if (blockIndex < this->getNumBlocks()) {
        for (size_t index = 0; index != -1 && index < this->blockAddressList.size(); ++index) {
            for (size_t nodeIndex = this->blockAddressList.at(index).size() - 1; nodeIndex > 0; --nodeIndex) {
                if (this->blockAddressList.at(index).at(nodeIndex) == blockIndex) {
                    this->blockTextList.at(index).erase(this->blockTextList.at(index).begin() + nodeIndex);
                    this->blockAddressList.at(index).erase(this->blockAddressList.at(index).begin() + nodeIndex);
                }
                else if (index >= blockIndex) {
                    --this->blockAddressList.at(index).at(nodeIndex);
                }
            }
        }
        if (blockIndex == this->firstBlock) {
            if (this->blockAddressList.at(this->firstBlock).size() > 1) {
                this->firstBlock = this->blockAddressList.at(this->firstBlock).at(1);
            }
        }
        this->blockTextList.erase(this->blockTextList.begin() + blockIndex);
        this->blockAddressList.erase(this->blockAddressList.begin() + blockIndex);
    }
}
void FileParser::removeMultipleBlocks(std::vector<size_t> blockIndices) {
    std::sort(blockIndices.begin(), blockIndices.end(), std::greater<size_t>());
    if (blockIndices.at(0) < this->getNumBlocks()) {
        for (size_t blockIndex : blockIndices) {
            this->removeBlock(blockIndex);
        }
    }
}

void FileParser::duplicateBlock(size_t blockIndex) {
    if (blockIndex < this->getNumBlocks()) {
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
    if (blockIndex < this->getNumBlocks()) {
        this->blockTextList.at(blockIndex).push_back(nodeText);
        this->blockAddressList.at(blockIndex).push_back(nodeAddress);
    }
}
void FileParser::addMultipleNodes(size_t blockIndex, std::vector<std::string> nodeTextList, std::vector<size_t> nodeAddressList) {
    for (size_t index = 0; index < this->getNumBlocks(); ++index) {
        this->addNode(blockIndex, nodeTextList.at(index), nodeAddressList.at(index));
    }
}

void FileParser::removeNode(size_t blockIndex, size_t nodeIndex) {
    if (nodeIndex != 0 && blockIndex < this->getNumBlocks() && nodeIndex < this->blockTextList.at(blockIndex).size()) {
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
    for (size_t index = 0; index < this->getNumBlocks(); ++index) {
        this->removeMultipleNodes(blockIndices.at(index), nodeIndices.at(index));
    }
}

void FileParser::duplicateNode(size_t ogBlockIndex, size_t ogNodeIndex, size_t pasteBlockIndex) {
    if (ogBlockIndex < this->getNumBlocks() && ogNodeIndex < this->blockTextList.at(ogBlockIndex).size() && pasteBlockIndex < this->getNumBlocks()) {
        this->addNode(pasteBlockIndex, this->blockTextList.at(ogBlockIndex).at(ogNodeIndex), this->blockAddressList.at(ogBlockIndex).at(ogNodeIndex));
    }
}
void FileParser::duplicateMultipleNodes(std::vector<size_t> ogBlockIndex, std::vector<size_t> ogNodeIndex, size_t pasteBlockIndex) {
    // Every block index in the ogBlockIndices list has a corresponding node index, (requiring duplicates if multiple nodes in the same block).
    for (size_t index = 0; index < this->getNumBlocks(); ++index) {
        this->duplicateNode(ogBlockIndex.at(index), ogNodeIndex.at(index), pasteBlockIndex);
    }
}
void FileParser::duplicateMultipleNodes(std::vector<size_t> ogBlockIndex, std::vector<size_t> ogNodeIndex, std::vector<size_t> pasteBlockIndices) {
    for (size_t pasteBlockIndex : pasteBlockIndices) {
        this->duplicateMultipleNodes(ogBlockIndex, ogNodeIndex, pasteBlockIndex);
    }
}

// File-handling

void FileParser::setPath(std::string file) {
    this->filePath = file;
}
void FileParser::setPath(const char file[]) {
    this->setPath((std::string)file);
}
void FileParser::setPath(wxString file) {
    this->setPath(file.ToStdString());
}

void FileParser::save(std::string file) {
    if (file != "") {
        std::ofstream fout(file.c_str(), std::ios::binary | std::ios::trunc);
        for (size_t lineIndex = 0; lineIndex < this->getNumBlocks(); ++lineIndex) {
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
}
void FileParser::save(const char file[]) {
    this->save((std::string)file);
}
void FileParser::save(wxString file) {
    this->save(file.ToStdString());
}
void FileParser::save() {
    if (this->getPath() != "") {
        this->save(this->getPath());
    }
}

void FileParser::update() {
    if (this->getPath() != "" && fs::exists(this->getPath().c_str())) {
        std::vector<std::vector<std::string>> newBlockTextList;
        std::vector<std::vector<size_t>> newBlockAddressList;
        size_t lineCounter = 0;
        std::string line;
        std::string fileContents;
        {
            std::ifstream fin(this->getPath().c_str(), std::ios::binary);
            std::ostringstream sout;
            sout << fin.rdbuf();
            fileContents = sout.str();
        }

        bool lastLineRead = false;
        for (size_t lineIndex = fileContents.find("\x{FF}\x{FF}\x{FF}\x{FF}\x{FF}\x{FF}\x{FF}\x{FF}"); !lastLineRead; lineIndex = fileContents.find("\x{FF}\x{FF}\x{FF}\x{FF}\x{FF}\x{FF}\x{FF}\x{FF}")) {
            lastLineRead = (lineIndex == std::string::npos);
            line = fileContents.substr(0, lineIndex);
            fileContents = fileContents.substr(lineIndex + 8);
            newBlockTextList.push_back( { { "" } } );
            newBlockAddressList.push_back( { { 0 } } );
            if (line.at(0) == '\x{01}' ) {
                this->firstBlock = lineCounter;
                line = line.substr(1);
            }

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

            ++lineCounter;
        }

        this->setBlockLists(newBlockTextList, newBlockAddressList);
    }
}

/*
======================================================

        Private

======================================================
*/

void FileParser::initialize(std::string file, bool startEmpty) {
    this->setPath(file);
    if (startEmpty || file == "") {
        this->firstBlock = 0;
        if (startEmpty) {
            this->blockTextList = {{}};
            this->blockAddressList = {{}};
        }
        else {
            this->blockTextList = {{"Example body"}};
            this->blockAddressList = {{0}};
        }
    }
    if (file != "" && !fs::exists((file.c_str()))) {
        if (startEmpty) {
            newFile(file);
        }
        else {
            newFile(file, "Example body");
        }
    }
//    else if (file != "") {
//        this->update();
//    }
}
void FileParser::initialize(std::string file, std::vector<std::vector<std::string>> blockTextLists, std::vector<std::vector<size_t>> blockAddressLists, size_t topBlock) {
    this->setPath(file);
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
