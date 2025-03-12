#include "Node.h"
#include <algorithm>
using namespace std;
Node::Node() : rollNo(0), name(""), cgpa(0.0), left(nullptr), right(nullptr), height(1), isRollNoKey(true) {}

Node::Node(int rollNo, const string& name, float cgpa, const vector<CourseInfo>& courses, bool isRollNoKey)
    : rollNo(rollNo), name(name), cgpa(cgpa), courses(courses), left(nullptr), right(nullptr), height(1), isRollNoKey(isRollNoKey) {}

int Node::getRollNo() const {
    return rollNo;
}

string Node::getName() const {
    return name;
}

float Node::getCGPA() const {
    return cgpa;
}

vector<CourseInfo>& Node::getCourses() {
    return courses;
}

const vector<CourseInfo>& Node::getCourses() const {
    return courses;
}

int Node::getNumCourses() const {
    return courses.size();
}

Node* Node::getLeft() const {
    return left;
}

Node* Node::getRight() const {
    return right;
}

int Node::getHeight() const {
    return height;
}

bool Node::getIsRollNoKey() const {
    return isRollNoKey;
}

void Node::setRollNo(int rollNo) {
    this->rollNo = rollNo;
}

void Node::setName(const string& name) {
    this->name = name;
}

void Node::setCGPA(float cgpa) {
    this->cgpa = cgpa;
}

void Node::setCourses(const vector<CourseInfo>& courses) {
    this->courses = courses;
}

void Node::setLeft(Node* left) {
    this->left = left;
}

void Node::setRight(Node* right) {
    this->right = right;
}

void Node::setHeight(int height) {
    this->height = height;
}

bool Node::addCourse(const string& courseCode, float marks) {
  
    for (const auto& course : courses) {
        if (course.getCourseCode() == courseCode) {
            return false; 
        }
    }
    
    courses.push_back(CourseInfo(courseCode, marks));
    return true;
}

bool Node::updateCourseMarks(const string& courseCode, float newMarks) {
    for (auto& course : courses) {
        if (course.getCourseCode() == courseCode) {
            course.setMarks(newMarks);
            return true;
        }
    }
    return false; 
}

bool Node::removeCourse(const string& courseCode) {
    auto it = find_if(courses.begin(), courses.end(), 
                          [&courseCode](const CourseInfo& course) {
                              return course.getCourseCode() == courseCode;
                          });
    
    if (it != courses.end()) {
        courses.erase(it);
        return true;
    }
    return false; 
}

CourseInfo* Node::findCourse(const string& courseCode) {
    for (auto& course : courses) {
        if (course.getCourseCode() == courseCode) {
            return &course;
        }
    }
    return nullptr;
}
