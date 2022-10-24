#include<iostream>
using namespace std;
int main()
{
	//problem4
	int nums[100] = {};
	int n;
	cin >> n;
	cin >> nums[0];
	cout << nums[0] << endl;
	for (int i{ 1 }; i < n; i++)
	{
		cin >> nums[i];
		cout << nums[i] << endl;
		if (nums[i - 1] > nums[i])
			i--;
	}
	for (int i{ 0 }; i < n; i++)
		cout << nums[i] << ' ';
	cout << endl;
	return 0;
}