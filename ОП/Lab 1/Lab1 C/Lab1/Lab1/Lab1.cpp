#include <iostream>
#include <math.h>
#include <stdio.h>
using namespace std;

int main()
{
    int R, H;
    double V1, V2;
    const float PI = 3.14;

    #Введення даних
    printf("Enter radius(R):");
    scanf_s("%d", &R);
    printf("Enter height(H):");
    scanf_s("%d", &H);

    #Розрахунок
    V1 = R * R * H * PI;
    V2 = V1 / 3;

    #Виведення даних
    printf("Volume of the cylinder:%d\n", V1);
    printf("Volume of the cone:%d\n", V2);
    system("pause");
}
