#pragma once
#include "Student.h"
#include <vector>

bool compareStudentCharacters(Student a, Student b);
bool compareStudentNumbers(Student a, Student b);
void categorizeStudents(std::vector<Student> &allStudents,
                        std::vector<Student> &belowFive,
                        std::vector<Student> &fiveAndUp);