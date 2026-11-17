#include "ToDo.h"
#include <fstream>

/*
	I denna fil tillför du funktionsdefinitioner enligt uppgiftsbeskrivningen.
*/


int addNumber(int value, int number = 1) {
		return(value += number);
}

bool copyFile(string originalFile, string copyfile) {
		fstream MyFile(originalFile, MyText);
		fstream MyCopy(copyfile, CopyText)

		while (std::getLine(MyFile, MyText)) {
				MyCopy(MyText, fstream:app);
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