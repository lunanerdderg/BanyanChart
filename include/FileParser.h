/* ===================================================

BanyanChart Copyright (c) 2026 lunanerdderg
<https://github.com/lunanerdderg/BanyanChart/blob/main/README.md>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted (subject to the limitations in the disclaimer
below) provided that the following conditions are met:

     * Redistributions of source code must retain the above copyright notice,
     this list of conditions and the following disclaimer.

     * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.

     * Neither the name of the copyright holder nor the names of its
     contributors may be used to endorse or promote products derived from this
     software without specific prior written permission.

DISCLAIMER

NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY
THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

=================================================== */

#ifndef FILEPARSER_H
#define FILEPARSER_H

//#include <iostream> // TESTING

#include "../BanyanChartApp.h"
#include <vector>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include <filesystem>
namespace fs = std::filesystem;

void newFile(std::string, std::string="");

class FileParser {
    public:
//        void coutBlockLists(); // TESTING
        FileParser(); FileParser(bool); FileParser(const char[]); FileParser(std::string); FileParser(wxString); FileParser(std::vector<std::vector<std::string>>, std::vector<std::vector<size_t>>, size_t=0); FileParser(const char[], std::vector<std::vector<std::string>>, std::vector<std::vector<size_t>>, size_t=0); FileParser(wxString, std::vector<std::vector<std::string>>, std::vector<std::vector<size_t>>, size_t=0); FileParser(std::string, std::vector<std::vector<std::string>>, std::vector<std::vector<size_t>>, size_t=0);
        virtual ~FileParser(); // const char[] // const char*
        void newInstance(bool=false); void newInstance(const char[]); void newInstance(std::string); void newInstance(wxString); void newInstance(std::vector<std::vector<std::string>>, std::vector<std::vector<size_t>>, size_t=0); void newInstance(const char[], std::vector<std::vector<std::string>>, std::vector<std::vector<size_t>>, size_t=0); void newInstance(wxString, std::vector<std::vector<std::string>>, std::vector<std::vector<size_t>>, size_t=0); void newInstance(std::string, std::vector<std::vector<std::string>>, std::vector<std::vector<size_t>>, size_t=0);
        // Get
        std::string getPath();
        size_t getFirstBlock();
        size_t getNumBlocks();
        size_t getNumNodes(size_t);
        std::string getNodeText(size_t, size_t=0);
        size_t getNodeAddress(size_t, size_t);
        std::string getBlockBody(size_t);
        std::vector<std::string> getBlockText(size_t);
        std::vector<size_t> getBlockAddress(size_t);
        std::vector<std::vector<std::string>> getBlockTextList();
        std::vector<std::vector<size_t>> getBlockAddressList();
        // Set
        void setBlockLists(std::vector<std::vector<std::string>>, std::vector<std::vector<size_t>>);
          // Block editing
        void setText(std::string, size_t, size_t=0); void setText(const char[], size_t, size_t=0);
        void setNodeAddress(size_t, size_t, size_t);
        void setFirstBlock(size_t);
        void addBlock(std::string=""); void addBlock(std::vector<std::string>, std::vector<size_t>); void addBlock(std::string, std::vector<std::string>, std::vector<size_t>);
        void addMultipleBlocks(std::vector<std::vector<std::string>>, std::vector<std::vector<size_t>>);
        void removeBlock(size_t); // BOOKMARK (Add functionality to make nodes point to nothing if block they point to is removed [-2 rather than -1?])
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
        void setPath(const char[]); void setPath(std::string); void setPath(wxString);
        void save();
        void save(const char[]); void save(std::string); void save(wxString);
        void update();

    private:
        size_t firstBlock;
        std::string filePath;
        std::vector<std::vector<std::string>> blockTextList;
        std::vector<std::vector<size_t>> blockAddressList;

        void initialize(std::string, bool=false); void initialize(std::string, std::vector<std::vector<std::string>>, std::vector<std::vector<size_t>>, size_t=0);
        // Streams
        size_t getSize_tFromBinary(std::ifstream&); size_t getSize_tFromBinary(std::istringstream&);
        void writeSize_tToBinary(std::ofstream&, size_t); void writeSize_tToBinary(std::ostringstream&, size_t);
};

#endif // FILEPARSER_H
