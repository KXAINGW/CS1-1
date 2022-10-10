#include<iostream>
using namespace std;
int main()
{
	//problem8
	double num, numerator = 1, denominator;
	cin >> num;
	cout << 1 << endl;
	for (int i{ 1 }; i <= num; i++)
	{
		cout << 1 << ' ';
		
		for (int j{ 1 }; j <= i; j++)
		{
			numerator = 1;
			denominator = 1;
			for (int k{ 1 }; k <= j; k++)
			{	
				numerator *= i-k+1;
				denominator *= k;	
			}
			cout << numerator / denominator << ' ';
		}
		cout << endl;
	}
	return 0;
}