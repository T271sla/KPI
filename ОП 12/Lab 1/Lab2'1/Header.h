#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <stdio.h>
using namespace std;

string fill_og();
int fill_files(string path_1, string path_2, string path_3, int rows);
string create_array(string S, int& sz);
void change(string* S, int size);
void replace_uneven(string path_4, string path_3);
string create_array_2(int size_2, string even_str, int& wrd);
void alph_sorting(string even_str, string path_4, string path_2);
