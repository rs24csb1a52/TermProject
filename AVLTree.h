#ifndef AVLTREE_H
#define AVLTREE_H

#include "Node.h"
#include <string>
#include <vector>
using namespace std;

class AVLTree {
private:
    Node* root;
    bool isRollNoKey; 
    
    int getHeight(Node* node);
    int getBalanceFactor(Node* node);
    Node* rightRotate(Node* y);
    Node* leftRotate(Node* x);
    
    Node* insertNode(Node* node, int rollNo, const string& name, float cgpa, const vector<CourseInfo>& courses);
    Node* deleteNode(Node* root, int rollNo);
    Node* findMinValueNode(Node* node);
    Node* findNode(Node* root, int rollNo);
    Node* findNodeByCGPA(Node* root, float cgpa);
    
   
    void inOrderTraversal(Node* node);
    void printStudentsInRollNoRange(Node* node, int minRoll, int maxRoll);
    void printStudentsInCGPARange(Node* node, float minCGPA, float maxCGPA);
    void printStudentsAboveRollNo(Node* node, int rollNo);
    void printStudentsBelowRollNo(Node* node, int rollNo);
    void printStudentsAboveCGPA(Node* node, float cgpa);
    void printStudentsBelowCGPA(Node* node, float cgpa);

public:
 
    AVLTree(bool isRollNoKey = true);
    

    ~AVLTree();
    
  
    void insert(int rollNo, const string& name, float cgpa, const vector<CourseInfo>& courses);
    bool remove(int rollNo);
    Node* search(int rollNo);
    Node* searchByCGPA(float cgpa);
    

    bool updateCGPA(int rollNo, float newCGPA);
    bool addCourse(int rollNo, const string& courseCode, float marks);
    bool updateCourseMarks(int rollNo, const string& courseCode, float newMarks);
    bool removeCourse(int rollNo, const string& courseCode);
    
 
    void displayAll();
    void displayStudentsInRollNoRange(int minRoll, int maxRoll);
    void displayStudentsInCGPARange(float minCGPA, float maxCGPA);
    void displayStudentsAboveRollNo(int rollNo);
    void displayStudentsBelowRollNo(int rollNo);
    void displayStudentsAboveCGPA(float cgpa);
    void displayStudentsBelowCGPA(float cgpa);
    
   
    void destroyTree(Node* node);
    

    Node* getRoot() const;
    
    
    bool getIsRollNoKey() const;
};

#endif // AVLTREE_H 
