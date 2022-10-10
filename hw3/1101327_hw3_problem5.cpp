#include<iostream>
#include<iomanip>
using namespace std;
int main()
{
	//problem 5
	int m, n, index = 0;
	cin >> m >> n;
	while (m--)
	{
		for (int i{ 0 };i<n;i++)
			cout <<setw(3) << ++index << ' ';
		cout << endl;
	}
	cout << endl;
	return 0;
}