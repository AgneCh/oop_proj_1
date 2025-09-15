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


struct Student{
    string firstName;
    string lastName;
    vector <int> grades;
    int exam;
    float finalGrade;
};

void printStudent(Student student){
    cout << student.firstName << " " << student.lastName << endl;
    for (int i = 0; i < student.grades.size(); i++){
        cout << student.grades[i] << endl;
    }
    cout << "Final grade: ";
    cout << student.finalGrade << endl;
}

Student getUserInput(){
    Student student;
    string grade;
    int n, temp_grade;

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
    int sumGrades = 0;
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