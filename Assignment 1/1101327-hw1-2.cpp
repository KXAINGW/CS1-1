#include <iostream> // allows program to perform input and output
using namespace std; // program uses names from the std namespace

int main()
{
   int number1; // first integer read from user
   int number2; // second integer read from user
   int number3; // third integer read from user

   cout << "Enter three distinct integers: ";
   cin >> number1 >> number2 >> number3;
   cout << "These numbers in ascending order: ";
   
   if (number1 < number2 && number1 < number3)
   {
	   if (number2 < number3)
		   cout << number1 << ' ' << number2 << ' ' << number3;
	   else
		   cout << number1 << ' ' << number3 << ' ' << number2;
   }
   else if (number2 < number3 && number2 < number1)
   {
	   if (number1 < number3)
		   cout << number2 << ' ' << number1 << ' ' << number3;
	   else
		   cout << number2 << ' ' << number3 << ' ' << number1;
   }   
   else
   {
	   if (number1 < number2)
		   cout << number3 << ' ' << number1 << ' ' << number2;
	   else
		   cout << number3 << ' ' << number2 << ' ' << number1;
   }
   cout << '\n';
   return 0;
}