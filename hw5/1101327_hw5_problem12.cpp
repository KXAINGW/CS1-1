#include<iostream>
using namespace std;
int main()
{
	//program12 not finish
	float arr[100][100] = {};
	int n;
	cout << "Please enter n: ";
	cin >> n;
	cout << "Matrix: " << endl;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> arr[i][j];
	cout << endl;

	for (int i = 0; i < n ; i++)  //column
	{
		for (int j = i + 1; j < n; j++)  //row
		{
			if (arr[j][i] != 0)
			{
				if(arr[j][i]<=arr[i][i])
				{
					float temp = (arr[i][i] / arr[j][i]);
					for (int l = 0; i + l < n; l++) // multiply & subtratiion
						arr[i][i + l] += -temp * arr[j][i + l];


					for (int l = 0; l < n; l++) // swap
					{
						float temp = arr[j][l];
						arr[j][l] = arr[i][l];
						arr[i][l] = temp;
					}
					cout << "Swap row" << i + 1 << " & row" << j + 1 << endl;

					//for (int l = 0; l < n; l++) // multiply
					//{
					//	if (arr[j][l])
					//		arr[j][l] = -arr[j][l];
					//}
				}
				else
				{
					float temp = ( arr[j][i]/arr[i][i] );
					for (int l = 0; i + l < n; l++) // multiply & subtratiion
						arr[j][i + l] += -temp * arr[i][i + l];
					//for (int l = 0; l < n; l++) // multiply
					//{
					//	if (arr[j][l])
					//		arr[j][l] = -arr[j][l];
					//}
				}
			}

		}
	}

	cout << "Triangular matix:" << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << arr[i][j] << ' ';
		cout << endl;
	}


}