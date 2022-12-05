#include<iostream>
#include<string>
#include<vector>
using namespace std;
int main()
{
	//program7
	// or use cin.peek()
	string str;
	vector<string>str2;
	cout << "Input string: ";
	getline(cin, str);
	string temp = "";
	for (size_t i = 0; i < str.size(); i++)
	{
		if(str[i]!=' ')
			temp += str[i];
		else
		{
			str2.push_back(temp);
			temp = "";
		}
	}
	str2.push_back(temp);
	for (int i = str2.size() - 1; i >= 0; i--)
		cout << str2[i] << ' ';
	cout << endl;
	return 0;
}