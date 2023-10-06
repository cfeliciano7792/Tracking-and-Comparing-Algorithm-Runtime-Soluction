/*
	Program Name:	CS260 Tracking and Comparing Algorithm Runtime Project
	Programmer:		Christian Feliciano
	Date:			10/5/2023
	Last Update:	10/6/2023
*/

#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include <vector>

using namespace std;
using namespace std::chrono;

typedef std::chrono::time_point<system_clock> timer;
typedef double Second;

void TriggerTimer(timer&);
Second TimerCountInSecond(timer, timer);

bool LinearSearch(const vector<int>&, int);
bool BinarySearchRecursive(const vector<int>&, int, int, int);
bool BinarySearch(const vector<int>&, int);
bool ReadFileToVector(vector<int>&, string);
void TimingSearch(const vector<int>&, int, string);

int main()
{
    vector<string> fileNames = {    "data_10_sorted.txt",
                                    "data_2000_sorted.txt" ,
                                    "data_10000_sorted.txt" ,
                                    "data_100000_sorted.txt" };
    for (int i = 0; i < fileNames.size(); i++)
    {
        string fileName = fileNames[i];
        vector<int> sortedData;

        //Populate the vector with data from data file: 
        if (ReadFileToVector(sortedData, fileName) == true)
        {
            string searchType = "linear"; //linear, binary, or recursive binary
            int notExistItem = 7777777;
            int existItem = sortedData[0.8 * sortedData.size() - 1];
            //Existing item to search with this formulation: 
            //sortedData[0.8 * sortedData.size()-1]
            //data_10_sorted.txt - 20756919 (8th item)
            //data_2000_sorted.txt - 20009195 (1,600th item)
            //data_10000_sorted.txt - 20023575 (8,000th item)
            //data_100000_sorted.txt - 19990985 (80,000th item)

            cout << "+++++++++++++++++++++++++++++++++++++" << endl;
            cout << " Searching on " << fileName << endl;
            cout << "+++++++++++++++++++++++++++++++++++++" << endl;

            //0a. Timing LINEAR search for non-existing item:
            TimingSearch(sortedData, notExistItem, searchType);

            //0b. Timing LINEAR search for existing item:
            TimingSearch(sortedData, existItem, searchType);

            //1a. Timing BINARY search for non-existing item:
            //### Add code here to call TimingSearch() function
            //in order to use binary search algorithm 
            //to search for non-existing item in the data file ###
            searchType = "binary";
            TimingSearch(sortedData, notExistItem, searchType);

            //1b. Timing BINARY search for existing item:
            //### Add code here to call TimingSearch() function
            //in order to use binary search algorithm 
            //to search for existing item in the data file ###
            TimingSearch(sortedData, existItem, searchType);

            //2a. Timing BINARY RECURSIVE search for non-existing item:
            //### Add code here to call TimingSearch() function
            //in order to use binary recursive search algorithm 
            //to search for non-existing item in the data file ###
            searchType = "recursive binary";
            TimingSearch(sortedData, notExistItem, searchType);
            //2b. Timing BINARY RECURSIVE search for existing item:
            //### Add code here to call TimingSearch() function
            //in order to use binary recursive search algorithm 
            //to search for existing item in the data file ###
            TimingSearch(sortedData, existItem, searchType);
       
        }
    }

	return 0;
}

/*******************************************************************
 *                       LinearSearch                              *
 * Called by: TimingSearch                                         *
 * Passed   : 2 arguments: a vector of numbers,                    *
 *            and the number to search for                         *
 * Purpose  : Determines if the number to search for is in the set *
 *            of stored numbers                                    *
 * Method   : Uses a linear search                                 *
 * Returns  : true (if the number is found) or false (if not found)*
 *******************************************************************/
bool LinearSearch(const vector<int> &numbers, int numToSearch)
{
    bool isFound = false;
    for (int i = 0; i < numbers.size(); i++)
    {
        if (numbers[i] == numToSearch)
        {
            isFound = true;
            break;
        }
    }

    return isFound;
}

/*******************************************************************
 *                       BinarySearchRecursive                     *
 * Called by: TimingSearch                                         *
 * Passed   : 4 arguments: a vector of numbers, the number to      *
 *            search for, the low index, and the high index        *
 * Purpose  : Determines if the number to search for is in the set *
 *            of stored numbers                                    *
 * Method   : Uses a binary search                                 *
 * Returns  : true (if the number is found) or false (if not found)*
 *******************************************************************/
bool BinarySearchRecursive(const vector<int> &numbers, int numToSearch, int low, int high)
{
    if (low > high)
    {
        return false;
    }

    int mid = (low + high) / 2;
    if (numbers[mid] < numToSearch) 
    {
        return BinarySearchRecursive(numbers, numToSearch, mid + 1, high);
    }
    else if (numbers[mid] > numToSearch) 
    {
        return BinarySearchRecursive(numbers, numToSearch, low, mid - 1);
    }
    else
    {
        return true;
    }
}

/*******************************************************************
 *                       BinarySearch                              *
 * Called by: TimingSearch                                         *
 * Passed   : 2 arguments: a vector of numbers,                    *
 *            and the number to search for                         *
 * Purpose  : Determines if the number to search for is in the set *
 *            of stored numbers                                    *
 * Method   : Uses a binary search                                 *
 * Returns  : true (if the number is found) or false (if not found)*
 *******************************************************************/
bool BinarySearch(const vector<int> &numbers, int numToSearch)
{
    bool isFound = false;
    int mid = 0;
    int low = 0;
    int high = numbers.size() - 1;

    while (high >= low) 
    {
        mid = (high + low) / 2;
        if (numbers[mid] < numToSearch) 
        {
            low = mid + 1;
        }
        else if (numbers[mid] > numToSearch) 
        {
            high = mid - 1;
        }
        else 
        {
            isFound = true;
            break;
        }
    }

    return isFound;
}

void TriggerTimer(timer& timeContainer)
{
    timeContainer = std::chrono::system_clock::now();
}

Second TimerCountInSecond(timer startTime, timer endTime)
{
    std::chrono::duration<Second> elapsed_seconds = endTime - startTime;
    return elapsed_seconds.count();
}

bool ReadFileToVector(vector<int> &numbers, string fileName)
{
    bool isReadGood = false;
    int number;
    fstream inFile;
    inFile.open(fileName, ios::in);
    if (inFile.fail())
    {
        cout << "File open failed." << endl;
    }
    else
    {
        do //Read the file until the end of the file
        {
            inFile >> number;
            numbers.push_back(number);

        } while (inFile.eof() == false);
        isReadGood = true;
    }

    inFile.close();

    return isReadGood;
}

/*******************************************************************
 *                       TimingSearch                              *
 * Called by: main                                                 *
 * Passed   : 3 arguments: a vector of numbers, the number to      *
 *            search for, and the search algorithm to use          *
 * Purpose  : Use a specific search algorithm to show seach        *
 *            runtime                                              *
 * Method   : Uses a search algorithm                              *
 * Returns  : None                                                 *
 *******************************************************************/
void TimingSearch(const vector<int> &sortedData, int searchItem, string searchType)
{
    timer start, end;
    bool isFound = false;    

    TriggerTimer(start);
    if (searchType == "linear")
    {
        isFound = LinearSearch(sortedData, searchItem);
    }
    //calls the binary search algorithm
    else if (searchType == "binary")
    {
        isFound = BinarySearch(sortedData, searchItem);
    }
    else
    {
        //calls recursive binary search algorithm. Passes 0 for the low index value and  sortedData.size()-1 for high
        isFound = BinarySearchRecursive(sortedData, searchItem, 0, sortedData.size()-1);
    }
    //### Add code here to use binary and binary recursive search algorithm ###

    TriggerTimer(end);
    int toMicroSecond = 1000000;
    cout << "Search Item: " << searchItem << endl;
    cout << "Search Type: " << searchType << " search" << endl;
    cout << "Item found: " << isFound << endl;
    cout << "Elapsed time: " << TimerCountInSecond(start, end) * toMicroSecond << " microsecond(s)" << endl;
    cout << "=====================================" << endl;
}