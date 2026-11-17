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
		int length = 0;

		for (int i = 0; i < nrOfElements; i++) {
				if (fromArray[i] >= from && fromArray[i] <= to) {
						toArray[length] = fromArray[i];
						length++;
				}
		}

		return length;
}

std::string findWords(std::string wordsArray[], int nrOfElements, char startsWith) {

		std::string returnvalue = "";
		int amountofwords = 0;
		for (int i = 0; i < nrOfElements; i++) {

				int letterposition = 0;

				for (char c : wordsArray[i]) {
						if (letterposition == 0 && c == startsWith) {
								if (amountofwords > 0) {
										returnvalue += " " + wordsArray[i];
								}
								else {
										returnvalue += wordsArray[i];
										amountofwords++;
								}
								break;
						}
						letterposition++;
				}
		}
		return returnvalue;
}