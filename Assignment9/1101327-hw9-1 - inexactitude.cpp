#include <iostream>
#include <fstream>
using namespace::std;

// reads in a C++ program from a cpp file, and put it to the array program
void load( char( *program )[ 100 ], int &numLines );

// deletes the comment beginning with "//" from sourceLine if any
void delComment( char sourceLine[] );

// deletes all string constants from sourceLine
void delStrConsts( char sourceLine[] );

// deletes all character constants from sourceLine
void delCharConsts( char sourceLine[] );

// extracts all identifiers from sourceLine, and put them into the array identifiers
void extractIdentifiers( char sourceLine[], char identifiers[][ 32 ], int &numIdentifiers );

// stores all non-keyword strings in the array identifiers into a text file
void store( char ( *identifiers )[ 32 ], int numIdentifiers );

// returns true if and only if str is a C++ keyword
bool keyword( char str[] );

// returns true if and only if identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate( char ( *identifiers )[ 32 ], int pos );

//output all element
void output(char array[][100], int length)
{
    for (int i = 0; i < length; i++)
        cout << array[i] << endl;
}
void output2(char array[][32], int length)
{
    for (int i = 0; i < length; i++)
        cout << array[i] << endl;
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
   char ( *program )[ 100 ] = new char[ 500 ][ 100 ];
   int numLines = 0;

   // reads in a C++ program from a cpp file, and put it to the array program
   load( program, numLines );

   char ( *identifiers )[ 32 ] = new char[ 500 ][ 32 ];
   int numIdentifiers = 0;

   for( int i = 0; i < numLines; i++ )
   {
      delComment( program[ i ] ); // deletes the comment beginning with "//" from program[ i ]
      delStrConsts( program[ i ] ); // deletes all string constants from program[ i ]
      delCharConsts( program[ i ] ); // deletes all character constants from program[ i ]
     
      if( strcmp( program[ i ], "" ) != 0 )
         extractIdentifiers( program[ i ], identifiers, numIdentifiers );
         // extracts all identifiers from program[ i ], and put them into the array identifiers
   }
   //output(program, numLines);
   //output2(identifiers, numIdentifiers);
   
   //delete program
   delete[] program;
   // stores all non-keyword strings in the array identifiers into a text file
   store( identifiers, numIdentifiers );

	system( "pause" );
}

void load( char( *program )[ 100 ], int &numLines )
{

    ifstream inFile("test2.cpp", ios::in);
    if (!inFile)
        cout << "File could not be opened" << endl;
    else
    {
        while (inFile.getline( program[numLines],100,'\n'))
            ++numLines;

            //cout << "good(): " << boolalpha << inFile.good() << endl;
            //cout << "fail(): " << boolalpha << inFile.fail() << endl;
            //cout << "program[numLines]: " << program[numLines] << endl;

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

void delStrConsts( char sourceLine[] )
{
    size_t length = strlen(sourceLine);
    if (length <= 1)
        return;

    char* noStrConsts = new char[length+1]();  // length+1 -> '\0'
    size_t lengthOfnoStr = 0;
    int shouldWrite = 1;

    //取出不是StrConst的值放入noStrConsts
    //judge sourceLine[0]
    if (sourceLine[0] == '"')
        ++shouldWrite;
    else
        noStrConsts[lengthOfnoStr++] = sourceLine[0];
    //judge sourceLine[1~length-1]
    for (size_t i = 1; i < length ; i++)
    {
        if (sourceLine[i] == '"' && sourceLine[i-1]!='\\')
            ++shouldWrite;
        if (shouldWrite % 2 && sourceLine[i]!='"')
            noStrConsts[lengthOfnoStr++] = sourceLine[i];
    }

    //sourceLine = noStrConsts
    strcpy_s(sourceLine, lengthOfnoStr + 1, noStrConsts);

   /*
   for (size_t i = 0; i < lenghtOfnoStr; i++)
        sourceLine[i] = noStrConsts[i];
   ourceLine[lenghtOfnoStr] = '\0';
   */

    //strcpy_s(sourceLine, noStrConsts); error?
    //strcpy_s(sourceLine, strlen(noStrConsts)+1, noStrConsts);
    delete[] noStrConsts;
}

void delCharConsts( char sourceLine[] )
{
    size_t length = strlen(sourceLine);
    if (length <= 1)
        return;

    char* noCharConsts = new char[length + 1]();
    size_t lengthOfnoChar = 0;
    int shouldWrite = 1;

    //judge sourceLine[0]
    if (sourceLine[0] == '\'')
        ++shouldWrite;
    else
        noCharConsts[lengthOfnoChar++] = sourceLine[0];
    //judge sourceLine[1~length-1]
    for (size_t i = 1; i < length; i++)
    {
        if (sourceLine[i] == '\'' && sourceLine[i - 1] != '\\')
            ++shouldWrite;
        if (shouldWrite % 2 && sourceLine[i] != '\'')
            noCharConsts[lengthOfnoChar++] = sourceLine[i];
    }

    //sourceLine = noCharConsts
    strcpy_s(sourceLine, strlen(noCharConsts) + 1, noCharConsts);

   /* 
   for (size_t i = 0; i < lengthOfnoChar; i++)
        sourceLine[i] = noCharConsts[i];
    sourceLine[lengthOfnoChar] = '\0';
    */
    delete[] noCharConsts;

}

void extractIdentifiers( char sourceLine[], char identifiers[][ 32 ], int &numIdentifiers )
{
    size_t length = strlen(sourceLine);
    size_t strlength = 0;
    char* str = new char[32];
    //write identifier on str  & write str on identifiers[]
    for (size_t i = 0; i < length; i++)
    {
        if (sourceLine[i] == '_' || sourceLine[i] >= 'a' && sourceLine[i] <= 'z' || sourceLine[i] >= 'A' && sourceLine[i] <= 'Z' || sourceLine[i] >= '0' && sourceLine[i] <= '9' && strlength != 0)
            str[strlength++] = sourceLine[i];
        else if (strlength)
        {
            str[strlength] = '\0';
            //only need to put identifier into identifiers
            //judge keyword -> store function
            /*
            if (!keyword(str))
                    strcpy_s(identifiers[numIdentifiers++], str);
            */
            strcpy_s(identifiers[numIdentifiers++], str);
            delete[] str;
            str = new char[32]();
            strlength = 0;
        }
    }
}

void store( char ( *identifiers )[ 32 ], int numIdentifiers )
{
    ofstream outFile("identifiers.txt", ios::out);
    for (int i = 0; i < numIdentifiers; i++)
        if (!keyword(identifiers[i]) && !duplicate(identifiers, i))
            outFile << identifiers[i] << endl;
;
    outFile.close();      
    //delete identifiers
    delete[] identifiers;
}

bool keyword( char str[] )
{
   size_t numKeywords = sizeof( keywords ) / 20;
   for( size_t i = 0; i < numKeywords; i++ )
      if( strcmp( keywords[ i ], str ) == 0 )
         return true;

   return false;
}

bool duplicate( char ( *identifiers )[ 32 ], int pos )
{
   for( int i = 0; i < pos; i++ )
      if( strcmp( identifiers[ i ], identifiers[ pos ] ) == 0 )
         return true;

   return false;
}