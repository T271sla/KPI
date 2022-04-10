#include "Header.h"

void alph_sorting(string even_str, string path_4, string path_2)
{
    int size_2 = 0;

    for (int i = 0; i < even_str.length(); i++)
    {
        if (isspace(even_str[i]))
        {
            size_2++;
        }
        if (i + 1 == even_str.length())
        {
            size_2++;
        }
    }

    string* S_2 = new string[size_2];
    int wrd = 0;

    for (int i = 0; i < size_2; i++) {
        S_2[i] = create_array_2(size_2, even_str, wrd);
    }

    change(S_2, size_2);

    fstream vrem(path_4, fstream::in | fstream::out | fstream::app);
    
    for (int i = 0; i < size_2; i++) {
        vrem << S_2[i] + ' ';
    }
    vrem << '\n';

    vrem.close();
    delete[]S_2;
}

string create_array_2(int size_2, string even_str, int& wrd)
{

    int j = 0;
    string word;

    for (int i = wrd; i < even_str.length(); i++)
    {
        if (isspace(even_str[i]))
        {
            wrd = i + 1;
            return word;
            break;
        }
        word = word + even_str[i];

        if (i + 1 == even_str.length())
        {
            return word;
            break;
        }
    }
}

void change(string* S, int size)
{
    for (int i = 0; i < size - 1; i++)
        for (int j = i + 1; j < size; j++) {
            string tempor = "";
            if (strcmp(S[i].c_str(), S[j].c_str()) > 0)
            {
                tempor = S[i];
                S[i] = S[j];
                S[j] = tempor;
            }
        }
}

string create_array(string S, int size)
{
    int i = 0;
    string buf;
    const char* temp = (S.c_str());

    while (i != size) {
        while (*temp != '\n') {	
            if (i == size - 1)
            {
                buf = buf + *temp;
            }
            *temp++;
        }
        *temp++;
        i++;
    }
    return buf;
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

        if (j == rows)
        {
            break;
        }

        if (j % 2 == 0)
        {
            getline(original, row);
            uneven << row + '\n';
            size++;
        }

        if (j % 2 != 0)
        {
            getline(original, row);
            even << row + '\n';
        }

        j++;

    }

    original.close();
    even.close();
    uneven.close();

    return size;
}

string fill_og() {

    string S, temp;

    while ((getline(cin, S)) && (S.length()) > 0)
    {
        temp = temp + S + '\n';
    }
    return temp;
}