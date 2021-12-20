#include <iostream>
#include <ctime>
using namespace std;

int main()
{
    srand(time(NULL));
    
    int n;
    cin >> n;
    cout << " " << endl;

    int rows = n;
    int cols = n;

    int dn = n / 2;
    int dn2 = dn + 1;
    int dn3 = dn - 1;

    int** arr = new int* [rows];

    for (int i = 0; i < rows; i++)
    {
        arr[i] = new int[cols];
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            arr[i][j] = rand();
        }
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << arr[i][j] << "\t";
        }
        cout << endl;
    }

    for (int i = 0; i < n; i++)
    {
        if (i < dn) {
            for (int j = 0; j < dn - i; j++)
            {
                arr[i][j] = 0;
                arr[i][j + dn2 + i] = 0;
            }
        }
        else if (i > dn) {
            for (int j = 0; j < -(dn - i); j++)
            {
                arr[i][j] = 0;
                arr[i][dn2 - j + dn3] = 0;
            }
        }
    }

    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            sum += arr[i][j];
        }
        cout << endl;
    }

    int max = arr[0][0];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (arr[i][j] > max) {
                max = arr[i][j];
            }
            else {
                continue;
            }
        }
        cout << endl;
    }
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << arr[i][j] << "\t";
        }
        cout << endl;
    }
    cout << " " << endl;
    cout << sum << endl;
    cout << " " << endl;
    cout << max << endl;

    for (int i = 0; i < rows; i++)
    {
        delete[] arr[i];
    }

    delete[] arr;
}
