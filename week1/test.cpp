#include <iostream>  
using namespace std;
 

int main() {
    int i,j;
    int rows, columns;
    rows=5;
    columns=5;
    int mat[rows][columns];
    for(i=0;i<rows;i++){
        for(j=0;j<columns;j++){
            mat[i][j]=rand()%100;    
        } 
    }        
    for (int x=0; x<rows; x++){
        for (int y=0; y<columns; y++){
            cout << mat[x][y] << " ";
        }
        cout << endl;
    }
    cout<<endl;
    return 0;
} 