#pragma once
#include "Student.h"
#include <vector>
#include <string>
#include <string_view>

std::string_view getNameLetters(const std::string& s);
int getNameNumber(const string& s);
bool compareStudentNames(const Student& a, const Student& b);
bool compareStudentGrades(const Student &a, const Student &b);
void categorizeStudents(StudentContainer &allStudents,
                        StudentContainer &belowFive,
                        StudentContainer &fiveAndUp);