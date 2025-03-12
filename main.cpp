#include "FileHandler.h"
#include "AVLTree.h"
#include <iostream>
#include <string>
using namespace std;
int main(int argc, char* argv[]) {
    if (argc < 2 || argc > 3) {
        cout << "Usage: " << argv[0] << " <input_file> [key_type]" << endl;
        cout << "key_type: rollno (default) or cgpa" << endl;
        return 1;
    }
    
    bool isRollNoKey = true;
    if (argc == 3) {
        string keyType = argv[2];
        if (keyType == "cgpa") {
            isRollNoKey = false;
            cout << "Using CGPA as the key for the AVL tree." << endl;
        } else if (keyType == "rollno") {
            cout << "Using Roll Number as the key for the AVL tree." << endl;
        } else {
            cout << "Invalid key type. Use 'rollno' or 'cgpa'." << endl;
            return 1;
        }
    } else {
        cout << "Using Roll Number as the key for the AVL tree (default)." << endl;
    }
    
    AVLTree tree(isRollNoKey);
    
    FileHandler fileHandler(tree);
    
    string filename = argv[1];
    cout << "Processing file: " << filename << endl;
    
    if (!fileHandler.processFile(filename)) {
        cout << "Error processing file: " << filename << endl;
        return 1;
    }
    
    cout << "File processed successfully." << endl;
    return 0;
}
