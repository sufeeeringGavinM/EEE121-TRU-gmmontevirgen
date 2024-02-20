#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <time.h>
#include"parsingTools.h"
#include"matrix.h"
#include"MatrixNxN.h"
#include"MatrixMxN.h"
using namespace std;

int main(){
    matrix Matrix;
    while(true){
        Matrix.getCommand(inputter());
        Matrix.inputCheck();
    }
    return 0;
}