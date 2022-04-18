#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

class Cone
{
public:
    int centerx;
    int centery;
    int centerz;
    int vertexx;
    int vertexy;
    int vertexz;
    int radius;
};

void input_param(vector <Cone>&, int& n);
void output_param(vector<Cone>&);
void find_t(vector<Cone>&, int n);
