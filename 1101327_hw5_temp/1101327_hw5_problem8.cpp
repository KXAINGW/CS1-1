#include<iostream>
using namespace std;
int main()
{
	//problem8
	int nums[100] = {};
	int n, sum = 0;;
	cin >> n;
	for (int i{ 0 }; i < n; i++)
	{
		cin >> nums[i];
		if (nums[i] < 0)
			sum += nums[i] * nums[i];
	}
	cout << "The sum of squares of negative numbers: " << sum << endl;
	return 0;
}