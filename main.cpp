#include <iostream>
#include <iomanip>
#include<vector>
#include<string>
#include<algorithm>


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

Student calcFinalGrade(Student student){

    // calculte mean
    double sumGrades = 0;
    for (int i = 0; i < student.grades.size(); i++){
        sumGrades += student.grades[i];
    }
    sumGrades += student.exam;
    cout << "sumGrades: "<< sumGrades <<endl;
    cout << student.exam << endl;
    cout << student.grades.size() << endl;
    student.finalGradeMean = sumGrades / (student.grades.size() + 1);
    
    // calculte median
    vector <double> allGrades = student.grades;
    allGrades.push_back(student.exam);
    int n = allGrades.size();
    sort(allGrades.begin(), allGrades.end());
    if (n % 2 != 0){
        student.finalGradeMedian = allGrades[n / 2];
    } else{
        student.finalGradeMedian = (allGrades[(n - 1) / 2] + allGrades[n / 2]) / 2.0;
    }


    return student;
}

int main(){
    Student student = getUserInput();
    student = calcFinalGrade(student);
    printStudent(student);
    return 0;
}