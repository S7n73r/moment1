#pragma once
#include <string>

using namespace std;

/*
	I denna fil tillför du funktionsdeklarationer enligt uppgiftsbeskrivningen.

... addNumber(...);

... copyFile(...);

... getInterval(...);

... findWords(...);
*/


int addNumber(int& value, int number = 1);

bool copyFile(string originalfile, string copyfile);

int getInterval(int fromArray[], int toArray[], int nrOfElements, int from, int to);

string findWords(string wordsArray[], int nrOfElements, char startsWith);