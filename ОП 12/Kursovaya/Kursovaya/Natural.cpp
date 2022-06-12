#include "Header.h"

void naturalExternalSort(class TextFile& A, class TextFile& B, class TextFile& C, int size, int n)
{
    A.openAdd();
    B.openErase();
    C.openErase();

    //заповнюємо файли В та С
    A.fillBC(size, B, C);

    A.close();
    B.close();
    C.close();

    B.openAdd();
    C.openAdd();
    A.openErase();

    if (size < n)
    {
        //об'єднюємо та сортуємо серії
        B.fillArrNatural(size, B, C, A);
    }

    A.close();
    B.close();
    C.close();

    if (size < n)
    {
        naturalExternalSort(A, B, C, size * 2, n);
    }
    else if(size == n)
    {
        string B = "B.txt";
        string C = "C.txt";
        string A = "Natural Output.txt";
        mergeFiles(B, C, A);
        return;
    }
}

void naturalExternalSortStart()
{
    srand(time(NULL));
    string path = "A.txt";
    string path_1 = "B.txt";
    string path_2 = "C.txt";

    TextFile A(path);
    TextFile B(path_1);
    TextFile C(path_2);

    int numElements = 100000;
    int m = 100;

    A.openErase();
    B.openErase();
    C.openErase();
    A.fillFile(numElements, m);//заповнюємо перший файл
    A.close();
    B.close();
    C.close();

    int runSize = 1250;

    naturalExternalSort(A, B, C, runSize, numElements);
};