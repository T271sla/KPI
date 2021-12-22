#include <iostream>
using namespace std;

int func(char str[]);

int main()
{
	char str[100];
	cout << "Enter string:" << endl;
	gets_s(str);
	cout << "\nList of words:\n";
	int res = func(str);
	cout << "\nNumber of words: ";
	cout << res << endl;

}

int func(char str[])
{
	int i = 0;
	int count = 0;
	int FirstNum = 0;
	int LastNum = 0;
	char FirstChar = str[0];
	char LastChar;
	while (str[i] != '\0') {
		if (isspace(str[i])) { 
			LastChar = str[i - 1]; 
			LastNum = i - 1; 
			if (FirstChar == LastChar) { 
				for (int j = FirstNum; j <= LastNum; j++) {
					cout << str[j];
				}
				cout << "\n";
				count++;

			}
			FirstChar = str[i + 1];
			FirstNum = i + 1;
		}
		if (str[i + 1] == '\0') { 
			LastChar = str[i]; 
			LastNum = i;
			if (FirstChar == LastChar) {
				for (int j = FirstNum; j <= LastNum; j++) {
					cout << str[j];
				}
				cout << "\n";
				count++;

			}

		}
		i++;
	}

	return count;
}
    
