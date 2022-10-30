#include<iostream>
using namespace std;
int main()
{
	//program11
	int arr1[100][100] = {}, arr2[100][100] = {}, arr3[100][100] = {};
	int m, n, k; 
	cout << "Please enter m & k & n: ";
	cin >> m >> k >> n;

	cout << "Matrix_A: " << endl;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < k; j++)
			cin >> arr1[i][j];

	cout << "Matrix_B: " << endl;
	for (int i = 0; i < k; i++)
		for (int j = 0; j < n; j++)
			cin >> arr2[i][j];


	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int l = 0; l < k; l++)
				arr3[i][j] += arr1[i][l] * arr2[l][j];
		}
	}

	cout << "Matrix_C:" << endl;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			cout << arr3[i][j] << ' ';
		cout << endl;
	}

	return 0;


}