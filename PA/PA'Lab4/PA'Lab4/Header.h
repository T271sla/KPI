#pragma once
#include <iostream>
using namespace std;

template<typename T>
class Node {
public:
    Node(T data) {
        this->left = nullptr;
        this->right = nullptr;
        this->data = data;
    }
    Node* left;
    Node* right;
    T data;
};
template<typename T>
class List {
private:
    Node<T>* head;
    Node<T>* GetNodeAt(int index) {
        Node<T>* current = this->head;
        for (int i = 0; i < index; i++)
        {
            current = current->right;
        }
        return current;
    }
public:
    List() {
        this->head = nullptr;
    }
    void Push(T data) {
        if (this->head == nullptr) {
            this->head = new Node<T>(data);
        }
        else {
            Node<T>* current = this->head;
            while (current->right != nullptr) {
                current = current->right;
            }
            current->right = new Node<T>(data);
        }
    }
    T Pop() {
        if (this->head == nullptr) {
            throw ("");
        }
        Node<T>* current = this->head;
        Node<T>* prev_current = nullptr;
        while (current->right != nullptr) {
            prev_current = current;
            current = current->right;
        }
        if (prev_current == nullptr) {
            this->head = nullptr;
        }
        else {
            prev_current->right = nullptr;
        }
        T data = current->data;
        delete current;
        return data;
    }
    int Length() {
        int i = 0;
        Node<T>* current = this->head;
        while (current != nullptr) {
            current = current->right;
            i++;
        }
        return i;
    }
    T GetAt(int index) {
        Node<T>* current = this->head;
        for (int i = 0; i < index; i++)
        {
            current = current->right;
        }
        return current->data;
    }
    void SetAt(T data, int index) {
        Node<T>* current = this->head;
        for (int i = 0; i < index; i++)
        {
            current = current->right;
        }
        current->data = data;
    }
    T Erase(int index) {
        if (this->head == nullptr) {
            throw ("");
        }
        Node<T>* current = this->head;
        Node<T>* prev_current = nullptr;
        for (int i = 0; i < index; i++)
        {
            prev_current = current;
            current = current->right;
        }
        if (prev_current == nullptr) {
            this->head = this->head->right;
        }
        else {
            prev_current->right = current->right;
        }
        T data = current->data;
        delete current;
        return data;
    }
};

void BuildGraph(int graph[200][200]);
void BuildPheromoneGraph(double pheromoneGraph[200][200]);
void BuildPheromoneSumGraph(double pheromoneSumGraph[200][200]);
void BuildVisibilityGraph(double visibilityGraph[200][200], int graph[200][200]);
void TSPAlgorithm(int graph[200][200], double pheromoneGraph[200][200], double pheromoneSumGraph[200][200]);
int GenerateStartingPoint(int UsedStartingPoints[45], int M);
bool CheckForStartingPoint(int UsedStartingPoints[45], int StartingPoint, int M);
double MoveProbability(int curVertix, int destination, int pheromone, int alpha, int beta, int graph[200][200], int UnvisitedVerticesCount);
double MoveProbabilityStepOne(int curVertix, int destination, int pheromone, int alpha, int beta, int graph[200][200]);
int GetLmin(int graph[200][200]);
void GetMin(int graph[200][200], int visited[200], int Vertix, int& iteration);
bool CheckVisited(int visited[200]);
void printArray(int arr[200]);
double RD(double min, double max);



class Ant
{
public:

    List<int> Path;
    List<int> UnvisitedVertices;

    Ant()
    {

    }

    Ant(int StartingPoint)
    {
        this->Path.Push(StartingPoint);
        for (int i = 0; i < 200; i++)
        {
            if (i != StartingPoint)
            {
                this->UnvisitedVertices.Push(i);
            }
        }
    }

    void Reset()
    {
        for (int i = 0; i < 200; i++)
        {
            this->Path.Pop();
            this->UnvisitedVertices.Push(i);
        }
    }

    void MoveToVertix(int destination)
    {
        this->Path.Push(destination);
        this->UnvisitedVertices.Erase(destination);
    }

    void ChooseDestination(double Probabilities[], int noPath)
    {
        double lowerBound = 0;
        double randomValue = RD(0, 1);
        int destination;

        for (int j = 0; j < this->UnvisitedVertices.Length() - noPath; j++)
        {
            if ((lowerBound <= randomValue) && (randomValue <= lowerBound + Probabilities[j]))
            {
                destination = j;
                break;
            }
        }

        MoveToVertix(destination);
    }

    int getL(int graph[200][200])
    {
        int L = 0;

        for (int i = 0; i < this->Path.Length() + 1; i++)
        {
            L += graph[this->Path.GetAt(i)][this->Path.GetAt(i + 1)];
        }

        return L;
    }
};


void printList(Ant Ant);