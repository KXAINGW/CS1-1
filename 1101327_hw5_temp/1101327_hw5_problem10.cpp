#include<iostream>
using namespace std;
int main()
{
	//program10
	//int m, n;
	//cin >> m >> n;
	//int array1[100][100] = {}, array2[100][100] = {}, temp = 0;

	//for (int i = 0; i < m; i++)
	//	for (int j = 0; j < n; j++)
	//		cin >> array1[i][j];

	//for (int i = 0; i < m; i++)
	//	for (int j = 0; j < n; j++)
	//	{
	//		cin >> temp;
	//		array1[i][j] += temp;
	//	}
	//for (int i = 0; i < m; i++)
	//{
	//	for (int j = 0; j < n; j++)
	//		cout << array1[i][j] << ' ';
	//	cout << endl;
	//}
	//
	//program11
	//int arr1[100][100] = {}, arr2[100][100] = {}, arr3[100][100] = {};
	//int m, n, l; // l is level k
	//cin >> m >> l >> n;

	//for (int i = 0; i < m; i++)
	//	for (int j = 0; j < l; j++)
	//		cin >> arr1[i][j];
	//for (int i = 0; i < l; i++)
	//	for (int j = 0; j < n; j++)
	//		cin >> arr2[i][j];

	//for (int i = 0; i < m; i++)
	//{
	//	for (int j = 0; j < n; j++)
	//	{
	//		for (int k = 0; k < l; k++)
	//			arr3[i][j] += arr1[i][k] * arr2[k][j];
	//	}
	//}
	//for (int i = 0; i < m; i++)
	//{
	//	for (int j = 0; j < n; j++)
	//		cout << arr3[i][j] << ' ';
	//	cout << endl;
	//}

	//program12 not finish
	//float arr[100][100] = {};
	//int n;
	//cin >> n;

	//for (int i = 0; i < n; i++)
	//	for (int j = 0; j < n; j++)
	//		cin >> arr[i][j];

	//for(int i = 0; i < n - 1; i++)
	//	for(int j = i + 1; j < n; j++)
	//		if (arr[j][i] != 0)
	//		{
	//			float temp = (arr[i][i] / arr[j][i]);
	//			for (int l = 0; l < n; l++) // multiply
	//				arr[j][l] *= -temp;


	//			for (int l = 0; l < n; l++) // add
	//				arr[j][l] += arr[i][l];

	//			for (int l = 0; l < n; l++) // swap
	//			{	
	//				float temp = arr[j][l];
	//				arr[j][l] = arr[i][l];
	//				arr[i][l] = temp;
	//			}

	//			for (int l = 0; l < n; l++) // multiply
	//				arr[j][l] = -arr[j][l];

	//			for (int i = 0; i < n; i++) // output
	//			{
	//				for (int j = 0; j < n; j++)
	//					cout << arr[i][j] << ' ';
	//				cout << endl;
	//			}
	//		}

	//for (int i = 0; i < n; i++)
	//{
	//	for (int j = 0; j < n; j++)
	//		cout << arr[i][j] << ' ';
	//	cout << endl;
	//}


	//program13
	int arr1[100] = {}, arr2[100] = {}, arr3[100] = {}, n;
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> arr1[i];
	for (int i = 0; i < n; i++)
		cin >> arr2[i];
	for (int i = 0; i < n; i++)
		arr3[i] = arr1[i] + arr2[i];
	for(int i = 0; i < n; i++)
		cout << arr3[i] << ' ';
}
