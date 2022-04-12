#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <stdio.h>
#include "Header.h"
using namespace std;

int main()
{
    int choice;

    cout << "Press Left Ctrl to rewrite the wile, or press Right Ctrl to add new lines to the file" << endl;

    while (true)
    {
        if (GetAsyncKeyState(VK_LCONTROL))
        {
            cout << "Rewrite" << endl;
            choice = 1;
            break;
        }
        if (GetAsyncKeyState(VK_RCONTROL))
        {
            cout << "Add" << endl;
            choice = 2;
            break;
        }
    }

    string path_1 = "original.txt";
    string path_2 = "even.txt";
    string path_3 = "uneven.txt";
    string path_4 = "vrem.txt";
    fstream original;
    fstream even;
    fstream uneven;
    fstream vrem;

    cout << "Enter strings for the first file strings (Enter empty line to proceed):" << endl;

    string orig = fill_og();
    if (choice == 1) {
        original.open(path_1, fstream::in | fstream::out | fstream::trunc);
        original << orig;
        original.close();
    }
    if (choice == 2) {
        original.open(path_1, fstream::in | fstream::out | fstream::app);
        original << orig;
        original.close();
    }

    cout << endl;

    int rows = -1;
    original.open(path_1, fstream::in | fstream::out | fstream::app);

    string count;
    while (!original.eof())
    {
        getline(original, count);
        rows++;
    }

    original.close();

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

    string uneven_s = "";

    cout << "Uneven strings:" << endl;

    uneven.open(path_3, fstream::in | fstream::out | fstream::app);
    
    while (!uneven.eof())
    {
        show = "";
        getline(uneven, show);
        uneven_s = uneven_s + show + '\n';
        cout << show << endl;
    }
    uneven.close();

    cout << endl;

    string* S = new string[size + 1];

    int sz = 0;

    for (int i = 0; i < size; i++) {
        S[i] = create_array(uneven_s, sz);
    }

    cout << endl;

    change(S, size);

    uneven.open(path_3, fstream::in | fstream::out | fstream::trunc);

    for (int i = 0; i < size; i++)
    {
        uneven << S[i] + '\n';
    }

    uneven.close();

    delete[]S;

    vrem.open(path_4, fstream::in | fstream::out | fstream::trunc);
    vrem.close();

    even.open(path_2, fstream::in | fstream::out | fstream::app);

    string even_str;

    int srt = 0;

    cout << "How many lines to sort: ";
    cin >> srt;

    int lines = 1;

    while (!even.eof())
    {
        getline(even, even_str);
        if (lines > srt)
        {
            vrem.open(path_4, fstream::in | fstream::out | fstream::app);
            vrem << even_str + '\n';
            vrem.close();
        }
        else {
            alph_sorting(even_str, path_4, path_2);
            lines++;
        }
    }
    even.close();

    vrem.open(path_4, fstream::in | fstream::out | fstream::app);
    even.open(path_2, fstream::in | fstream::out | fstream::trunc);

    string fin;

    while (!vrem.eof())
    {
        fin = "";
        getline(vrem, fin);
        even << fin + '\n';
    }

    even.close();
    vrem.close();;

    cout << endl;

    remove("vrem.txt");

    even.open(path_2, fstream::in | fstream::out | fstream::app);

    cout << "Altered even strings:" << endl;

    while (!even.eof())
    {
        show = "";
        getline(even, show);
        cout << show << endl;
    }
    even.close();

    cout << endl;

    cout << "Altered uneven strings:" << endl;

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
