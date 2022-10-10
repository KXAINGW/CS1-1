#include<iostream>
using namespace std;
int main()
{
	//problem20
	int num, factor =2;
	cin >> num;
	while (num > 1)
	{
		if (num % factor == 0)
		{
			cout << factor;
			num /= factor;	
			if (num !=1)
				cout << '*';
		}
		else
			factor++;

	}
	cout << endl;
	return 0;
}