#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

#define TC_NAME TC
#define TEST_CASE(funcName) bool funcName(bool verbose = false)
#define TEST_START(description) TestCase TC_NAME(description, verbose); TC_NAME.start()
#define TEST_END TC_NAME.end()

#define TEST(stepDescription, actual, expected) TC_NAME.test(stepDescription, actual, expected, __LINE__, __FILE__)
#define TEST_TEMPLATED(type, stepDescription, actual, expected) TC_NAME.test<type>(stepDescription, actual, expected, __LINE__, __FILE__)

#define TEST_CONDITION(stepDescription, condition, actual, expected) TC_NAME.test(stepDescription, condition, actual, expected, __LINE__, __FILE__)
#define TEST_CONDITION_TEMPLATED(type, stepDescription, condition, actual, expected) TC_NAME.test<type>(stepDescription, condition, actual, expected, __LINE__, __FILE__)

#define TEST_CONTAINS(stepDescription, actual, expected) TC_NAME.testContains(stepDescription, actual, expected, __LINE__, __FILE__)

#define TEST_ARRAY(stepDescription, actual, expected, nrOfElements) TC_NAME.testArray(stepDescription, actual, expected, nrOfElements, __LINE__, __FILE__)
#define TEST_COMPARE_FILES(stepDescription, actualFilename, expectedFilename) TC_NAME.testCompareFiles(stepDescription, actualFilename, expectedFilename, __LINE__, __FILE__)

class TestCase
{
public:
	TestCase(const string& description, bool verbose = false)
		: tcDescription(description), verbose(verbose) {
	};

	void start() {
		cout << this->tcDescription << ": ";
	}

	bool end() {
		if (verbose) {
			cout << endl;
		}
		else {
			if (this->testCaseOk) {
				cout << "OK!" << endl;
			}
			else {
				cout << "\nFAILED!" << endl;
			}
		}
		return this->testCaseOk;
	}

	template <typename T>
	bool test(const string& stepDescription, T actual, T expected, int line = 0, const string& file = "") {
		return this->testStep(++stepNr, stepDescription,  actual == expected, actual, expected, verbose, line, file);
	}

	template <typename T>
	bool test(const string& stepDescription, bool condition, T actual, T expected, int line = 0, const string& file = "") {
		return this->testStep(++stepNr, stepDescription, condition, actual, expected, verbose, line, file);
	}

	bool testContains(const string& stepDescription, string actual, vector<string> expected, int line = 0, const string& file = "");

	template <typename T>
	bool testArray(const string& stepDescription, T actual[], T expected[], int nrOfElements, int line = 0, const string& file = "");

	bool testCompareFiles(const string& stepDescription, const string& actualFilename, const string& expectedFilename, int line = 0, const string& file = "");

private:
	void printLineAndFileInfo(int line, const string& file) {
		cout << "\n\t-->File: " << file;
		cout << "\n\t-->Line: " << line << endl;
	}

	template <typename T>
	void printArray(T arr[], int nrOfElements) {
		cout << "[";

		for (int i = 0; i < nrOfElements; ++i) {
			cout << arr[i] << (i < nrOfElements-1 ? ", " : "");
		}
		cout << "]";
	}

	template <typename T>
	bool testStep(int stepNr, const string& stepDescription, bool condition, T actual, T expected, bool verbose, int line = 0, const string& file = "") {
		if (condition == false)
		{
			cout << "\n\t[" << stepNr << " FAILED]: " << stepDescription
				<< " ->Expected: " << expected << ", but was: " << actual << endl;
			printLineAndFileInfo(line, file);
			this->testCaseOk = false;
		}
		else if (verbose) {
			cout << "\n\t[" << stepNr << " OK]: " << stepDescription;
		}
		else {
			cout << ".";
		}
		return this->testCaseOk; // eller condition????
	}

private:
	int stepNr = 0;
	string tcDescription;
	bool testCaseOk = true;
	bool verbose = false;
};

/**
* Template specialization for booleans, printing true/false instead of 1/0.
*/
template<>
bool TestCase::testStep(int stepNr, const string& stepDescription, bool condition, bool actual, bool expected, bool verbose, int line, const string& file) {
	if (condition == false)
	{
		cout << "\n\t[" << stepNr << " FAILED]: " << stepDescription
			<< " ->Expected " << std::boolalpha << expected << ", but was " << actual << std::noboolalpha << endl;
		printLineAndFileInfo(line, file);

		this->testCaseOk = false;
	}
	else if (verbose) {
		cout << "\n\t[" << stepNr << " OK]: " << stepDescription;
	}
	else {
		cout << ".";
	}
	return this->testCaseOk;
}

/**
* Test if actual contains all expected words.
*/
bool TestCase::testContains(const string& stepDescription, string actual, vector<string> expected, int line, const string& file) {

	stepNr++;

	if (verbose) {
		cout << "\n\t[" << stepNr << "...]: " << stepDescription;
	}

	bool containsAll = true;
	for (const string& expect : expected) {
		if (actual.find(expect) == string::npos) {
			containsAll = false;
			if (verbose) {
				cout << "\n\t[" << stepNr << " FAILED]: ->Expected: " << expect << ", but was: " << actual << endl;
			}
			else {
				cout << "\n\t[" << stepNr << " FAILED]: " << stepDescription << " ->Expected: " << expect << ", but was : " << actual << endl;
			}
			printLineAndFileInfo(line, file);
			this->testCaseOk = false;
		}
		else if (verbose)
		{
			cout << "\n\t\t-contains: " << expect;
		}
		else
		{
			cout << ".";
		}
	}
	if (containsAll) {
		if (verbose) {

			cout << "\n\t[" << stepNr << " OK]";// << stepDescription;
		}
	}
	else if (verbose)
	{
		cout << "\n\t[" << stepNr << " FAILED]";// << stepDescription;

	}

	return containsAll;
}

bool TestCase::testCompareFiles(const string& stepDescription, const string& actualFilename, const string& expectedFilename, int line, const string& file)
{
	stepNr++;
	bool filesAreEqual = true;

	ifstream actualFile(actualFilename);
	ifstream expectedFile(expectedFilename);

	if (!actualFile.is_open() || !expectedFile.is_open()) {
		return false;
	}
	string actualLine, expectedLine;
	int lineNumber = 0;
	bool identical = true;
	bool eofActual, eofExpected = false;
	
	while (true) {
		eofActual = !getline(actualFile, actualLine);
		eofExpected = !getline(expectedFile, expectedLine);
		lineNumber++;

		if (eofActual && eofExpected) {
			break; // Both files ended, identical so far
		}
		if (eofActual != eofExpected) {
			break;
		}
		if (actualLine != expectedLine) {
			identical = false;
			break;
		}
	}

	if (eofActual != eofExpected && eofExpected && actualLine != "") { // Accept an extra newline at the end of the copied file
		cout << "\n\t[" << stepNr << " FAILED]: " << stepDescription << " -> Files differ: one file has more lines.";
		cout << "\n\tLast lines:";
		cout << "\n\t\t" << expectedFilename << ": " << expectedLine;
		cout << "\n\t\t" << actualFilename << ": " << actualLine;


		printLineAndFileInfo(line, file);

		this->testCaseOk = false;
		filesAreEqual = false;

	} else if (!identical) {
		cout << "\n\t[" << stepNr << " FAILED]: " << stepDescription << " ->Expected ";
		cout << expectedLine << " at line number " << lineNumber;
		cout << ", but was ";
		cout << actualLine << endl;

		printLineAndFileInfo(line, file);

		this->testCaseOk = false;
		filesAreEqual = false;
	}
	else if (verbose) {
		cout << "\n\t[" << stepNr << " OK]: " << stepDescription;
	}
	else {
		cout << ".";
	}


	return filesAreEqual;
}

template<typename T>
inline bool TestCase::testArray(const string& stepDescription, T actual[], T expected[], int nrOfElements, int line, const string& file)
{
	bool areEqual = true;

	this->stepNr++;

	for (int i = 0; i < nrOfElements && areEqual; ++i) {
		areEqual = actual[i] == expected[i];
	}

	if (!areEqual) {
		cout << "\n\t[" << stepNr << " FAILED]: " << stepDescription << " ->Expected ";
		this->printArray(expected, nrOfElements);
		cout << ", but was ";
		this->printArray(actual, nrOfElements);

		printLineAndFileInfo(line, file);

		this->testCaseOk = false;
	}
	else if (verbose) {
		cout << "\n\t[" << stepNr << " OK]: " << stepDescription;
	}
	else {
		cout << ".";
	}

	return areEqual;
}

class TestRunner
{
public:
	TestRunner() = default;
	TestRunner(std::string name) : name(name) {};

	void registerTestCase(bool (*testCaseFunction)(bool), std::string shortName) {
		this->testCaseNames.push_back(shortName);
		this->testCaseMap.insert({shortName, testCaseFunction});
	}

	int run(int argc, char** argv)
	{
		if (argc > 1)
		{
			std::string argument(argv[1]);
			if (argument == "--help") {
				printHelp();
				return 0;
			}
			if (argument == "--silent") {
				return this->runAllTests(false);
			}

			auto element = this->testCaseMap.find(argument);
			if (element != this->testCaseMap.end()) {
				if (element->second(false)) { // run testFunction
					return 0;
				}
				return 1;
			}

			cout << "Invalid test. Run with --help option to see usage." << endl;
			return false;
		}

		return this->runAllTests();
	}

private:

	void printHelp()
	{

		cout << "Runs all tests (default), or only a specific test according to argument.\
\n--silent: Runs all tests with minimal output\
\n--help: This help text\
\nSpecific test arguments:";

		for (auto testCaseName : this->testCaseNames) {
			cout << "\n\t" << testCaseName;
		}
	}

	int runAllTests(bool verbose = true)
	{
		cout << "Testing " << this->name << "...\n" << endl;

		int nrOfTests = static_cast<int>( this->testCaseMap.size());
		int score = 0;

		for (string testCaseName : this->testCaseNames) {
			if (this->testCaseMap[testCaseName](verbose)) {
				score++;
			}
		}

		cout << "\nPassed: " << score << ", Failed: " << nrOfTests - score << endl;
		if (score == nrOfTests) {
			cout << "\nAll tests passed, well done!" << endl;
		}

		return score == nrOfTests ? 0 : 1;
	}

private:
	std::string name;
	std::vector<std::string> testCaseNames; // Keeps registered order of tests.
	std::map<std::string, bool (*)(bool)> testCaseMap;
};
