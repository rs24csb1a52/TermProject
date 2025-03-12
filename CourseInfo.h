#ifndef COURSEINFO_H
#define COURSEINFO_H

#include <string>
using namespace std;
class CourseInfo {
private:
    string courseCode;  
    float marks;             
public:
    CourseInfo();
    CourseInfo(const string& courseCode, float marks);
    
    string getCourseCode() const;
    float getMarks() const;
    
    void setCourseCode(const string& courseCode);
    void setMarks(float marks);
};

#endif
