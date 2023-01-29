#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

void readData(const string &fileName, vector<double> &flightVals, vector<double> &liftVals);
double interpolation(double userChoice, const vector<double> &flightVals, const vector<double> &liftVals);
bool isOrdered(const vector<double> &);
void reorder(vector<double> &flightVals, vector<double> &liftVals);

int main(int argc, char *argv[]) {

    string windTunnelData;
    vector<double> flightVals;
    vector<double> liftVals;
    bool Ordered;
    double userChoice;
    string yesOrNo;

    windTunnelData = argv[1];

    readData (windTunnelData, flightVals, liftVals);

    if (flightVals.size() == 0)
    {
        cout << "Nothing" << endl;
        return 1;
    }
//else {
    Ordered = isOrdered (flightVals);
    
    if (Ordered == 0)
    {
        reorder (flightVals, liftVals);
    }
    
    for (unsigned int i = 0; i < flightVals.size(); ++i) {
        cout << flightVals.at(i) << " " << liftVals.at(i) << endl;
    }

    cout << endl;
    cout << "Choose a flight path angle: ";
    cin >> userChoice;
    cout << endl;

    cout << "Interpolation: " << interpolation (userChoice, flightVals, liftVals) << endl;
    cout << endl;
    cout << "Want to enter another flight path angle? Yes or No? ";
    cin >> yesOrNo;
    cout << endl;

    while (yesOrNo == "Yes") 
    {
    cout << "Choose a flight path angle: ";
    cin >> userChoice;
    cout << endl;
    cout << "Interpolation: " << interpolation (userChoice, flightVals, liftVals) << endl;
    cout << endl;
    cout << "Want to enter another flight path angle? Yes or No? ";
    cin >> yesOrNo;
    cout << endl;
    }
//}
    
    return 0;
}

void readData(const string &fileName, vector<double> &flightVals, vector<double> &liftVals) {

    ifstream dataFS;
    dataFS.open(fileName);

    double flightInt;
    double liftInt;

    if (!dataFS.is_open()) 
    {
        cout << "Error opening " << fileName << endl;
        exit(1);
    }

    while (dataFS >> flightInt && dataFS >> liftInt) 
    {
        flightVals.push_back(flightInt);
        liftVals.push_back(liftInt);
    }


    dataFS.close();
}

double interpolation(double userFlightPath, const vector<double> &flightVals, const vector<double> &liftVals) {
   
    double maxFlightVal = flightVals.at(0);

    for (unsigned int i = 0; i < flightVals.size(); ++i) 
    {
        if (maxFlightVal < flightVals.at(i)) 
        {
            maxFlightVal = flightVals.at(i);
        }
    }
    
    double minFlightVal = flightVals.at(0);

    for (unsigned int i = 0; i < flightVals.size(); ++i) 
    {
        if (minFlightVal > flightVals.at(i)) 
        {
            minFlightVal = flightVals.at(i);
        }
    }

    if (userFlightPath > maxFlightVal || userFlightPath < minFlightVal) 
    {
        return 0.0;
    }

    double angleA;
    double angleC;
    double liftA;
    double liftC;
    double polationVal;

    if (userFlightPath <= maxFlightVal && userFlightPath >= minFlightVal) 
    {
        for (unsigned int i = 0; i < flightVals.size(); ++i) 
        {
            if (userFlightPath == flightVals.at(i)) 
            {
                polationVal = liftVals.at(i);
                return polationVal;
            }
        }
    }

    if (userFlightPath <= maxFlightVal && userFlightPath >= minFlightVal) 
    {
            for (unsigned int i = 0; i < flightVals.size() - 1; ++i) 
            {
                if (userFlightPath > flightVals.at(i) && userFlightPath < flightVals.at(i + 1)) 
                {
                    angleA = flightVals.at(i);
                    angleC = flightVals.at(i + 1);
                    liftA = liftVals.at(i);
                    liftC = liftVals.at(i + 1);
                }
            }
        }

    polationVal = liftA + ((userFlightPath - angleA) / (angleC - angleA)) * (liftC - liftA);

    return polationVal;
}

bool isOrdered(const vector<double> &flightVals) {

    bool ordered = true;

    if (flightVals.size() == 0 || flightVals.size() == 1) {
        return ordered;
    }

    for (unsigned int i = 0; i < flightVals.size() - 1; ++i) {
        if ( flightVals.at(i) > flightVals.at(i + 1) ) {
            ordered = false;
        }
    }
    return ordered;
}

void reorder(vector<double> &flightVals, vector<double> &liftVals) {

    unsigned int i;
    unsigned int j;
    double flightTemp;
    double liftTemp;

    if (flightVals.size() == 0) {
        cout << "Nothing" << endl;
        return;
    }
    
    for (i = 0; i < flightVals.size() - 1; ++i) 
    {
            for (j = i + 1; j < flightVals.size(); ++j) 
            {
                if (flightVals.at(j) < flightVals.at(i)) 
                {
                    flightTemp = flightVals.at(i);
                    flightVals.at(i) = flightVals.at(j);
                    flightVals.at(j) = flightTemp;

                    liftTemp = liftVals.at(i);
                    liftVals.at(i) = liftVals.at(j);
                    liftVals.at(j) = liftTemp;
                }
            }
    }
}