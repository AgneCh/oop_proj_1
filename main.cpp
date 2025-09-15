#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>


//using namespace std;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::setw;
using std::right;
using std::left;
using std::setfill;
using std::fixed;
using std::setprecision;
using std::sort;

struct Student{
    string firstName;
    string lastName;
    vector <double> grades;
    double exam;
    double finalGradeMean;
    double finalGradeMedian;
};

void printStudent(Student student){
    // -- header --
    cout << left
        << setw(15) << "Last name"
        << setw(10) << "Name"
        << setw(20) << "Final grade (mean)"
        << setw(20) << "Final grade (median)" << endl;
    
    // -- separator line --
    cout << setfill('-')
              << setw(15) << ""
              << setw(10) << ""
              << setw(20) << ""
              << setw(20) << "" << endl
              << setfill(' ');

    // -- student data --
    cout << left 
        << setw(15) << student.lastName 
        << setw(10) << student.firstName
        << fixed << setprecision(2)
        << setw(20) << student.finalGradeMean
        << setw(20) << student.finalGradeMedian << endl; 
}

Student getUserInput(){
    Student student;
    string grade;
    double temp_grade;
    int n;

    cout << "Input student data." << endl;
    cout << "First name: "; cin >> student.firstName;
    cout << "Last name: "; cin >> student.lastName;
    cout << "How many grades does " << student.firstName << " " << student.lastName << " have? "; cin >> n; 
    
    for (int i = 0; i < n; i++){
        cout << i +1 << " grade: "; cin >> temp_grade;
        student.grades.push_back(temp_grade);
    }

    cout << "Input exam grade: "; cin >> student.exam;
    
    return student;
}

double hwMean(vector<double> grades){
    if (grades.empty()){
        return 0.00;
    }

    double sum = 0.0; 
    for (double i : grades) sum += i;
    return sum / grades.size();
}

double hwMedian(vector<double> grades){
    if (grades.empty()){
        return 0.00;
    }

    sort(grades.begin(), grades.end());
    int n = grades.size();
    if (n % 2 != 0){
        return grades[n / 2];
    } else {
        return (grades[(n - 1) / 2] + grades[n / 2]) / 2.0;
    }
}

Student calcFinalGrade(Student student){
    double mean = hwMean(student.grades);
    double median = hwMedian(student.grades);

    student.finalGradeMean = 0.4 * mean + 0.6 * student.exam;
    student.finalGradeMedian = 0.4 * median + 0.6 * student.exam;

    return student;
}

int main(){
    Student student = getUserInput();
    student = calcFinalGrade(student);
    printStudent(student);
    return 0;
}