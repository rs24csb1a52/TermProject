#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "AVLTree.h"
#include <string>
#include <vector>
using namespace std; 
class FileHandler {
private:
    AVLTree& tree;
    
    vector<string> splitString(const string& str, char delimiter);
    string trim(const string& str);
    
    void handleInsertStudent(const vector<string>& lines, int& lineIndex);
    void handleModifyCGPA(const string& line);
    void handleAddCourse(const string& line);
    void handleModifyCourseMarks(const string& line);
    void handleDeleteCourse(const string& line);
    void handleDeleteStudent(const string& line);
    void handlePrintAboveRollNo(const string& line);
    void handlePrintBelowRollNo(const string& line);
    void handlePrintBetweenRollNo(const string& line);
    void handlePrintAboveCGPA(const string& line);
    void handlePrintBelowCGPA(const string& line);
    void handlePrintBetweenCGPA(const string& line);
    
public:
    FileHandler(AVLTree& tree);
    
    bool processFile(const string& filename);
};

#endif // FILEHANDLER_H
