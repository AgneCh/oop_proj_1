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
            cout << to_string(fileLenght) + "txt file was generated in: " << secCreate << " s\n";

        }
        else if (menuChoice == 5) // sort student list into categories
        {   
            vector<Student> studentData;
            vector<Student> strugglers;
            vector<Student> highAchievers;
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

            auto t0 = steady_clock::now();
            loadStudentsFromFile(studentData, fileName);
            auto secLoad = duration_cast<duration<double>>(steady_clock::now() - t0).count();
            cout << "Uploaded" + fileName + " in: " << secLoad << " s\n";
            studentData.shrink_to_fit();
            cout << "\n";
            cout << "Student data is uploaded to the system." << "\n";
            cout << "\n";

            for (int i = 0; i < studentData.size(); i++)
            {
                studentData[i] = calcFinalGrade(studentData[i]);
            }

            t0 = steady_clock::now();
            categorizeStudents(studentData, strugglers, highAchievers);
            auto secSorted = duration_cast<duration<double>>(steady_clock::now() - t0).count();
            cout << fileName + "sorted in to two groups in: " << secSorted << " s\n";

            t0 = steady_clock::now();
            createStudentFile(strugglers, "strugglers.txt");
            auto secStrug = duration_cast<duration<double>>(steady_clock::now() - t0).count();
            cout << "strugglers.txt created in: " << secStrug << " s\n";

            t0 = steady_clock::now();
            createStudentFile(highAchievers, "highAchievers.txt");
            auto secHA = duration_cast<duration<double>>(steady_clock::now() - t0).count();
            cout << "highAchievers.txt created in: " << secStrug << " s\n";
            cout << "\n";
        }
        else
        {
            break;
        }
    }
    return 0;
}
