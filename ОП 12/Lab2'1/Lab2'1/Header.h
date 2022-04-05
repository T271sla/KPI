#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <stdio.h>
using namespace std;

int fill_og(string path_1);
int fill_files(string path_1, string path_2, string path_3, int rows);
int* create_array(string path_3, int size);
void change(int i, string path_4, string path_3, int arr[]);
void replace_uneven(string path_4, string path_3);
int fill_vrem(string path_4, string path_2, string even_str);
int* create_array_2(string path_4, int size);
void arrange_vrem(int i, string path_4, string path_5, int arr[]);
void replace_vrem(string path_4, string path_5);
void alph_sorting(string even_str, string path_4, string path_2, string path_5);
