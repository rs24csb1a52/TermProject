#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "node_operations.h"
#include <string>
#include <vector>

class FileHandler {
private:
    Node*& root;
    std::string currentCommand;
    bool isRollNumberKey;

    // Helper functions for parsing data
    std::vector<std::string> splitAndTrim(const std::string& str);
    bool parseStudentData(const std::string& line, int& rollNo, std::string& name, float& cgpa, int& numSubjects);
    bool parseCourseData(const std::string& line, int& courseId, float& marks);
    
    // Helper functions for each operation type
    void handleInitialList(const std::vector<std::string>& lines);
    void processLine(const std::string& line);

    std::string trim(const std::string& str);

public:
    FileHandler(Node*& root, bool isRollNumberKey = true) : root(root), isRollNumberKey(isRollNumberKey) {}
    bool processFile(const std::string& filename);
};

#endif
