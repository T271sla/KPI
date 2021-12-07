#include <iostream>
using namespace std;

int main()
{
    //Створення масиву
    double size;
    double n;
    cout << "Enter the size of the array" << endl;
    cin >> size;
    double* arr = new double[size];
    cout << "Enter every element the array:" << endl;

    for (int i = 0; i < size; i++)
    {
        cin >> n;
        arr[i] = n;
    }

    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << "\n";

    //Пошук максимального та мінімального додатнього чисел
    double max = arr[0];
    int idx_1 = 0;
    for (int i = 1; i < size; i++)
    {
        if (arr[i] >= max) {
            max = arr[i];
            idx_1 = i;
        }
        else {
            continue;
        }
    }
    
    double min = arr[0];
    int idx_2 = 0;
    for (int i = 0; i < size; i++)

    {
        if ((arr[i] <= min) && (arr[i] > 0)) {
            min = arr[i];
            idx_2 = i;
        }
        else {
            continue;
        }
    }

    //Вивід проміжних даних
    cout << "The max number in array: " << max << endl;
    cout << "The min positive number in array: " << min << endl;
    cout << "Min's index in array: " << idx_2 + 1 << endl;
    
    //Заміна місцями
    arr[idx_1] = min;
    arr[idx_2] = max;

    //Вивід результатів
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << "\n";
    
    delete [] arr;
}

