#include<iostream>
#include<cstring>
using namespace std;
int main()
{
	//program 2
	char arr[100];
	cout << "Input string: ";
	cin.getline(arr, 100);
	for (int i = strlen(arr) - 1; i >= 0; i--)
		cout << arr[i];
	cout << endl;
	return 0;
}