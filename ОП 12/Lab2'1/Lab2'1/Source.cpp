#include "Header.h"

void alph_sorting(string even_str, string path_4, string path_2, string path_5)
{

    int size_2 = fill_vrem(path_4, path_2, even_str);

    int* arr_2 = create_array_2(path_4, size_2);

    fstream addi(path_5, fstream::in | fstream::out | fstream::trunc);
    addi.close();

    for (int i = 0; i < size_2; i++)
    {
        arrange_vrem(i, path_4, path_5, arr_2);
    }

    replace_vrem(path_4, path_5);
}

void replace_vrem(string path_4, string path_5)
{
    fstream vrem(path_4, fstream::in | fstream::out | fstream::trunc);
    fstream addi(path_5, fstream::in | fstream::out | fstream::app);

    string row;

    while (!addi.eof())
    {
        getline(addi, row);
        for (int i = 0; i < row.length(); i++)
        {
            if (row[i] == '\n')
            {
                row[i] = ' ';
            }
        }
        vrem << row << " ";
    }
}

void arrange_vrem(int i, string path_4, string path_5, int arr[])
{
    fstream vrem(path_4, fstream::in | fstream::out | fstream::app);
    fstream addi(path_5, fstream::in | fstream::out | fstream::app);

    string lex;

    while (!vrem.eof())
    {
        getline(vrem, lex);
        if (arr[i] == lex[0])
        {
            addi << lex;
            addi << '\n';
        }
    }

    vrem.close();
    addi.close();
}

int* create_array_2(string path_4, int size_2)
{
    fstream vrem(path_4, fstream::in | fstream::out | fstream::app);

    int* arr_2 = new int[size_2];

    string joj;

    int h = 0;
    int a;

    while (!vrem.eof())
    {
        getline(vrem, joj);
        a = joj[0];
        arr_2[h] = a;
        h++;
    }

    int temp = arr_2[0];

    for (int i = 0; i < size_2; i++) {
        for (int j = 0; j < size_2; j++) {
            if (arr_2[j - 1] > arr_2[j]) {
                temp = arr_2[j];
                arr_2[j] = arr_2[j - 1];
                arr_2[j - 1] = temp;
            }
        }
    }

    vrem.close();

    return arr_2;
}

int fill_vrem(string path_4, string path_2, string even_str)
{
    fstream vrem(path_4, fstream::in | fstream::out | fstream::app);
    fstream even(path_2, fstream::in | fstream::out | fstream::app);

    string str = even_str;
    int size = 1;


    for (int i = 0; i < str.length(); i++)
    {
        if (isspace(str[i]))
        {
            str[i] = '\n';
            size++;
        }
    }
    vrem << str;

    even.close();
    vrem.close();

    return size;
}

void replace_uneven(string path_4, string path_3)
{
    fstream vrem(path_4, fstream::in | fstream::out | fstream::app);
    fstream uneven(path_3, fstream::in | fstream::out | fstream::trunc);

    string lex;

    while (!vrem.eof())
    {
        getline(vrem, lex);
        uneven << lex;
        uneven << '\n';
    }

    vrem.close();
    uneven.close();
}

void change(int i, string path_4, string path_3, int arr[])
{
    fstream vrem(path_4, fstream::in | fstream::out | fstream::app);
    fstream uneven(path_3, fstream::in | fstream::out | fstream::app);

    string lex;

    while (!uneven.eof())
    {
        getline(uneven, lex);
        if (arr[i] == lex[0])
        {
            vrem << lex;
            vrem << '\n';
        }
    }

    uneven.close();
    vrem.close();
}

int* create_array(string path_3, int size)
{
    int* arr = new int[size];

    fstream uneven(path_3, fstream::in | fstream::out | fstream::app);

    string joj;

    int h = 0;
    int a;

    while (!uneven.eof())
    {
        getline(uneven, joj);
        a = joj[0];
        arr[h] = a;
        h++;
    }

    int temp = arr[0];

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (arr[j - 1] > arr[j]) {
                temp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = temp;
            }
        }
    }

    uneven.close();

    return arr;
}

int fill_files(string path_1, string path_2, string path_3, int rows)
{
    fstream even(path_2, fstream::in | fstream::out | fstream::trunc);
    fstream uneven(path_3, fstream::in | fstream::out | fstream::trunc);

    string row;

    int j = 0;

    int size = 0;

    fstream original(path_1, fstream::in | fstream::out | fstream::app);

    while (!original.eof())
    {
        row = "";

        if (j == rows - 1)
        {
            break;
        }

        if (j % 2 == 0)
        {
            getline(original, row);
            uneven << row;
            uneven << '\n';
            size++;
        }

        if (j % 2 != 0)
        {
            getline(original, row);
            even << row;
            even << '\n';
        }

        j++;

    }

    original.close();
    even.close();
    uneven.close();

    return size;
}

int fill_og(string path_1)
{
    char choice;

    int k = 0;

    fstream original(path_1, fstream::in | fstream::out | fstream::trunc);

    if (!original.is_open())
    {
        cout << "Error" << endl;
    }
    else
    {
        string str;
        while (str != "end") {
            getline(cin, str);
            original << str;
            original << '\n';
            k++;
        }
    }

    original.close();

    cout << endl;

    return k;
}