#include "StudentSort.h"
#include <cmath>
#include <cctype>
#include <string>
#include <iterator>

using std::round;
using std::string;

std::string_view getNameLetters(const std::string &s)
{
    size_t i = 0;
    while (i < s.size() && !(s[i] >= '0' && s[i] <= '9'))
        ++i;
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

// Stradegy 1
void categorizeStudents_1(StudentContainer &allStudents, StudentContainer &belowFive, StudentContainer &fiveAndUp)
{

    for (const auto &s : allStudents)
    {
        if (s.finalGradeMean < 5.0)
        {
            belowFive.push_back(s);
        }
        else
        {
            fiveAndUp.push_back(s);
        }
    }
}

// Stradegy 2
void categorizeStudents_2(StudentContainer &allStudents, StudentContainer &belowFive, StudentContainer &fiveAndUp)
{
#ifdef USE_LIST

    for (auto it = allStudents.begin(); it != allStudents.end();)
    {
        auto cur = it++;
        if (cur->finalGradeMean < 5.0)
            belowFive.splice(belowFive.end(), allStudents, cur);
    }

#else
    belowFive.reserve(allStudents.size() / 2);
    fiveAndUp.reserve(allStudents.size() / 2);
    std::size_t i = 0;
    while (i < allStudents.size())
    {
        if (allStudents[i].finalGradeMean < 5.0)
        {
            belowFive.push_back(std::move(allStudents[i]));
            allStudents[i] = std::move(allStudents.back());
            allStudents.pop_back();
        }
        else
        {
            ++i;
        }
    }

#endif
    fiveAndUp = std::move(allStudents);
}

// Stradegy 3
void categorizeStudents_3(StudentContainer &allStudents, StudentContainer &belowFive, StudentContainer &fiveAndUp)
{
    auto it = std::partition(allStudents.begin(), allStudents.end(), [](const Student &s)
                             { return s.finalGradeMean < 5.0; });

    belowFive.assign(allStudents.begin(), it);
    fiveAndUp.assign(it, allStudents.end());
}