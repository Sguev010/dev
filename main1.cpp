#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{

    string inputFile;
    string outputFile;
    vector<int> fileInts;
    int fileNum;

    // Assign to inputFile value of 2nd command line argument
    inputFile = argv[1];

    // Assign to outputFile value of 3rd command line argument
    outputFile = argv[2];

    // Create input stream and open input csv file.
    ifstream inFS;
    inFS.open(inputFile);

    // Verify file opened correctly.
    if (!inFS.is_open())
    {
        // Output error message and return 1 if file stream did not open correctly.
        cout << "Error opening " << inputFile << endl;
        exit(1);
    }

    // Read in integers from input file to vector.
    char trash;

    while (inFS >> fileNum)
    {
        fileInts.push_back(fileNum);
        inFS >> trash;
    }
    // Close input stream.
    inFS.close();

    // Get integer average of all values read in.
    int avg;
    int sum = 0;

    for (unsigned int i = 0; i < fileInts.size(); ++i)
    {
        sum = sum + fileInts.at(i);
    }

    avg = sum / fileInts.size();

    // Convert each value within vector to be the difference between the original value and the average.
    for (unsigned int i = 0; i < fileInts.size(); ++i)
    {
        fileInts.at(i) -= avg;
    }

    // Create output stream and open/create output csv file.
    ofstream outFS;
    //outFS.open(outputFile, fstream::in | fstream::out | fstream::app);
    outFS.open(outputFile, ofstream::out | ofstream::trunc);

    // Verify file opened or was created correctly.
    if (!outFS.is_open())
    {
        // Output error message and return 1 if file stream did not open correctly.
        cout << "Error opening " << outputFile << endl;
        exit(1);
    }

    // Write converted values into ouptut csv file, each integer separated by a comma.
    for (unsigned int i = 0; i < fileInts.size(); ++i)
    {
        if (i == fileInts.size() - 1)
        {
            outFS << fileInts.at(i);
        }
        else
        {
            outFS << fileInts.at(i) << ",";
        }
    }

    // Close output stream
    outFS.close();

    return 0;
}
