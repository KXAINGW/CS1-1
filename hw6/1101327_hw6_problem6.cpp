#include<iostream>
#include<string>
using namespace std;
int main()
{
	//program6
	string str;
	cout << "Input string: ";
	getline(cin, str);
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] != ' ')
			cout << str[i];
		else
			cout << endl;
	}
	cout << endl;
	return 0;
}