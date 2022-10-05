#include <iostream>
using namespace std;

int main()
{
   int year;

   cout << "Enter a year ( 1583-3000 ): ";
   cin >> year;
   
   if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
	   cout << "Year " << year << " is a leap year.\n";
   else
	   cout<< "Year " << year << " is a common year.\n";
   return 0;
}