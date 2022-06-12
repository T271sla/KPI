#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <cstdio>
#include <ctime>
using namespace std;

void PolyPhaseSortStart();
void polyphaseSort(int n, int m, int check_1, int check_2, int check_3, string path_1, string path_2, string path_3, int fib[], int idx);
void fill_matrix(int** matrix, string path);
void mergeSort(int array[], int const begin, int const end);
void merge(int array[], int const left, int const mid, int const right);
void mergeFiles(string B, string C, string A);
void naturalExternalSortStart();
void naturalExternalSort(class TextFile& A, class TextFile& B, class TextFile& C, int size, int n);
void createArr(int size, class TextFile& B, class TextFile& C, class TextFile& A);
void multiwaySortStart();
void multiwaySort(char* input_file, char* output_file, int num_ways, int run_size);
void createInitialRuns(char* input_file, int run_size, int num_ways);
void mergeFilesMultiway(char* output_file, int n, int k);
void mergeSortMultiway(int arr[], int l, int r);
void mergeMultiway(int arr[], int l, int m, int r);


//���� �����
class TextFile
{
private:
    string path;
public:
    fstream file;

    TextFile(string pathTo)
    {
        path = pathTo;
    }

    //�������� �����, �� ��������� ���� ����
    void openAdd()
    {
        file.open(path, fstream::in | fstream::out | fstream::app);
    }

    //�������� �����, ��������� ���� ����
    void openErase()
    {
        file.open(path, fstream::in | fstream::out | fstream::trunc);
    }

    //�������� �����
    void close()
    {
        file.close();
    }

    //���������� ����� ����������� �������������� ����������
    void fillFile(int n, int m)
    {
        for (int i = 0; i < n; i++)
        {
            file << rand() % m + 1 << '\n';
        }
    }

    //���������� ������ ������������� �������� �� �����
    void arrToFile(int arr[], int size)
    {
        for (int i = 0; i < size; i++)
        {
            file << arr[i] << '\n';
        }
    }

    //����� ��� ���������� ������
    //�������� ����� � �� � �� ������� �������� � ���
    //�������� � ����� � ��������� � ����� � �� �
    //������ "-", ��� ������� ���
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

    //����� ���������� �������� 䳿, �� � ������� ��� �������������� ����������
    void fill12(int run, int oneRuns, int twoRuns, int oneAddRuns, int twoAddRuns, class TextFile& One, class TextFile& Two)
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

        //���������� ����� 1 �� 2 ���, ��� ������� �������� � ��� ���� ������ ������ � ���� Գ�������
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

    void fillArrNatural(int size, class TextFile& B, class TextFile& C, class TextFile& A)
    {
        int* arr = new int[size];
        int pos = 0;

        string temp;
        string row = "";

        //������� ����� � ����
        int strB = 0;
        int strC = 0;

        //�������� �� ��������� ����
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

        //���������� ���� � ������������� ��������
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

    //����� ��� ���������� �������� ����� � ������������� ���������
    void fillThree(int size, int iteration, int runs, int& currOnePosition, int& currTwoPosition, class TextFile& One, class TextFile& Two, class TextFile& Three)
    {
        if (iteration == runs)
        {
            return; //���������, ���� ������� ��������� ����� �� ������� ���������� ����
        }
        One.openAdd();
        Two.openAdd();
        int* arr = new int[size];
        int pos = 0;//������ ����� � �����
        string temp;
        Two.file.seekg(currTwoPosition, ios_base::beg);
        One.file.seekg(currOnePosition, ios_base::beg);
        while (!Two.file.eof())
        {
            getline(Two.file, temp);
            currTwoPosition += temp.length() + 2;//��������� ���� �����, ��� ������ ������� �� ��������� �������� � �������� ��������
            if ((temp != "-") && (temp != ""))
            {
                arr[pos] = stoi(temp);
                pos++;
            }
            if (temp == "-")
            {
                break;//���� �������
            }
        }

        while (!One.file.eof())
        {
            getline(One.file, temp);
            currOnePosition += temp.length() + 2;//��������� currTwoPosition
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

        mergeSort(arr, 0, size - 1);//������� �����
        Three.openAdd();
        for (int i = 0; i < size; i++)
        {
            Three.file << arr[i] << '\n';//�������� ����
        }
        Three.file << "-" << '\n';
        Three.close();

        One.close();
        Two.close();
        delete[] arr;

        fillThree(size, iteration + 1, runs, currOnePosition, currTwoPosition, One, Two, Three);//���������� �� ��������� ���� � ������
    }


    //����� ��� ��������� ����������� ���� � ������� �����
    //���������� �������� ��� � ���������� ����, ��������� ��� � �������, �� ���������� �������� �������� �����
    void clearOne(int runs, int onePosition, class TextFile& One, class TextFile& Addon)
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

    void fillFilePolyphase(int runs, int size, class TextFile& One, class TextFile& Two, class TextFile& Three, class TextFile& Addon)
    {
        int onePosition = 0;
        int twoPosition = 0;
        int iteration = 0;//��������� ������ fillThree
        fillThree(size, iteration, runs, onePosition, twoPosition, One, Two, Three);
        clearOne(runs, onePosition, One, Addon);
        Two.openErase();
        Two.close();
    }
};
