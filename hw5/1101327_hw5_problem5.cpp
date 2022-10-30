#include<iostream>
using namespace std;
int main()
{
	//problem5
	int nums1[100][100], num, sum1 = 0;
	int m, n;
	cout << "Input m rows: ";
	cin >> m;
	cout << "Input n colums: ";
	cin >> n;

	cout << "Matrix:" << endl;
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			cout << '(' << i << ',' << j << "): ";
			cin >> nums1[i][j];
		}
	}

	cout << endl << endl;
	cout << "Matrix:" << endl;
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
			cout << nums1[i][j] << ' ';
		cout << endl;
	}
	cout << "Please enter integer: ";
	cin >> num;
	cout << "Matrix:" << endl;
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (nums1[i][j] == num)
			{
				sum1++;
				cout << "Location: " << i << ' ' << j << endl;
			}

		}
	}
	if (sum1)
		cout << "How many elements: " << sum1 << endl;
	else
		cout << "There is no element of the matrix matches this number" << endl;
	return 0;

}