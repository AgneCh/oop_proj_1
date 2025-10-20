#include "StudentSort.h"
#include <cmath>
#include <cctype>
#include <string>

using std::round;
using std::string;

std::string_view getNameLetters(const std::string& s) {
    size_t i = 0;
    while (i < s.size() && !(s[i] >= '0' && s[i] <= '9')) ++i;
    return std::string_view{s.data(), i};
}

int getNameNumber(const string &s)
{
    size_t i = 0;
    while (i < s.size() && !(s[i] >= '0' && s[i] <= '9'))
        ++i;
    int number = 0;
    while (i < s.size() && (s[i] >= '0' && s[i] <= '9'))
    {
        number = number * 10 + (s[i] - '0');
        ++i;
    }
    return number;
}

bool compareStudentNames(const Student &a, const Student &b)
{
    auto aLetters = getNameLetters(a.firstName);
    auto bLetters = getNameLetters(b.firstName);

    if (aLetters != bLetters)
        return aLetters < bLetters;

    return getNameNumber(a.firstName) < getNameNumber(b.firstName);
}

bool compareStudentGrades(const Student &a, const Student &b)
{
    return a.finalGradeMean < b.finalGradeMean;
}

void categorizeStudents(StudentContainer &allStudents, StudentContainer &belowFive, StudentContainer &fiveAndUp)
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