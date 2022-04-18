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

int main()
{
    vector<Cone> parameters;
    int n;
    input_param(parameters, n);
    cout << endl;
    output_param(parameters);
    find_t(parameters, n);
}

