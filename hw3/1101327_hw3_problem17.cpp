#include<iostream>
#include<cmath>
using namespace std;
int main()
{
	//problem17
	int num,evenSum = 0,oddSum = 0;
	bool isprime = true;
	do
	{	
		cin >> num;
		if (num % 2 == 0)
			evenSum += num;
		else
			oddSum += num;
		isprime = true;
		for (int i{ 2 }; i <= sqrt(num); i++)
		{
			if (num % i == 0)
			{
				isprime =false;
				break;
			}
		}
	} while (!isprime);
	cout << "Sum of even numbers: " << evenSum << endl;
	cout << "Sum of odd numbers: " << oddSum << endl;
	return 0;
}