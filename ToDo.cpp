#include "ToDo.h"
#include <fstream>

/*
	I denna fil tillför du funktionsdefinitioner enligt uppgiftsbeskrivningen.
*/


void addNumber(int& value, int number) {
		value += number;
}

bool copyFile(string originalfile, string copyfile) {
		ifstream MyFile(originalfile);
		ofstream MyCopy(copyfile);

		if (!MyFile.is_open() || !MyCopy.is_open()) {
				return false;
		}

		char character;

		while (MyFile.get(character)) {
				MyCopy.put(character);
		}

		MyFile.close();
		return true;
}

int getInterval(int fromArray[], int toArray[], int nrOfElements, int from, int to) {
		return 0;
}

std::string findWords(std::string wordsArray[], int nrOfElements, char startsWith) {
		return "";
}