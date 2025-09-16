#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <random>
#include <fstream>
#include <sstream>
#include <assert.h>

// using namespace std;
using std::cin;
using std::cout;
using std::endl;
using std::fixed;
using std::ifstream;
using std::invalid_argument;
using std::istringstream;
using std::left;
using std::mt19937;
using std::numeric_limits;
using std::random_device;
using std::setfill;
using std::setprecision;
using std::setw;
using std::sort;
using std::stod;
using std::stof;
using std::streamsize;
using std::string;
using std::uniform_int_distribution;
using std::vector;

struct Student
{
    string firstName;
    string lastName;
    vector<double> grades;
    double exam;
    double finalGradeMean;
    double finalGradeMedian;
};

void printHeader(const int wLastName, const int wFirsName, const int wGrade, string mode)
{
    if (mode == "m")
    {
        // -- header --
        cout << left
             << setw(wFirsName) << "Name"
             << setw(wLastName) << "Last name"
             << setw(wGrade) << "Final grade (mean)" << endl;

        // -- separator line --
        cout << setfill('-')
             << setw(wFirsName) << ""
             << setw(wLastName) << ""
             << setw(wGrade) << "" << endl
             << setfill(' ');
    }
    else if (mode == "md")
    {
        // -- header --
        cout << left
             << setw(wFirsName) << "Name"
             << setw(wLastName) << "Last name"
             << setw(wGrade) << "Final grade (median)" << endl;

        // -- separator line --
        cout << setfill('-')
             << setw(wFirsName) << ""
             << setw(wLastName) << ""
             << setw(wGrade) << "" << endl
             << setfill(' ');
    }
    else
    {
        // -- header --
        cout << left
             << setw(wFirsName) << "Name"
             << setw(wLastName) << "Last name"
             << setw(wGrade) << "Final grade (mean)"
             << setw(wGrade) << "Final grade (median)" << endl;

        // -- separator line --
        cout << setfill('-')
             << setw(wFirsName) << ""
             << setw(wLastName) << ""
             << setw(wGrade) << ""
             << setw(wGrade) << "" << endl
             << setfill(' ');
    }
}

void printStudents(vector<Student> &students, string mode)
{
    const int wLastName = 15;
    const int wFirsName = 15;
    const int wGrade = 20;
    Student student;

    printHeader(wLastName, wFirsName, wGrade, mode);
    for (int i = 0; i < students.size(); i++)
    {
        student = students[i];
        if (mode == "m")
        {

            // -- student data --
            cout << left
                 << setw(wFirsName) << student.firstName
                 << setw(wLastName) << student.lastName
                 << fixed << setprecision(2)
                 << setw(wGrade) << student.finalGradeMean << endl;
        }
        else if (mode == "md")
        {

            // -- student data --
            cout << left
                 << setw(wFirsName) << student.firstName
                 << setw(wLastName) << student.lastName
                 << fixed << setprecision(2)
                 << setw(wGrade) << student.finalGradeMedian << endl;
        }
        else
        {

            // -- student data --
            cout << left
                 << setw(wFirsName) << student.firstName
                 << setw(wLastName) << student.lastName
                 << fixed << setprecision(2)
                 << setw(wGrade) << student.finalGradeMean
                 << setw(wGrade) << student.finalGradeMedian << endl;
        }
    }
}

int getRandomGrade()
{
    static mt19937 gen(random_device{}()); // seed once
    static uniform_int_distribution<int> dist(1, 10);
    return dist(gen);
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
            // check if input contains number
            try
            {
                temp_grade = stof(userInput); // TODO: allows inputs like 2k5 -> rezult: 2
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
        temp_grade = stof(userInput);
    }
    student.exam = temp_grade;

    return student;
}

double hwMean(vector<double> grades)
{
    if (grades.empty())
    {
        return 0.0;
    }

    double sum = 0.0;
    for (double i : grades)
        sum += i;
    return sum / grades.size();
}

double hwMedian(vector<double> grades)
{
    if (grades.empty())
    {
        return 0.0;
    }

    sort(grades.begin(), grades.end());
    int n = grades.size();
    if (n % 2 != 0)
    {
        return grades[n / 2];
    }
    else
    {
        return (grades[(n - 1) / 2] + grades[n / 2]) / 2.0;
    }
}

Student calcFinalGrade(Student student)
{
    double mean = hwMean(student.grades);
    double median = hwMedian(student.grades);

    student.finalGradeMean = 0.4 * mean + 0.6 * student.exam;
    student.finalGradeMedian = 0.4 * median + 0.6 * student.exam;

    return student;
}

int getUserMenuChoice()
{
    int n;

    while (true)
    {
        // TODO: user selects 2 without student data input
        cout << "" << endl;
        cout << "Choose number from the menu:" << endl;
        cout << "1. Add new student" << endl;
        cout << "2. Calculate grades" << endl;
        cout << "3. Insert student data from a file" << endl;
        cout << "" << endl;
        cin >> n;
        if (n == 1 || n == 2 || n == 3)
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

vector<string> stripWhiteSpace(string &s)
{
    vector<string> result;
    string tempStr;
    for (int i = 0; i < s.size(); i++)
    {
        char currentChar = s[i];

        if (currentChar != ' ')
        {
            tempStr = tempStr + s[i];

            // make sure to push the last character
            if (i == s.size() - 1)
            {
                result.push_back(tempStr);
            }
        }
        else
        {
            if (tempStr == "")
            {
                continue;
            }
            result.push_back(tempStr);
            tempStr = "";
        }
    }

    return result;
}

Student processStudentRow(vector<string> studentRow)
{

    assert(!(studentRow.size() == 0));

    Student student;
    string firstname = studentRow[0];
    string lastname = studentRow[1];

    cout << "f: " << firstname << endl;
    student.firstName = firstname;
    student.lastName = lastname;

    for (int i = 2; i < studentRow.size(); i++)
    {
        double tempGrade = stod(studentRow[i]);
        if (i == studentRow.size() - 1)
        {
            student.exam = tempGrade;
        }
        else
        {

            student.grades.push_back(tempGrade);
        }
    }
    // cout << "Student data is uploaded to the system." << endl;
    return student;
}

bool compareLastname(Student a, Student b)
{
    return a.firstName < b.firstName;
}

int main()
{
    string mode;
    vector<Student> students;

    while (true)
    {
        int menuChoice = getUserMenuChoice();
        if (menuChoice == 1)
        {
            students.push_back(getUserStudentInput());
        }
        else if (menuChoice == 2)
        {
            getModeChoice(mode);
            for (int i = 0; i < students.size(); i++)
            {
                students[i] = calcFinalGrade(students[i]);
            }
            printStudents(students, mode);
            return 0;
        }
        else
        {
            string fileName;
            cout << "Enter file name in the following format: fileName.txt" << endl;
            while (true)
            {
                cin >> fileName;
                if (checkFileAvailability(fileName) == 0)
                {
                    break;
                }
                cout << "Enter correct file name!" << endl;
            }

            string curLine;
            ifstream file(fileName);
            getline(file, curLine); // skip header
            while (getline(file, curLine))
            {
                if (curLine.length() == 0)
                {
                    continue;
                }

                vector<string> row = stripWhiteSpace(curLine);
                Student student = processStudentRow(row);
                students.push_back(student);
            }
            cout << "" << endl;
            cout << "Student data is uploaded to the system." << endl;
            cout << "" << endl;
            sort(students.begin(), students.end(), compareLastname);
            cout << "" << endl;
            for (int i = 0; i < students.size(); i++)
            {
                students[i] = calcFinalGrade(students[i]);
            }
            printStudents(students, "b");
            cout << "" << endl;
        }
    }
    return 0;
}
