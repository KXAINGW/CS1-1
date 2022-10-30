#include<iostream>
using namespace std;
int main()
{
	//problem6
	int nums[100][100], temp;
	cout << "Please enter 4*4 matrix: " << endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			cin >> nums[i][j];
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = i + 1; j < 4; j++)
		{
			temp = nums[j][i];
			nums[j][i] = nums[i][j];
			nums[i][j] = temp;
		}

	}

	cout << "Transpose martix: " << endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			cout << nums[i][j] << ' ';
		cout << endl;
	}
	return 0;
}