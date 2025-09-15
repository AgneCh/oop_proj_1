#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

// using namespace std;
using std::cin;
using std::cout;
using std::endl;
using std::fixed;
using std::invalid_argument;
using std::left;
using std::numeric_limits;
using std::setfill;
using std::setprecision;
using std::setw;
using std::sort;
using std::stof;
using std::streamsize;
using std::string;
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
        cout << left
             << setw(wLastName) << "Last name"
             << setw(wFirsName) << "Name"
             << setw(wGrade) << "Final grade (mean)" << endl;

        // -- separator line --
        cout << setfill('-')
             << setw(wLastName) << ""
             << setw(wFirsName) << ""
             << setw(wGrade) << "" << endl
             << setfill(' ');
    }
    else if (mode == "md")
    {
        // -- header --
        cout << left
             << setw(wLastName) << "Last name"
             << setw(wFirsName) << "Name"
             << setw(wGrade) << "Final grade (median)" << endl;

        // -- separator line --
        cout << setfill('-')
             << setw(wLastName) << ""
             << setw(wFirsName) << ""
             << setw(wGrade) << "" << endl
             << setfill(' ');
    }
    else
    {
        // -- header --
        cout << left
             << setw(wLastName) << "Last name"
             << setw(wFirsName) << "Name"
             << setw(wGrade) << "Final grade (mean)"
             << setw(wGrade) << "Final grade (median)" << endl;

        // -- separator line --
        cout << setfill('-')
             << setw(wLastName) << ""
             << setw(wFirsName) << ""
             << setw(wGrade) << ""
             << setw(wGrade) << "" << endl
             << setfill(' ');
    }
}

void printStudents(vector<Student> &students, string mode)
{
    const int wLastName = 15;
    const int wFirsName = 10;
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
                 << setw(wLastName) << student.lastName
                 << setw(wFirsName) << student.firstName
                 << fixed << setprecision(2)
                 << setw(wGrade) << student.finalGradeMean << endl;
        }
        else if (mode == "md")
        {

            // -- student data --
            cout << left
                 << setw(wLastName) << student.lastName
                 << setw(wFirsName) << student.firstName
                 << fixed << setprecision(2)
                 << setw(wGrade) << student.finalGradeMedian << endl;
        }
        else
        {

            // -- student data --
            cout << left
                 << setw(wLastName) << student.lastName
                 << setw(wFirsName) << student.firstName
                 << fixed << setprecision(2)
                 << setw(wGrade) << student.finalGradeMean
                 << setw(wGrade) << student.finalGradeMedian << endl;
        }
    }
}

Student getUserStudentInput()
{
    Student student;
    string grade;
    double temp_grade;
    string stopWord = "stop";
    string userInput;

    cout << "Input student data." << endl;
    cout << "First name: ";
    cin >> student.firstName;
    cout << "Last name: ";
    cin >> student.lastName;
    cout << "Enter " << student.firstName << "'s " << student.lastName << " homework grade (2-10), one at the time." << endl;

    while (true)
    {

        cout << "Input grade or type 'stop': ";
        cin >> userInput;
        if (userInput == stopWord)
        {
            break;
        }

        // check if input contains number
        // TODO: allows 2k5 -> 2. maybe we need to fix
        try
        {
            temp_grade = stof(userInput);
        }
        catch (invalid_argument err)
        {
            cout << "Invalid input!" << endl;
            continue;
        }

        // check if grade is 2-10
        if (temp_grade >= 2 && temp_grade <= 10)
        {
            student.grades.push_back(temp_grade);
        }
        else
        {
            cout << "Grade must be between 2 and 10." << endl;
        }
    }

    cout << "Input exam grade: ";
    cin >> student.exam;

    return student;
}

double hwMean(vector<double> grades)
{
    if (grades.empty())
    {
        return 0.00;
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
        return 0.00;
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
        //TODO: user selects 2 without student data input
        cout << "Choose number from the menu:" << endl;
        cout << "1. Add new student" << endl;
        cout << "2. Calculate grades" << endl;
        cin >> n;
        if (n == 1 || n == 2)
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
    cout << "How would you view the calclated final grade using:" << endl;
    cout << "m = mean" << endl;
    cout << "md = median" << endl;
    cout << "b = both" << endl;


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
        else
        {
            getModeChoice(mode);
            for (int i = 0; i < students.size(); i++)
            {
                students[i] = calcFinalGrade(students[i]);
            }
            printStudents(students, mode);
            return 0;
        }
    }
    return 0;
}