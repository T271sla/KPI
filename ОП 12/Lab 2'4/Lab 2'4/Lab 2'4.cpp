#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

class Numeral_16
{
private:
    int N;
public:
    Numeral_16(int valueN)
    {
        N = valueN;
    }

    void SetN2(int valueN)
    {
        N = valueN;
    }

    int GetN()
    {
        return N;
    }

    Numeral_16& operator ++()
    {
        this->N++;
        return *this;
    }

    Numeral_16& operator +=(int i)
    {
        this->N += i;
        return *this;
    }

    Numeral_16 operator+(const Numeral_16& other) {
        return Numeral_16(this->N + other.N);
    }
};

int main()
{
    int n;
    int m;
    int i;
    cin >> hex >> n;
    cin >> hex >> m;

    Numeral_16 a(n);
    Numeral_16 b(m);

    b.SetN2(m);

    ++a;

    cout << endl;
    cout << "N2 + ";
    cin >> i;

    b += i;

    Numeral_16 c(1);

    c = a + b;

    cout << endl;
    cout << hex << a.GetN() << '\t' << hex << b.GetN() << '\t' << hex << c.GetN() << endl << endl;
    cout << dec << c.GetN();
}
