#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
using namespace std;

struct Meds
{
    string name, after, expiration;
};

struct Opened
{
    string name, time, before;
};

void input_meds(vector <Meds>&, int& m, string path_1);
void output_meds(vector <Meds>&);
void input_opened(vector <Opened>&, int& n);
void output_opened(vector <Opened>&);
void in_opened(vector <Opened>&, vector<Meds>&, int n, int m);
string before_time(vector<Opened>&, vector<Meds>&, int i, int j);
void fill_second(vector<Opened>&, string path_2, int n);
void delete_line(vector <Opened>&, int n, string path_2, string path_3);
int make_number(string str);