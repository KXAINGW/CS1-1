#include<iostream>
#include<iomanip>
using namespace std;
int main()
{
	//problem19
	int n,num = 3;
	bool isprime;
	cin >> n;
	cout << 2 << ' ';
	while (num<=n)
	{
		isprime = true;
		for (int i{ 2 }; i <= sqrt(num); i++)
		{
			if (num % i == 0)
			{
				isprime = false;
				break;
			}
		}
		if (isprime)
			cout << num << ' ';
		num++;
	}
	cout << endl;
	return 0;
}