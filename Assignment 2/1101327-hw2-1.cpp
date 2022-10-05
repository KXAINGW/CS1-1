#include<iostream>
using namespace std;

//UVA 10300
int main()
{
	int test_cast, farmer_num;
	long long int size, animalnum, degree, premium;
	int i = 0, i2;

	cin >> test_cast;
	while (i++ < test_cast)
	{
		cin >> farmer_num;
		i2 = 0;
		premium = 0;
		while (i2++ < farmer_num)
		{
			cin >> size >> animalnum >> degree;
			premium += size * degree;
		}
		cout << premium << '\n';
	}
	return 0;
}