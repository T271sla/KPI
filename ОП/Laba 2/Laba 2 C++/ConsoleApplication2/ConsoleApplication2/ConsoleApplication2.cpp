#include <iostream>
using namespace std;

int main()
{
    double a, b, c;
    long long int Sum_1, Sum_2, Sum_3;

    cout << "Enter a: ";
    cin >> a;
    cout << "Enter b: ";
    cin >> b;
    cout << "Enter c: ";
    cin >> c;

    Sum_1 = a + b;
    Sum_2 = a + c;
    Sum_3 = b + c;

    if (Sum_1%2) { 
        cout << "a+b is uneven" << endl;
    }
    else {
        cout << "a+b is even" << endl;
    }
    if (Sum_2%2) {
        cout << "a+c is uneven" << endl;
    }

    else {
        cout << "a+c is even" << endl;
    }

    if (Sum_3%2) {
        cout << "b+c is uneven" << endl;
    }
    else {
        cout << "b+c is even" << endl;
    }

    system("pause");
    return 0;
}
