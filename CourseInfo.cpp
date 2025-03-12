#include "CourseInfo.h"
#include <iostream>

CourseInfo::CourseInfo() : courseCode(""), marks(0.0) {}

CourseInfo::CourseInfo(const std::string& courseCode, float marks) 
    : courseCode(courseCode), marks(marks) {}

std::string CourseInfo::getCourseCode() const {
    return courseCode;
}

float CourseInfo::getMarks() const {
    return marks;
}

void CourseInfo::setCourseCode(const std::string& courseCode) {
    this->courseCode = courseCode;
}

void CourseInfo::setMarks(float marks) {
    this->marks = marks;
}
