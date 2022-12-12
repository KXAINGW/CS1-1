// This program reads a binary file,
// updates grades previously written to the file,
// adds new grades in the file,
// and deletes data previously stored in the file.

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>
using namespace std;

struct StudentData
{
    char studentId[8];
    char lastName[12];
    char firstName[12];
    int grade;
};

enum class Choices { PRINT = 1, UPDATE, NEW, DELETE, END };

// enable user to input menu choice
Choices enterChoice();

// create text file for printing
void createTextFile(fstream& readFromFile);

// update grade in record
void updateRecord(fstream& updateFile);

// add a new grade in record
void newRecord(fstream& insertInFile);

// delete an existing record
void deleteRecord(fstream& deleteFromFile);

// obtain student ID from user
void getID(const char* const prompt, char studentId[]);

int main()
{
    // open file for reading and writing
    fstream inOutGrade("grades.dat", ios::in | ios::out | ios::binary);

    // exit program if fstream cannot open file
    if (!inOutGrade)
    {
        cerr << "File could not be opened." << endl;
        system("pause");
        exit(1);
    }

    Choices choice; // store user choice

    // enable user to specify action
    while ((choice = enterChoice()) != Choices::END)
    {
        switch (choice)
        {
        case Choices::PRINT:
            createTextFile(inOutGrade); // create text file from binary file
            break;
        case Choices::UPDATE:
            updateRecord(inOutGrade); // update grade
            break;
        case Choices::NEW:
            newRecord(inOutGrade); // add a new grade
            break;
        case Choices::DELETE:
            deleteRecord(inOutGrade); // delete existing record
            break;
        default:
            cerr << "Incorrect choice" << endl;
            break;
        }

        //(mode) turn into good
        //cout <<  boolalpha<< inOutGrade.good() << endl;
        inOutGrade.clear();
        inOutGrade.seekg(0, ios::beg);
        //cout << inOutGrade.good() << boolalpha << endl;
        //cout << inOutGrade.fail() << boolalpha << endl;



        cout << endl;
    }

    inOutGrade.close();

    system("pause");
}

// enable user to input menu choice
Choices enterChoice()
{
    // display available options
    cout << "Enter your choice" << endl
        << "1 - store a text file of all students' information" << endl
        << "    called \"grades.txt\" for printing" << endl
        << "2 - update a student's grade" << endl
        << "3 - add a student's grade" << endl
        << "4 - delete a student's information" << endl
        << "5 - end program\n? ";

    int menuChoice;
    cin >> menuChoice;
    return static_cast<Choices>(menuChoice);
}

// create text file for printing
void createTextFile(fstream& readFromFile)
{
    //write file
    ofstream outFile("grades.txt", ios::out);
    //read one by one
    /*
    while (readFromFile.read(reinterpret_cast<char*>(&student), sizeof(StudentData)))
        outFile << student.studentId << "  " << setw(12) << left << student.firstName << setw(13) << student.lastName << setw(5) << right << student.grade << endl;
    */
    StudentData student[51];
    //read all
    readFromFile.read(reinterpret_cast<char*>(&student), sizeof(student));
    readFromFile.clear();  
    readFromFile.seekg(0, ios::end);
    int size = readFromFile.tellg() / sizeof(StudentData);
    //adjust size
    while (size > 0 && strcmp(student[size - 1].studentId, "") == 0)
        --size;
    for(int i = 0;i<size;i++)
        outFile << student[i].studentId << "  " << setw(12) << left << student[i].firstName << setw(13) << student[i].lastName << setw(5) << right << student[i].grade << endl;

    outFile.close();

    //read file
    string stringLine;
    ifstream inFile("grades.txt", ios::in);
    if (!inFile)
    {
        cerr << "Open file failed" << endl;
        exit(1);
    }
    cout << endl;
    cout << "ID" << "       " << "Last Name" << "   " << "First Name" << "   " << "Grade" << endl;
    while (getline(inFile, stringLine))
        cout << stringLine << endl;
    inFile.close();
}

// update grade in record
void updateRecord(fstream& updateFile)
{
    char studentId[8];
    getID("\nEnter student ID to update", studentId);


    cout << endl;
    //11114XX
    StudentData student[51];
    //read all
    updateFile.read(reinterpret_cast<char*>(&student), sizeof(student));
    updateFile.clear();   //I guess it read the end of file
    updateFile.seekg(0, ios::end);
    int size = updateFile.tellg() / sizeof(StudentData);
    //adjust size
    //while (size > 1 && strcmp(student[size - 1].studentId, student[size - 2].studentId) == 0)
    //    --size;
    int index = -1;
    //or use binary search
    for (int i = 0; i < size; i++)
    {
        //find this student position
        if (strcmp(student[i].studentId, studentId) == 0)
        {
            index = i;
            break;
        }
    }
    //no this student
    if (index == -1)
    {
        cout << "Student ID " << studentId << " is empty.\n";
        return;
    }

    //no grade
    if (student[index].grade == -1)
        cout << "Student ID " << studentId << " has no grade.\n";
    //update grade
    else
    {
        int newGrade;
        cout << student[index].studentId << "  " << student[index].lastName << "        " << student[index].firstName << "          " << student[index].grade << endl;
        cout << endl;
        cout << "Enter grade: ";
        cin >> newGrade;
        cout << endl;
        updateFile.seekg(index * sizeof(StudentData), ios::beg);
        student[index].grade = newGrade;
        //cin >> student[index].grade
        updateFile.write(reinterpret_cast<const char*>(&student[index]), sizeof(StudentData));
        cout << student[index].studentId << "  " << student[index].lastName << "        " << student[index].firstName << "          " << student[index].grade << endl;
    }

}

// add a new grade in record
void newRecord(fstream& insertInFile)
{
    char studentId[8];
    getID("\nEnter student ID to add", studentId);

    cout << endl;
    StudentData student[51];
    //read all
    insertInFile.read(reinterpret_cast<char*>(&student), sizeof(student));
    insertInFile.clear();   //I guess it read the end of file
    insertInFile.seekg(0, ios::end);
    int size = insertInFile.tellg() / sizeof(StudentData);
    int index = -1;
    //find 11114XX
    for (int i = 0; i < size; i++)
    {
        if (strcmp(student[i].studentId, studentId) == 0)
        {
            index = i;
            break;
        }
    }
    //no this student
    if (index == -1)
    {
        cout << "Student ID " << studentId << " is empty.\n";
        return;
    }

    //add grade
    cout << "Enter grade: ";
    cin >> student[index].grade;
    cout << endl;
    insertInFile.seekg(index * sizeof(StudentData), ios::beg);
    insertInFile.write(reinterpret_cast<char*>(&student[index]), sizeof(StudentData));
    cout << student[index].studentId << "  " << student[index].lastName << "        " << student[index].firstName << "          " << student[index].grade << endl;

}

// delete an existing record
void deleteRecord(fstream& deleteFromFile)
{
    char studentId[8];
    getID("\nEnter student ID to delete", studentId);

    cout << endl;
    StudentData student[51];
    deleteFromFile.read(reinterpret_cast<char*>(&student), sizeof(student));   //I guess it read the end of file
    //cout << deleteFromFile.good() << endl;
    //cout << deleteFromFile.fail() << endl;
    //cout << deleteFromFile.eof() << endl; 
    deleteFromFile.clear();
    deleteFromFile.seekg(0, ios::end);
    int size = deleteFromFile.tellg() / sizeof(StudentData);
    int index = -1;
    //find delete target
    for (int i = 0; i < size; i++)
    {
        if (strcmp(student[i].studentId, studentId) == 0)
        {
            index = i;
            break;
        }
    }

    //no this student
    if (index == -1)
    {
        cout << "Student ID " << studentId << " is empty.\n";
        return;
    }
    //delete
    deleteFromFile.seekg(index * sizeof(StudentData), ios::beg);
    for (int i = index + 1; i < size; i++)
        deleteFromFile.write(reinterpret_cast<char*>(&student[i]), sizeof(StudentData));
    //delete original data
    StudentData blankRecord = { "","","",-1 };
    deleteFromFile.write(reinterpret_cast<const char*>(&blankRecord), sizeof(StudentData));
    cout << "Student ID " << studentId << " deleted.\n";
}

// obtain student ID from user
void getID(const char* const prompt, char studentId[])
{
    do
    {
        cout << prompt << " ( 1111401 - 1111450 ): ";
        cin >> studentId;
    } while (strcmp(studentId, "1111401") == -1 || strcmp(studentId, "1111450") == 1);
}