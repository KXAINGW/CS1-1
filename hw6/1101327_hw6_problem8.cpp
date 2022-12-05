#include<iostream>
#include<string>
using namespace std;
int main()
{
	int num;
	cout << "Pls input number(0~999999): ";
	cin >> num;
	string digit1[] = { "","one","two","three","four","five","six","seven","eight","nine" };
	string digit2[] = { "ten","eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen","nineteen" };
	string digit3[] = { "","","twenty","thirty","forty","fifty","sixty","seventy","eighty","ninety" };
	//while (cin >> num) {
		if (num > 0 && num < 1000000)
		{
			if (num > 999)
			{
				if (num / 100000)
				{
					cout << digit1[num / 100000] << " hundred ";
					num %= 100000;
				}
				if (num >= 1000)
				{
					if (num / 10000 > 1)
					{
						cout << digit3[num / 10000] << ' ';
						if ((num / 1000) % 10)
							cout << digit1[(num / 1000) % 10] << ' ';
					}
					else if (num / 10000 == 1)
						cout << digit2[(num / 1000) % 10] << ' ';
					else
						cout << digit1[num / 1000] << ' ';
					num %= 1000;
				}
				cout << "thousand" << ' ';
			}
			if (num / 100)
			{
				cout << digit1[num / 100] << " hundred ";
				num %= 100;
				if (num)
					cout << "and ";
			}
			if (num)
			{
				if ((num / 10) > 1)
				{
					cout << digit3[num / 10] << ' ';
					if (num % 10)
						cout << digit1[num % 10] << ' ';
				}
				else if ((num / 10) == 1)
					cout << digit2[num % 10] << ' ';
				else
					cout << digit1[num % 10] << ' ';
			}
			cout << "TWD" << endl;
		}
		else if (num == 0)
			cout << "Zero TWD" << endl;
		else
			cout << "Error" << endl;
		cout << endl;
		cout << "Pls input number(0~999999): ";

	//}
	return 0;
}