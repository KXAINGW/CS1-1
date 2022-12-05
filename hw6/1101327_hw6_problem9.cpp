#include<iostream>
#include<string>
#include<vector>
using namespace std;
int main()
{
	//program9
	string str;
	vector<string>str2;
	string temp = "";
	cout << "Input string: ";
	getline(cin, str);
	int shouldWrite = 1;
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == ' ' || str[i] == '\"')
			shouldWrite = 0;
		else
			shouldWrite = 1;
		if (shouldWrite)
			temp += str[i];
		else if (!shouldWrite && temp != "")
		{
			str2.push_back(temp);
			temp = "";
		}
	}
	if (temp != "")
		str2.push_back(temp);
	cout << '\"';
	for (size_t i = 0; i < str2.size(); i++)
	{
		if(i ==str2.size()-1)
			cout<<str2[i]<< '\"' << endl;
		else
			cout << str2[i] << ' ';
	}
	return 0;
}