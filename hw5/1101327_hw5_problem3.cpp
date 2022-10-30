#include<iostream>
using namespace std;
int main()
{
	//problem3
	int nums[100], n,max,min,sum = 0;
	cout << "Please enter n: ";
	cin >> n;
	for (int i{ 0 }; i < n; i++)
	{
		cin >> nums[i];
		if (i == 0)
		{
			max = nums[0];
			min = nums[0];
		}
		else
		{
			if (max < nums[i])
				max = nums[i];
			if (min > nums[i])
				min = nums[i];
		}
		sum += nums[i];
	}
	cout << "The largest element of the array: " << max << endl;
	cout << "The smallest element of the array: " << min << endl;
	cout << "The sum of the elements in the array: " << sum << endl;
	return 0;
}