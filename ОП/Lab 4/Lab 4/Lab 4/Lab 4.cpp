#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	double sum_1;
	double sum_2;
	double res_1 = 0;
	double res_2 = 0;
	int n_1 = 1;
	int n_2 = 100;

	do {
		sum_1 = (pow(-1, n_1 + 1) * 1 / n_1);
		res_1 += sum_1;
		n_1 += 1;
	} while (n_1 < 101);

	cout << "First result = " << res_1 << endl;

	do {
		sum_2 = (pow(-1, n_2 + 1) * 1 / n_2);
		res_2 += sum_2;
		n_2 -= 1;
	} while (n_2 > 1);

	cout << "Second result = " << res_2 << endl;

	if (res_1 > res_2) {
		cout << "First result is greater" << endl;
	}
	else
		cout << "Second result is greater" << endl;

	system("pause");
	return 0;
}
