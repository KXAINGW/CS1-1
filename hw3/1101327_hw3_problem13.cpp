#include<iostream>
#include<iomanip>
using namespace std;
int main()
{
	//problem13
	for (int i{ 10 }; i <= 100; i += 10)
	{
		for (int j{ i - 9 }; j <= i; j++)
			cout << setw(3)<< j << ' ';
		cout << endl;
	}
	return 0;
}