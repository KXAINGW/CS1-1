#include<iostream>
using namespace std;
int main()
{
	//problem9
	int n, nums[100];
	cout << "Please enter n: ";
	cin >> n;
	for (int i{ 0 }; i < n; i++)
		cin >> nums[i];
	int temp;
	for (int i{ 0 }; i < n / 2; i++)
	{
		temp = nums[i];
		nums[i] = nums[n - i - 1];
		nums[n - i - 1] = temp;
	}
	cout << "reverse into: ";
	for (int i{ 0 }; i < n; i++)
		cout << nums[i] << ' ';
	cout << endl;
}