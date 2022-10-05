#include<iostream>
using namespace std;

//UVA 11799
int main()
{
	int T, N, cspeed, max;
	cin >> T;
	for (int i{ 0 }; i < T; i++)
	{
		cin >> N;
		cin >> max;
		N -= 1;
		while (N--)
		{
			cin >> cspeed;
			if (cspeed > max)
				max = cspeed;
		}
		
		cout << "Case " << i + 1 << ": " << max << endl;
	}

	return 0;
}