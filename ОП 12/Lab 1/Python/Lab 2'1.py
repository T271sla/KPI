import math
import os

def creating_main_file(path):
    print("Enter text: ")
    j = 0
    line = ""
    check1 = True
    while check1 == True:
        line = input() + '\n'
        if len(line) < 3:
            print('Entering of text is ended')
            check1 = False
        file = open(path, 'a+')
        file.write(line)
        file.close()

def fill_files(path, path2, path3):
    sorting_text = []
    file = open(path, 'r')
    file2 = open(path2, 'a+')
    file3 = open(path3, 'a+')
    sorting_text = file.readlines()
    sorting_text_uneven = []
    for i in range(0, len(sorting_text) - 1):
        if i % 2 == 0:
            file2.write(sorting_text[i])
            sorting_text_uneven.append(sorting_text[i])
        else:
            file3.write(sorting_text[i])
            
    return sorting_text_uneven
    file.close()
    file2.close()
    file3.close()

def sort_of_strings(path2, sorting_text_uneven):
    sorting_text_uneven.sort()
    file2 = open(path2, 'w+')
    for j in range(0, len(sorting_text_uneven)):
        file2.write(sorting_text_uneven[j])
    file2.close()

def sort_of_words(path4, line):
    list = []
    spc = 0
    size = 1

    for i in range(spc, len(line) - 1):
        if line[i] == ' ':
            size = size + 1
    
    for j in range (0, size):
        word = ""
        for i in range(spc, len(line) - 1):
            if line[i] == ' ':
                spc = i + 1
                break
            word = word + line[i]
        list.append(word)

    list.sort()

    line2 = ""
    
    for i in range(0, size):
        line2 = line2 + list[i] + " "

    line2 = line2 + '\n'
    file4 = open(path4, 'a+')
    for j in range(0, len(line2)):
        file4.write(line2[j])
    file4.close()

def show_file(path):
    file = open(path, "r")
    buff = file.readlines()
    print("File content of ", path)
    for i in range(0, len(buff)):
        print(buff[i])
    file.close()

def func():
    path = "original.txt"
    path2 = "uneven.txt"
    path3 = "even.txt"
    path4 = "vrem.txt"
    file1 = open(path, 'w+')
    file2 = open(path2, 'w+')
    file3 = open(path3, 'w+')
    file4 = open(path4, 'w+')
    file1.close()
    file2.close()
    file3.close()
    file4.close()

    creating_main_file(path)
    uneven = fill_files(path, path2, path3)
    sort_of_strings(path2, uneven)

    file3 = open(path3, 'r')
    check2 = True
    num = 0
    print("How many lines to sort: ")
    hw = int(input())
    while check2 == True:
        line = file3.readline()
        if not line:
            check2 = False
        if (num < hw):
            sort_of_words(path4, line)
        else:
            file4 = open(path4, 'a+')
            for j in range(0, len(line)):
                file4.write(line[j])
            file4.close()
        num = num + 1
        
    file3.close()

    while check2 == True:
        line = file3.readline()
        if not line:
            check2 = False
        if (num < hw):
            sort_of_words(path4, line)
        else:
            file4 = open(path4, 'a+')
            for j in range(0, len(line)):
                file4.write(line[j])
            file4.close()
        num = num + 1
    
    file3 = open(path3, 'w+')
    file4 = open(path4, 'r')

    check3 = True

    while check3 == True:
        line = file4.readline()
        if not line:
            check3 = False
        file3.write(line)

    file3.close()
    file4.close()

    os.remove("vrem.txt")

    show_file(path2)
    show_file(path3)
    
func()