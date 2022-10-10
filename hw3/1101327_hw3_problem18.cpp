#include<iostream>
using namespace std;
int main()
{
	//problem18
	int num, numDigit = 0, sumDigit = 0;
	cin >> num;
	while (num >=1)
	{
		sumDigit += num% 10;
		num /= 10;
		numDigit++;
	}
	cout << "Number of digits: " << numDigit << endl;
	cout << "Sum of digits: " << sumDigit << endl;
	return 0;
}