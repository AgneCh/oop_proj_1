#include <iostream>
#include <iomanip>
#include<vector>
#include<string>


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

struct Student{
    string firstName;
    string lastName;
    vector <double> grades;
    int exam;
    double finalGrade;
};

void printStudent(Student student){
    // -- header --
    cout << left
        << setw(15) << "Last name"
        << setw(10) << "Name"
        << setw(4) << "Final grade (mean)" << endl;
    
    // -- seperator line --
    cout << setfill('-')
              << setw(15) << ""
              << setw(10) << ""
              << setw(18) << "" << endl
              << setfill(' ');

    // -- student data --
    cout << left 
        << setw(15) << student.lastName 
        << setw(10) << left << student.firstName
        << right << fixed << setprecision(2)
        << setw(4) << left << student.finalGrade << endl; 
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
    double sumGrades = 0;
    for (int i = 0; i < student.grades.size(); i++){
        sumGrades += student.grades[i];
    }
    sumGrades += student.exam;
    cout << "sumGrades: "<< sumGrades <<endl;
    cout << student.exam << endl;
    cout << student.grades.size() << endl;
    student.finalGrade = sumGrades / (student.grades.size() + 1);

    return student;
}

int main(){
    Student student = getUserInput();
    student = calcFinalGrade(student);
    printStudent(student);
    return 0;
}