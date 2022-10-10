#include<iostream>
using namespace std;
int main()
{
	//problem16
	int a, b, c;
	cout << "abc:";
	for (a = 1; a < 10; a++)
	{
		for (b = 1; b < 10; b++)
		{
			for (c = 1; c < 10; c++)
			{
				if (100 * a + 10 * b + c == a * a * a + b * b * b + c * c * c)
					cout << a << b << c << ' ';
			}
		}
	}
	cout << endl;
	return 0;
}