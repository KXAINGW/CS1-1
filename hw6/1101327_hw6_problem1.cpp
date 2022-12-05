#include<iostream>
#include<cstring>
using namespace std;
int main()
{
	//program 1
	char arr[100];
	cout << "Input string: ";
	cin >> arr;
	for (size_t i = 0; i < strlen(arr); i++)
		cout << arr[i] << ':' << static_cast<int>(arr[i]) << ' ';
	cout << endl;
	return 0;
}