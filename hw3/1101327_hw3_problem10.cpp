#include<iostream>
using namespace std;
int main()
{
	//problem10
	double n, grade, gradeMax, gradeMin,sum;
	cout << "Enter the number of subjects in the semester: ";
	cin >> n;
	cout << "Enter the score of each subject (the score is from 0.0f to 10.0f): ";
	cin >> sum;
	gradeMax = sum;
	gradeMin = sum;
	int m = n-1;
	while (m--)
	{
		cin >> grade;
		sum += grade;
		if (gradeMax < grade)
			gradeMax = grade;
		if (gradeMin > grade)
			gradeMin = grade;
	}
	cout << "The average score of that student: " << sum / n << endl;
	cout << "The highest score of that student: " << gradeMax << endl;
	cout << "The lowest score of that student: " << gradeMin << endl;
	return 0;
}