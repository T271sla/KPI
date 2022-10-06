#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <cstdio>
#include <ctime>
#include <vector>;
using namespace std;

void merge(int array[], int const left, int const mid, int const right);
void mergeSort(int array[], int const begin, int const end);
void mergeFiles(string B, string C, string A);
void cleanOutput(string path_1, string path_2, int zero, int negOne);
void createInput(int size, int min, int max, int& zero, int& negOne);
void polyphaseSort(int n, int m, int check_1, int check_2, int check_3, class TextFilePoly& One, class TextFilePoly& Two, class TextFilePoly& Three, class TextFilePoly& Addon, int fib[], int idx, int lastIdx);

class TextFile
{
protected:
    string path;
public:
    fstream file;
    TextFile(string pathTo)
    {
        path = pathTo;
    }

    //відкриття файлу, не видаляючу його зміст
    void openAdd()
    {
        file.open(path, fstream::in | fstream::out | fstream::app);
    }

    //відкриття файлу, видаляючу його зміст
    void openErase()
    {
        file.open(path, fstream::in | fstream::out | fstream::trunc);
    }

    //закриття файлу
    void close()
    {
        file.close();
    }

    //заповнення файлу випадковими цілочисельними елементами
    void fillFile(int size, int min, int max, int& zero, int& negOne)
    {
        int dig;
        srand(time(NULL));
        if ((max >= 0) && (min >= 0))
        {
            for (int i = 0; i < size; i++)
            {
                dig = rand() % (max - min) + min;
                if (dig == 0)
                {
                    zero++;
                }
                if (dig == -1)
                {
                    negOne++;
                }
                file << dig << '\n';
            }
        }
        if ((max >= 0) && (min < 0))
        {
            for (int i = 0; i < size; i++)
            {
                dig = (rand() % max) - (rand() % (min * -1));
                if (dig == 0)
                {
                    zero++;
                }
                if (dig == -1)
                {
                    negOne++;
                }
                file << dig - 1 << '\n';
            }
        }
        if ((max < 0) && (min < 0))
        {
            for (int i = 0; i < size; i++)
            {
                dig = -(rand() % (max - min) + min);
                if (dig == 0)
                {
                    zero++;
                }
                if (dig == -1)
                {
                    negOne++;
                }
                file << dig << '\n';
            }
        }
    }

    //переміщення масиву цілочисельних елементів до файлу
    void arrToFile(int arr[], int size)
    {
        for (int i = 0; i < size; i++)
        {
            file << arr[i] << '\n';
        }
    }
};

class TextFilePoly : public TextFile
{
public:

    TextFilePoly(string pathTo) :TextFile(pathTo)
    {

    }

    void fillFilePolyphase(int runs, int size, class TextFilePoly& One, class TextFilePoly& Two, class TextFilePoly& Three, class TextFilePoly& Addon)
    {
        int onePosition = 0;
        int twoPosition = 0;
        int iteration = 0;//інтерація масиву fillThree
        fillThree(size, iteration, runs, onePosition, twoPosition, One, Two, Three);
        clearOne(runs, onePosition, One, Addon);
        Two.openErase();
        Two.close();
    }

    //метод виконуючий аналогічні дії, що і минулий для багатофазового сортування
    void fill12(int run, int oneRuns, int twoRuns, int oneAddRuns, int twoAddRuns, class TextFilePoly& One, class TextFilePoly& Two)
    {
        string temp;
        int count = 0;
        int anotherCount = 0;

        while (!file.eof())
        {
            getline(file, temp);
            if ((count >= oneRuns) && (temp != ""))
            {
                Two.file << temp << '\n';
                anotherCount++;
                if (anotherCount == run)
                {
                    Two.file << "-" << '\n';
                    anotherCount = 0;
                }
            }
            if ((count < oneRuns) && (temp != ""))
            {
                One.file << temp << '\n';
                anotherCount++;
                if (anotherCount == run)
                {
                    One.file << "-" << '\n';
                    anotherCount = 0;
                    count++;
                }

            }
        }

        //заповнюємо файли 1 та 2 далі, щоб кількість елементів в них була кратна числам с ряду Фібоначчі
        for (int i = oneRuns; i < oneAddRuns; i++)
        {
            for (int j = 0; j < run; j++)
            {
                One.file << -1 << '\n';
            }
            One.file << "-" << '\n';
        }

        for (int i = twoRuns; i < twoAddRuns; i++)
        {
            for (int j = 0; j < run; j++)
            {
                Two.file << -1 << '\n';
            }
            Two.file << "-" << '\n';
        }
    }

    //метод для заповнення третього файлу в багатофазному сортуванні
    void fillThree(int size, int iteration, int runs, int& currOnePosition, int& currTwoPosition, class TextFilePoly& One, class TextFilePoly& Two, class TextFilePoly& Three)
    {
        if (iteration == runs)
        {
            return; //пертаємося, коли кількість інтерацій дійшла до кількості необхідних серій
        }
        One.openAdd();
        Two.openAdd();
        int* arr = new int[size];
        int pos = 0;//індекс числа в масиві
        string temp;
        Two.file.seekg(currTwoPosition, ios_base::beg);
        One.file.seekg(currOnePosition, ios_base::beg);
        while (!Two.file.eof())
        {
            getline(Two.file, temp);
            currTwoPosition += temp.length() + 2;//зберегаємо байт числа, щоб одразу перейти до потрібного елемента в наступній ітерачії
            if ((temp != "-") && (temp != ""))
            {
                arr[pos] = stoi(temp);
                pos++;
            }
            if (temp == "-")
            {
                break;//серія окінчена
            }
        }

        while (!One.file.eof())
        {
            getline(One.file, temp);
            currOnePosition += temp.length() + 2;//аналогічно currTwoPosition
            if ((temp != "-") && (temp != ""))
            {
                arr[pos] = stoi(temp);
                pos++;
            }
            if (temp == "-")
            {
                break;
            }
        }

        One.close();
        Two.close();

        mergeSort(arr, 0, size - 1);//сортуємо масив
        Three.openAdd();
        for (int i = 0; i < size; i++)
        {
            Three.file << arr[i] << '\n';//заповнюмє файл
        }
        Three.file << "-" << '\n';
        Three.close();

        One.close();
        Two.close();
        delete[] arr;

        fillThree(size, iteration + 1, runs, currOnePosition, currTwoPosition, One, Two, Three);//переходимо до наступний серій в файлах
    }

    //метод для видалення переміщенних серій з більшого файлу
    //переносимо необхідні серії в додатковий файл, видаляємо все з першого, та переносимо збережені елементи назад
    void clearOne(int runs, int onePosition, class TextFilePoly& One, class TextFilePoly& Addon)
    {
        string temp;

        Addon.openErase();
        One.openAdd();
        One.file.seekg(onePosition, ios_base::beg);
        while (!One.file.eof())
        {
            getline(One.file, temp);
            Addon.file << temp << '\n';
        }
        Addon.close();
        One.close();

        Addon.openAdd();
        One.openErase();

        while (!Addon.file.eof())
        {
            getline(Addon.file, temp);
            One.file << temp << '\n';
        }

        Addon.close();
        One.close();
    }
};

int main()
{
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

    int size;
    int min;
    int max;
    int zero = 0;
    int negOne = 0;

    cout << "Enter size: ";
    cin >> size;
    cout << "Enter min element: ";
    cin >> min;
    cout << "Enter max element: ";
    cin >> max;

    createInput(size, min, max, zero, negOne);
    original.openAdd();
    one.openErase();
    two.openErase();
    three.openErase();
    original.fill12(size / 100, 66, 34, 89, 55, one, two);//заповнюємо файли 1.txt та 2.txt
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

    polyphaseSort(89, 55, 89, 55, 0, one, two, three, addon, fib, idx, lastIdx);
    string tempOut = "Temp Polyphase Output.txt";
    string out = "Polyphase Output.txt";
    cleanOutput(tempOut, out, zero, negOne);
}

void createInput(int size, int min, int max, int& zero, int& negOne)
{
    string path = "Input.txt";
    TextFile original(path);
    original.openErase();
    original.fillFile(size, min, max, zero, negOne);
    original.close();
}

void polyphaseSort(int n, int m, int check_1, int check_2, int check_3, class TextFilePoly& One, class TextFilePoly& Two, class TextFilePoly& Three, class TextFilePoly& Addon, int fib[], int idx, int lastIdx)
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
    Three.fillFilePolyphase(m, fib[idx], One, Two, Three, Addon);

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

void merge(int array[], int const left, int const mid, int const right)
{
    auto const subArrayOne = mid - left + 1;
    auto const subArrayTwo = right - mid;

    auto* leftArray = new int[subArrayOne],
        * rightArray = new int[subArrayTwo];

    for (auto i = 0; i < subArrayOne; i++)
        leftArray[i] = array[left + i];
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray[j] = array[mid + 1 + j];

    auto indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0;
    int indexOfMergedArray = left;

    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else {
            array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }
    while (indexOfSubArrayOne < subArrayOne) {
        array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }
    while (indexOfSubArrayTwo < subArrayTwo) {
        array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
}

void mergeSort(int array[], int const begin, int const end)
{
    if (begin >= end)
    {
        return;
    }

    auto mid = begin + (end - begin) / 2;
    mergeSort(array, begin, mid);
    mergeSort(array, mid + 1, end);
    merge(array, begin, mid, end);
}

//функція для об'єднання двох файлів з відсортованними елементами
void mergeFiles(string B, string C, string A) {
    ifstream fin(B);
    ifstream fin2(C);
    ofstream fout(A);

    string line;
    int in1, in2;
    if (fin) {
        getline(fin, line);
        in1 = atoi(line.c_str());
    }
    if (fin2) {
        getline(fin2, line);
        in2 = atoi(line.c_str());
    }
    bool first = true;
    while (fin || fin2) {
        if (fin && fin2) {
            if (in2 <= in1) {
                fout << in2 << endl;
                getline(fin2, line);
                in2 = atoi(line.c_str());
            }
            else {
                fout << in1 << endl;
                getline(fin, line);
                in1 = atoi(line.c_str());
            }
        }
        else {
            if (first) {
                if (!fin) {
                    fout << in2 << endl;
                }
                else if (!fin2) {
                    fout << in1 << endl;
                }
            }
            else
            {
                fout << line << endl;
            }


            if (fin)
            {
                getline(fin, line);
            }
            else if (fin2)
            {
                getline(fin2, line);
            }

            first = false;
        }
    }
}

void cleanOutput(string path_1, string path_2, int zero, int negOne)
{
    fstream tempOutput(path_1, fstream::in | fstream::out | fstream::app);
    fstream Output(path_2, fstream::in | fstream::out | fstream::trunc);
    string temp;
    int zeroCount = 0;
    int negOneCount = 0;

    while (!tempOutput.eof())
    {
        getline(tempOutput, temp);
        if ((temp != "0") && (temp != "-1") && (temp != "-"))
        {
            Output << temp << '\n';
        }
        if ((temp == "0") && (zeroCount < zero))
        {
            Output << temp << '\n';
            zeroCount++;
        }
        if ((temp == "-1") && (negOneCount < negOne))
        {
            Output << temp << '\n';
            negOneCount++;
        }
    }
}
