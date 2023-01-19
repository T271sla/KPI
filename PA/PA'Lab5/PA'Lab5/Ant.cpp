#include "Ant.h"

Ant::Ant(int StartingPoint, int eliteGenerator)
{
    this->StartingPoint = StartingPoint;
    this->Path.push_back(StartingPoint);
    for (int i = 0; i < 200; i++)
    {
        if (i != StartingPoint)
        {
            this->UnvisitedVertices.push_back(i);
        }
    }

    if (eliteGenerator == 1)
    {
        this->elite = true;
    }
}

void Ant::Reset()
{
    this->Path.clear();
    this->Path.push_back(this->StartingPoint);
    this->UnvisitedVertices.clear();
    for (int i = 0; i < 300; i++)
    {
        if (i != this->Path.at(0))
        {
            this->UnvisitedVertices.push_back(i);
        }
    }
}

void Ant::MoveToVertix(int destination, int destinationIdx)
{
    this->Path.push_back(destination);
    this->UnvisitedVertices.erase(this->UnvisitedVertices.begin() + destinationIdx);
}

void Ant::ChooseDestination(vector<Probability> Probabilities)
{
    double lowerBound = 0;
    double randomValue = ((double)rand() / (RAND_MAX));
    int destination = 0;
    int destinationIdx = 0;

    if (randomValue == 1)
    {
        destination = UnvisitedVertices.at(UnvisitedVertices.size() - 1);
        destinationIdx = UnvisitedVertices.size() - 1;
    }
    else if (randomValue == 0)
    {
        destination = UnvisitedVertices.at(0);
        destinationIdx = 0;
    }
    else if (UnvisitedVertices.size() == 1)
    {
        destination = UnvisitedVertices.at(0);
        destinationIdx = 0;
    }
    else
    {
        for (int j = 0; j < Probabilities.size(); j++)
        {
            if ((Probabilities.at(j).chance > -1) && (Probabilities.at(j).vertix == this->UnvisitedVertices.at(j)))
            {
                if ((lowerBound < randomValue) && (randomValue <= lowerBound + Probabilities.at(j).chance))
                {
                    destination = UnvisitedVertices.at(j);
                    destinationIdx = j;
                    break;
                }
                else
                {
                    lowerBound += Probabilities.at(j).chance;
                }
            }
        }
    }

    MoveToVertix(destination, destinationIdx);
}

double Ant::getL(int graph[300][300])
{
    int L = 0;

    for (int i = 0; i < this->Path.size() - 1; i++)
    {
        L += graph[this->Path.at(i)][this->Path.at(i + 1)];
    }

    return L;
}