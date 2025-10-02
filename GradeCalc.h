#pragma once
#include "Student.h"
#include <vector>

int getRandomGrade();
double hwMean(const std::vector<int>& grades);
double hwMedian(std::vector<int> grades); 
Student calcFinalGrade(Student student);
