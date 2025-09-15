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

void printStudent(const Student& student, string mode){

    const int wLastName = 15;
    const int wFirsName = 10;
    const int wGrade = 20;

    if (mode == "m"){
        // -- header --
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

        // -- student data --
        cout << left 
            << setw(wLastName) << student.lastName 
            << setw(wFirsName) << student.firstName
            << fixed << setprecision(2)
            << setw(wGrade) << student.finalGradeMean << endl; 

    } else if (mode == "md"){
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

        // -- student data --
        cout << left 
            << setw(wLastName) << student.lastName 
            << setw(wFirsName) << student.firstName
            << fixed << setprecision(2)
            << setw(wGrade) << student.finalGradeMedian << endl; 

    } else {
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

        // -- student data --
        cout << left 
            << setw(wLastName) << student.lastName 
            << setw(wFirsName) << student.firstName
            << fixed << setprecision(2)
            << setw(wGrade) << student.finalGradeMean
            << setw(wGrade) << student.finalGradeMedian << endl; 
    }

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
    string mode;
    Student student = getUserInput();
    student = calcFinalGrade(student);
    cout << "How would you like to calclated the final grade? Using:" << endl;
    cout << "m = mean" << endl;
    cout << "md = median" << endl;
    cout << "b = both" << endl; cin>>mode;
    printStudent(student, mode);
    return 0;
}