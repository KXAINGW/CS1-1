#include<iostream>
using namespace std;
int main()
{
	//problem2
	int n, n0 = 0, n1 = 1, temp;
	cin >> n;
	while (n>1)
	{
		temp = n1;
		n1 += n0;
		n0 = temp;
		n--;
	}
	cout <<n1<< endl;
	return 0;
}