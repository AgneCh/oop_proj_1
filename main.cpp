#include "Student.h"
#include "GradeCalc.h"
#include "StudentSort.h"
#include "StudentIO.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>

using std::cin;
using std::cout;
using std::invalid_argument;
using std::to_string;
using std::vector;

int main()
{
    using namespace std::chrono;
    string mode;
    StudentContainer students;

    while (true)
    {
        int menuChoice = getUserMenuChoice();
        if (menuChoice == 1) // Add new student
        {
            students.push_back(getUserStudentInput());
            cout << "Student data saved in memory address: " << &students.back() << "\n";
        }
        else if (menuChoice == 2) // Calculate grades
        {
            if (students.size() == 0)
            {
                cout << "No student data found in the system!" << "\n";
                continue;
            }
            getModeChoice(mode);
            for (auto &s : students)
            {
                s = calcFinalGrade(s);
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
#ifndef USE_LIST
            students.shrink_to_fit();
#endif

            cout << "\n";
            cout << "Student data is uploaded to the system." << "\n";
            cout << "\n";
#ifdef USE_LIST
            students.sort(compareStudentCharacters);
            students.sort(compareStudentNumbers);
#else
            sort(students.begin(), students.end(), compareStudentCharacters);
            sort(students.begin(), students.end(), compareStudentNumbers);
#endif

            cout << "\n";
            for (auto &s : students)
            {
                s = calcFinalGrade(s);
            }
            printStudents(students, "b");
            cout << "\n";
        }
        else if (menuChoice == 4) // Generate random student file
        {
            StudentContainer studentData;

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
            StudentContainer studentData;
            StudentContainer strugglers;
            StudentContainer highAchievers;
            string fileName;
            string sortChoice;
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
#ifndef USE_LIST
            studentData.shrink_to_fit();
#endif
            cout << "\n";
            cout << "Student data is uploaded to the system." << "\n";
            cout << "\n";

            for (auto &s : studentData)
            {
                s = calcFinalGrade(s);
            }

            t0 = steady_clock::now();
            categorizeStudents(studentData, strugglers, highAchievers);
            auto secSorted = duration_cast<duration<double>>(steady_clock::now() - t0).count();
            cout << fileName + " sorted in to two groups in: " << secSorted << " s\n";

            cout << "To sort categorized files by name type 'n' or 'g' to sort by grade: " << "\n";

            while (true)

            {
                cin >> sortChoice;

                if (sortChoice == "n")

                {
#ifdef USE_LIST
                    strugglers.sort(compareStudentCharacters);
                    strugglers.sort(compareStudentNumbers);
                    highAchievers.sort(compareStudentCharacters);
                    highAchievers.sort(compareStudentNumbers);

#else
                    sort(strugglers.begin(), strugglers.end(), compareStudentCharacters);
                    sort(strugglers.begin(), strugglers.end(), compareStudentNumbers);

                    sort(highAchievers.begin(), highAchievers.end(), compareStudentCharacters);
                    sort(highAchievers.begin(), highAchievers.end(), compareStudentNumbers);
#endif
                    break;
                }

                else if (sortChoice == "g")

                {
#ifdef USE_LIST
                    strugglers.sort(compareStudentGrades);
                    highAchievers.sort(compareStudentGrades);
#else
                    sort(strugglers.begin(), strugglers.end(), compareStudentGrades);
                    sort(highAchievers.begin(), highAchievers.end(), compareStudentGrades);
#endif
                    break;
                }

                cout << "Invalid choice!\n";
            }

            t0 = steady_clock::now();
            createStudentFile(strugglers, "strugglers.txt");
            createStudentFile(highAchievers, "highAchievers.txt");
            auto sec = duration_cast<duration<double>>(steady_clock::now() - t0).count();
            cout << "Categorized files were created in: " << sec << " s\n";
        }
        else
        {
            break;
        }
    }
    return 0;
}
