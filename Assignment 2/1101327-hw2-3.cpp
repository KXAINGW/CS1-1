#include<iostream>
using namespace std;

//UVA 11764
int main()
{
	int a;
	cin >> a;
	const int b = a;
	int k, walls[51] = {}, high, low, walls_num;
	cin >> k;
	int k_num = 0;

	while (k--)
	{
		cin >> walls_num;
		high = 0, low = 0;
		for (int i{ 0 }; i < walls_num; i++)
			cin >> walls[i];

		for (int i{ 0 }; i < walls_num-1; i++)
		{
			if (walls[i] < walls[i + 1])
				high++;
			else if (walls[i] > walls[i + 1])
				low++;
		}

		cout << "Case " << ++k_num << ": " << high << ' ' << low << endl;
	}
	return 0;
}