#include<iostream>
#include<cmath>
using namespace std;
int main()
{
	//problem3
	double n, s1, s2, s3;
	cin >> n;
	s1 = 0;
	for (double i{ 0 }; i <= n; i++)
		s1 += i;
	s2 = 0;
	for (double i{ 1 }; i <= n; i++)
		s2 += i / (i + 1);
	s3 = 0;
	for (double i{ 0 }; i <= n; i++)
		s3 += pow(-1.0, i) * i;

	cout << "S1: " << s1 << endl << "S2: " << s2 << endl << "S3: " << s3 << endl;
	return 0;

}