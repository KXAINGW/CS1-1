#include<iostream>
#include<string>
#include<vector>
#include<cctype>
using namespace std;
int main()
{
	//program11
	int n;
	cout << "Input n: ";
	cin >> n;		
	cin.ignore();
	while (n--)
	{
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
				temp[0] = toupper(temp[0]);
				str2.push_back(temp);
				temp = "";
			}
		}
		if (temp != "")
		{
			temp[0] = toupper(temp[0]);
			str2.push_back(temp);
		}
		for (size_t i = 0; i < str2.size(); i++)
				cout << str2[i] << ' ';
		cout << endl;
	}
	return 0;
}