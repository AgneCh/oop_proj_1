#pragma once
#include <string>
#include <vector>
#include <list>

using std::string;
using std::vector;
using std::list;

struct Student
{
    string firstName;
    string lastName;
    vector<int> grades;
    int exam;
    double finalGradeMean;
    double finalGradeMedian;
};

#ifdef USE_LIST
using StudentContainer = list<Student>;
inline const char* getContainerName() {
    return "std::list<Student>";
}
#else
using StudentContainer = vector<Student>;
inline const char* getContainerName() {
    return "std::vector<Student>";
}
#endif