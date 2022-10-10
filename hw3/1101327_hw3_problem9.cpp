#include<iostream>
using namespace std;
int main()
{
	//problem9
	double n, time, ave;
	cout << "Enter the number of athletes in the team: ";
	cin >> n;
	double temp = n;
	ave = 0;
	cout << "Enter the time of each athlete: ";
	while (temp--)
	{
		cin >> time;
		ave += time;
	}
	cout << "The team's total cycling time: " << ave << endl;
	cout << "Average cycling time of the whole team: " << ave/n << endl;
	return 0;
}