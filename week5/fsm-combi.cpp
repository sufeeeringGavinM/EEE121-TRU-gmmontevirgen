#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

void genStateCombi(vector<string> &stateList, int numStates, string stateTrans) {
    if (numStates == 0) {
        cout << stateTrans << endl;
        return;
    }

    for (int i=0; i<stateList.size(); i++){
        genStateCombi(stateList,numStates-1, stateTrans + stateList[i]+" ");
    }
}

void printAllStates(vector<string> &stateList) {
    genStateCombi(stateList, stateList.size(), "");
}

int main() {
    vector<string> stateList;
    stateList = {"RESET", "IDLE", "ACTIVE", "DONE"};
    printAllStates(stateList);
    return 0;
}
