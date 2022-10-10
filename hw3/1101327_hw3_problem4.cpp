#include<iostream>
#include<iomanip>
using namespace std;
int main()
{
	//problem4
	double x, ans = 1;
	int n;
	cin >> x >> n;
	while (n--)
		ans *= x;
	cout << fixed << setprecision(4) << ans << endl;

	return 0;
}