#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
bool isExist(string arr, int now)
{
	for (int i = 0; i < now; i++)
		if (arr[i] == arr[now])
			return 1;
	return 0;
}
int main()
{
	//program 4
	string arr;
	vector<char>ch;
	cout << "Input string: ";
	cin >> arr;
	for (size_t i = 0; i < arr.size(); i++)
		if (ch.end() == find(ch.begin(), ch.end(), arr[i]))
			ch.push_back(arr[i]);

	for (size_t i = 0; i < ch.size(); i++)
		cout << ch[i] << ':' << count(arr.begin(), arr.end(), ch[i])<<' ';
	cout << endl;

	//or
	//string arr;
	//cin >> arr;
	//int ch[100] = {};
	//for (int i = 0; i < arr.size(); i++)
	//	ch[static_cast<int>(arr[i])]++;
	//for (int i = 0; i < arr.size(); i++)
	//	if (!isExist(arr, i))
	//		cout << arr[i] << ':' << ch[static_cast<int>(arr[i])] << ' ';
	
	return 0;
}