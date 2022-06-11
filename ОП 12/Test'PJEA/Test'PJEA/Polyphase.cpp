#include "Header.h"

void polyphaseSort(int n, int m, int check_1, int check_2, int check_3, class TextFile& One, class TextFile& Two, class TextFile& Three, class TextFile& Addon, int fib[], int idx)
{
    Three.fillFilePolyphase(m, fib[idx], One, Two, Three, Addon);

    if (fib[idx] == 1440)
    {
        return;
    }

    if ((check_1 > check_2) && (check_3 == 0))
    {
        polyphaseSort(m, n - m, n - m, 0, m, Three, One, Two, Addon, fib, idx + 1);
    }
    else if ((check_3 > check_1) && (check_2 == 0))
    {
        polyphaseSort(m, n - m, 0, m, n - m, Three, One, Two, Addon, fib, idx + 1);
    }
    else if ((check_2 > check_3) && (check_1 == 0))
    {
        polyphaseSort(m, n - m, m, n - m, 0, Three, One, Two, Addon, fib, idx + 1);
    }
}

void PolyPhaseSortStart()
{
    string path_1 = "1.txt";
    string path_2 = "2.txt";
    string path_3 = "3.txt";
    string path_4 = "addon.txt";

    string path = "original.txt";

    TextFile original(path);
    original.openErase();
    original.fillFile(1000000, 100);
    original.close();

    TextFile one(path_1);
    TextFile two(path_2);
    TextFile three(path_3);
    TextFile addon(path_4);
    
    original.openAdd();
    one.openErase();
    two.openErase();
    three.openErase();
    original.fill12(10000, 66, 34, 89, 55, one, two);
    original.close();
    one.close();
    two.close();
    three.close();

    int fib[] = { 20000, 30000, 50000, 80000, 130000, 210000, 340000, 550000, 890000, 1440000 };
    int idx = 0;

    polyphaseSort(89, 55, 89, 55, 0, one, two, three, addon, fib, idx);
};