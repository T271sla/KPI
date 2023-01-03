#include "Header.h"

void printList(Ant Ant)
{
	for (int i = 0; i < 200; i++)
	{
		cout << Ant.Path.GetAt(i) << "->";
	}

	cout << endl;
	cout << endl;
}

void printArray(int arr[200])
{
	for (int i = 0; i < 200; i++)
	{
		cout << arr[i] << "->";
	}

	cout << endl;
	cout << endl;
}