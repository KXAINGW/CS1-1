#include <iostream>
#include <fstream>
#include <vector>
using namespace::std;

// reads in a C++ program from a cpp file, and put it to the vector program
void load( vector< char * > &program );

// deletes the comment beginning with "//" from sourceLine if any
void delComment( char sourceLine[] );

// deletes all string constants from sourceLine
void delStrConsts( char sourceLine[] );

// deletes all character constants from sourceLine
void delCharConsts( char sourceLine[] );

// extracts all identifiers from sourceLine, and put them into the vector identifiers
void extractIdentifiers( char sourceLine[], vector< char * > &identifiers );

// stores all non-keyword strings in the vector identifiers into a text file
void store( vector< char * > &identifiers );

// returns true if and only if str is a C++ keyword
bool keyword( char str[] );

// returns true if and only if identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate( vector< char * > &identifiers, int pos );
//output
void output(char sourceLine[])
{
    for (size_t i = 0; i < strlen(sourceLine); i++)
        cout << sourceLine[i];
    cout << endl;
}

const char keywords[][ 20 ] = { "auto", "break", "case", "char", "const",
                                "continue", "default", "define","do", "double",
                                "else", "enum", "extern", "float", "for",
                                "goto", "if", "int", "long", "register",
                                "return", "short", "signed", "sizeof",
                                "static", "struct", "switch", "typedef",
                                "union", "unsigned", "void", "volatile",
                                "while", "bool", "catch", "class",
                                "const_cast", "delete", "dynamic_cast",
                                "explicit", "false", "friend", "inline",
                                "mutable", "namespace", "new", "operator",
                                "private", "protected", "public",
                                "reinterpret_cast", "static_cast", "template",
                                "this", "throw", "true", "try", "typeid",
                                "typename", "using", "virtual", "include" };

int main()
{
   vector< char * > program;

   // reads in a C++ program from a cpp file, and put it to the vector program
   load( program );

   vector< char * > identifiers;
   for( size_t i = 0; i < program.size(); i++ )
   {
      delComment( program[ i ] ); // deletes the comment beginning with "//" from program[ i ]

      delStrConsts( program[ i ] ); // deletes all string constants from program[ i ]
      delCharConsts( program[ i ] ); // deletes all character constants from program[ i ]
      if( strcmp( program[ i ], "" ) != 0 )
         extractIdentifiers( program[ i ], identifiers );
         // extracts all identifiers from program[ i ], and put them into the vector identifiers
   }

   // stores all non-keyword strings in the vector identifiers into a text file
   store( identifiers );

	system( "pause" );
}

void load( vector< char * > &program )
{

    ifstream inFile("test2.cpp", ios::in);
    if (!inFile)
        cout << "File could not be opened" << endl;
    else
    {
        char* temp = new char[100]();
        while (inFile.getline(temp, 100))
        {
            //allocate address
            program.push_back(temp);
            temp = new char[100]();
        }
        inFile.close();
    }

}

void delComment( char sourceLine[] )
{
   size_t length = strlen( sourceLine );
   if( length > 1 )
      for( size_t i = 0; i < length - 1; i++ )
         if( sourceLine[ i ] == '/' && sourceLine[ i + 1 ] == '/' )
         {
            sourceLine[ i ] = '\0';
            return;
         }
}

void delStrConsts(char sourceLine[])
{
    if (strlen(sourceLine) <= 1)
        return;
    vector<char> noStrConsts;
    int shouldWrite = 1;
    if (sourceLine[0] == '"')
        ++shouldWrite;
    else
        noStrConsts.push_back(sourceLine[0]);
    for (size_t i = 1; i < strlen(sourceLine); i++)
    {
        if (sourceLine[i] == '"' && sourceLine[i - 1] != '\\')
            ++shouldWrite;
        if (shouldWrite % 2 && sourceLine[i] != '"')
            noStrConsts.push_back(sourceLine[i]);
    }
    
    for (size_t i = 0; i < noStrConsts.size(); i++)
        sourceLine[i] = noStrConsts[i];
    sourceLine[noStrConsts.size()] = NULL;



}

void delCharConsts( char sourceLine[] )
{

    if (strlen(sourceLine) <= 1)
        return;
    char* noCharConsts = new char[strlen(sourceLine)+1]();
    size_t lengthOfnoChar = 0;
    int shouldWrite = 1;
    if (sourceLine[0] == '\'')
        ++shouldWrite;
    else
        noCharConsts[lengthOfnoChar++] = sourceLine[0];
    for (size_t i = 1; i < strlen(sourceLine); i++)
    {
        if (sourceLine[i] == '\'' && sourceLine[i - 1] != '\\')
            ++shouldWrite;
        if (shouldWrite % 2 && sourceLine[i] != '\'')
            noCharConsts[lengthOfnoChar++] = sourceLine[i];
    }
    strcpy_s(sourceLine, strlen(noCharConsts)+1, noCharConsts);
    delete[] noCharConsts;
}

void extractIdentifiers( char sourceLine[], vector< char * > &identifiers )
{
    char* str = new char[strlen(sourceLine) + 1]();
    size_t strlength = strlen(str);
    bool beginDigit = 0;
    for (size_t i = 0; i < strlen(sourceLine); i++)
    {
        if (strlength == 0 && (sourceLine[i] >= '0' && sourceLine[i] <= '9'))
            beginDigit = 1;
        else if (sourceLine[i] == ' ')
            beginDigit = 0;
        if (!beginDigit)
        {
            if (sourceLine[i] == '_' || sourceLine[i] >= 'a' && sourceLine[i] <= 'z' || sourceLine[i] >= 'A' && sourceLine[i] <= 'Z' || sourceLine[i] >= '0' && sourceLine[i] <= '9')
                str[strlength++] = sourceLine[i];
            else if (strlength)
            {
                identifiers.push_back(str);
                str = new char[strlen(sourceLine) + 1]();
                strlength = 0;
            }
        }
    }
    delete[] sourceLine;

}

void store( vector< char * > &identifiers )
{
    ofstream outFile("identifiers.txt", ios::out);
    for (size_t i = 0; i < identifiers.size(); i++)
        if (!keyword(identifiers[i]) && !duplicate(identifiers, static_cast<int>(i)))
            outFile << identifiers[i] << endl;

    for (size_t i = 0; i < identifiers.size(); i++)
        delete[] identifiers[i];
    outFile.close();
}

bool keyword( char str[] )
{
   size_t numKeywords = sizeof( keywords ) / 20;
   for( size_t i = 0; i < numKeywords; i++ )
      if( strcmp( keywords[ i ], str ) == 0 )
         return true;

   return false;
}

bool duplicate( vector< char * > &identifiers, int pos )
{
   for( int i = 0; i < pos; i++ )
      if( strcmp( identifiers[ i ], identifiers[ pos ] ) == 0 )
         return true;

   return false;
}