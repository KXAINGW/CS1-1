#include<iostream>
using namespace std;
int main()
{
	//program10
	int m, n;
	cout << "Please enter m & n: ";
	cin >> m >> n;
	int array1[100][100] = {}, array2[100][100] = {}, temp = 0;

	cout << "Matrix_A:" << endl;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			cin >> array1[i][j];

	cout << "Matrix_B:" << endl;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
		{
			cin >> temp;
			array1[i][j] += temp;
		}

	cout << "Matrix_C:" << endl;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			cout << array1[i][j] << ' ';
		cout << endl;
	}
	
	return 0;

}
