#include "FileHandler.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;

FileHandler::FileHandler(AVLTree& tree) : tree(tree) {}

vector<string> FileHandler::splitString(const string& str, char delimiter) {
    vector<string> tokens;
    stringstream ss(str);
    string token;
    
    while (getline(ss, token, delimiter)) {
        tokens.push_back(trim(token));
    }
    
    return tokens;
}


string FileHandler::trim(const string& str) {
    auto start = find_if_not(str.begin(), str.end(), [](unsigned char c) {
        return isspace(c);
    });
    
    auto end = find_if_not(str.rbegin(), str.rend(), [](unsigned char c) {
        return isspace(c);
    }).base();
    
    return (start < end) ? string(start, end) : string();
}

bool FileHandler::processFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return false;
    }
    
    vector<string> lines;
    string line;
    
    while (getline(file, line)) {
        lines.push_back(line);
    }
    
    file.close();
    
    
    int lineIndex = 0;
    while (lineIndex < lines.size()) {
        line = trim(lines[lineIndex]);
        
        
        if (line.empty()) {
            lineIndex++;
            continue;
        }
        
        
        if (line[0] == '#') {
            int operation = 0;
            try {
                operation = stoi(line.substr(1));
            } catch (const exception& e) {
                cerr << "Error parsing operation: " << line << endl;
                lineIndex++;
                continue;
            }
            
            lineIndex++;
            
            
            switch (operation) {
                case 1: // Insert student
                    handleInsertStudent(lines, lineIndex);
                    break;
                    
                case 2: // Modify student CGPA
                    if (lineIndex < lines.size()) {
                        handleModifyCGPA(lines[lineIndex]);
                        lineIndex++;
                    }
                    break;
                    
                case 3: // Add new course
                    if (lineIndex < lines.size()) {
                        handleAddCourse(lines[lineIndex]);
                        lineIndex++;
                    }
                    break;
                    
                case 4: // Modify course marks
                    if (lineIndex < lines.size()) {
                        handleModifyCourseMarks(lines[lineIndex]);
                        lineIndex++;
                    }
                    break;
                    
                case 5: // Delete course
                    if (lineIndex < lines.size()) {
                        handleDeleteCourse(lines[lineIndex]);
                        lineIndex++;
                    }
                    break;
                    
                case 6: // Delete student
                    if (lineIndex < lines.size()) {
                        handleDeleteStudent(lines[lineIndex]);
                        lineIndex++;
                    }
                    break;
                    
                case 7: // Print students with roll number greater than given value
                    if (tree.getIsRollNoKey() && lineIndex < lines.size()) {
                        handlePrintAboveRollNo(lines[lineIndex]);
                        lineIndex++;
                    } else {
                        lineIndex++;
                    }
                    break;
                    
                case 8: // Print students with roll number less than given value
                    if (tree.getIsRollNoKey() && lineIndex < lines.size()) {
                        handlePrintBelowRollNo(lines[lineIndex]);
                        lineIndex++;
                    } else {
                        lineIndex++;
                    }
                    break;
                    
                case 9: // Print students with roll number between two given values
                    if (tree.getIsRollNoKey() && lineIndex < lines.size()) {
                        handlePrintBetweenRollNo(lines[lineIndex]);
                        lineIndex++;
                    } else {
                        lineIndex++;
                    }
                    break;
                    
                case 10: // Print students with CGPA greater than given value
                    if (!tree.getIsRollNoKey() && lineIndex < lines.size()) {
                        handlePrintAboveCGPA(lines[lineIndex]);
                        lineIndex++;
                    } else {
                        lineIndex++;
                    }
                    break;
                    
                case 11: // Print students with CGPA less than given value
                    if (!tree.getIsRollNoKey() && lineIndex < lines.size()) {
                        handlePrintBelowCGPA(lines[lineIndex]);
                        lineIndex++;
                    } else {
                        lineIndex++;
                    }
                    break;
                    
                case 12: // Print students with CGPA between two given values
                    if (!tree.getIsRollNoKey() && lineIndex < lines.size()) {
                        handlePrintBetweenCGPA(lines[lineIndex]);
                        lineIndex++;
                    } else {
                        lineIndex++;
                    }
                    break;
                    
                default:
                    cerr << "Unknown operation: " << operation << endl;
                    lineIndex++;
                    break;
            }
        } else {
            lineIndex++;
        }
        
        
        tree.displayAll();
    }
    
    return true;
}


void FileHandler::handleInsertStudent(const vector<string>& lines, int& lineIndex) {
    if (lineIndex >= lines.size()) {
        return;
    }


    string studentLine = lines[lineIndex++];
    vector<string> studentData = splitString(studentLine, ',');
    
    if (studentData.size() < 4) {
        cerr << "Error: Invalid student data format" << endl;
        return;
    }
    
    int rollNo;
    string name;
    float cgpa;
    int numSubjects;
    
    try {
        rollNo = stoi(studentData[0]);
        name = studentData[1];
        cgpa = stof(studentData[2]);
        numSubjects = stoi(studentData[3]);
    } catch (const exception& e) {
        cerr << "Error parsing student data: " << e.what() << endl;
        return;
    }
    
    vector<CourseInfo> courses;
    for (int i = 0; i < numSubjects && lineIndex < lines.size(); i++) {
        string courseLine = lines[lineIndex++];
        vector<string> courseData = splitString(courseLine, ',');
        
        if (courseData.size() < 2) {
            cerr << "Error: Invalid course data format" << endl;
            continue;
        }
        
        string courseCode = courseData[0];
        float marks;
        
        try {
            marks = stof(courseData[1]);
        } catch (const exception& e) {
            cerr << "Error parsing course marks: " << e.what() << endl;
            continue;
        }
        
        courses.push_back(CourseInfo(courseCode, marks));
    }
    
    
    tree.insert(rollNo, name, cgpa, courses);
    cout << "Inserted student: " << rollNo << ", " << name << endl;
}


void FileHandler::handleModifyCGPA(const string& line) {
    vector<string> data = splitString(line, ',');
    
    if (data.size() < 2) {
        cerr << "Error: Invalid CGPA modification format" << endl;
        return;
    }
    
    int rollNo;
    float newCGPA;
    
    try {
        rollNo = stoi(data[0]);
        newCGPA = stof(data[1]);
    } catch (const exception& e) {
        cerr << "Error parsing CGPA modification data: " << e.what() << endl;
        return;
    }
    
    if (tree.updateCGPA(rollNo, newCGPA)) {
        cout << "Updated CGPA for student " << rollNo << " to " << newCGPA << endl;
    } else {
        cerr << "Error: Student " << rollNo << " not found" << endl;
    }
}


void FileHandler::handleAddCourse(const string& line) {
    vector<string> data = splitString(line, ',');
    
    if (data.size() < 3) {
        cerr << "Error: Invalid course addition format" << endl;
        return;
    }
    
    int rollNo;
    string courseCode;
    float marks;
    
    try {
        rollNo = stoi(data[0]);
        courseCode = data[1];
        marks = stof(data[2]);
    } catch (const exception& e) {
        cerr << "Error parsing course addition data: " << e.what() << endl;
        return;
    }
    
    if (tree.addCourse(rollNo, courseCode, marks)) {
        cout << "Added course " << courseCode << " with marks " << marks << " to student " << rollNo << endl;
    } else {
        cerr << "Error: Could not add course to student " << rollNo << endl;
    }
}


void FileHandler::handleModifyCourseMarks(const string& line) {
    vector<string> data = splitString(line, ',');
    
    if (data.size() < 3) {
        cerr << "Error: Invalid course marks modification format" << endl;
        return;
    }
    
    int rollNo;
    string courseCode;
    float newMarks;
    
    try {
        rollNo = stoi(data[0]);
        courseCode = data[1];
        newMarks = stof(data[2]);
    } catch (const exception& e) {
        cerr << "Error parsing course marks modification data: " << e.what() << endl;
        return;
    }
    
    if (tree.updateCourseMarks(rollNo, courseCode, newMarks)) {
        cout << "Updated marks for course " << courseCode << " to " << newMarks << " for student " << rollNo << endl;
    } else {
        cerr << "Error: Could not update course marks for student " << rollNo << endl;
    }
}


void FileHandler::handleDeleteCourse(const string& line) {
    vector<string> data = splitString(line, ',');
    
    if (data.size() < 2) {
        cerr << "Error: Invalid course deletion format" << endl;
        return;
    }
    
    int rollNo;
    string courseCode;
    
    try {
        rollNo = stoi(data[0]);
        courseCode = data[1];
    } catch (const exception& e) {
        cerr << "Error parsing course deletion data: " << e.what() << endl;
        return;
    }
    
    if (tree.removeCourse(rollNo, courseCode)) {
        cout << "Deleted course " << courseCode << " from student " << rollNo << endl;
    } else {
        cerr << "Error: Could not delete course from student " << rollNo << endl;
    }
}


void FileHandler::handleDeleteStudent(const string& line) {
    int rollNo;
    
    try {
        rollNo = stoi(trim(line));
    } catch (const exception& e) {
        cerr << "Error parsing student deletion data: " << e.what() << endl;
        return;
    }
    
    if (tree.remove(rollNo)) {
        cout << "Deleted student " << rollNo << endl;
    } else {
        cerr << "Error: Student " << rollNo << " not found" << endl;
    }
}


void FileHandler::handlePrintAboveRollNo(const string& line) {
    int rollNo;
    
    try {
        rollNo = stoi(trim(line));
    } catch (const exception& e) {
        cerr << "Error parsing roll number: " << e.what() << endl;
        return;
    }
    
    tree.displayStudentsAboveRollNo(rollNo);
}


void FileHandler::handlePrintBelowRollNo(const string& line) {
    int rollNo;
    
    try {
        rollNo = stoi(trim(line));
    } catch (const exception& e) {
        cerr << "Error parsing roll number: " << e.what() << endl;
        return;
    }
    
    tree.displayStudentsBelowRollNo(rollNo);
}


void FileHandler::handlePrintBetweenRollNo(const string& line) {
    vector<string> data = splitString(line, ',');
    
    if (data.size() < 2) {
        cerr << "Error: Invalid roll number range format" << endl;
        return;
    }
    
    int minRoll, maxRoll;
    
    try {
        minRoll = stoi(data[0]);
        maxRoll = stoi(data[1]);
    } catch (const exception& e) {
        cerr << "Error parsing roll number range: " << e.what() << endl;
        return;
    }
    
    tree.displayStudentsInRollNoRange(minRoll, maxRoll);
}


void FileHandler::handlePrintAboveCGPA(const string& line) {
    float cgpa;
    
    try {
        cgpa = stof(trim(line));
    } catch (const exception& e) {
        cerr << "Error parsing CGPA: " << e.what() << endl;
        return;
    }
    
    tree.displayStudentsAboveCGPA(cgpa);
}


void FileHandler::handlePrintBelowCGPA(const string& line) {
    float cgpa;
    
    try {
        cgpa = stof(trim(line));
    } catch (const exception& e) {
        cerr << "Error parsing CGPA: " << e.what() << endl;
        return;
    }
    
    tree.displayStudentsBelowCGPA(cgpa);
}


void FileHandler::handlePrintBetweenCGPA(const string& line) {
    vector<string> data = splitString(line, ',');
    
    if (data.size() < 2) {
        cerr << "Error: Invalid CGPA range format" << endl;
        return;
    }
    
    float minCGPA, maxCGPA;
    
    try {
        minCGPA = stof(data[0]);
        maxCGPA = stof(data[1]);
    } catch (const exception& e) {
        cerr << "Error parsing CGPA range: " << e.what() << endl;
        return;
    }
    
    tree.displayStudentsInCGPARange(minCGPA, maxCGPA);
}
