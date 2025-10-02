#include "Student.h"
#include "GradeCalc.h"
#include "StudentSort.h"
#include "StudentIO.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>

using std::vector;
using std::cout;
using std::cin;
using std::invalid_argument;
using std::to_string;

int main()
{
    using namespace std::chrono;
    string mode;
    vector<Student> students;

    while (true)
    {
        int menuChoice = getUserMenuChoice();
        if (menuChoice == 1) // Add new student
        {
            students.push_back(getUserStudentInput());
        }
        else if (menuChoice == 2) // Calculate grades
        {
            if (students.size() == 0)
            {
                cout << "No student data found in the system!" << "\n";
                continue;
            }
            getModeChoice(mode);
            for (int i = 0; i < students.size(); i++)
            {
                students[i] = calcFinalGrade(students[i]);
            }
            printStudents(students, mode);
        }
        else if (menuChoice == 3) // Insert student data from a file
        {
            string fileName;
            cout << "Enter file name in the following format: fileName.txt" << "\n";
            while (true)
            {
                cin >> fileName;
                if (checkFileAvailability(fileName) == 0)
                {
                    break;
                }
                cout << "Enter correct file name!" << "\n";
            }

            loadStudentsFromFile(students, fileName);
            students.shrink_to_fit();

            cout << "\n";
            cout << "Student data is uploaded to the system." << "\n";
            cout << "\n";
            sort(students.begin(), students.end(), compareStudentCharacters);
            sort(students.begin(), students.end(), compareStudentNumbers);

            cout << "\n";
            for (int i = 0; i < students.size(); i++)
            {
                students[i] = calcFinalGrade(students[i]);
            }
            printStudents(students, "b");
            cout << "\n";
        }
        else if (menuChoice == 4) // Generate random student file
        {
            vector<Student> studentData;
            vector<Student> strugglers;
            vector<Student> highAchievers;

            int fileLenght;
            string fileName;
            string usrInput;
            while (true)
            {
                cout << "How many student records would you like to generate? ";
                cin >> usrInput;

                size_t parsed = 0;

                try
                {
                    fileLenght = stoi(usrInput, &parsed);
                    if (parsed != usrInput.size())
                    {
                        cout << "Invalid input!" << "\n";
                        continue;
                    }
                    break;
                }
                catch (invalid_argument err)
                {
                    cout << "Invalid input!" << "\n";
                    continue;
                }
            }

            fileName = "Student" + to_string(fileLenght) + ".txt";

            // measure execution time
            auto t0 = steady_clock::now();
            generateRandomStudentFile(fileName, fileLenght);
            auto secCreate = duration_cast<duration<double>>(steady_clock::now() - t0).count();
            cout << "Generated Student" + to_string(fileLenght) + " in: " << secCreate << " s\n";

            t0 = steady_clock::now();
            loadStudentsFromFile(studentData, fileName);
            studentData.shrink_to_fit();
            auto secLoad = duration_cast<duration<double>>(steady_clock::now() - t0).count();
            cout << "Uploaded" + fileName + " in: " << secLoad << " s\n";
            cout << "\n";
            cout << "Student data is uploaded to the system." << "\n";
            cout << "\n";

            for (int i = 0; i < studentData.size(); i++)
            {
                studentData[i] = calcFinalGrade(studentData[i]);
            }

            categorizeStudents(studentData, strugglers, highAchievers);
            createStudentFile(strugglers, "strugglers.txt");
            createStudentFile(highAchievers, "highAchievers.txt");
            cout << "\n";
        }
        else
        {
            break;
        }
    }
    return 0;
}
