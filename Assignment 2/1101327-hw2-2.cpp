#include<iostream>
using namespace std;

// UVA 11498
int main()
{
	int k, x, y, N, M;
	while (cin >> k, k)
	{
		cin >> x >> y;
		for (int i = 0; i < k; i++)
		{
			cin >> N >> M;
			if (N == x || M == y)
				cout << "divisa" << endl;
			else if (N > x && M > y)
				cout << "NE" << endl;
			else if (N<x && M>y)
				cout << "NO" << endl;
			else if (N < x && M < y)
				cout << "SO" << endl;
			else
				cout << "SE" << endl;
		}
	}
	return 0;
}