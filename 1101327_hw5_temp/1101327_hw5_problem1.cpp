#include<iostream>
using namespace std;
int main()
{
	//problem1
	int nums[100],n =0;
	cin >> n;
	for (int i{ 0 }; i < n; i++)
		cin >> nums[i];

	int temp;
	for (int i{ n-1 }; i > 0; i--)
	{
		for (int j{ 0 }; j < i ; j++)
		{
			if (nums[j] <  nums[j + 1])
			{
				temp = nums[j];
				nums[j] = nums[j + 1];
				nums[j + 1] = temp;
			}
		}
	}

	for (int i{ 0 }; i < n; i++)
		cout << nums[i];
	cout << endl;
	return 0;
}