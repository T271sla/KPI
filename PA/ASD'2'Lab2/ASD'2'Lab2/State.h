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
	int GetQueenPosition(int index)
	{
		return board[index];
	}
	void moveQueen(int QueenNumber, int position);
	int F2();
	bool CheckSolution();
	bool operator==(State field);
};
