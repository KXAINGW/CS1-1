#include<iostream>
using namespace std;
int main()
{
	//problem11
	double k, n;
	cin >> n;
	k = 0;
	while (pow(2, k) < n)
		k++;
	cout << k << endl;
	return 0;
}