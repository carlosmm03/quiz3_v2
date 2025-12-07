#pragma once

#include <vector>
#include <tuple>
#include <string>

#include "Subject.h"
#include "Student.h"

struct Query {
    static float q0();

    static int q1();

    static std::vector<Subject> q2();

    static std::vector<Student> q3();

    static std::vector<std::tuple<std::string, int>> q4();
};
