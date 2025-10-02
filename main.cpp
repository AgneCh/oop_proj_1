#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <random>
#include <fstream>
#include <cassert>
#include <cctype>
#include <chrono>

using std::cin;
using std::count;
using std::cout;
using std::endl;
using std::fixed;
using std::ifstream;
using std::invalid_argument;
using std::isdigit;
using std::isspace;
using std::istreambuf_iterator;
using std::left;
using std::move;
using std::mt19937;
using std::numeric_limits;
using std::ofstream;
using std::ostringstream;
using std::random_device;
using std::round;
using std::setfill;
using std::setprecision;
using std::setw;
using std::sort;
using std::stod;
using std::stof;
using std::stoi;
using std::streamsize;
using std::string;
using std::to_string;
using std::uniform_int_distribution;
using std::vector;
using std::isspace;

struct Student
{
    string firstName;
    string lastName;
    vector<int> grades;
    int exam;
    double finalGradeMean;
    double finalGradeMedian;
};

string createHeader(string mode)
{
    ostringstream header;
    const int wLastName = 15;
    const int wFirsName = 15;
    const int wGrade = 20;

    if (mode == "m")
    {
        // -- header --
        header << left
               << setw(wFirsName) << "Name"
               << setw(wLastName) << "Last name"
               << setw(wGrade) << "Final grade (mean)" << '\n';
        // -- separator line --
        header << setfill('-')
               << setw(wFirsName) << ""
               << setw(wLastName) << ""
               << setw(wGrade) << "" << '\n'
               << setfill(' ');
    }
    else if (mode == "md")
    {
        // -- header --
        header << left
               << setw(wFirsName) << "Name"
               << setw(wLastName) << "Last name"
               << setw(wGrade) << "Final grade (median)" << '\n';

        // -- separator line --
        header << setfill('-')
               << setw(wFirsName) << ""
               << setw(wLastName) << ""
               << setw(wGrade) << "" << '\n'
               << setfill(' ');
    }
    else
    {
        // -- header --
        header << left
               << setw(wFirsName) << "Name"
               << setw(wLastName) << "Last name"
               << setw(wGrade) << "Final grade (mean)"
               << setw(wGrade) << "Final grade (median)" << '\n';

        // -- separator line --
        header << setfill('-')
               << setw(wFirsName) << ""
               << setw(wLastName) << ""
               << setw(wGrade) << ""
               << setw(wGrade) << "" << '\n'
               << setfill(' ');
    }
    return header.str();
}

string formatStudentRow(const Student &student, string mode)
{
    ostringstream studentRow;
    const int wLastName = 15;
    const int wFirsName = 15;
    const int wGrade = 20;

    if (mode == "m")
    {

        // -- student data --
        studentRow << left
                   << setw(wFirsName) << student.firstName
                   << setw(wLastName) << student.lastName
                   << fixed << setprecision(2)
                   << setw(wGrade) << student.finalGradeMean << '\n';
    }
    else if (mode == "md")
    {

        // -- student data --
        studentRow << left
                   << setw(wFirsName) << student.firstName
                   << setw(wLastName) << student.lastName
                   << fixed << setprecision(2)
                   << setw(wGrade) << student.finalGradeMedian << '\n';
    }
    else
    {

        // -- student data --
        studentRow << left
                   << setw(wFirsName) << student.firstName
                   << setw(wLastName) << student.lastName
                   << fixed << setprecision(2)
                   << setw(wGrade) << student.finalGradeMean
                   << setw(wGrade) << student.finalGradeMedian << '\n';
    }

    return studentRow.str();
}

void printStudents(vector<Student> &students, string mode)
{

    Student student;

    cout << createHeader(mode);
    for (int i = 0; i < students.size(); i++)
    {
        student = students[i];
        cout << formatStudentRow(student, mode);
    }
}

int getRandomGrade()
{
    static mt19937 gen(random_device{}()); // seed once
    static uniform_int_distribution<int> dist(1, 10);
    return dist(gen);
}

Student getUserStudentInput()
{
    Student student;
    string grade;
    double temp_grade;
    string stopWord = "stop";
    string randomWord = "r";
    string userInput;

    cout << "Input student data." << endl;
    cout << "First name: ";
    cin >> student.firstName;
    cout << "Last name: ";
    cin >> student.lastName;

    while (true)
    {
        cout << "" << endl;
        cout << "Enter " << student.firstName << " " << student.lastName << " homework grade (1-10) manually, type 'r' to generated random grade or type 'stop': ";
        cin >> userInput;
        if (userInput == stopWord)
        {
            break;
        }

        if (userInput == randomWord)
        {
            temp_grade = getRandomGrade();
            cout << "Random grade is: " << temp_grade << endl;
        }
        else
        {
            // check if input contains a digit
            size_t parsed = 0;
            try
            {
                temp_grade = stoi(userInput, &parsed);
                if (parsed != userInput.size())
                {
                    cout << "Invalid input!" << endl;
                    continue;
                }
            }
            catch (invalid_argument err)
            {
                cout << "Invalid input!" << endl;
                continue;
            }
        }

        // check if grade is 1-10
        if (temp_grade >= 1 && temp_grade <= 10)
        {
            student.grades.push_back(temp_grade);
        }
        else
        {
            cout << "Grade must be between 1 and 10." << endl;
        }
    }

    while (true)
    {
        cout << "" << endl;
        cout << "Input exam grade manually, or write 'r' to generated random grade: ";
        cin >> userInput;

        if (userInput == randomWord)
        {
            temp_grade = getRandomGrade();
            cout << "Random exam grade is: " << temp_grade << endl;
        }
        else
        {
            size_t parsed = 0;
            try
            {

                temp_grade = stoi(userInput, &parsed);
                if (parsed != userInput.size())
                {
                    cout << "Invalid input!" << endl;
                    continue;
                }
            }
            catch (invalid_argument err)
            {
                cout << "Invalid input!" << endl;
                continue;
            }
        }
        if (temp_grade >= 1 && temp_grade <= 10)
        {
            student.exam = temp_grade;
            break;
        }
        else
        {
            cout << "Grade must be between 1 and 10." << endl;
        }
    }

    return student;
}

double hwMean(vector<int> grades)
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
    double mean = hwMean(student.grades);
    double median = hwMedian(student.grades);

    student.finalGradeMean = 0.4 * mean + 0.6 * student.exam;
    student.finalGradeMedian = 0.4 * median + 0.6 * student.exam;

    return student;
}

int getUserMenuChoice()
{
    int n;

    while (true)
    {
        cout << "" << endl;
        cout << "Choose a number from the menu:" << endl;
        cout << "1. Add new student" << endl;
        cout << "2. Calculate grades" << endl;
        cout << "3. Insert student data from a file" << endl;
        cout << "4. Generate random student file" << endl;
        cout << "5. Exit" << endl;
        cout << "" << endl;
        cin >> n;
        if (n == 1 || n == 2 || n == 3 || n == 4)
        {
            return n;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid menu number!" << endl;
    }
}

void getModeChoice(string &mode)
{
    cout << "" << endl;
    cout << "Would you like to view the calculated final grade with:" << endl;
    cout << "m = mean" << endl;
    cout << "md = median" << endl;
    cout << "b = both" << endl;
    cout << "" << endl;

    while (true)
    {
        cin >> mode;
        if (mode != "m" && mode != "md" && mode != "b")
        {
            cout << "You must input valid value!" << endl;
            continue;
        }
        break;
    }
}

int checkFileAvailability(string file)
{
    string fileText;
    ifstream f(file);

    if (!f.is_open())
    {
        cout << "Error opening the file!" << endl;
        return 1;
    }

    f.close();
    return 0;
}

void stripWhiteSpace(string &line, vector<string> &result)
{
    result.clear();
    result.reserve(8);

    const size_t len = line.size();
    size_t currPosition = 0;

    while (currPosition < len)
    {
        while (currPosition < len && isspace(static_cast<unsigned char>(line[currPosition])))
            ++currPosition;
        if (currPosition >= len)
            break;

        size_t start = currPosition;
        while (currPosition < len && !isspace(static_cast<unsigned char>(line[currPosition])))
            ++currPosition;
        result.emplace_back(line, start, currPosition - start);
    }
}

Student processStudentRow(vector<string> studentRow)
{

    assert(!(studentRow.size() == 0));

    Student student;
    string firstname = studentRow[0];
    string lastname = studentRow[1];

    student.firstName = firstname;
    student.lastName = lastname;

    for (int i = 2; i < studentRow.size(); i++)
    {
        double tempGrade = stoi(studentRow[i]);
        if (i == studentRow.size() - 1)
        {
            student.exam = tempGrade;
        }
        else
        {

            student.grades.push_back(tempGrade);
        }
    }

    return student;
}

string getNameCharacters(string name)
{
    string result = "";
    char current;
    for (int i = 0; i < name.length(); i++)
    {
        current = name[i];
        if (!isdigit(current))
        {
            result = result + current;
        }
    }
    return result;
}

int getNameNumbers(string name)
{
    string result = "";
    char current;
    for (int i = 0; i < name.length(); i++)
    {
        current = name[i];
        if (isdigit(current))
        {
            result = result + current;
        }
    }
    if (result.size() != 0)
    {
        return stoi(result);
    }
    else
    {
        return 0;
    }
}

bool compareStudentCharacters(Student a, Student b)
{
    string aStr = getNameCharacters(a.firstName);
    string bStr = getNameCharacters(b.firstName);
    return aStr < bStr;
}
bool compareStudentNumbers(Student a, Student b)
{
    int aInt = getNameNumbers(a.firstName);
    int bInt = getNameNumbers(b.firstName);
    return aInt < bInt;
}

void generateRandomStudentFile(string fileName, int numOfLines)
{
    ofstream f(fileName);
    if (!f.is_open())
    {
        cout << "Error creating file!" << fileName << endl;
        return;
    }

    // create header
    f << left << setw(15) << "Name" << setw(15) << "Surname";
    for (int i = 0; i < 5; ++i)
        f << setw(5) << "HM" + to_string(i + 1);
    f << setw(5) << "Exam" << '\n';

    for (int i = 0; i < numOfLines; ++i)
    {
        f << left << setw(15) << "Name" + to_string(i + 1)
          << setw(15) << "Surname" + to_string(i + 1);

        for (int j = 0; j < 5; ++j)
        {
            f << setw(5) << getRandomGrade();
        }
        f << setw(5) << getRandomGrade() << '\n';
    }

    f.close();
    cout << endl;
    cout << "File " << fileName << " is successfully created." << '\n';
}

void loadStudentsFromFile(vector<Student> &students, const string &fileName)
{
    ifstream file(fileName);

    size_t numOfLines = count(istreambuf_iterator<char>(file), istreambuf_iterator<char>(), '\n');

    file.clear();
    file.seekg(0);

    string curLine;
    getline(file, curLine); // skip header
    if(numOfLines > 0) --numOfLines; 
    students.reserve(numOfLines);

    vector<string> row;

    while (getline(file, curLine))
    {
        if (curLine.empty())
        {
            continue;
        }

        stripWhiteSpace(curLine, row);
        Student student = processStudentRow(row);
        students.push_back(move(student));
    }
}

void categorizeStudents(vector<Student> &allStudents, vector<Student> &belowFive, vector<Student> &fiveAndUp)
{
    double threshold = 5.0;

    belowFive.clear();
    fiveAndUp.clear();

    for (const auto &s : allStudents)
    {
        double roundedGrade = round(s.finalGradeMean);
        if (roundedGrade < threshold)
        {
            belowFive.push_back(s);
        }
        else
        {
            fiveAndUp.push_back(s);
        }
    }
}

void createStudentFile(vector<Student> &studentList, string fileName)
{
    Student student;
    ofstream f(fileName);
    if (!f.is_open())
    {
        cout << "Error creating file!" << fileName << "\n";
        return;
    }

    f << createHeader("m");
    for (int i = 0; i < studentList.size(); i++)
    {
        student = studentList[i];
        f << formatStudentRow(student, "m");
    }
    f.close();
    cout << "\n";
    cout << "File " << fileName << " is successfully created." << "\n";
}

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
            cout << "Uploaded" + fileName + " in: " << secLoad << " ms\n";
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
