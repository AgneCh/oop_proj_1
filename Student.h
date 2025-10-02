#pragma once
#include <string>
#include <vector>

using std::string;
using std::vector;

struct Student
{
    string firstName;
    string lastName;
    vector<int> grades;
    int exam;
    double finalGradeMean;
    double finalGradeMedian;
};