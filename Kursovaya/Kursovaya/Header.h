#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <cstdio>
#include <ctime>
#include <vector>;
using namespace std;

int PolyPhaseSortStart(int size, int& times, int zero, int negOne);
void polyphaseSort(int n, int m, int check_1, int check_2, int check_3, class TextFilePoly& One, class TextFilePoly& Two, class TextFilePoly& Three, class TextFilePoly& Addon, int fib[], int idx, int lastIdx, int& times);
void fill_matrix(int** matrix, string path);
void mergeSort(int array[], int const begin, int const end);
void merge(int array[], int const left, int const mid, int const right);
void mergeFiles(string B, string C, string A);
int naturalExternalSortStart(int size, int& times, int zero, int negOne);
void naturalExternalSort(class TextFileNatural& A, class TextFileNatural& B, class TextFileNatural& C, int size, int n, int& times);
void createArr(int size, class TextFileNatural& B, class TextFileNatural& C, class TextFileNatural& A);
int multiwaySortStart(int size, int& times);
void mergeFilesMultiway(string output_file, int n, int k, int& times);
void mergeSortMultiway(int arr[], int l, int r);
void mergeMultiway(int arr[], int l, int m, int r);
void cleanOutput(string path_1, string path_2, int zero, int negOne);
void createInput(int size, int min, int max, int& zero, int& negOne);


//клас файлу
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

    TextFilePoly(string pathTo):TextFile(pathTo)
    {
        
    }

    void fillFilePolyphase(int runs, int size, class TextFilePoly& One, class TextFilePoly& Two, class TextFilePoly& Three, class TextFilePoly& Addon, int& times)
    {
        int onePosition = 0;
        int twoPosition = 0;
        int iteration = 0;//інтерація масиву fillThree
        fillThree(size, iteration, runs, onePosition, twoPosition, One, Two, Three, times);
        clearOne(runs, onePosition, One, Addon, times);
        Two.openErase();
        Two.close();
        times++;
    }

    //метод виконуючий аналогічні дії, що і минулий для багатофазового сортування
    void fill12(int run, int oneRuns, int twoRuns, int oneAddRuns, int twoAddRuns, class TextFilePoly& One, class TextFilePoly& Two, int& times)
    {
        string temp;
        int count = 0;
        int anotherCount = 0;

        times++;
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
    void fillThree(int size, int iteration, int runs, int& currOnePosition, int& currTwoPosition, class TextFilePoly& One, class TextFilePoly& Two, class TextFilePoly& Three, int& times)
    {
        if (iteration == runs)
        {
            return; //пертаємося, коли кількість інтерацій дійшла до кількості необхідних серій
        }
        One.openAdd();
        Two.openAdd();
        times += 2;
        int* arr = new int[size];
        int pos = 0;//індекс числа в масиві
        string temp;
        Two.file.seekg(currTwoPosition, ios_base::beg);
        One.file.seekg(currOnePosition, ios_base::beg);
        times++;
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

        times++;
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
        times++;
        for (int i = 0; i < size; i++)
        {
            Three.file << arr[i] << '\n';//заповнюмє файл
        }
        Three.file << "-" << '\n';
        Three.close();

        One.close();
        Two.close();
        delete[] arr;

        fillThree(size, iteration + 1, runs, currOnePosition, currTwoPosition, One, Two, Three, times);//переходимо до наступний серій в файлах
    }

    //метод для видалення переміщенних серій з більшого файлу
    //переносимо необхідні серії в додатковий файл, видаляємо все з першого, та переносимо збережені елементи назад
    void clearOne(int runs, int onePosition, class TextFilePoly& One, class TextFilePoly& Addon, int& times)
    {
        string temp;

        Addon.openErase();
        One.openAdd();
        times += 2;
        One.file.seekg(onePosition, ios_base::beg);
        times++;
        while (!One.file.eof())
        {
            getline(One.file, temp);
            Addon.file << temp << '\n';
        }
        Addon.close();
        One.close();

        Addon.openAdd();
        One.openErase();
        times += 3;

        while (!Addon.file.eof())
        {
            getline(Addon.file, temp);
            One.file << temp << '\n';
        }

        Addon.close();
        One.close();
    }
};

class TextFileNatural : public TextFile
{
public:
    TextFileNatural(string pathTo) :TextFile(pathTo)
    {

    }
    //метод для природного злиття
    //передаємо файли В та С та кількість елементів в серії
    //елементи с файлу А копіюються в файли В та С
    //додаємо "-", щоб відділяти серії
    void fillBC(int n, class TextFile& B, class TextFile& C)
    {
        string temp;
        int count = 0;
        int anotherCount = 0;

        while (!file.eof())
        {
            getline(file, temp);
            if (count == 1)
            {
                C.file << temp << '\n';
                anotherCount++;
                if (anotherCount == n / 2)
                {
                    C.file << "-" << '\n';
                    anotherCount = 0;
                    count++;
                }
            }
            if (count == 0)
            {
                B.file << temp << '\n';
                anotherCount++;
                if (anotherCount == n / 2)
                {
                    B.file << "-" << '\n';
                    anotherCount = 0;
                    count++;
                }

            }
            if (count == 2)
            {
                count = 0;
            }
        }
    }

    void fillArrNatural(int size, class TextFile& B, class TextFile& C, class TextFile& A)
    {
        int* arr = new int[size];
        int pos = 0;

        string temp;
        string row = "";

        //кількість строк у файлі
        int strB = 0;
        int strC = 0;

        //перевірка чи закінчився файл
        bool fileB = false;
        bool fileC = false;
        bool both = false;

        while ((!file.eof()) && (!C.file.eof()))
        {
            getline(file, temp);
            strB++;
            if ((temp != "-") && ((temp != "")))
            {
                arr[pos] = stoi(temp);
                pos++;
            }
            if (temp == "")
            {
                fileB = true;
            }
            getline(C.file, temp);
            strC++;
            if ((temp != "-") && ((temp != "")))
            {
                arr[pos] = stoi(temp);
                pos++;
            }
            if (temp == "")
            {
                fileC = true;
            }
            if (pos == size)
            {
                mergeSort(arr, 0, size - 1);
                A.arrToFile(arr, size);
                pos = 0;
            }
            if (fileB && fileC)
            {
                both = true;
                fileB = false;
                fileC = false;
            }
        }

        int getTo = 0;

        //заповнюємо файл А відсортованими масивами
        if (fileB && !fileC)
        {
            while (!file.eof())
            {
                getline(file, temp);
                getTo++;
                if (getTo > strB)
                {
                    if ((temp != "-") && ((temp != "")))
                    {
                        A.file << temp << '\n';
                    }
                }
            }
        }
        if (fileC && !fileB)
        {
            while (!C.file.eof())
            {
                getline(C.file, temp);
                getTo++;
                if (getTo > strC)
                {
                    if ((temp != "-") && ((temp != "")))
                    {
                        A.file << temp << '\n';
                    }
                }
            }
        }

        delete[] arr;
    }
};

class TextFileMultiway : public TextFile
{
public:
    TextFileMultiway(string pathTo) :TextFile(pathTo)
    {

    }

    void setPath(string pathTo)
    {
        string path = pathTo;
    }
    
    void createInitialRuns(int run_size, int num_ways, int& times)
    {
        openAdd();
        times++;

        //створюємо задану кількість файлів, в яких будуть знаходитися відсортовані масиви
        vector<TextFileMultiway*> outFile;

        for (int i = 0; i < num_ways; i++)
        {
            string num = to_string(i);
            TextFileMultiway* fl = new TextFileMultiway(num);
            outFile.push_back(fl);
            outFile[i]->openErase();
            times++;
        }

        int* arr = new int[run_size];

        bool more_input = true;
        int next_output_file = 0;

        int i;
        string temp;
        int pos = 0;
        //заповнюємо масив необхідною кількістю елементів, пілся чого сортуємо його та відправляємо в тимчасовий файл
        times++;
        while (!file.eof())
        {
            getline(file, temp);
            if ((temp != "") && (pos < run_size))
            {
                arr[pos] = stoi(temp);
                pos++;
            }
            if (temp == "")
            {
                break;
            }

            if (pos == run_size)
            {
                mergeSort(arr, 0, pos - 1);

                for (int j = 0; j < run_size; j++)
                {
                    outFile[next_output_file]->file << arr[j] << '\n';
                }
                next_output_file++;
                pos = 0;
            }
        }

        for (int i = 0; i < num_ways; i++)
        {
            outFile[i]->close();
        }

        close();
    }
};

struct MinHeapNode {
    int element;

    int i;
};

class MinHeap {

    MinHeapNode* harr;

    int heap_size;

public:

    int left(int i)
    {
        return (2 * i + 1);
    }

    int right(int i)
    {
        return (2 * i + 2);
    }

    MinHeapNode getMin()
    {
        return harr[0];
    }

    void replaceMin(MinHeapNode x)
    {
        harr[0] = x;
        MinHeapify(0);
    }

    MinHeap(MinHeapNode arr[], int size)
    {
        heap_size = size;
        harr = arr;
        int i = (heap_size - 1) / 2;
        while (i >= 0) {
            MinHeapify(i);
            i--;
        }
    }

    void MinHeapify(int i)
    {
        int l = left(i);
        int r = right(i);
        int smallest = i;
        if (l < heap_size && harr[l].element < harr[i].element)
            smallest = l;
        if (r < heap_size && harr[r].element < harr[smallest].element)
            smallest = r;
        if (smallest != i) {
            swap(&harr[i], &harr[smallest]);
            MinHeapify(smallest);
        }
    }

    void swap(MinHeapNode* x, MinHeapNode* y)
    {
        MinHeapNode temp = *x;
        *x = *y;
        *y = temp;
    }
};
