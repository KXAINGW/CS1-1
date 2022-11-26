#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace::std;

 // reads in a C++ program from a cpp file, and put it to the vector program
void load( vector< string > &program );

// deletes the comment beginning with "//" from sourceLine if any
void delComment( string &sourceLine );

// deletes all string constants from sourceLine
void delStrConsts( string &sourceLine );

// deletes all character constants from sourceLine
void delCharConsts( string &sourceLine );

// extracts all identifiers from sourceLine, and put them into the vector identifiers
void extractIdentifiers( string &sourceLine, vector< string > &identifiers );

// stores all non-keyword strings in the vector identifiers into a text file
void store( vector< string > &identifiers );

// return true if and only if "str" is a C++ keyword
bool keyword( string str );

// returns true if and only if identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate( vector< string > &identifiers, int pos );

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
   vector< string > program;

   // reads in a C++ program from a cpp file, and put it to the vector program
   load( program );

   vector< string > identifiers;
   string null;

   for( size_t i = 0; i < program.size(); i++ )
   {
      delComment( program[ i ] ); // deletes the comment beginning with "//" from program[ i ]
      delStrConsts( program[ i ] ); // deletes all string constants from program[ i ]
      delCharConsts( program[ i ] ); // deletes all character constants from program[ i ]

      if( program[ i ] != null )
         extractIdentifiers( program[ i ], identifiers );
         // extracts all identifiers from program[ i ], and put them into the vector identifiers
   }
   // stores all non-keyword strings in the vector identifiers into a text file
   store( identifiers );

	system( "pause" );
}

void load( vector< string > &program )
{
    ifstream inFile("test2.cpp", ios::in);
    if (!inFile)
        cout << "File could not be opened" << endl;
    else
    {
        string str;
        while (getline(inFile, str))
            program.push_back(str);
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
    if (sourceLine.size() <= 1)
        return;

    string noStrConsts = "";
    int shouldWrite = 1;
    if (sourceLine[0] == '"')
        ++shouldWrite;
    else
        noStrConsts.push_back(sourceLine[0]);

    for (size_t i = 1; i < sourceLine.size(); i++)
    {
        if (sourceLine[i] == '"' && sourceLine[i - 1] != '\\')
            ++shouldWrite;
        if (shouldWrite % 2 && sourceLine[i] != '\"')
            noStrConsts.push_back(sourceLine[i]);
    }
    sourceLine = noStrConsts;


}

void delCharConsts( string &sourceLine )
{
    if (sourceLine.size() <= 1)
        return;
    string noCharConsts = "";
    int shouldWrite = 1;
    if (sourceLine[0] == '\'')
        ++shouldWrite;
    else
        noCharConsts.push_back(sourceLine[0]);
    for (size_t i = 1; i < sourceLine.size(); i++)
    {
        if (sourceLine[i] == '\'' && sourceLine[i - 1] != '\\')
            ++shouldWrite;
        if (shouldWrite % 2 && sourceLine[i] != '\'')
            noCharConsts.push_back(sourceLine[i]);
    }
    sourceLine = noCharConsts;

}

void extractIdentifiers( string &sourceLine, vector< string > &identifiers )
{

    string str = "";
    bool beginDigit = 0;
    for (size_t i = 0; i < sourceLine.size(); i++)
    {
        if (str.size() == 0 && (sourceLine[i] >= '0' && sourceLine[i] <= '9'))
            beginDigit = 1;
        else if (sourceLine[i] == ' ')
            beginDigit = 0;
        if(!beginDigit)
        {
            if (sourceLine[i] == '_' || sourceLine[i] >= 'a' && sourceLine[i] <= 'z' || sourceLine[i] >= 'A' && sourceLine[i] <= 'Z' || sourceLine[i] >= '0' && sourceLine[i] <= '9')
                str.push_back(sourceLine[i]);
            else if (str.size())
            {
                identifiers.push_back(str);
                str = "";
            }
        }
            
    }

}

void store( vector< string > &identifiers )
{
    ofstream outFile("identifiers.txt", ios::out);
    for (size_t i = 0; i < identifiers.size(); i++)
        if (!keyword(identifiers[i]) && !duplicate(identifiers, static_cast<int>(i)))
            outFile << identifiers[i] << endl;
    outFile.close();


}

bool keyword( string str )
{
   size_t numKeywords = sizeof( keywords ) / 20;
   for( size_t i = 0; i < numKeywords; i++ )
      if( keywords[ i ] == str )
         return true;

   return false;
}

bool duplicate( vector< string > &identifiers, int pos )
{
   for( int i = 0; i < pos; i++ )
      if( identifiers[ i ] == identifiers[ pos ] )
         return true;

   return false;
}