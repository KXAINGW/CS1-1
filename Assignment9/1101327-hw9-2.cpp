#include <iostream>
#include <fstream>
#include <string>
using namespace::std;

// reads in a C++ program from a cpp file, and put it to the array program
void load( string *program, int &numLines );

// deletes the comment beginning with "//" from sourceLine if any
void delComment( string &sourceLine );

// deletes all string constants from sourceLine
void delStrConsts( string &sourceLine );

// deletes all character constants from sourceLine
void delCharConsts( string &sourceLine );

// extracts all identifiers from sourceLine, and put them into the array identifiers
void extractIdentifiers( string &sourceLine, string *identifiers, int &numIdentifiers );

// stores all non-keyword strings in the array identifiers into a text file
void store( string *identifiers, int numIdentifiers );

// return true if and only if "str" is a C++ keyword
bool keyword( string str );

// returns true if and only if identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate( string *identifiers, int pos );
const string keywords[] = { "auto", "break", "case", "char", "const",
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
   string *program = new string[ 500 ];
   int numLines = 0;

   // reads in a C++ program from a cpp file, and put it to the array program
   load( program, numLines );

   string *identifiers = new string[ 500 ];
   string null;
   int numIdentifiers = 0;

   for( int i = 0; i < numLines; i++ )
   {
      delComment( program[ i ] ); // deletes the comment beginning with "//" from program[ i ]
      delStrConsts( program[ i ] ); // deletes all string constants from program[ i ]
      delCharConsts( program[ i ] ); // deletes all character constants from program[ i ]

      if( program[ i ] != null )
         extractIdentifiers( program[ i ], identifiers, numIdentifiers );
         // extracts all identifiers from program[ i ], and put them into the array identifiers
   }
   delete[]program;
   // stores all non-keyword strings in the array identifiers into a text file
   store( identifiers, numIdentifiers );

	system( "pause" );
}

void load( string *program, int &numLines )
{
    ifstream inFile("test1.cpp", ios::in);
    if(!inFile)
        cout << "File could not be opened" << endl;
    else
    {
        while (getline(inFile, program[numLines]))
            ++numLines;
        inFile.close();
    }


}

void delComment( string &sourceLine )
{
   size_t length = sourceLine.size();
   if( length > 1 )
      for( size_t i = 0; i < length - 1; i++ )
         if( sourceLine[ i ] == '/' && sourceLine[ i + 1 ] == '/' )
         {
            sourceLine.erase( i, length );
            break;
         }
}

void delStrConsts( string &sourceLine )
{
    size_t length = sourceLine.size();
    if (length <= 1)
        return;

    string noStrConsts = "";
    int sholdWrite = 1;

    //取出不是StrConst的值放入noStrConsts 
    if (sourceLine[0] == '"')
        ++sholdWrite;
    else
        //*string can't not use push_back. should use -> push_back
        noStrConsts.push_back(sourceLine[0]);   //push_back equivalent to +=
    for (size_t i = 1; i < length; i++)
    {
        if (sourceLine[i] == '"' && sourceLine[i - 1] != '\\')
            ++sholdWrite;
        if (sholdWrite % 2 && sourceLine[i] != '"')
            noStrConsts.push_back(sourceLine[i]);
    }
    //copy
    sourceLine = noStrConsts;
    


}

void delCharConsts( string &sourceLine )
{
    size_t length = sourceLine.size();
    if (length <= 1)
        return;

    string noCharConsts = "";
    int shouldWrite = 1;
    if (sourceLine[0] == '\'')
        ++shouldWrite;
    else
        noCharConsts.push_back(sourceLine[0]);

    for (size_t i = 1; i < length; i++)
    {
        if (sourceLine[i] == '\'' && sourceLine[i - 1] != '\\')
            ++shouldWrite;
        if (shouldWrite % 2 && sourceLine[i] != '\'')
            noCharConsts.push_back(sourceLine[i]);
    }

    sourceLine = noCharConsts;


}

void extractIdentifiers( string &sourceLine, string *identifiers, int &numIdentifiers )
{
    size_t length = sourceLine.size();
    string str = "";
    bool beginDigit = 0;
    for (size_t i = 0; i < length; i++)
    {
        if (str.size() == 0 && (sourceLine[i] >= '0' && sourceLine[i] <= '9'))
            beginDigit = 1;
        else if (sourceLine[i] == ' ')
            beginDigit = 0;
        if (!beginDigit)
        {
            if (sourceLine[i] == '_' || sourceLine[i] >= 'a' && sourceLine[i] <= 'z' || sourceLine[i] >= 'A' && sourceLine[i] <= 'Z' || sourceLine[i] >= '0' && sourceLine[i] <= '9')
                str.push_back(sourceLine[i]);
            else if (str.size())
            {
                identifiers[numIdentifiers++] = str;
                str = "";
            }
        }
    }


}

void store( string *identifiers, int numIdentifiers )
{

    ofstream outFile("identifiers.txt", ios::out);
    for (size_t i = 0; i < numIdentifiers; i++)
        if (!keyword(identifiers[i]) && !duplicate(identifiers, i))
            outFile << identifiers[i] << endl;
    outFile.close();
    delete[]identifiers;
}

bool keyword( string str )
{
   const int numKeywords = sizeof( keywords ) / 20;
   for( int i = 0; i < numKeywords; i++ )
      if( keywords[ i ] == str )
         return true;

   return false;
}

bool duplicate( string *identifiers, int pos )
{
   for( int i = 0; i < pos; i++ )
      if( identifiers[ i ] == identifiers[ pos ] )
         return true;

   return false;
}