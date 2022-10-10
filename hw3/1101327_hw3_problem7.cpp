#include<iostream>
using namespace std;
int main()
{
	//problem7
	int n, m;
	cin >> n >> m;
	for (int i{ 1 }; i <= n; i++)
	{
		if (i != 1 && i != n)
		{
			cout << '*' << ' ';
			for (int j{ 2 }; j < m; j++)
				cout << "  ";
			cout << '*';
		}
		else
			for (int j{ 0 }; j < m; j++)
				cout << '*' <<' ';
		cout << endl;
	}
	return 0;
}