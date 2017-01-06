// By: Omer Khan
// fo1672
// CSC 2201

#include <iostream>
using namespace std;

void insertionSort(double a[], int length)
{
	for (int i = 1; i < length; i++)

	{
		double key = a[i];
		int j = i - 1;

		while (j >= 0 && a[j] > key)
		{
			a[j + 1] = a[j];
			j = j - 1;
		}
		a[j + 1] = key;
	}
}

int main()
{
	double a[6] = { 71, 32, 43.5, 5, 49, 12 };

	insertionSort(a, 6); 

	for (int i = 0; i < 6; i++)
	{
		cout << a[i] << " ";
	}

	return 0;
}