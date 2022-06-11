#include "Header.h"

void naturalExternalSort(class TextFile& A, class TextFile& B, class TextFile& C, int size, int origSize, int n)
{
    A.openAdd();
    B.openErase();
    C.openErase();

    A.fillBC(size, B, C);

    A.close();
    B.close();
    C.close();

    B.openAdd();
    C.openAdd();
    A.openErase();

    if (size < n)
    {
        B.fillArrNatural(size, B, C, A);
    }
    else
    {
        string out = "Natural Output.txt";
        string B = "B.txt";
        string C = "C.txt";
        mergeFiles(B, C, out);
        return;
    }

    A.close();
    B.close();
    C.close();

    if (size < n)
    {
        naturalExternalSort(A, B, C, size * 2, origSize, n);
    }
}

void naturalExternalSortStart()
{
    string path = "A.txt";
    string path_1 = "B.txt";
    string path_2 = "C.txt";

    TextFile A(path);
    TextFile B(path_1);
    TextFile C(path_2);

    int numElements = 10000;
    int m = 100;

    A.openErase();
    B.openErase();
    C.openErase();
    A.fillFile(numElements, m);
    A.close();
    B.close();
    C.close();

    int runSize = 1250;
    int origSize = runSize;

    naturalExternalSort(A, B, C, runSize, origSize, numElements);
};