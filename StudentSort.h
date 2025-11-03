#pragma once
#include "Student.h"
#include <vector>
#include <string>
#include <string_view>
#include <algorithm>

std::string_view getNameLetters(const std::string &s);
int getNameNumber(const string &s);
bool compareStudentNames(const Student &a, const Student &b);
bool compareStudentGrades(const Student &a, const Student &b);
void categorizeStudents_1(StudentContainer &allStudents,
                          StudentContainer &belowFive,
                          StudentContainer &fiveAndUp);
void categorizeStudents_2(StudentContainer &allStudents,
                          StudentContainer &belowFive,
                          StudentContainer &fiveAndUp);
void categorizeStudents_3(StudentContainer &allStudents,
                          StudentContainer &belowFive,
                          StudentContainer &fiveAndUp);