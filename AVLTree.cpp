#include "AVLTree.h"
#include <algorithm>
#include <iostream>
using namespace std;

AVLTree::AVLTree(bool isRollNoKey) : root(nullptr), isRollNoKey(isRollNoKey) {}


AVLTree::~AVLTree() {
    destroyTree(root);
}

void AVLTree::destroyTree(Node* node) {
    if (node != nullptr) {
        destroyTree(node->getLeft());
        destroyTree(node->getRight());
        delete node;
    }
}


int AVLTree::getHeight(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->getHeight();
}

int AVLTree::getBalanceFactor(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return getHeight(node->getLeft()) - getHeight(node->getRight());
}


Node* AVLTree::rightRotate(Node* y) {
    Node* x = y->getLeft();
    Node* T2 = x->getRight();

    
    x->setRight(y);
    y->setLeft(T2);

   
    y->setHeight(max(getHeight(y->getLeft()), getHeight(y->getRight())) + 1);
    x->setHeight(max(getHeight(x->getLeft()), getHeight(x->getRight())) + 1);

   
    return x;
}


Node* AVLTree::leftRotate(Node* x) {
    Node* y = x->getRight();
    Node* T2 = y->getLeft();


    y->setLeft(x);
    x->setRight(T2);


    x->setHeight(max(getHeight(x->getLeft()), getHeight(x->getRight())) + 1);
    y->setHeight(max(getHeight(y->getLeft()), getHeight(y->getRight())) + 1);


    return y;
}


Node* AVLTree::insertNode(Node* node, int rollNo, const string& name, float cgpa, const vector<CourseInfo>& courses) {

    if (node == nullptr) {
        return new Node(rollNo, name, cgpa, courses, isRollNoKey);
    }

    
    if (isRollNoKey) {
        if (rollNo < node->getRollNo()) {
            node->setLeft(insertNode(node->getLeft(), rollNo, name, cgpa, courses));
        } else if (rollNo > node->getRollNo()) {
            node->setRight(insertNode(node->getRight(), rollNo, name, cgpa, courses));
        } else {
            return node;
        }
    } else {
        if (cgpa < node->getCGPA()) {
            node->setLeft(insertNode(node->getLeft(), rollNo, name, cgpa, courses));
        } else if (cgpa > node->getCGPA()) {
            node->setRight(insertNode(node->getRight(), rollNo, name, cgpa, courses));
        } else {
            if (rollNo < node->getRollNo()) {
                node->setLeft(insertNode(node->getLeft(), rollNo, name, cgpa, courses));
            } else if (rollNo > node->getRollNo()) {
                node->setRight(insertNode(node->getRight(), rollNo, name, cgpa, courses));
            } else {
                return node;
            }
        }
    }

    node->setHeight(1 + max(getHeight(node->getLeft()), getHeight(node->getRight())));

    int balance = getBalanceFactor(node);

    if (balance > 1) {
        if (isRollNoKey) {
            if (rollNo < node->getLeft()->getRollNo()) {
                return rightRotate(node);
            }
            else if (rollNo > node->getLeft()->getRollNo()) {
                node->setLeft(leftRotate(node->getLeft()));
                return rightRotate(node);
            }
        } else {
            if (cgpa < node->getLeft()->getCGPA()) {
                return rightRotate(node);
            }
            else if (cgpa > node->getLeft()->getCGPA()) {
                node->setLeft(leftRotate(node->getLeft()));
                return rightRotate(node);
            }
        }
    }

    if (balance < -1) {
        if (isRollNoKey) {
            if (rollNo > node->getRight()->getRollNo()) {
                return leftRotate(node);
            }
            else if (rollNo < node->getRight()->getRollNo()) {
                node->setRight(rightRotate(node->getRight()));
                return leftRotate(node);
            }
        } else {
            if (cgpa > node->getRight()->getCGPA()) {
                return leftRotate(node);
            }
            else if (cgpa < node->getRight()->getCGPA()) {
                node->setRight(rightRotate(node->getRight()));
                return leftRotate(node);
            }
        }
    }

    return node;
}

Node* AVLTree::findMinValueNode(Node* node) {
    Node* current = node;
    
    while (current && current->getLeft() != nullptr) {
        current = current->getLeft();
    }
    
    return current;
}

Node* AVLTree::deleteNode(Node* root, int rollNo) {
    if (root == nullptr) {
        return root;
    }
    
    if (isRollNoKey) {
        if (rollNo < root->getRollNo()) {
            root->setLeft(deleteNode(root->getLeft(), rollNo));
        } else if (rollNo > root->getRollNo()) {
            root->setRight(deleteNode(root->getRight(), rollNo));
        } else {
            if (root->getLeft() == nullptr || root->getRight() == nullptr) {
                Node* temp = root->getLeft() ? root->getLeft() : root->getRight();
                
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else {
                    *root = *temp; 
                }
                
                delete temp;
            } else {
                Node* temp = findMinValueNode(root->getRight());
                
                root->setRollNo(temp->getRollNo());
                root->setName(temp->getName());
                root->setCGPA(temp->getCGPA());
                root->setCourses(temp->getCourses());
                
                root->setRight(deleteNode(root->getRight(), temp->getRollNo()));
            }
        }
    } else {
        Node* nodeToDelete = findNode(root, rollNo);
        if (nodeToDelete == nullptr) {
            return root; 
        }
        
        float cgpa = nodeToDelete->getCGPA();
        
        if (cgpa < root->getCGPA()) {
            root->setLeft(deleteNode(root->getLeft(), rollNo));
        } else if (cgpa > root->getCGPA()) {
            root->setRight(deleteNode(root->getRight(), rollNo));
        } else {
            if (rollNo < root->getRollNo()) {
                root->setLeft(deleteNode(root->getLeft(), rollNo));
            } else if (rollNo > root->getRollNo()) {
                root->setRight(deleteNode(root->getRight(), rollNo));
            } else {
                if (root->getLeft() == nullptr || root->getRight() == nullptr) {
                    Node* temp = root->getLeft() ? root->getLeft() : root->getRight();
                    
                    if (temp == nullptr) {
                        temp = root;
                        root = nullptr;
                    } else {
                        *root = *temp; 
                    }
                    
                    delete temp;
                } else {
                    Node* temp = findMinValueNode(root->getRight());
                    
                    root->setRollNo(temp->getRollNo());
                    root->setName(temp->getName());
                    root->setCGPA(temp->getCGPA());
                    root->setCourses(temp->getCourses());
                    
                    root->setRight(deleteNode(root->getRight(), temp->getRollNo()));
                }
            }
        }
    }
    
    if (root == nullptr) {
        return root;
    }
    
    root->setHeight(1 + max(getHeight(root->getLeft()), getHeight(root->getRight())));
    
    int balance = getBalanceFactor(root);
    
    if (balance > 1 && getBalanceFactor(root->getLeft()) >= 0) {
        return rightRotate(root);
    }
    
    if (balance > 1 && getBalanceFactor(root->getLeft()) < 0) {
        root->setLeft(leftRotate(root->getLeft()));
        return rightRotate(root);
    }
    
    if (balance < -1 && getBalanceFactor(root->getRight()) <= 0) {
        return leftRotate(root);
    }
    
    if (balance < -1 && getBalanceFactor(root->getRight()) > 0) {
        root->setRight(rightRotate(root->getRight()));
        return leftRotate(root);
    }
    
    return root;
}

Node* AVLTree::findNode(Node* root, int rollNo) {
    if (root == nullptr) {
        return nullptr;
    }
    
    if (rollNo == root->getRollNo()) {
        return root;
    }
    
    if (isRollNoKey) {
        if (rollNo < root->getRollNo()) {
            return findNode(root->getLeft(), rollNo);
        } else {
            return findNode(root->getRight(), rollNo);
        }
    } else {
        Node* leftResult = findNode(root->getLeft(), rollNo);
        if (leftResult != nullptr) {
            return leftResult;
        }
        
        return findNode(root->getRight(), rollNo);
    }
}

Node* AVLTree::findNodeByCGPA(Node* root, float cgpa) {
    if (root == nullptr) {
        return nullptr;
    }
    
    if (cgpa == root->getCGPA()) {
        return root;
    }
    
    if (!isRollNoKey) {
        if (cgpa < root->getCGPA()) {
            return findNodeByCGPA(root->getLeft(), cgpa);
        } else {
            return findNodeByCGPA(root->getRight(), cgpa);
        }
    } else {
        Node* leftResult = findNodeByCGPA(root->getLeft(), cgpa);
        if (leftResult != nullptr) {
            return leftResult;
        }
        
        return findNodeByCGPA(root->getRight(), cgpa);
    }
}

void AVLTree::insert(int rollNo, const string& name, float cgpa, const vector<CourseInfo>& courses) {
    root = insertNode(root, rollNo, name, cgpa, courses);
}

bool AVLTree::remove(int rollNo) {
    if (findNode(root, rollNo) == nullptr) {
        return false;
    }
    
    root = deleteNode(root, rollNo);
    return true;
}

Node* AVLTree::search(int rollNo) {
    return findNode(root, rollNo);
}

Node* AVLTree::searchByCGPA(float cgpa) {
    return findNodeByCGPA(root, cgpa);
}

bool AVLTree::updateCGPA(int rollNo, float newCGPA) {
    Node* student = findNode(root, rollNo);
    if (student == nullptr) {
        return false; 
    }
    
    if (!isRollNoKey) {
        vector<CourseInfo> courses = student->getCourses();
        string name = student->getName();
        
        remove(rollNo);
        
        insert(rollNo, name, newCGPA, courses);
    } else {
        student->setCGPA(newCGPA);
    }
    
    return true;
}
bool AVLTree::addCourse(int rollNo, const string& courseCode, float marks) {
    Node* student = findNode(root, rollNo);
    if (student == nullptr) {
        return false; 
    }
    
    return student->addCourse(courseCode, marks);
}

bool AVLTree::updateCourseMarks(int rollNo, const string& courseCode, float newMarks) {
    Node* student = findNode(root, rollNo);
    if (student == nullptr) {
        return false; 
    }
    
    return student->updateCourseMarks(courseCode, newMarks);
}

bool AVLTree::removeCourse(int rollNo, const string& courseCode) {
    Node* student = findNode(root, rollNo);
    if (student == nullptr) {
        return false; 
    }
    
    return student->removeCourse(courseCode);
}

void AVLTree::inOrderTraversal(Node* node) {
    if (node != nullptr) {
        inOrderTraversal(node->getLeft());
        
        cout << "Roll No: " << node->getRollNo() << ", Name: " << node->getName()
                  << ", CGPA: " << node->getCGPA() << ", Courses: " << node->getNumCourses() << endl;
        

        for (const auto& course : node->getCourses()) {
            cout << "  Course: " << course.getCourseCode() << ", Marks: " << course.getMarks() << endl;
        }
        
        inOrderTraversal(node->getRight());
    }
}

void AVLTree::displayAll() {
    cout << "Student Records:" << endl;
    inOrderTraversal(root);
    cout << endl;
}

void AVLTree::printStudentsInRollNoRange(Node* node, int minRoll, int maxRoll) {
    if (node == nullptr) {
        return;
    }
    
    if (minRoll < node->getRollNo()) {
        printStudentsInRollNoRange(node->getLeft(), minRoll, maxRoll);
    }
    
    if (minRoll <= node->getRollNo() && node->getRollNo() <= maxRoll) {
        cout << "Roll No: " << node->getRollNo() << ", Name: " << node->getName()
                  << ", CGPA: " << node->getCGPA() << ", Courses: " << node->getNumCourses() << endl;

        for (const auto& course : node->getCourses()) {
            cout << "  Course: " << course.getCourseCode() << ", Marks: " << course.getMarks() << endl;
        }
    }
    
    if (maxRoll > node->getRollNo()) {
        printStudentsInRollNoRange(node->getRight(), minRoll, maxRoll);
    }
}
void AVLTree::printStudentsInCGPARange(Node* node, float minCGPA, float maxCGPA) {
    if (node == nullptr) {
        return;
    }
    printStudentsInCGPARange(node->getLeft(), minCGPA, maxCGPA);
    
    if (minCGPA <= node->getCGPA() && node->getCGPA() <= maxCGPA) {
        cout << "Roll No: " << node->getRollNo() << ", Name: " << node->getName()
                  << ", CGPA: " << node->getCGPA() << ", Courses: " << node->getNumCourses() << endl;
        
        for (const auto& course : node->getCourses()) {
            cout << "  Course: " << course.getCourseCode() << ", Marks: " << course.getMarks() << endl;
        }
    }
    
    printStudentsInCGPARange(node->getRight(), minCGPA, maxCGPA);
}

void AVLTree::printStudentsAboveRollNo(Node* node, int rollNo) {
    if (node == nullptr) {
        return;
    }
    
    if (node->getRollNo() > rollNo) {
        cout << "Roll No: " << node->getRollNo() << ", Name: " << node->getName()
                  << ", CGPA: " << node->getCGPA() << ", Courses: " << node->getNumCourses() << endl;
        
        for (const auto& course : node->getCourses()) {
            cout << "  Course: " << course.getCourseCode() << ", Marks: " << course.getMarks() << endl;
        }
        
        printStudentsAboveRollNo(node->getLeft(), rollNo);
    }
    
    printStudentsAboveRollNo(node->getRight(), rollNo);
}

void AVLTree::printStudentsBelowRollNo(Node* node, int rollNo) {
    if (node == nullptr) {
        return;
    }
    
    printStudentsBelowRollNo(node->getLeft(), rollNo);
    
    if (node->getRollNo() < rollNo) {
        cout << "Roll No: " << node->getRollNo() << ", Name: " << node->getName()
                  << ", CGPA: " << node->getCGPA() << ", Courses: " << node->getNumCourses() << endl;
        
        for (const auto& course : node->getCourses()) {
            cout << "  Course: " << course.getCourseCode() << ", Marks: " << course.getMarks() << endl;
        }
        
        printStudentsBelowRollNo(node->getRight(), rollNo);
    }
}

void AVLTree::printStudentsAboveCGPA(Node* node, float cgpa) {
    if (node == nullptr) {
        return;
    }
    
    printStudentsAboveCGPA(node->getLeft(), cgpa);
    
    if (node->getCGPA() > cgpa) {
        cout << "Roll No: " << node->getRollNo() << ", Name: " << node->getName()
                  << ", CGPA: " << node->getCGPA() << ", Courses: " << node->getNumCourses() << endl;
        
        for (const auto& course : node->getCourses()) {
            cout << "  Course: " << course.getCourseCode() << ", Marks: " << course.getMarks() << endl;
        }
    }
    
    printStudentsAboveCGPA(node->getRight(), cgpa);
}

void AVLTree::printStudentsBelowCGPA(Node* node, float cgpa) {
    if (node == nullptr) {
        return;
    }
    
    printStudentsBelowCGPA(node->getLeft(), cgpa);
    
    if (node->getCGPA() < cgpa) {
        cout << "Roll No: " << node->getRollNo() << ", Name: " << node->getName()
                  << ", CGPA: " << node->getCGPA() << ", Courses: " << node->getNumCourses() << endl;
        
        for (const auto& course : node->getCourses()) {
            cout << "  Course: " << course.getCourseCode() << ", Marks: " << course.getMarks() << endl;
        }
    }
    
    printStudentsBelowCGPA(node->getRight(), cgpa);
}

void AVLTree::displayStudentsInRollNoRange(int minRoll, int maxRoll) {
    cout << "Students with Roll No between " << minRoll << " and " << maxRoll << ":" << endl;
    printStudentsInRollNoRange(root, minRoll, maxRoll);
    cout << endl;
}

void AVLTree::displayStudentsInCGPARange(float minCGPA, float maxCGPA) {
    cout << "Students with CGPA between " << minCGPA << " and " << maxCGPA << ":" << endl;
    printStudentsInCGPARange(root, minCGPA, maxCGPA);
    cout << endl;
}

void AVLTree::displayStudentsAboveRollNo(int rollNo) {
    cout << "Students with Roll No greater than " << rollNo << ":" << endl;
    printStudentsAboveRollNo(root, rollNo);
    cout << endl;
}

void AVLTree::displayStudentsBelowRollNo(int rollNo) {
    cout << "Students with Roll No less than " << rollNo << ":" << endl;
    printStudentsBelowRollNo(root, rollNo);
    cout << endl;
}

void AVLTree::displayStudentsAboveCGPA(float cgpa) {
    cout << "Students with CGPA greater than " << cgpa << ":" << endl;
    printStudentsAboveCGPA(root, cgpa);
    cout << endl;
}

void AVLTree::displayStudentsBelowCGPA(float cgpa) {
    cout << "Students with CGPA less than " << cgpa << ":" << endl;
    printStudentsBelowCGPA(root, cgpa);
    cout << endl;
}
Node* AVLTree::getRoot() const {
    return root;
}

bool AVLTree::getIsRollNoKey() const {
    return isRollNoKey;
} 
