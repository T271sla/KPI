#include <iostream>
#include <math.h>
using namespace std;

int func(int n)
{
	do {
		int res;
		n /= 10;
	} while (n > 10);

	return n;
}

int main()
{
	int a, b, c, sum;
	cout << "Enter a, b, c" << endl;
	cin >> a >> b >> c;
	sum = func(a) + func(b) + func(c);
	cout << "Sum of first digits of entered numbers is:" << endl;
	cout << sum << endl;
	
	system("pause");
	return 0;
}