#include<iostream>
using namespace std;
int main()
{
	//problem6
	int matrix[4][4] = { {1,2,3,4},
					   {2,5,5,8},
					   {9,4,2,0},
					   {1,5,8,6} };
	int temp;
	for (int i{ 0 }; i <4; i++)
	{
		for (int j{ i }; j < 4; j++)
		{
			temp = matrix[i][j];
			matrix[i][j] = matrix[j][i];
			matrix[j][i] = temp;
		}
	}
	for (int i{ 0 }; i < 4; i++)
	{
		for (int j{ 0 }; j < 4; j++)
			cout << matrix[i][j] << ' ';
		cout << endl;
	}
	return 0;
}