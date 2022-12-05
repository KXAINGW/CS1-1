#include<iostream>
#include<string>
#include<vector>
using namespace std;
int main()
{
	//program 5
	string str;
	cout << "Input string: ";
	getline(cin, str);
	vector<string>arr;;
	string temp = "";
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] != ' ')
			temp += str[i];
		else
		{
			arr.push_back(temp);
			temp = "";
		}

	}
	arr.push_back(temp);
	cout << endl;

	cout << "a) " << arr[0] << endl << "   ";
	for (size_t i = 1; i < arr.size(); i++)
		cout << arr[i] << ' ';
	cout << endl;
	cout << endl;

	cout << "b) " << arr[arr.size() - 1] << endl << "   ";
	for (size_t i = 0; i < arr.size() - 1; i++)
		cout << arr[i] << ' ';
	cout << endl;
	return 0;


}