#include <iostream>
#include <cmath>
using namespace std;

#define PI 3.14159265

int main()
{
	double x;
	double fact = 1;                   
	double sum;
	double sum_2 = 1;
	int n = 1;     
	double eps = 0.000001;

	cout << "Enter x:";
	cin >> x;
	do {
			fact *= (2 * n - 1) * 2 * n;                           
			sum = (pow(-1, n) * pow(x, (2 * n)) / fact);          
			if (sum < 1 | sum > -1)                                       
			{
				sum_2 += sum;
			}
			n += 1;
		} while (abs(sum) > eps);                       

	cout << "Cos(x) = " << sum_2 << endl;
	system("pause");
	return 0;
}
