#include<iostream>
using namespace std;
int main()
{
	//problem12
	double n = 2, s, sum = 0.5;
	cin >> s;
	while (sum < s)
	{
		n++;
		sum += 1 / n;		
	}
	if (s <= 0.5)
		cout << "Too small" << endl;
	else
		cout << --n << endl;
	
}