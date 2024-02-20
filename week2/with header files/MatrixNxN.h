#ifndef MATRIXNXN_H
#define MATRIXNXN_H
#include "matrix.h"
using namespace std;

class matrixNxN: public matrix{
    private:
        int rows, columns;
        vector<vector<int> > mat;
    public:
        matrixNxN(vector<string> command);
};

matrixNxN::matrixNxN(vector<string> command) : matrix(){
    rows=stoi(command[2]);
    columns=stoi(command[2]); //rows and columns are just the same
}

#endif
