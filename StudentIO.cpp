#include "StudentIO.h"
#include "GradeCalc.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <fstream>
#include <cassert>
#include <cctype>
#include <iterator>
#include <sstream> 

using std::cin;
using std::count;
using std::cout;
using std::endl;
using std::fixed;
using std::ifstream;
using std::invalid_argument;
using std::isdigit;
using std::isspace;
using std::isspace;
using std::left;
using std::move;
using std::numeric_limits;
using std::ofstream;
using std::ostringstream;
using std::setfill;
using std::setprecision;
using std::setw;
using std::sort;
using std::stod;
using std::stof;
using std::stoi;
using std::streamsize;
using std::string;
using std::to_string;
using std::istreambuf_iterator;
using std::vector;

string createHeader(string mode)
{
    ostringstream header;
    const int wLastName = 15;
    const int wFirsName = 15;
    const int wGrade = 20;

    if (mode == "m")
    {
        // -- header --
        header << left
               << setw(wFirsName) << "Name"
               << setw(wLastName) << "Last name"
               << setw(wGrade) << "Final grade (mean)" << '\n';
        // -- separator line --
        header << setfill('-')
               << setw(wFirsName) << ""
               << setw(wLastName) << ""
               << setw(wGrade) << "" << '\n'
               << setfill(' ');
    }
    else if (mode == "md")
    {
        // -- header --
        header << left
               << setw(wFirsName) << "Name"
               << setw(wLastName) << "Last name"
               << setw(wGrade) << "Final grade (median)" << '\n';

        // -- separator line --
        header << setfill('-')
               << setw(wFirsName) << ""
               << setw(wLastName) << ""
               << setw(wGrade) << "" << '\n'
               << setfill(' ');
    }
    else
    {
        // -- header --
        header << left
               << setw(wFirsName) << "Name"
               << setw(wLastName) << "Last name"
               << setw(wGrade) << "Final grade (mean)"
               << setw(wGrade) << "Final grade (median)" << '\n';

        // -- separator line --
        header << setfill('-')
               << setw(wFirsName) << ""
               << setw(wLastName) << ""
               << setw(wGrade) << ""
               << setw(wGrade) << "" << '\n'
               << setfill(' ');
    }
    return header.str();
}

string formatStudentRow(const Student &student, string mode)
{
    ostringstream studentRow;
    const int wLastName = 15;
    const int wFirsName = 15;
    const int wGrade = 20;

    if (mode == "m")
    {

        // -- student data --
        studentRow << left
                   << setw(wFirsName) << student.firstName
                   << setw(wLastName) << student.lastName
                   << fixed << setprecision(2)
                   << setw(wGrade) << student.finalGradeMean << '\n';
    }
    else if (mode == "md")
    {

        // -- student data --
        studentRow << left
                   << setw(wFirsName) << student.firstName
                   << setw(wLastName) << student.lastName
                   << fixed << setprecision(2)
                   << setw(wGrade) << student.finalGradeMedian << '\n';
    }
    else
    {

        // -- student data --
        studentRow << left
                   << setw(wFirsName) << student.firstName
                   << setw(wLastName) << student.lastName
                   << fixed << setprecision(2)
                   << setw(wGrade) << student.finalGradeMean
                   << setw(wGrade) << student.finalGradeMedian << '\n';
    }

    return studentRow.str();
}

void printStudents(StudentContainer& students, string mode){

    cout << createHeader(mode);
    for (auto& student : students)
    {
        cout << formatStudentRow(student, mode);
    }
}

Student getUserStudentInput()
{
    Student student;
    string grade;
    double temp_grade;
    string stopWord = "stop";
    string randomWord = "r";
    string userInput;

    cout << "Input student data." << endl;
    cout << "First name: ";
    cin >> student.firstName;
    cout << "Last name: ";
    cin >> student.lastName;

    while (true)
    {
        cout << "" << endl;
        cout << "Enter " << student.firstName << " " << student.lastName << " homework grade (1-10) manually, type 'r' to generated random grade or type 'stop': ";
        cin >> userInput;
        if (userInput == stopWord)
        {
            break;
        }

        if (userInput == randomWord)
        {
            temp_grade = getRandomGrade();
            cout << "Random grade is: " << temp_grade << endl;
        }
        else
        {
            // check if input contains a digit
            size_t parsed = 0;
            try
            {
                temp_grade = stoi(userInput, &parsed);
                if (parsed != userInput.size())
                {
                    cout << "Invalid input!" << endl;
                    continue;
                }
            }
            catch (invalid_argument err)
            {
                cout << "Invalid input!" << endl;
                continue;
            }
        }

        // check if grade is 1-10
        if (temp_grade >= 1 && temp_grade <= 10)
        {
            student.grades.push_back(temp_grade);
        }
        else
        {
            cout << "Grade must be between 1 and 10." << endl;
        }
    }

    while (true)
    {
        cout << "" << endl;
        cout << "Input exam grade manually, or write 'r' to generated random grade: ";
        cin >> userInput;

        if (userInput == randomWord)
        {
            temp_grade = getRandomGrade();
            cout << "Random exam grade is: " << temp_grade << endl;
        }
        else
        {
            size_t parsed = 0;
            try
            {

                temp_grade = stoi(userInput, &parsed);
                if (parsed != userInput.size())
                {
                    cout << "Invalid input!" << endl;
                    continue;
                }
            }
            catch (invalid_argument err)
            {
                cout << "Invalid input!" << endl;
                continue;
            }
        }
        if (temp_grade >= 1 && temp_grade <= 10)
        {
            student.exam = temp_grade;
            break;
        }
        else
        {
            cout << "Grade must be between 1 and 10." << endl;
        }
    }

    return student;
}

int getUserMenuChoice()
{
    int n;

    while (true)
    {
        cout << "" << endl;
        cout << "Choose a number from the menu:" << endl;
        cout << "1. Add new student" << endl;
        cout << "2. Calculate grades" << endl;
        cout << "3. Insert student data from a file" << endl;
        cout << "4. Generate random student file" << endl;
        cout << "5. Sort student data into categories" << endl;
        cout << "6. Exit" << endl;
        cout << "" << endl;
        cin >> n;
        if (n == 1 || n == 2 || n == 3 || n == 4 || n == 5 || n == 6)
        {
            return n;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid menu number!" << endl;
    }
}

void getModeChoice(string &mode)
{
    cout << "" << endl;
    cout << "Would you like to view the calculated final grade with:" << endl;
    cout << "m = mean" << endl;
    cout << "md = median" << endl;
    cout << "b = both" << endl;
    cout << "" << endl;

    while (true)
    {
        cin >> mode;
        if (mode != "m" && mode != "md" && mode != "b")
        {
            cout << "You must input valid value!" << endl;
            continue;
        }
        break;
    }
}

int checkFileAvailability(string file)
{
    string fileText;
    ifstream f(file);

    if (!f.is_open())
    {
        cout << "Error opening the file!" << endl;
        return 1;
    }

    f.close();
    return 0;
}

void stripWhiteSpace(string &line, vector<string> &result)
{
    result.clear();
    #ifndef USE_LIST
    result.reserve(8);
    #endif

    const size_t len = line.size();
    size_t currPosition = 0;

    while (currPosition < len)
    {
        while (currPosition < len && isspace(static_cast<unsigned char>(line[currPosition])))
            ++currPosition;
        if (currPosition >= len)
            break;

        size_t start = currPosition;
        while (currPosition < len && !isspace(static_cast<unsigned char>(line[currPosition])))
            ++currPosition;
        result.emplace_back(line, start, currPosition - start);
    }
}

Student processStudentRow(vector<string> studentRow)
{

    assert(!(studentRow.size() == 0));

    Student student;
    string firstname = studentRow[0];
    string lastname = studentRow[1];

    student.firstName = firstname;
    student.lastName = lastname;

    for (int i = 2; i < studentRow.size(); i++)
    {
        double tempGrade = stoi(studentRow[i]);
        if (i == studentRow.size() - 1)
        {
            student.exam = tempGrade;
        }
        else
        {

            student.grades.push_back(tempGrade);
        }
    }

    return student;
}

void generateRandomStudentFile(string fileName, int numOfLines)
{
    ofstream f(fileName);
    if (!f.is_open())
    {
        cout << "Error creating file!" << fileName << endl;
        return;
    }

    // create header
    f << left << setw(15) << "Name" << setw(15) << "Surname";
    for (int i = 0; i < 5; ++i)
        f << setw(5) << "HM" + to_string(i + 1);
    f << setw(5) << "Exam" << '\n';

    for (int i = 0; i < numOfLines; ++i)
    {
        f << left << setw(15) << "Name" + to_string(i + 1)
          << setw(15) << "Surname" + to_string(i + 1);

        for (int j = 0; j < 5; ++j)
        {
            f << setw(5) << getRandomGrade();
        }
        f << setw(5) << getRandomGrade() << '\n';
    }

    f.close();
    cout << endl;
    cout << "File " << fileName << " is successfully created." << '\n';
}

void loadStudentsFromFile(StudentContainer& students, std::string fileName)
{
    ifstream file(fileName);

    size_t numOfLines = count(istreambuf_iterator<char>(file), istreambuf_iterator<char>(), '\n');

    file.clear();
    file.seekg(0);

    string curLine;
    getline(file, curLine); // skip header
    if (numOfLines > 0)
        --numOfLines;
    #ifndef USE_LIST
    students.reserve(numOfLines);
    #endif

    vector<string> row;

    while (getline(file, curLine))
    {
        if (curLine.empty())
        {
            continue;
        }

        stripWhiteSpace(curLine, row);
        Student student = processStudentRow(row);
        students.push_back(move(student));
    }
}

void createStudentFile(StudentContainer& studentList, string fileName)
{
    ofstream f(fileName);
    if (!f.is_open())
    {
        cout << "Error creating file!" << fileName << "\n";
        return;
    }

    f << createHeader("m");
    for (auto& student : studentList)
    {
        f << formatStudentRow(student, "m");
    }
    f.close();
    cout << "\n";
    cout << "File " << fileName << " is successfully created." << "\n";
}