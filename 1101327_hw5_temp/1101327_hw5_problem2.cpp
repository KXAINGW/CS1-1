#include<iostream>
using namespace std;
int main()
{
	//problem2
	int nums[100], n = 0;
	cin >> n;
	for (int i{ 0 }; i < n; i++)
		cin >> nums[i];

	int temp;
	for (int i{ n - 1 }; i > 0; i--)
	{
		for (int j{ 0 }; j < i; j++)
		{
			if (nums[j] > nums[j + 1])
			{
				temp = nums[j];
				nums[j] = nums[j + 1];
				nums[j + 1] = temp;
			}
		}
	}


	for (int i{ 0 }; i < n; i++)
	{
		for (int j{ i + 1 }; j < n; j++)
		{
			if (nums[i] == nums[j])
			{
				for (int k{ j }; k < n; k++)
					nums[k] = nums[k + 1];
				n--;
				j--;
			}

		}
	}


	for (int i{ 0 }; i < n; i++)
		cout << nums[i];
	cout << endl;
	return 0;
}