#ifndef MATRIXMXN_H
#define MATRIXMXN_H
#include "matrix.h"
using namespace std;

class matrixMxN: public matrix{
    private:
        int rows, columns;
        vector<vector<int> > mat;
    public:
        matrixMxN(vector<string> command);
};

matrixMxN::matrixMxN(vector<string> command) : matrix(){
    rows=stoi(command[2]); 
    columns=stoi(command[3]);
}

#endif
