#include "Header.h"

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

//������� ��� ��'������� ���� ����� � �������������� ����������
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