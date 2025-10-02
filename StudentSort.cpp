#include "StudentSort.h"
#include <cmath>
#include <cctype>
#include <string>

using std::string;
using std::isdigit;
using std::stoi;
using std::round;

string getNameCharacters(string name)
{
    string result = "";
    char current;
    for (int i = 0; i < name.length(); i++)
    {
        current = name[i];
        if (!isdigit(current))
        {
            result = result + current;
        }
    }
    return result;
}

int getNameNumbers(string name)
{
    string result = "";
    char current;
    for (int i = 0; i < name.length(); i++)
    {
        current = name[i];
        if (isdigit(current))
        {
            result = result + current;
        }
    }
    if (result.size() != 0)
    {
        return stoi(result);
    }
    else
    {
        return 0;
    }
}

bool compareStudentCharacters(Student a, Student b)
{
    string aStr = getNameCharacters(a.firstName);
    string bStr = getNameCharacters(b.firstName);
    return aStr < bStr;
}
bool compareStudentNumbers(Student a, Student b)
{
    int aInt = getNameNumbers(a.firstName);
    int bInt = getNameNumbers(b.firstName);
    return aInt < bInt;
}

void categorizeStudents(vector<Student> &allStudents, vector<Student> &belowFive, vector<Student> &fiveAndUp)
{
    double threshold = 5.0;

    belowFive.clear();
    fiveAndUp.clear();

    for (const auto &s : allStudents)
    {
        double roundedGrade = round(s.finalGradeMean);
        if (roundedGrade < threshold)
        {
            belowFive.push_back(s);
        }
        else
        {
            fiveAndUp.push_back(s);
        }
    }
}