#include "Header.h"

void create(R2& a, R2& b, R2& c, R3& d, R3& e, R3& f, R3& g)
{

    int x;
    int y;
    int z;

    cout << "Enter 2D vectors: " << endl;

    for (int i = 0; i < 3; i++)
    {
        cin >> x;
        cin >> y;
        if (i == 0)
        {
            a.Set(x, y);
        }
        if (i == 1)
        {
            b.Set(x, y);
        }
        if (i == 2)
        {
            c.Set(x, y);
        }
    }

    cout << "Enter 3D vectors: " << endl;

    for (int i = 0; i < 4; i++)
    {
        cin >> x;
        cin >> y;
        cin >> z;
        if (i == 0)
        {
            d.Set3D(x, y, z);
        }
        if (i == 1)
        {
            e.Set3D(x, y, z);
        }
        if (i == 2)
        {
            f.Set3D(x, y, z);
        }
        if (i == 3)
        {
            g.Set3D(x, y, z);
        }
    }
}

void check(R2 a, R2 b, R2 c, R3 d, R3 e, R3 f, R3 g)
{
    int sum = 0;

    if (d.paral(a))
    {
        sum += a.length();
    }
    if (d.paral(b))
    {
        sum += b.length();
    }
    if (d.paral(c))
    {
        sum += c.length();
    }
    if (d.paral(e))
    {
        sum += e.length3D();
    }
    if (d.paral(f))
    {
        sum += f.length3D();
    }
    if (d.paral(g))
    {
        sum += g.length3D();
    }

    int sum2 = 0;

    if (d.perpen3D(e))
    {
        sum2 += e.length3D();
    }
    if (d.perpen3D(f))
    {
        sum2 += d.length3D();
    }
    if (d.perpen3D(g))
    {
        sum2 += g.length3D();
    }

    cout << "Sum lengths of parallel vectors: " << sum << endl;
    cout << "Sum lengths of perpendicular vectors: " << sum2 << endl;
}