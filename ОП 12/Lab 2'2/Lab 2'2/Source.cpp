#include "Header.h"

void input_meds(vector<Meds>& mas, int& m, string path_1)
{
    Meds b;
    ofstream firstOut(path_1, ios::binary);
    string nw = "\n";

    cout << "Input number of medicaments : ";
    cin >> m;
    cin.ignore();
    for (int i = 0; i < m; i++)
    {
        cout << "Input name: ";
        getline(cin, b.name);
        cout << "Usable after opening for(HH:MM): ";
        getline(cin, b.after);
        cout << "Expiration date(in years): ";
        getline(cin, b.expiration);
        mas.push_back(b);
        firstOut.write((char*)&b, sizeof(Meds) + 2);
    }
    firstOut.write((char*)&nw, sizeof(Meds) + 2);
    firstOut.close();
}

void output_meds(vector<Meds>& mas)
{
    for (int i = 0; i < mas.size(); i++)
    {
        cout << setw(16) << mas[i].name << setw(16) << mas[i].after << setw(16) << mas[i].expiration << endl;
    }
}

void input_opened(vector<Opened>& arr, int& n)
{
    Opened c;
    cout << "Input number of opened medicaments : ";
    cin >> n;
    cin.ignore();
    for (int i = 0; i < n; i++)
    {
        cout << "Input name: ";
        getline(cin, c.name);
        cout << "Input the time of opnening: ";
        getline(cin, c.time);
        arr.push_back(c);
    }
}

void in_opened(vector<Opened>& arr, vector<Meds>& mas, int n, int m)
{
    Opened c;
    Meds b;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (arr[i].name == mas[j].name)
            {
                arr[i].before = before_time(arr, mas, i, j);
                arr.push_back(c);
            }
        }
    }
}

string before_time(vector<Opened>& arr, vector<Meds>& mas, int i, int j)
{
    string a = arr[i].time;
    string f = mas[j].after;
    string b;
    string g;

    for (int i = 0; i < a.length(); i++)
    {
        if (a[i] == ':')
        {
            continue;
        }
        b = b + a[i];
    }

    for (int i = 0; i < a.length(); i++)
    {
        if (f[i] == ':')
        {
            continue;
        }
        g = g + f[i];
    }

    int c;
    int h;

    c = stoi(b);
    h = stoi(g);

    int k = h + c;

    string d;

    d = to_string(k);

    string e = "";

    if (k < 1000)
    {
        e = e + "0";
    }
    if (k < 100)
    {
        e = e + "00:";
    }
    if (k < 10)
    {
        e = e + "00:0";
    }

    for (int i = 0; i < d.length() + 1; i++)
    {
        if (i < d.length() / 2)
        {
            e = e + d[i];
        }
        if (i == d.length() / 2)
        {
            e = e + ':';
        }
        if (i > d.length() / 2)
        {
            e = e + d[i - 1];
        }

    }

    return e;
}


void output_opened(vector<Opened>& arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        cout << setw(16) << arr[i].name << setw(16) << arr[i].time << setw(16) << arr[i].before << endl;
    }
}

void fill_second(vector<Opened>& arr, string path_2, int n)
{
    Opened c;
    ofstream secondOut(path_2, ios::binary);
    string a;
    string b;
    string d;
    string nw = "\n";
    for (int i = 0; i < n; i++)
    {
        c.name = arr[i].name;
        c.time = arr[i].time;
        c.before = arr[i].before;
        secondOut.write((char*)&c, sizeof(Opened));
        secondOut.write((char*)&nw, nw.length() + 1);
    }
    secondOut.close();
}


void delete_line(vector<Opened>& arr, int n, string path_2, string path_3)
{
    cout << "Input Current time: ";
    string cur;
    getline(cin, cur);

    int cur_time = make_number(cur);
    int size = 0;

    for (int i = 0; i < n; i++)
    {
        int bfr = make_number(arr[i].before);
        if (cur_time < bfr)
        {
            size++;
        }
    }

    int* row = new int[size];
    int j = 0;
    int k = 0;

    for (int i = 0; i < n; i++)
    {
        int bfr = make_number(arr[i].before);
        if (cur_time < bfr)
        {
            row[j] = i;
            j++;
        }
        else
        {
            k++;
        }
    }

    fstream vrem(path_3, ios::binary | ios::in | ios::out | ios::app);

    Opened c;
    int p = 0;
    string nw = "\n";

    for (int i = 0; i < n; i++)
    {
        if (i == row[p])
        {
            c.name = arr[i].name;
            c.time = arr[i].time;
            c.before = arr[i].before;
            vrem.write((char*)&c, sizeof(Opened) - k);
            vrem.write((char*)&nw, sizeof(Opened) - k);
            p++;
        }
    }

    vrem.close();
}

int make_number(string str)
{
    string a;

    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == ':')
        {
            continue;
        }
        a = a + str[i];
    }

    int c;

    c = stoi(a);

    return c;
}
