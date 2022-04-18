#include "Header.h"

void input_param(vector<Cone>& arr, int& n)
{
    Cone a;

    cout << "Input number of cones: ";
    cin >> n;
    cin.ignore();
    for (int i = 0; i < n; i++)
    {
        cout << "Input cordinates of the center(x, y, z): " << endl;
        cin >> a.centerx;
        cin >> a.centery;
        cin >> a.centerz;
        cout << "Input cordinates of the vertex(x, y, z): " << endl;
        cin >> a.vertexx;
        cin >> a.vertexy;
        cin >> a.vertexz;
        cout << "Input radiss: ";
        cin >> a.radius;
        arr.push_back(a);
    }
}

void output_param(vector<Cone>& arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        cout << "Cone " << i + 1 << endl;
        cout << "Coradinates of the center: " << arr[i].centerx << ", " << arr[i].centery << ", " << arr[i].centerz << endl;
        cout << "Coradinates of the vertex: " << arr[i].vertexx << ", " << arr[i].vertexy << ", " << arr[i].vertexz << endl;
        cout << "Radius: " << arr[i].radius << endl;
        cout << endl;
    }
}


void find_t(vector<Cone>& arr, int n)
{
    int* height = new int[n];

    for (int i = 0; i < n; i++)
    {
        int x = (arr[i].vertexx - arr[i].centerx) * (arr[i].vertexx - arr[i].centerx);
        int y = (arr[i].vertexy - arr[i].centery) * (arr[i].vertexy - arr[i].centery);
        int z = (arr[i].vertexz - arr[i].centerz) * (arr[i].vertexz - arr[i].centerz);
        height[i] = sqrt(x + y + z);
    }

    cout << "Altitudes: ";

    for (int i = 0; i < n; i++)
    {
        cout << height[i] << " ";
    }

    cout << endl;

    int* tvir = new int[n];

    for (int i = 0; i < n; i++)
    {
        int h = height[i] * height[i];
        int r = arr[i].radius * arr[i].radius;
        tvir[i] = sqrt(h + r);
    }

    int max = tvir[0];
    int cn = 0;

    for (int i = 0; i < n; i++)
    {
        if (tvir[i] > max)
        {
            max = tvir[i];
            cn = i;
        }
    }

    cout << "Slant heights: ";

    for (int i = 0; i < n; i++)
    {
        cout << tvir[i] << " ";
    }

    cout << endl;

    cout << "Cone " << cn + 1 << ": " << max;
}