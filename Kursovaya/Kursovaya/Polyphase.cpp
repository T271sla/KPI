//Основний файл багатофазового сортування
#include "Header.h"

void polyphaseSort(int n, int m, int check_1, int check_2, int check_3, class TextFilePoly& One, class TextFilePoly& Two, class TextFilePoly& Three, class TextFilePoly& Addon, int fib[], int idx, int lastIdx, int& times)
{
    //якщо залишилося два файли по одній серії, то об'єднюємо їх без використання пам'яті на масив
    if (fib[idx] == fib[lastIdx])
    {
        string B = "Poly1.txt";
        string C = "Poly2.txt";
        string A = "Temp Polyphase Output.txt";
        mergeFiles(B, C, A);
        return;
    }

    //заповнюємо третій файл необхідною кілкістю перенесених та відсортований серій з перший двух
    Three.fillFilePolyphase(m, fib[idx], One, Two, Three, Addon, times);

    //в залежності від кількості серій в кожному файлі на данний момент робимо їх першим, другим чи третім
    //перший-більний
    //другий-менший
    //третій-порожній
    if ((check_1 > check_2) && (check_3 == 0))
    {
        polyphaseSort(m, n - m, n - m, 0, m, Three, One, Two, Addon, fib, idx + 1, lastIdx, times);
    }
    else if ((check_3 > check_1) && (check_2 == 0))
    {
        polyphaseSort(m, n - m, 0, m, n - m, Three, One, Two, Addon, fib, idx + 1, lastIdx, times);
    }
    else if ((check_2 > check_3) && (check_1 == 0))
    {
        polyphaseSort(m, n - m, m, n - m, 0, Three, One, Two, Addon, fib, idx + 1, lastIdx, times);
    }
}

int PolyPhaseSortStart(int size, int& times, int zero, int negOne)
{
    unsigned int start_time = clock();
    string path_1 = "Poly1.txt";
    string path_2 = "Poly2.txt";
    string path_3 = "Poly3.txt";
    string path_4 = "addon.txt";

    string path = "Input.txt";

    TextFilePoly original(path);

    TextFilePoly one(path_1);
    TextFilePoly two(path_2);
    TextFilePoly three(path_3);
    TextFilePoly addon(path_4);

    original.openAdd();
    one.openErase();
    two.openErase();
    three.openErase();
    times += 4;
    original.fill12(size / 100, 66, 34, 89, 55, one, two, times);//заповнюємо файли 1.txt та 2.txt
    original.close();
    one.close();
    two.close();
    three.close();

    int templateFib[] = { 2, 3, 5, 8, 13, 21, 34, 55, 89, 144 };//ряд Фібоначчі, який буду виступати кількістю елементів в серії третього файлу
    int lastIdx = 9;//індекс його останнього числа
    int fib[10];
    int idx = 0;//поточний індекс

    for (int i = 0; i < 10; i++)
    {
        fib[i] = templateFib[i] * (size / 100);
    }

    polyphaseSort(89, 55, 89, 55, 0, one, two, three, addon, fib, idx, lastIdx, times);
    string tempOut = "Temp Polyphase Output.txt";
    string out = "Polyphase Output.txt";
    unsigned int end_time = clock();
    cleanOutput(tempOut, out, zero, negOne);

    return end_time - start_time;
};