#include <iostream>
using namespace std;

int func(int n)
{
	do {
		n /= 10;
	} while (n > 10);

	return n;
}

int main()
{
	int a, b, c, sum;
	cout << "Enter a, b, c ∈ [1; +inf)" << endl;
	cin >> a >> b >> c;
	if (a >= 1 && b >= 1 && c >= 1) {
		sum = func(a) + func(b) + func(c);
		cout << "Sum of first digits of entered numbers is:" << endl;
		cout << sum << endl;
	}
	else {
		cout << "One number (or more) doesn't belong to the required range. Try again." << endl;
	}
	
	system("pause");
	return 0;
}
