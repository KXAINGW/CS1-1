// Exercise 4.18 Solution: ex04_18.cpp
// Display decimal, binary, octal and hexadecimal numbers.
#include <iostream>
using namespace std; 

int main()
{
   int number; // a positive integer less than 32
   int bit1;   // the rightmost bit of number
   int bit2;
   int bit3;
   int bit4;
   int bit5;   // the leftmost bit of number

   cout << "Enter a positive integer less than 32: ";
   cin >> number;
   cout << "The binary equivalent of " << number << " is ";

   bit1 = 0, bit2 = 0, bit3 = 0, bit4 = 0, bit5 = 0;
   if (number >= 16)
   {
	   bit5 += 1;
	   number -= 16;
   }
   if (number >= 8)
   {
	   bit4 += 1;
	   number -= 8;
   }if (number >= 4)
   {
	   bit3+= 1;
	   number -= 4;
   }if (number >= 2)
   {
	   bit2 += 1;
	   number -= 2;
	   bit1 += number;
   }
   cout << bit5 << bit4 << bit3 << bit2 << bit1 << '\n';
   return 0;

}