#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	double sum_1 = 0;
	double sum_2 = 0;
	float n_1, n_2;

	for (n_1 = 1; n_1 <= 100; n_1 += 1)
		sum_1 += (pow(-1, n_1 + 1) * (1 / n_1));
	cout << "First sum = " << sum_1 << endl;

	for (n_2 = 100; n_2 >= 1; n_2 -= 1)
		sum_2 += (pow(-1, n_2 + 1) * (1 / n_2));
	cout << "Second sum = " << sum_2 << endl;

	if (sum_1 > sum_2) {
		cout << "First result is greater" << endl;
	}
	else if (sum_1 < sum_2) {
		cout << "Second result is greater" << endl;
	}
	else cout << "Results are the same" << endl;

	system("pause");
	return 0;
}
