// Polynomial division provided that the quotient and remainder have integer coefficients

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;
using std::ios;

// outputs the specified polynomial
void output( int coefficient[], int exponent[], int size );

// returns true if and only if the specified polynomial has at least a zero term
bool zeroTerms( int coefficient[], int size );

// returns true if and only if the specified polynomial is zero polynomial
bool isZero( int coefficient[], int size );

// returns true if and only if polynomial1 == polynomial2
bool equal( int coefficient1[], int exponent1[], int size1,
            int coefficient2[], int exponent2[], int size2 );

// polynomial1 = -polynomial2
void minus( int coefficient1[], int exponent1[], int &size1,
            int coefficient2[], int exponent2[], int size2 );

// addend += adder
void addition( int addendCoef[], int addendExpon[], int &addendSize,
               int adderCoef[], int adderExpon[], int adderSize );

// minuend -= subtrahend
void subtraction( int minuendCoef[], int minuendExpon[], int &minuendSize,
                  int subtrahendCoef[], int subtrahendExpon[], int subtrahendSize );

// product = multiplicand * multiplier
void multiplication( int multiplicandCoef[], int multiplicandExpon[], int multiplicandSize,
                     int multiplierCoef[], int multiplierExpon[], int multiplierSize,
                     int productCoef[], int productExpon[], int &productSize );

// quotient = dividend / divisor; remainder = dividend % divisor
// provided that dividendExpon[ dividendSize - 1 ] >= divisorExpon[ divisorSize - 1 ]
void division( int dividendCoef[], int dividendExpon[], int dividendSize,
               int divisorCoef[], int divisorExpon[], int divisorSize,
               int quotientCoef[], int quotientExpon[], int &quotientSize,
               int remainderCoef[], int remainderExpon[], int &remainderSize );

const int numTestCases = 200; // the number of test cases
const int arraySize = 20;

int main()
{
    //int a1[3] = { 3,2,1}; int a2[3] = { 0,2,3 }; int a3 = 3;
    //int b1[4] = { 1,1,1,1 }; int b2[4] = { 0,1,2,3}; int b3 = 4;
    ////次方由高到低會不一樣
    //addition(a1, a2, a3, b1, b2, b3);
    //output(a1, a2, a3);


   ifstream inFile( "Polynomials.dat", ios::in | ios::binary );

   if( !inFile )
   {
      cout << "File could not be opened" << endl;
      system( "pause" );
      exit( 1 );
   }

   int numErrors = numTestCases;
   for( int i = 0; i < numTestCases; i++ )
   {
      int dividendCoef[ arraySize ] = {};
      int dividendExpon[ arraySize ] = {};
      int divisorCoef[ arraySize ] = {};
      int divisorExpon[ arraySize ] = {};

      // input dividend and divisor from the file Polynomials.dat
      inFile.read( reinterpret_cast< char * >( dividendCoef ), 80 );
      inFile.read( reinterpret_cast< char * >( dividendExpon ), 80 );
      inFile.read( reinterpret_cast< char * >( divisorCoef ), 80 );
      inFile.read( reinterpret_cast< char * >( divisorExpon ), 80 );

      int dividendSize = arraySize;
      while( dividendSize > 1 && dividendCoef[ dividendSize - 1 ] == 0 )
         dividendSize--;

      int divisorSize = arraySize;
      while( divisorSize > 1 && divisorCoef[ divisorSize - 1 ] == 0 )
         divisorSize--;

      int quotientCoef[ arraySize ] = {};
      int quotientExpon[ arraySize ] = {};
      int remainderCoef[ arraySize ] = {};
      int remainderExpon[ arraySize ] = {};
      int quotientSize = 1;
      int remainderSize = 1;

      cout << "dividend:  ";
      output( dividendCoef, dividendExpon, dividendSize );

      cout << " divisor:  ";
      output( divisorCoef, divisorExpon, divisorSize );

      //debug addition
      //addition(dividendCoef, dividendExpon, dividendSize, divisorCoef, divisorExpon, divisorSize);
      //output(dividendCoef, dividendExpon, dividendSize);
      
      //debug multiplication !!有些數值會超出長度!!
      //int productCoef[arraySize] = {};
      //int productExpon[arraySize] = {};
      //int productSize = 1;
      //multiplication(dividendCoef, dividendExpon, dividendSize, divisorCoef, divisorExpon, divisorSize, productCoef, productExpon,productSize);
      //output(productCoef, productExpon, productSize);

      // quotient = dividend / divisor; remainder = dividend % divisor
      // thus, dividend == divisor * quotient + remainder
      division( dividendCoef, dividendExpon, dividendSize,
                divisorCoef, divisorExpon, divisorSize,
                quotientCoef, quotientExpon, quotientSize,
                remainderCoef, remainderExpon, remainderSize );

      cout << "quotient:  ";
      output( quotientCoef, quotientExpon, quotientSize );
      cout << endl;

      if( zeroTerms( quotientCoef, quotientSize ) )
         cout << "quotient has at least a zero term!\n";

      if( zeroTerms( remainderCoef, remainderSize ) )
         cout << "remainder has at least a zero term!\n";

      int bufferCoef[ arraySize ] = {};
      int bufferExpon[ arraySize ] = {};
      int bufferSize = 1;

      // buffer = divisor * quotient
      multiplication( divisorCoef, divisorExpon, divisorSize,
                      quotientCoef, quotientExpon, quotientSize,
                      bufferCoef, bufferExpon, bufferSize );

      if( zeroTerms( bufferCoef, bufferSize ) )
         cout << "buffer has at least a zero term!\n";

      // buffer = buffer + remainder = divisor * quotient + remainder
      addition( bufferCoef, bufferExpon, bufferSize,
                remainderCoef, remainderExpon, remainderSize );

      if( zeroTerms( bufferCoef, bufferSize ) )
         cout << "buffer has at least a zero term!\n";
      
      // if buffer != dividend, an error occurred!
      if( equal( bufferCoef, bufferExpon, bufferSize,
                 dividendCoef, dividendExpon, dividendSize ) )
         numErrors--;
   }

   inFile.close();

   cout << "There are " << numErrors << " errors!\n\n";

   system( "pause" );
}

// outputs the specified polynomial
void output( int coefficient[], int exponent[], int size )
{
   // the specified polynomial is zero polynomial
   if( isZero( coefficient, size ) )
      cout << 0;
   else
   {
      if( coefficient[ size - 1 ] < 0 )
         cout << "-" << -coefficient[ size - 1 ];
      else if( coefficient[ size - 1 ] > 0 )
         cout << coefficient[ size - 1 ];

      if( exponent[ size - 1 ] > 0 )
      {
         if( exponent[ size - 1 ] == 1 )
            cout << "x";
         else
            cout << "x^" << exponent[ size - 1 ];
      }

      for( int i = size - 2; i >= 0; i-- )
      {
         if( coefficient[ i ] < 0 )
            cout << " - " << -coefficient[ i ];
         else if( coefficient[ i ] > 0 )
            cout << " + " << coefficient[ i ];

         if( exponent[ i ] > 0 )
         {
            if( exponent[ i ] == 1 )
               cout << "x";
            else
               cout << "x^" << exponent[ i ];
         }
      }
   }

   cout << endl;
}

// returns true if and only if the specified polynomial has at least a zero term
bool zeroTerms( int coefficient[], int size )
{
   if( !isZero( coefficient, size ) )
      for( int i = 0; i < size; i++ )
         if( coefficient[ i ] == 0 )
            return true;

   return false;
}

// returns true if and only if the specified polynomial is zero polynomial
bool isZero( int coefficient[], int size )
{
   if( size == 1 && coefficient[ 0 ] == 0 )
      return true;
   return false;
}

// returns true if and only if polynomial1 == polynomial2
bool equal( int coefficient1[], int exponent1[], int size1,
            int coefficient2[], int exponent2[], int size2 )
{
    if (size1 != size2)
        return false;   

   for( int i = 0; i < size1; i++ )
      if( coefficient1[ i ] != coefficient2[ i ] || exponent1[ i ] != exponent2[ i ] )
         return false;

   return true;
}

// polynomial1 = -polynomial2
void minus( int coefficient1[], int exponent1[], int &size1,
            int coefficient2[], int exponent2[], int size2 )
{
   size1 = size2;
   for( int i = 0; i < size1; i++ )
   {
      coefficient1[ i ] = -coefficient2[ i ];
      exponent1[ i ] = exponent2[ i ];
   }
}

// addend += adder
void addition( int addendCoef[], int addendExpon[], int &addendSize,
               int adderCoef[], int adderExpon[], int adderSize )
{


   // if( adder == 0 )
   if( isZero( adderCoef, adderSize ) )
      return;

   // if( addend == 0 )
   if( isZero( addendCoef, addendSize ) )
   {
      // addend = adder
      addendSize = adderSize;
      for( int i = 0; i < addendSize; i++ )
      {
         addendCoef[ i ] = adderCoef[ i ];
         addendExpon[ i ] = adderExpon[ i ];
      }
      return;
   }

   int sumCoef[ arraySize ] = {};
   int sumExpon[ arraySize ] = {};
   int i = 0;
   int j = 0;
   int k = 0;
   //k處理addendSize(sumSize)
   while( i < addendSize && j < adderSize )
   {
       //處理少數 exponent,coefficient
       if (addendExpon[i] != adderExpon[j])
       {
           if (addendExpon[i] > adderExpon[j])
           {              
               sumCoef[k] += adderCoef[j];
               sumExpon[k] = adderExpon[j];
               k++;
               j++;
           }
           else
           {
               sumCoef[k] += addendCoef[i];
               sumExpon[k] = addendExpon[i];
               k++;
               i++;
           }
       }
       else
       {
           if (addendCoef[i] + adderCoef[j] != 0)
           {
               sumCoef[k] += addendCoef[i];
               sumCoef[k] += adderCoef[j];
               sumExpon[k] = addendExpon[i];
               k++;
               i++;
               j++;
           }
           else
               i++, j++;
       }
   }

   while( i < addendSize )
   {
       sumCoef[k] += addendCoef[i];
       sumExpon[k] = addendExpon[i];
       k++;
       i++;
   }

   while( j < adderSize )
   {
       sumCoef[k] += adderCoef[j];
       sumExpon[k] = adderExpon[j];
       k++;
       j++;
   }

   addendSize = k;
   for( int i = 0; i < addendSize; i++ ) // addend = sum
   {
      addendCoef[ i ] = sumCoef[ i ];
      addendExpon[ i ] = sumExpon[ i ];
   }

   if( zeroTerms( addendCoef, addendSize ) )
      cout << "addend has at least a zero term!\n";
}

// minuend -= subtrahend
void subtraction( int minuendCoef[], int minuendExpon[], int &minuendSize,
                  int subtrahendCoef[], int subtrahendExpon[], int subtrahendSize )
{
   // minuend == subtrahend
   if( equal( minuendCoef, minuendExpon, minuendSize, subtrahendCoef, subtrahendExpon, subtrahendSize ) )
   {
      minuendSize = 1;     // minuend = 0;
      minuendCoef[ 0 ] = 0;
      minuendExpon[ 0 ] = 0;
      return;
   }

   // buffer = 0
   int bufferCoef[ arraySize ] = {};
   int bufferExpon[ arraySize ] = {};
   int bufferSize = 1;

   // buffer = -subtrahend
   minus( bufferCoef, bufferExpon, bufferSize, subtrahendCoef, subtrahendExpon, subtrahendSize );

   // minuend = minuend + buffer = minuend - subtrahend
   addition( minuendCoef, minuendExpon, minuendSize, bufferCoef, bufferExpon, bufferSize );

   if( zeroTerms( minuendCoef, minuendSize ) )
      cout << "minuend has at least a zero term!\n";
}

// product = multiplicand * multiplier
void multiplication( int multiplicandCoef[], int multiplicandExpon[], int multiplicandSize,
                     int multiplierCoef[], int multiplierExpon[], int multiplierSize,
                     int productCoef[], int productExpon[], int &productSize )
{
   // product = 0;
   productSize = 1;
   productCoef[ 0 ] = 0;
   productExpon[ 0 ] = 0;
   int bufferCoef[ arraySize ] = {};
   int bufferExpon[ arraySize ] = {};
   int bufferSize = multiplicandSize;

   for (int i{ 0 }; i < multiplierSize; i++)
   {
       for (int j{ 0 }; j < multiplicandSize; j++)
       {
           bufferCoef[j] = multiplicandCoef[j] * multiplierCoef[i];
           bufferExpon[j] = multiplicandExpon[j] + multiplierExpon[i];
       }
       addition(productCoef, productExpon, productSize, bufferCoef, bufferExpon, bufferSize);
   }


   if( zeroTerms( productCoef, productSize ) )
      cout << "product has at least a zero term!\n";
}

// quotient = dividend / divisor; remainder = dividend % divisor
// provided that dividendExpon[ dividendSize - 1 ] >= divisorExpon[ divisorSize - 1 ]
void division( int dividendCoef[], int dividendExpon[], int dividendSize,
               int divisorCoef[], int divisorExpon[], int divisorSize,
               int quotientCoef[], int quotientExpon[], int &quotientSize,
               int remainderCoef[], int remainderExpon[], int &remainderSize )
{
   // if( dividend == 0 )
   if( isZero( dividendCoef, dividendSize ) )
   {
      // quotient = 0
      quotientSize = 1;
      quotientCoef[ 0 ] = 0;
      quotientExpon[ 0 ] = 0;

      // remainder = 0
      remainderSize = 1;
      remainderCoef[ 0 ] = 0;
      remainderExpon[ 0 ] = 0;
      return;
   }

   // remainder = dividend
   remainderSize = dividendSize;
   for( int i = 0; i < remainderSize; i++ )
   {
      remainderCoef[ i ] = dividendCoef[ i ];
      remainderExpon[ i ] = dividendExpon[ i ];
   }

   quotientSize = dividendExpon[ dividendSize - 1 ] - divisorExpon[ divisorSize - 1 ] + 1;
   for( int i = quotientSize - 1; i >= 0; i-- )
   {
       int monomialCoef[1] = {};
       int monomialExpon[1] = {};
       int monomialSize = 1;
       
       quotientCoef[i] = remainderCoef[remainderSize-1] / divisorCoef[divisorSize-1];
       quotientExpon[i] = remainderExpon[remainderSize-1] - divisorExpon[divisorSize-1];
       monomialCoef[0] = remainderCoef[remainderSize-1] / divisorCoef[divisorSize-1];
       monomialExpon[0] = remainderExpon[remainderSize-1] - divisorExpon[divisorSize-1];

       int bufferCoef[arraySize] = {};
       int bufferExpon[arraySize] = {};
       int bufferSize = divisorSize;
       multiplication(divisorCoef, divisorExpon, divisorSize, monomialCoef, monomialExpon, monomialSize, bufferCoef, bufferExpon, bufferSize);
       subtraction(remainderCoef, remainderExpon, remainderSize, bufferCoef, bufferExpon, bufferSize);
       //output(remainderCoef, remainderExpon, remainderSize);

       
       if (isZero(remainderCoef, remainderSize) || remainderExpon[remainderSize - 1] < divisorExpon[divisorSize - 1])
       {
           quotientSize -=i;
           for (int j{ 0 }; j< quotientSize; j++)
           {
               quotientCoef[j] = quotientCoef[j+i];
               quotientExpon[j] = quotientExpon[j+i];
           }
           return;
           
       }


       //int size = quotientSize;
       //if (isZero(remainderCoef, remainderSize) || remainderExpon[remainderSize - 1] < divisorExpon[divisorSize - 1])
       //{
       //    for (int n = 0; n <size - i; n++)
       //    {
       //        quotientCoef[n] = quotientCoef[n + i];
       //        quotientExpon[n] = quotientExpon[n + i];
       //    }
       //    quotientSize = size - i;
       //    return;
       //}
   }
}