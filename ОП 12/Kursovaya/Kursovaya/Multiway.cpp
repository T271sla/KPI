#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"

struct MinHeapNode {
    int element;

    int i;
};

void swap(MinHeapNode* x, MinHeapNode* y);

class MinHeap {

    MinHeapNode* harr;

    int heap_size;

public:
    MinHeap(MinHeapNode a[], int size);

    void MinHeapify(int);

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
};

MinHeap::MinHeap(MinHeapNode a[], int size)
{
    heap_size = size;
    harr = a;
    int i = (heap_size - 1) / 2;
    while (i >= 0) {
        MinHeapify(i);
        i--;
    }
}

void MinHeap::MinHeapify(int i)
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

void mergeFilesMultiway(string output_file, int n, int k)
{
    char out_path[] = "Multiway Output.txt";
    FILE* in[100];
    for (int i = 0; i < k; i++) {
        char fileName[2];

        snprintf(fileName, sizeof(fileName), "%d", i);

        in[i] = fopen(fileName, "r");
    }

    FILE* out = fopen(out_path, "w");

    //створюємо незростаючу піраміду, що буде містити в собі перші елементи кожного файлу
    //заносимо корінь пірміди до вихідного файлу та зміюємо піраміду відповідно, додавши наступний елемент тимчасового файлу
    MinHeapNode* harr = new MinHeapNode[k];
    int i;
    for (i = 0; i < k; i++) {
        if (fscanf(in[i], "%d\n", &harr[i].element) != 1)
            break;

        harr[i].i = i;
    }
    MinHeap hp(harr, i);

    int count = 0;

    while (count != i) {
        MinHeapNode root = hp.getMin();
        fprintf(out, "%d\n", root.element);

        if (fscanf(in[root.i], "%d\n", &root.element) != 1) {
            root.element = INT_MAX;
            count++;
        }

        hp.replaceMin(root);
    }

    for (int i = 0; i < k; i++)
        fclose(in[i]);

    fclose(out);
}

void createInitialRuns(string input_file, int run_size, int num_ways)
{
    TextFile inFile(input_file);
    inFile.openAdd();

    //створюємо задану кількість файлів, в яких будуть знаходитися відсортовані масиви
    fstream outFile[100];

    for (int i = 0; i < num_ways; i++)
    {
        string num = to_string(i);
        outFile[i].open(num, fstream::in | fstream::out | fstream::trunc);
    }

    int* arr = (int*)malloc(run_size * sizeof(int));

    bool more_input = true;
    int next_output_file = 0;

    int i;
    string temp;
    int pos = 0;
    //заповнюємо масив необхідною кількістю елементів, пілся чого сортуємо його та відправляємо в тимчасовий файл
    while (!inFile.file.eof())
    {
        getline(inFile.file, temp);
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
                outFile[next_output_file] << arr[j] << '\n';
            }
            next_output_file++;
            pos = 0;
        }
    }

    for (int i = 0; i < num_ways; i++)
    {
        outFile[i].close();
    }

    inFile.close();
}

void multiwaySort(string input_file, string output_file, int num_ways, int run_size)
{
    createInitialRuns(input_file, run_size, num_ways);

    mergeFilesMultiway(output_file, run_size, num_ways);
}

void multiwaySortStart()
{
    srand(time(NULL));
    //кількість тимчасових файлів
    int numWays = 100;

    //кількість елементів в них
    int runSize = 100;

    string input_file = "Multiway Input.txt";
    string output_file = "Multiway Output.txt";

    TextFile inFile(input_file);

    inFile.openErase();

    srand(time(NULL));

    inFile.fillFile(numWays * runSize, 1000);

    inFile.close();

    multiwaySort(input_file, output_file, numWays, runSize);
}