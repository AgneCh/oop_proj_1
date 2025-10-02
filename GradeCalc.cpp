#include "GradeCalc.h"
#include <algorithm>

using std::vector;


double hwMean(const vector<int>& grades)
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

double hwMedian(vector<int> grades)
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
    const double mean = hwMean(student.grades);
    const double median = hwMedian(student.grades);

    student.finalGradeMean = 0.4 * mean + 0.6 * student.exam;
    student.finalGradeMedian = 0.4 * median + 0.6 * student.exam;

    return student;
}