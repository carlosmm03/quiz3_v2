#include "Query.h"
#include "Student.h"
#include "Subject.h"
#include "Grade.h"
#include "Department.h"
#include "Coordination.h"
#include "Deanship.h"

#include <iostream>
#include <algorithm>
#include <set>
#include <tuple>

using std::string;
using std::vector;
using std::tuple;
using std::make_tuple;


Student GetStudent(string studentIdStr) {
    const auto& table = Student::table();
    auto it = std::find_if(table.begin(), table.end(),
        [&](const Student& s){ return s.id().str() == studentIdStr; });
    
    if (it != table.end()) return *it;
    return Student("00-00000", "Unknown", "0000");
}

Subject GetSubject(string codeStr) {
    const auto& table = Subject::table();
    auto it = std::find_if(table.begin(), table.end(),
        [&](Subject s){ return s.code().str() == codeStr; });
    
    if (it != table.end()) return *it;
    return Subject("0000", "0000", "Unknown", 0);
}

float Query::q0() {
    float totalGradeSum = 0.0f;
    int count = 0;
    const auto& grades = Grade::table();

    for (const auto& g : grades) {
        if (g.year() == 2044) {
            Student student = GetStudent(g.studentId().str());
            
            if (student.majorCode().str() == "0600") {
                totalGradeSum += g.score();
                count++;
            }
        }
    }
    return (count > 0) ? (totalGradeSum / count) : 0.0f;
}


int Query::q1() {
    int count = 0;
    std::set<string> processedIds;
    const auto& grades = Grade::table();

    for (const auto& g : grades) {
        if (g.year() == 2050) {
            string studentId = g.studentId().str();
            
            if (processedIds.count(studentId)) continue;

            Student student = GetStudent(studentId);
            string majorCode = student.majorCode().str();
            
            bool isTargetMajor = (majorCode == "0800" || majorCode == "0600");

            if (student.isGraduate() && isTargetMajor) {
                count++;
                processedIds.insert(studentId);
            }
        }
    }
    return count;
}

vector<Subject> Query::q2() {
    vector<Subject> result;
    
    string compSciDeptId = "";
    const auto& departments = Department::table();
    
    for (auto d : departments) {
        if (d.description().str().find("Computacion") != string::npos) {
            compSciDeptId = d.key().str();
            break;
        }
    }

    if (!compSciDeptId.empty()) {
        const auto& subjects = Subject::table();
        for (auto s : subjects) {
            if (s.departmentCode().str() == compSciDeptId) {
                result.push_back(s);
            }
        }
    }
    
    return result;
}


vector<Student> Query::q3() {
    vector<Student> result;
    const auto& students = Student::table();
    const auto& grades = Grade::table();

    for (const auto& student : students) {
        if (!student.isActive()) continue;

        bool tookMath7 = false;
        bool passedPhysics1 = false;

        for (const auto& grade : grades) {
            if (grade.studentId().str() == student.id().str()) {
                
                Subject subject = GetSubject(grade.subjectCode().str());
                string subjectName = subject.description().str();

                if (subjectName == "Matematicas VII") {
                    tookMath7 = true;
                }
                
                if (subjectName == "Fisica I" && grade.score() >= 4) {
                    passedPhysics1 = true;
                }
            }
        }

        if (tookMath7 && passedPhysics1) {
            result.push_back(student);
        }
    }
    return result;
}


vector<tuple<string, int>> Query::q4() {
    vector<tuple<string, int>> result;
    const auto& students = Student::table();
    const auto& grades = Grade::table();

    for (const auto& student : students) {
        if (student.majorCode().str() != "0600" || !student.isActive()) continue;

        bool tookMath4 = false;
        int accumulatedCredits = 0;

        for (const auto& grade : grades) {
            if (grade.studentId().str() == student.id().str()) {
                
                Subject subject = GetSubject(grade.subjectCode().str());
                string subjectName = subject.description().str();

                if (subjectName == "Matematicas IV") {
                    tookMath4 = true;
                }

                if (grade.year() <= 2046 && grade.score() >= 10) {
                    accumulatedCredits += subject.credits();
                }
            }
        }

        if (tookMath4) {
            result.push_back(make_tuple(student.id().str(), accumulatedCredits));
        }
    }
    return result;
}
