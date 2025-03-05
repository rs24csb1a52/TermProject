#include "node.h"
#include <algorithm>
using namespace std;

Node::Node(int rollNo, const string& name, float cgpa, int numSubjects, CourseInfo* courses, bool isRollNoKey)
    : rollNo(rollNo), name(name), cgpa(cgpa), numSubjects(numSubjects), isRollNoKey(isRollNoKey) {
    this->courses = new CourseInfo[max(1, numSubjects)];
    if (courses != nullptr) {
        for (int i = 0; i < numSubjects; i++) {
            this->courses[i] = courses[i];
        }
    }
    right = nullptr;
    left = nullptr;
    height = 1;
}

Node::Node() {
    this->rollNo = 0;
    this->name = "";
    this->cgpa = 0.0;
    this->numSubjects = 0;
    this->courses = nullptr;
    this->right = nullptr;
    this->left = nullptr;
    this->height = 1;
    this->isRollNoKey = true;
}

bool Node::isRollNumberKey() const {
    return isRollNoKey;
}

int Node::getRollNo() const {
    return rollNo;
}

string Node::getName() const {
    return name;
}

float Node::getCGPA() const {
    return cgpa;
}

CourseInfo* Node::getCourses() const {
    return courses;
}

int Node::getNumSubjects() const {
    return numSubjects;
}

int Node::getHeight() const {
    return height;
}

Node* Node::getRight() const {
    return right;
}

Node* Node::getLeft() const {
    return left;
}

void Node::setRollNo(int rollNo) {
    this->rollNo = rollNo;
}

void Node::setName(string name) {
    this->name = name;
}

void Node::setCGPA(float newCGPA) {
    cgpa = newCGPA;
}

void Node::setHeight(int h) {
    height = h;
}

void Node::setNumSubjects(int newNumSubjects) {
    CourseInfo* newCourses = new CourseInfo[max(0, newNumSubjects)];

    int copyCount = min(numSubjects, newNumSubjects);
    for (int i = 0; i < copyCount; i++) {
        newCourses[i] = courses[i];
    }

    delete[] courses;
    courses = newCourses;
    numSubjects = newNumSubjects;
}

void Node::setCourses(CourseInfo* newCourses) {
    delete[] courses; // Free the old courses array
    courses = newCourses; // Assign the new courses array
}

void Node::setCourseId(int index, int newCourseId) {
    if (index >= 0 && index < numSubjects) {
        courses[index].setCourseId(newCourseId);
    }
}

void Node::setCourseMarks(int index, float newMarks) {
    if (index >= 0 && index < numSubjects) {
        courses[index].setMarks(newMarks);
    }
}

void Node::setRight(Node* right) {
    this->right = right;
}

void Node::setLeft(Node* left) {
    this->left = left;
}
