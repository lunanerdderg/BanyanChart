#include "FileParser.h"

int main() {
    FileParser file("");
//    FileParser file("test.byfc", true);
//    file.coutBlockLists(); std::cout << "\n\n";
//    file.duplicateMultipleNodes({1,2}, {1,2}, {0,3});
    file.coutBlockLists();
    file.save();
    std::cout << std::endl << ( file.getPath() == "" ) << std::endl;
    return 0;
}
