#include <iostream>
using namespace std;

int main()
{
    int sum = 0;

    for (int i = 100; i <= 200; i++)
        for (int j = 2; j <= sqrt(i); j++)
        {
            if (i % j == 0)
                break;

            else if (j+1 > sqrt(i)) {
                sum = 1 + ((i-1) % 9);
                cout << "\n" << "Digital root of " << i << " is " << sum << " ";

            }

        }

    system("pause");
    return 0;
}