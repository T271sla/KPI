#pragma once
#include <iostream>
using namespace std;

class State
{
private:
	int board[8];
public:
	State();
	void print();
	void randomState();
	void makeState();
	bool CheckForSolution();
	int GetQueenPosition(int index)
	{
		return board[index];
	}
	void moveQueen(int QueenNumber, int position);
	friend int F2(State board);
	bool operator==(State board);
};

int countPairsInArr(int arr[], int n);

int Combination(int n, int m);
