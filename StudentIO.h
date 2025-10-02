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
void printStudents(std::vector<Student>& students, std::string mode);


// files
int  checkFileAvailability(std::string file);
void generateRandomStudentFile(std::string fileName, int numOfLines);
void loadStudentsFromFile(vector<Student>& students, std::string fileName);
void createStudentFile(std::vector<Student>& studentList, std::string fileName);

// parsing
void stripWhiteSpace(std::string& s, std::vector<std::string>& result);
Student processStudentRow(std::vector<std::string> studentRow);