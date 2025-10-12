#pragma once
#include "Student.h"
#include <string>
#include <vector>

using std::vector;

//input
Student getUserStudentInput();
int getUserMenuChoice();
void getModeChoice(std::string& mode);

// formatting
std::string createHeader(std::string mode);
std::string formatStudentRow(const Student& student, std::string mode);
void printStudents(StudentContainer& students, std::string mode);


// files
int  checkFileAvailability(std::string file);
void generateRandomStudentFile(std::string fileName, int numOfLines);
void loadStudentsFromFile(StudentContainer& students, std::string fileName);
void createStudentFile(StudentContainer& studentList, std::string fileName);

// parsing
void stripWhiteSpace(std::string& s, std::vector<std::string>& result);
Student processStudentRow(std::vector<std::string> studentRow);