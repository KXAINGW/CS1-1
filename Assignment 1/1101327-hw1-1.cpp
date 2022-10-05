#include <iostream> // allows program to perform input and output
using namespace std; // program uses names from the std namespace

int main()
{
   int number1; // first integer read from user
   int number2; // second integer read from user
   int number3; // third integer read from user

   cout << "Enter three distinct integers: ";
   cin >> number1 >> number2 >> number3;
   cout << "Median is ";

   if (number1 > number2)
   {
	   if (number2 > number3)
		   cout << number2;
	   else
	   {
		   if (number3 > number1)
			   cout << number1;
		   else
			   cout << number3;
	   }
   }
   else
   {
	   /*if (number1 > number3) 
			cout<<number1;
	   else
	   {
		   if (number3 > number2)
			   cout << number2;
		   else
			   cout << number3;
	   }*/
		   
	   (number1 > number3) ? cout << number1 : (number3 > number2) ? cout << number2 : cout << number3;
   }
   cout<<'\n';
   return 0;
      
}