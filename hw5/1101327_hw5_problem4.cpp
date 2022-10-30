#include<iostream>
using namespace std;
int main()
{
	//problem4
	int nums[100];
	int n;
	cout << "Please enter n: ";
	cin >> n;
	cout << "Input element #1: ";
	cin >> nums[0];
	cout << nums[0] << endl;
	for (int i = 1; i < n; i++)
	{
		cout << "Input element #" << i + 1 << ": ";
		cin >> nums[i];
		cout << nums[i] << endl;
		if (nums[i - 1] > nums[i])
		{
			cout << "Incorrect output: " << nums[i] << endl;
			i--;
		}
	}
	for (int i = 0; i < n; i++)
		cout << nums[i] << ' ';
	cout << endl;

	int num;
	cout << "Please enter number: ";
	cin >> num;
	int k = 0;
	while (nums[k] < num)
		k++;
	for (int i{ n - 1 }; i >= k; i--)
		nums[i + 1] = nums[i];
	n++;
	nums[k] = num;
	for (int i = 0; i < n; i++)
		cout << nums[i] << ' ';

	cout << endl;
	return 0;
}