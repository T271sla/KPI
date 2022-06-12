#include "Header.h"

void polyphaseSort(int n, int m, int check_1, int check_2, int check_3, class TextFile& One, class TextFile& Two, class TextFile& Three, class TextFile& Addon, int fib[], int idx, int lastIdx)
{
    //заповнюємо третій файл необхідною кілкістю перенесених та відсортований серій з перший двух
    Three.fillFilePolyphase(m, fib[idx], One, Two, Three, Addon);

    //якщо залишилося два файли по одній серії, то об'єднюємо їх без використання пам'яті на масив
    if (fib[idx + 1] == fib[lastIdx])
    {
        string B = "1.txt";
        string C = "2.txt";
        string A = "Polyphase Output.txt";
        mergeFiles(B, C, A);
        return;
    }

    //в залежності від кількості серій в кожному файлі на данний момент робимо їх першим, другим чи третім
    //перший-більний
    //другий-менший
    //третій-порожній
    if ((check_1 > check_2) && (check_3 == 0))
    {
        polyphaseSort(m, n - m, n - m, 0, m, Three, One, Two, Addon, fib, idx + 1, lastIdx);
    }
    else if ((check_3 > check_1) && (check_2 == 0))
    {
        polyphaseSort(m, n - m, 0, m, n - m, Three, One, Two, Addon, fib, idx + 1, lastIdx);
    }
    else if ((check_2 > check_3) && (check_1 == 0))
    {
        polyphaseSort(m, n - m, m, n - m, 0, Three, One, Two, Addon, fib, idx + 1, lastIdx);
    }
}

void PolyPhaseSortStart()
{
    srand(time(NULL));
    string path_1 = "1.txt";
    string path_2 = "2.txt";
    string path_3 = "3.txt";
    string path_4 = "addon.txt";

    string path = "original.txt";


    //заповнюємо оригінальний файл
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
    original.fill12(10000, 66, 34, 89, 55, one, two);//заповнюємо файли 1.txt та 2.txt
    original.close();
    one.close();
    two.close();
    three.close();

    int fib[] = { 20000, 30000, 50000, 80000, 130000, 210000, 340000, 550000, 890000, 1440000 };//ряд Фібоначчі, який буду виступати кількістю елементів в серії третього файлу
    int lastIdx = 9;//індекс його останнього числа
    int idx = 0;//поточний індекс

    polyphaseSort(89, 55, 89, 55, 0, one, two, three, addon, fib, idx, lastIdx);
};