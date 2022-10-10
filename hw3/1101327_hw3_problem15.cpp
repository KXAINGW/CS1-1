#include<iostream>
using namespace std;
int main()
{
	//problem15
	double n, s0 = 1, s1 = 0, s2 = 0,denominator;
	cin >> n;
	while (n)
	{
		s0 *= n;
		s1 += 1 / n;
		denominator = 1;
		for (int i{ 1 }; i <= n; i++)
			denominator *= i;
		s2 += 1 / denominator;
		n--;
	}
	cout << "S0: " << s0 << endl;
	cout << "S1: " << s1 << endl;
	cout << "S2: " << s2 << endl;
	return 0;

}