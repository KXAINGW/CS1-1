#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
using namespace std;
bool cmp(string a,string b)
{
	return a > b;
}
int main()
{
	int n;
	cout << "Input n: ";
	cin >> n;
	cin.ignore();
	vector<string>name;
	for (int i = 0; i < n; i++)
	{
		string str;
		getline(cin, str, '\n');
		name.push_back(str);
	}
	sort(name.begin(), name.end(), cmp);
	//reverse(name.begin(), name.end());
	for (size_t i = 0; i < name.size(); i++)
		cout << name[i] << endl;
	return 0;
}