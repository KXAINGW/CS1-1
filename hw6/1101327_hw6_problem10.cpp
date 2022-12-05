#include<iostream>
#include<string>
#include<vector>
#include<cctype>
using namespace std;
int main()
{
	//program10
	string str;
	vector<string>lwr;
	vector<string>upr;
	string lwrtemp = "";
	string uprtemp = "";
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
		{
			lwrtemp += tolower(str[i]);
			uprtemp += toupper(str[i]);
		}
		else if (!shouldWrite && lwrtemp != "")
		{
			lwr.push_back(lwrtemp);
			lwrtemp = "";
			upr.push_back(uprtemp);
			uprtemp = "";
		}
	}


	if (lwrtemp != "")
		lwr.push_back(lwrtemp);
	//transform(begin(str2), end(str2), begin(str2), toupper);
	cout << '\"';
	for (size_t i = 0; i < lwr.size(); i++)
	{
		if (i == lwr.size() - 1)
			cout << lwr[i] << '\"' << endl;
		else
			cout << lwr[i] << ' ';
	}

	if (uprtemp != "")
		upr.push_back(uprtemp);
	cout << '\"';
	for (size_t i = 0; i < upr.size(); i++)
	{
		if (i == upr.size() - 1)
			cout << upr[i] << '\"' << endl;
		else
			cout << upr[i] << ' ';
	}

	return 0;
}