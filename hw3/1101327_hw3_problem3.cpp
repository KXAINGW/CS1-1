#include<iostream>
using namespace std;
int main()
{
	//problem3
	int n, n0 = 0, n1 = 1, temp;
	cin >> n;
	n += 1;
	if (n >= n1)
		cout << n1 << ' ';
	while (n > 1)
	{
		temp = n1;
		n1 += n0;
		n0 = temp;
		cout << n1 << ' ';
		n--;
	}
	cout << endl;
	return 0;
}