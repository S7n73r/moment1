#include <iostream>
#include <string>
#include "TestCase.h"
#include "ToDo.h"
#include <exception>

using namespace std;

TEST_CASE(testAddNumber)
{
    TEST_START("testAddNumber");

    int value, number, expected;

    value = number = 1;
    expected = value + number;
    addNumber(value, number);
    TEST("add positive", value, expected);

    value = 1; number = -1;
    expected = value + number;
    addNumber(value, number);
    TEST("add negative", value, expected);

    value = 1; number = 0;
    expected = value + number;
    addNumber(value, number);
    TEST("add nothing", value, expected);

    value = number = 1;
    expected = value + number;
    addNumber(value);
    TEST("add default", value, expected);

    return TEST_END;
}

TEST_CASE(testCopyFile)
{
    TEST_START("testCopyFile");

    TEST("handles non existing file", copyFile("", "fileCopy.txt"), false);

    TEST("can open existing file", copyFile("text1.txt", "fileCopy.txt"), true);

    copyFile("text1.txt", "fileCopy.txt");
    TEST_COMPARE_FILES("copy existing file", "fileCopy.txt", "text1.txt");

    copyFile("text2.txt", "fileCopy.txt");
    TEST_COMPARE_FILES("copy file 2", "fileCopy.txt", "text2.txt");

    copyFile("text3.txt", "fileCopy.txt");
    TEST_COMPARE_FILES("copy file 3", "fileCopy.txt", "text3.txt");

    copyFile("emptyFile.txt", "fileCopy.txt");
    TEST_COMPARE_FILES("copy empty file", "fileCopy.txt", "emptyFile.txt");

    return TEST_END;
}

TEST_CASE(testGetInterval)
{
    TEST_START("testGetInterval");

    int fromArray[] = { 1, 2, 3, 4, 5, 6 };
    const int ARR_SIZE = std::size(fromArray);
    int toArray[ARR_SIZE];

    int nrOfValues = getInterval(fromArray, toArray, ARR_SIZE, 2, 5);
    int expected[]{ 2, 3, 4, 5 };
    TEST_ARRAY("some values within interval", toArray, expected, 4);
    TEST("...nr of values", nrOfValues, 4);

    nrOfValues = getInterval(fromArray, toArray, ARR_SIZE, 1, 6);
    int expected2[]{1, 2, 3, 4, 5, 6};
    TEST_ARRAY("all values exactly within interval", toArray, expected2, 6);
    TEST("...nr of values", nrOfValues, 6);

    nrOfValues = getInterval(fromArray, toArray, ARR_SIZE, 0, 10);
    int expected3[]{ 1, 2, 3, 4, 5, 6 };
    TEST_ARRAY("all values within interval", toArray, expected3, 6);
    TEST("...nr of values", nrOfValues, 6);

    nrOfValues = getInterval(fromArray, toArray, ARR_SIZE, 10, 20);
    int expected4[]{ 1, 2, 3, 4, 5, 6 };
    TEST_ARRAY("no values within interval", toArray, expected4, 0);
    TEST("...nr of values", nrOfValues, 0);

    int* empty_arr = nullptr;
    nrOfValues = getInterval(empty_arr, toArray, 0, 10, 20);
    TEST("empty values array", nrOfValues, 0);

    return TEST_END;
}

TEST_CASE(testFindWords)
{
    TEST_START("testFindWords");

    string arr[]{ "adam", "bertil", "ceasar", "bo", "sten", "sven" };
    const int ARR_SIZE = std::size(arr);

    TEST("find none", findWords(arr, ARR_SIZE, 'z'), string(""));

    TEST("find one", findWords(arr, ARR_SIZE, 'a'), string("adam"));

    TEST("find two", findWords(arr, ARR_SIZE, 'b'), string("bertil bo"));

    TEST("find from empty array", findWords(arr, 0, 'a'), string(""));

    return TEST_END;
}


// -------------------- MAIN --------------------
int main(int argc, char* argv[])
{
    #if defined(_WIN32) || defined(_WIN64)
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    #endif

    TestRunner runner("Praktiskt Moment A");

    runner.registerTestCase(testAddNumber, "add");
    runner.registerTestCase(testCopyFile, "copy");
    runner.registerTestCase(testGetInterval, "getinterval");
    runner.registerTestCase(testFindWords, "findwords");

    return runner.run(argc, argv);
}