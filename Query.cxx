#include "Query.h"
#include "Database.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <iomanip>
#include <set>
#include <map>

using namespace std;

// --- Helper Functions ---

Student GetStudent(const string& studentId) {
    auto it = find_if(students.begin(), students.end(), 
        [&](const Student& s) { return s.studentId == studentId; });
    if (it != students.end()) return *it;
    return Student();
}

Subject GetSubject(const string& code) {
    auto it = find_if(subjects.begin(), subjects.end(), 
        [&](const Subject& s) { return s.code == code; });
    if (it != subjects.end()) return *it;
    return Subject();
}

// ---------------------------------------------------------
// QUERY 0
// ---------------------------------------------------------
int Query::q0() {
    cout << "=== Query 0: Average Elec. Eng. (2044) ===" << endl;
    
    float totalGrade = 0.0f;
    int count = 0;

    for (const auto& r : records) {
        if (r.year == 2044) {
            Student s = GetStudent(r.studentId);
            if (s.major == "Ingenieria Electronica") {
                totalGrade += r.grade;
                count++;
            }
        }
    }

    float average = (count > 0) ? (totalGrade / count) : 0.0f;

    cout << "Average: " << average << endl;
    cout << "-------------------------------------------------" << endl;

    return EXIT_SUCCESS;
}

// ---------------------------------------------------------
// QUERY 1
// ---------------------------------------------------------
int Query::q1() {
    cout << "=== Query 1: Comp/Elec Graduates (2050) ===" << endl;

    int graduateCount = 0;
    set<string> processedStudentIds;

    for (const auto& r : records) {
        if (r.year == 2050) {
            if (processedStudentIds.find(r.studentId) == processedStudentIds.end()) {
                Student s = GetStudent(r.studentId);
                bool majorOk = (s.major == "Computacion" || s.major == "Ingenieria Electronica");
                
                if (s.status == "Graduado" && majorOk) {
                    graduateCount++;
                    processedStudentIds.insert(r.studentId);
                }
            }
        }
    }

    cout << "Graduate Count: " << graduateCount << endl;
    cout << "-------------------------------------------" << endl;

    return EXIT_SUCCESS;
}

// ---------------------------------------------------------
// QUERY 2
// ---------------------------------------------------------
int Query::q2() {
    cout << "=== Query 2: Computer Science Subjects ===" << endl;
    cout << left << setw(10) << "CODE" << setw(30) << "NAME" << setw(5) << "CREDITS" << endl;

    for (const auto& s : subjects) {
        if (s.department == "Computacion") {
            cout << left << setw(10) << s.code 
                 << setw(30) << s.name 
                 << setw(5) << s.credits << endl;
        }
    }
    cout << "----------------------------------------------" << endl;
    return EXIT_SUCCESS;
}

// ---------------------------------------------------------
// QUERY 3
// ---------------------------------------------------------
int Query::q3() {
    cout << "=== Query 3: Active Students (Math VII + Passed Physics I) ===" << endl;
    cout << left << setw(15) << "STUDENT_ID" << setw(30) << "MAJOR" << endl;

    for (const auto& s : students) {
        if (s.status != "Activo") continue;

        bool tookMath7 = false;
        bool passedPhysics1 = false;

        for (const auto& r : records) {
            if (r.studentId == s.studentId) {
                Subject subj = GetSubject(r.subjectCode);
                
                if (subj.name == "Matematicas VII") tookMath7 = true;
                
                if (subj.name == "Fisica I" && r.grade >= 4.0) passedPhysics1 = true;
            }
        }

        if (tookMath7 && passedPhysics1) {
            cout << left << setw(15) << s.studentId << setw(30) << s.major << endl;
        }
    }
    cout << "----------------------------------------------------------" << endl;
    return EXIT_SUCCESS;
}

// ---------------------------------------------------------
// QUERY 4
// ---------------------------------------------------------
int Query::q4() {
    cout << "=== Query 4: Approved Credits (Elec. Eng. up to 2046) ===" << endl;
    cout << left << setw(15) << "STUDENT_ID" << setw(10) << "TOTAL CREDITS" << endl;

    for (const auto& s : students) {
        if (s.major != "Ingenieria Electronica" || s.status != "Activo") continue;

        bool tookMath4 = false;
        int totalCredits = 0;

        for (const auto& r : records) {
            if (r.studentId == s.studentId) {
                Subject subj = GetSubject(r.subjectCode);
                
                if (subj.name == "Matematicas IV") {
                    tookMath4 = true;
                }

                if (r.year <= 2046 && r.grade >= 10.0) { 
                    totalCredits += subj.credits;
                }
            }
        }

        if (tookMath4) {
            cout << left << setw(15) << s.studentId << setw(10) << totalCredits << endl;
        }
    }
    cout << "----------------------------------------------------" << endl;
    return EXIT_SUCCESS;
}