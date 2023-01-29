#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main (int argc, char *argv[]) {
    
    vector<double> v;
    double Val;
    string fileName;

    fileName = argv[1];

    ifstream inFS;
    inFS.open(fileName);

    while (inFS >> Val) {
        v.push_back(Val);
    }

    inFS.close();

    for (unsigned int i = 0; i < v.size(); ++i) {
        cout << v.at(i) << endl;
    }
    
    return 0;
}