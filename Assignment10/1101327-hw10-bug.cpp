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
   char studentId[ 8 ];
   char lastName[ 12 ];
   char firstName[ 12 ];
   int grade;
};

enum class Choices{ PRINT = 1, UPDATE, NEW, DELETE, END };

// enable user to input menu choice
Choices enterChoice();

// create text file for printing
void createTextFile( fstream &readFromFile );

// update grade in record
void updateRecord( fstream &updateFile );

// add a new grade in record
void newRecord( fstream &insertInFile );

// delete an existing record
void deleteRecord( fstream &deleteFromFile );

// obtain student ID from user
void getID( const char * const prompt, char studentId[] );

int main()
{
   // open file for reading and writing
   fstream inOutGrade( "grades.dat", ios::in | ios::out | ios::binary );

   // exit program if fstream cannot open file
   if( !inOutGrade )
   {
      cerr << "File could not be opened." << endl;
      system( "pause" );
      exit( 1 );
   }

   Choices choice; // store user choice

   // enable user to specify action
   while( ( choice = enterChoice() ) != Choices::END )
   {
      switch( choice )
      {
      case Choices::PRINT:
         createTextFile( inOutGrade ); // create text file from binary file
         break;
      case Choices::UPDATE:
         updateRecord( inOutGrade ); // update grade
         break;
      case Choices::NEW:
         newRecord( inOutGrade ); // add a new grade
         break;
      case Choices::DELETE:
         deleteRecord( inOutGrade ); // delete existing record
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

   system( "pause" );
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
   return static_cast< Choices >( menuChoice );
}

// create text file for printing
void createTextFile( fstream &readFromFile )
{
    //write file
    ofstream outFile("grades.txt", ios::out);
    StudentData student;
    while (readFromFile.read(reinterpret_cast<char*>(&student), sizeof(StudentData)))
        outFile << student.studentId << "  " << setw(12) << left << student.firstName << setw(13) << student.lastName << setw(5) << right << student.grade << endl;
    outFile.close();

    //read file
    string stringLine;
    ifstream inFile("grades.txt", ios::out);
    if (!inFile)
    {
        cerr << "Open file failed" << endl;
        exit(1);
    }
    cout << "ID" << "       " << "Last Name" << "   " << "First Name" << "   " << "Grade" << endl;
    while (getline(inFile, stringLine))
        cout << stringLine << endl;
    inFile.close();
}

// update grade in record
void updateRecord( fstream &updateFile )
{
   char studentId[ 8 ];
   getID( "\nEnter student ID to update", studentId );

  
   cout << endl;
   //11114XX
   StudentData student;
   int inClassID = 10 * (studentId[5] - '0') + (studentId[6] - '0');
   updateFile.seekg((inClassID - 1) * sizeof(StudentData), ios::beg);
   updateFile.read(reinterpret_cast<char*>(&student), sizeof(StudentData));
   //no this student
   if (strcmp(student.studentId, studentId) != 0)
       cout << "Student ID " << studentId << " is empty.\n";
   //no grade
   else if (student.grade == -1)
       cout << "Student ID " << studentId << " has no grade.\n";
   else
   {
       int newGrade;
       cout << student.studentId << "  " << student.lastName << "        " << student.firstName << "          " << student.grade << endl;
       cout << "Enter grade: ";
       cin >> newGrade;
       cout << endl;
       updateFile.seekg((inClassID - 1) * sizeof(StudentData), ios::beg);
       student.grade = newGrade;
       updateFile.write(reinterpret_cast<const char*>(&student), sizeof(StudentData));
   }

}

// add a new grade in record
void newRecord( fstream &insertInFile )
{
   char studentId[ 8 ];
   getID( "\nEnter student ID to add", studentId );

   cout << endl;
   StudentData student[100];
   int inClassID = 10 * (studentId[5] - '0') + (studentId[6] - '0');
   insertInFile.seekg(0, ios::end);
   int endPosition = insertInFile.tellg() / sizeof(StudentData);  //end -> the end of file +1
   insertInFile.seekg((inClassID - 1) * sizeof(StudentData), ios::beg);
   int a = insertInFile.tellg();
   int begPosition = insertInFile.tellg() / sizeof(StudentData);
   insertInFile.read(reinterpret_cast<char*>(&student), sizeof(student));  //I guess it read the end of file
   insertInFile.clear();

   //no this student
   if (strcmp(student[0].studentId, studentId) != 0)
       cout << "Student ID " << student[0].studentId << " is empty.\n";
   else
   {
       //add grade
       cout << "Enter grade: ";
       cin >> student[0].grade;
       insertInFile.seekg((inClassID - 1) * sizeof(StudentData), ios::beg);
       int moveCase = endPosition - 1 - begPosition;  //end -> the end of file +1
       for (int i = 0; i <= moveCase; i++)
           insertInFile.write(reinterpret_cast<char*>(&student[i]), sizeof(StudentData));
       cout << "Student ID " << studentId << " deleted.\n";
   }



}

// delete an existing record
void deleteRecord( fstream &deleteFromFile )
{
   char studentId[ 8 ];
   getID( "\nEnter student ID to delete", studentId );

   cout << endl;
   StudentData student[100];
   int inClassID = 10 * (studentId[5] - '0') + (studentId[6] - '0');
   deleteFromFile.seekg(0, ios::end);
   int endPosition = deleteFromFile.tellg() / sizeof(StudentData);  //end -> the end of file +1
   deleteFromFile.seekg((inClassID - 1) * sizeof(StudentData), ios::beg);
   int a = deleteFromFile.tellg();
   int begPosition = deleteFromFile.tellg() / sizeof(StudentData);
   deleteFromFile.read(reinterpret_cast<char*>(&student), sizeof(student));  //I guess it read the end of file
   //cout << deleteFromFile.good() << endl;
   //cout << deleteFromFile.fail() << endl;
   //cout << deleteFromFile.eof() << endl;
   deleteFromFile.clear();

   //no this student
   if (strcmp(student[0].studentId, studentId) != 0)
       cout << "Student ID " << student[0].studentId << " is empty.\n";
   else
   {   
       //delete target
       deleteFromFile.seekg((inClassID - 1) * sizeof(StudentData), ios::beg);
       int moveCase = endPosition - 1 - begPosition;  //end -> the end of file +1
       for (int i = 1; i <= moveCase; i++)
           deleteFromFile.write(reinterpret_cast<char*>(&student[i]), sizeof(StudentData));
       cout << "Student ID " << studentId << " deleted.\n";
   }


}

// obtain student ID from user
void getID( const char * const prompt, char studentId[] )
{
   do
   {
      cout << prompt << " ( 1111401 - 1111450 ): ";
      cin >> studentId;
   } while( strcmp( studentId, "1111401" ) == -1 || strcmp( studentId, "1111450" ) == 1 );
}