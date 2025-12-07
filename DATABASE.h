#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>
#include <iostream>

// --- Struct Definitions ---

struct Student {
    std::string studentId;
    std::string major;
    std::string status;
    
    void print() const {
        std::cout << "Student: " << studentId << " (" << major << ") - " << status << std::endl;
    }
};

struct Subject {
    std::string code;
    std::string name;
    std::string department;
    int credits;
};

struct Record {
    std::string studentId;
    std::string subjectCode;
    int year;
    float grade;
};

// --- Global "Table" Declarations ---

extern std::vector<Student> students;
extern std::vector<Subject> subjects;
extern std::vector<Record> records; 

#endif // DATABASE_H