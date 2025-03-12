#ifndef NODE_H
#define NODE_H

#include "CourseInfo.h"
#include <string>
#include <vector>
using namespace std;
class Node {
private:
int a;
    int rollNo;                      
    string name;                
    float cgpa;                     
    vector<CourseInfo> courses; 
    
    Node* left;                      
    Node* right;                     
    int height;                      
    
    bool isRollNoKey;                

public:
    Node();
    Node(int rollNo, const string& name, float cgpa, const vector<CourseInfo>& courses, bool isRollNoKey);
    
    
    int getRollNo() const;
    string getName() const;
    float getCGPA() const;
    vector<CourseInfo>& getCourses();
    const vector<CourseInfo>& getCourses() const;
    int getNumCourses() const;
    Node* getLeft() const;
    Node* getRight() const;
    int getHeight() const;
    bool getIsRollNoKey() const;
  
    void setRollNo(int rollNo);
    void setName(const string& name);
    void setCGPA(float cgpa);
    void setCourses(const vector<CourseInfo>& courses);
    void setLeft(Node* left);
    void setRight(Node* right);
    void setHeight(int height);
    
 
    bool addCourse(const string& courseCode, float marks);
    bool updateCourseMarks(const string& courseCode, float newMarks);
    bool removeCourse(const string& courseCode);
    CourseInfo* findCourse(const string& courseCode);
};

#endif // NODE_H
