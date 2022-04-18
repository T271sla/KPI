#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include "Header.h"
using namespace std;

void input_meds(vector <Meds>&, int& m, string path_1);
void output_meds(vector <Meds>&);
void input_opened(vector <Opened>&, int& n);
void output_opened(vector <Opened>&);
void in_opened(vector <Opened>&, vector<Meds>&, int n, int m);
string before_time(vector<Opened>&, vector<Meds>&, int i, int j);
void fill_second(vector<Opened>&, string path_2, int n);
void delete_line(vector <Opened>&, int n, string path_2, string path_3);

int main()
{
    string path_1 = "first.txt";
    string path_2 = "second.txt";
    string path_3 = "vrem.txt";
    vector<Meds> katalog;
    int m;
    input_meds(katalog, m, path_1);
    cout << "List of medicaments: \n";
    output_meds(katalog);

    fstream vrem(path_3, ios::binary | ios::in | ios::out | ios::trunc);
    vrem.close();

    cout << endl;
    int n;
    vector<Opened> kat;
    input_opened(kat, n);
    in_opened(kat, katalog, n, m);
    cout << "List of medicaments: \n";
    output_opened(kat);
    fill_second(kat, path_2, n);
    delete_line(kat, n, path_2, path_3);

    remove("second.txt");
    rename("vrem.txt", "second.txt");
    cout << endl;
    cout << endl;

    return 0;
}

