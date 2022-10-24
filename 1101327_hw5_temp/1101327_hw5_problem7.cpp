#include<iostream>
#include<cmath>
using namespace std;
int main()
{
	//problem7
	int nums[100] = {};
	int n,oddNum = 0,evenNum = 0;
	int primeNumIndex = 0, nprimeNumIndex = 0;
	int primeNum[100] = {};
	int nprimeNum[100] = {};
	cin >> n;
	for (int i{ 0 }; i < n; i++)
	{
		cin >> nums[i];
		if (nums[i] % 2 == 0)
			evenNum++;
		else
			oddNum++;

		bool isprime = true;
		for (int j{ 2 }; j <= sqrt(nums[i]); j++)
		{
			if (nums[i] % j == 0)
			{
				isprime = false;
				break;
			}
		}
		if (isprime && nums[i] != 1)
		{
			primeNum[primeNumIndex] = nums[i];
			primeNumIndex++;
		}
		else
		{
			nprimeNum[nprimeNumIndex] = nums[i];
			nprimeNumIndex++;
		}
	}
	cout << "How many odd numbers: " << oddNum << endl;
	cout << "How many even numbers: " << evenNum << endl;
	cout << "Prime numbers: ";
	for (int i{ 0 }; i < primeNumIndex; i++)
		cout << primeNum[i] << ' ';
	cout << endl;
	cout << "Numbers that are not prime: ";
	for (int i{ 0 }; i < nprimeNumIndex; i++)
		cout << nprimeNum[i] << ' ';
	cout << endl;

}