#include<iostream>
using namespace std;
int main()
{
	//problem13

	int nums1[100], nums2[100], merge[200];
	int n1, n2, temp;
	cout << "Please enter n1: ";
	cin >> n1;
	cout << "Input array1: ";
	for (int i = 0; i < n1; i++)
		cin >> nums1[i];

	cout << "Please enter n2: ";
	cin >> n2;
	cout << "Input array2: ";
	for (int i = 0; i < n2; i++)
		cin >> nums2[i];

	for (int i = n1 - 1; i >= 0; i--)
	{
		for (int j = 0; j < i ; j++)
		{
			if (nums1[j] > nums1[j + 1])
			{
				temp = nums1[j];
				nums1[j] = nums1[j + 1];
				nums1[j + 1] = temp;
			}
		}
	}

	for (int i = n2 - 1; i >= 0; i--)
	{
		for (int j = 0; j < i ; j++)
		{
			if (nums2[j] > nums2[j + 1])
			{
				temp = nums2[j];
				nums2[j] = nums2[j + 1];
				nums2[j + 1] = temp;
			}
		}
	}


	int i = 0, j = 0, k = 0;
	while (i < n1 && j < n2)
	{
		if (nums1[i] > nums2[j])
		{
			merge[k] = nums2[j];
			k++, j++;
		}
		else if (nums1[i] < nums2[j])
		{
			merge[k] = nums1[i];
			k++, i++;
		}
		else
		{
			merge[k] = nums1[i];
			k++, i++;
			merge[k] = nums2[j];
			k++, j++;
		}
	}
	while (i < n1)
	{
		merge[k] = nums1[i];
		k++, i++;
	}
	while (j < n2)
	{
		merge[k] = nums2[j];
		k++, j++;
	}

	cout << "Merged matrix: ";
	for (int i = 0; i < k; i++)
		cout << merge[i] << ' ';
	cout << endl;

	return 0;

}