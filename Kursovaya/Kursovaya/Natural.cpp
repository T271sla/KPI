//Основний файл природного сортування
#include "Header.h"

void naturalExternalSort(class TextFileNatural& A, class TextFileNatural& B, class TextFileNatural& C, int size, int n, int& times)
{
    A.openAdd();
    B.openErase();
    C.openErase();
    times += 3;

    //заповнюємо файли В та С
    A.fillBC(size, B, C);
    times++;

    A.close();
    B.close();
    C.close();

    B.openAdd();
    C.openAdd();
    A.openErase();
    times += 3;

    if (size < n)
    {
        //об'єднюємо та сортуємо серії
        B.fillArrNatural(size, B, C, A);
        times += 4;
    }

    A.close();
    B.close();
    C.close();

    if (size < n)
    {
        naturalExternalSort(A, B, C, size * 2, n, times);
    }
    else if(size == n)
    {
        string B = "B.txt";
        string C = "C.txt";
        string A = "Temp Natural Output.txt";
        mergeFiles(B, C, A);
        return;
    }
}

int naturalExternalSortStart(int size, int& times, int zero, int negOne)
{
    unsigned int start_time = clock();
    string path = "A.txt";
    string path_1 = "B.txt";
    string path_2 = "C.txt";
    string input = "Input.txt";

    TextFileNatural A(path);
    TextFileNatural B(path_1);
    TextFileNatural C(path_2);
    TextFileNatural In(input);

    string temp;

    In.openAdd();
    A.openErase();
    times += 3;
    while (!In.file.eof())
    {
        getline(In.file, temp);
        if (temp != "")
        {
            A.file << temp << '\n';
        }
    }
    In.close();
    A.close();

    int runSize;
    int tempSize = size;

    while (tempSize % 2 == 0)
    {
        tempSize /= 2;
    }

    runSize = tempSize * 2;

    naturalExternalSort(A, B, C, runSize, size, times);
    string tempOut = "Temp Natural Output.txt";
    string out = "Natural Output.txt";
    unsigned int end_time = clock();
    cleanOutput(tempOut, out, zero, negOne);
    return end_time - start_time;
};