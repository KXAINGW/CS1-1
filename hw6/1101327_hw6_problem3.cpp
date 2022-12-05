#include<iostream>
#include<cstring>
using namespace std;
int main()
{
	//program 3
	char arr[100];
	cout << "Input string: ";
	cin.getline(arr, 100);
	int middle = strlen(arr) / 2;
	bool isSymmetric = 1;
	for (int i = 0; i < middle; i++)
	{
		if (arr[i] != arr[strlen(arr) - i - 1])
		{
			isSymmetric = 0;
			break;
		}
	}
	if (isSymmetric)
		cout << "The sequence " << arr << " is a symmetric string." << endl;
	else
		cout << "The sequence " << arr << " is not a symmetric string." << endl;
	return 0;
}