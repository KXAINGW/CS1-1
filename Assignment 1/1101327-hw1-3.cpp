#include <iostream>
using namespace std;

int main()
{
   int number;

   cout << "Enter a 5-digit positive integer: ";
   cin >> number;
   cout << "The digits in the reverse order : ";

   cout << number % 10 << number % 100 / 10 << number % 1000 / 100 << number % 10000 / 1000 << number / 10000 << '\n';
   return 0;



}