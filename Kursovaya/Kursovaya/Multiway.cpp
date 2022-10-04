//Основний файл багатошляхового сортування
#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"

void mergeFilesMultiway(string output_file, int n, int k, int& times)
{
    char out_path[] = "Multiway Output.txt";
    FILE* in[100];
    for (int i = 0; i < k; i++) {
        char fileName[2];

        snprintf(fileName, sizeof(fileName), "%d", i);

        in[i] = fopen(fileName, "r");
        times++;
    }

    FILE* out = fopen(out_path, "w");
    times++;

    //створюємо незростаючу піраміду, що буде містити в собі перші елементи кожного файлу
    //заносимо корінь пірміди до вихідного файлу та зміюємо піраміду відповідно, додавши наступний елемент тимчасового файлу
    MinHeapNode* harr = new MinHeapNode[k];
    int i;
    times++;
    for (i = 0; i < k; i++)
    {
        if (fscanf(in[i], "%d\n", &harr[i].element) != 1)
        {
            break;
        }

        harr[i].i = i;
    }
    MinHeap hp(harr, i);

    int count = 0;

    while (count != i) {
        MinHeapNode root = hp.getMin();
        fprintf(out, "%d\n", root.element);

        if (fscanf(in[root.i], "%d\n", &root.element) != 1)
        {
            root.element = INT_MAX;
            count++;
        }

        hp.replaceMin(root);
    }

    for (int i = 0; i < k; i++)
    {
        fclose(in[i]);
    }

    fclose(out);
}

void multiwaySort(TextFileMultiway& inFile, string output_file, int num_ways, int run_size, int& times)
{
    inFile.createInitialRuns(run_size, num_ways, times);

    mergeFilesMultiway(output_file, run_size, num_ways, times);
}

int multiwaySortStart(int size, int& times)
{
    unsigned int start_time = clock();
    int numWays;
    //кількість тимчасових файлів
    if (size >= 100)
    {
        numWays = 100;
    }
    else if (size >= 10)
    {
        numWays = 10;
    }
    else
    {
        numWays = 1;
    }

    //кількість елементів в них
    int runSize = size/numWays;

    string input_file = "Input.txt";
    string output_file = "Multiway Output.txt";

    TextFileMultiway inFile(input_file);

    multiwaySort(inFile, output_file, numWays, runSize, times);

    unsigned int end_time = clock();
    return end_time - start_time;
}