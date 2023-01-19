#pragma once
#include "Header.h"

class Ant
{
public:

    int StartingPoint;
    bool elite = false;
    vector<int> Path;
    vector<int> UnvisitedVertices;

    Ant()
    {
        this->Path.push_back(1);
        this->UnvisitedVertices.push_back(1);
        this->Path.clear();
        this->UnvisitedVertices.clear();
    }

    Ant(int StartingPoint, int eliteGenerator);

    void Reset();

    void MoveToVertix(int destination, int destinationIdx);

    void ChooseDestination(vector<Probability> Probabilities);

    double getL(int graph[300][300]);
};
