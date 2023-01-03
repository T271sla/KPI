#include <iostream>
#include <ctime>
#include "Search.h"
using namespace std;

void FindLDFS();
void FindAstar();

int main()
{
	srand(time(NULL));

	FindLDFS();
}

void FindLDFS()
{
	State parent;
	parent.randomState();

	cout << "First step:" << endl;

	parent.print();

	long int start = clock();
	LDFS(parent);
	long int end = clock();

	cout << "LDFS time - " << end - start << "ms" << endl;
}

void FindAstar()
{
	State parent;
	parent.randomState();

	cout << "First step:" << endl;

	parent.print();

	cout << "Searching for solution..." << endl;

	long int start = clock();
	Astar(parent);
	long int end = clock();

	cout << "A* time - " << end - start << "ms" << endl;
}
