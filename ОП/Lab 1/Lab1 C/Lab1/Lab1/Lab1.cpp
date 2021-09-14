#include <iostream>
#include <math.h>
#include <stdio.h>
using namespace std;

int main()
{
    int R, H;
    double V1, V2;
    const float PI = 3.14;

    //Введення даних
    cout << "Enter the height: ";
    cin >> H;
    cout << "Enter the radius: ";
    cin >> R;
    
    //Розрахунок
    V1 = R * R * H * PI;
    V2 = V1 / 3;
    
    //Виведення даних
    cout << "Volume of the cilinder: " << V1 << endl;
    cout << "Volume of the con: " << V2 << endl;
    system("pause");
    return 0;
}
