#pragma once
#include "Student.h"
#include <vector>

bool compareStudentCharacters(Student a, Student b);
bool compareStudentNumbers(Student a, Student b);
bool compareStudentGrades(const Student &a, const Student &b);
void categorizeStudents(StudentContainer &allStudents,
                        StudentContainer &belowFive,
                        StudentContainer &fiveAndUp);