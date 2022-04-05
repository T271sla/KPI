#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <stdio.h>
#include "Header.h"
using namespace std;

int main()
{

    string path_1 = "original.txt";
    string path_2 = "even.txt";
    string path_3 = "uneven.txt";
    string path_4 = "vrem.txt";
    string path_5 = "addi.txt";
    fstream original;
    fstream even;
    fstream uneven;
    fstream vrem;
    fstream addi;

    cout << "Enter strings for the first file strings (enter 'end' to proceed):" << endl;

    int rows = fill_og(path_1);

    cout << endl;

    int size = fill_files(path_1, path_2, path_3, rows);

    cout << "Even strings:" << endl;
    even.open(path_2, fstream::in | fstream::out | fstream::app);

    string show;

    while (!even.eof())
    {
        show = "";
        getline(even, show);
        cout << show << endl;
    }
    even.close();
    
    cout << endl;
    cout << endl;

    cout << "Unven strings:" << endl;

    uneven.open(path_3, fstream::in | fstream::out | fstream::app);
    
    while (!uneven.eof())
    {
        show = "";
        getline(uneven, show);
        cout << show << endl;
    }
    uneven.close();


    int* arr = create_array(path_3, size);

    vrem.open(path_4, fstream::in | fstream::out | fstream::trunc);
    vrem.close();

    for (int i = 0; i < size; i++)
    {
        change(i, path_4, path_3, arr);
    }

    cout << endl;

    replace_uneven(path_4, path_3);

    even.open(path_2, fstream::in | fstream::out | fstream::app);
    vrem.open(path_4, fstream::in | fstream::out | fstream::trunc);
    vrem.close();

    string even_str;

    while (!even.eof())
    {
        getline(even, even_str);
        alph_sorting(even_str, path_4, path_2, path_5);
    }
    even.close();

    even.open(path_2, fstream::in | fstream::out | fstream::trunc);
    vrem.open(path_4, fstream::in | fstream::out | fstream::app);

    string fin;

    while (!vrem.eof())
    {
        getline(vrem, fin);
        even << fin;
    }

    even.close();
    vrem.close();

    remove("vrem.txt");
    remove("addi.txt");

    cout << endl;

    cout << "Altered even strings:" << endl;
    even.open(path_2, fstream::in | fstream::out | fstream::app);

    while (!even.eof())
    {
        show = "";
        getline(even, show);
        cout << show << endl;
    }
    even.close();

    cout << endl;
    cout << endl;

    cout << "Altered unven strings:" << endl;

    uneven.open(path_3, fstream::in | fstream::out | fstream::app);

    while (!uneven.eof())
    {
        show = "";
        getline(uneven, show);
        cout << show << endl;
    }
    uneven.close();

    return 0;
}