#pragma once
#include <iostream>
using namespace std;

class TVector
{
public:

    int x;
    int y;

    void Set(int valueX, int valueY)
    {
        x = valueX;
        y = valueY;
    }

    void perpen(TVector j)
    {
        if (x * j.x + y * j.y == 0)
        {
            cout << "Vectors are perpendicular" << endl;
        }
        else
        {
            cout << "Vectors are not perpendicular" << endl;
        }
    }

    bool paral(TVector j)
    {
        if (x / j.x == y / j.y)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    int length()
    {
        int len = abs(sqrt(x * x + y * y));
        return len;
    }

    void print()
    {
        cout << x << " " << y << endl;
    }
};

class R2 : public TVector
{
public:
};

class R3 : public TVector
{
public:
    int z;

    void Set3D(int valueX, int valueY, int valueZ)
    {
        x = valueX;
        y = valueY;
        z = valueZ;
    }

    int length3D()
    {
        int len = abs(sqrt(x * x + y * y + z * z));
        return len;
    }

    bool perpen3D(R3 j)
    {
        if (x * j.x + y * j.y + z + j.z == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

void create(R2& a, R2& b, R2& c, R3& d, R3& e, R3& f, R3& g);
void check(R2 a, R2 b, R2 c, R3 d, R3 e, R3 f, R3 g);