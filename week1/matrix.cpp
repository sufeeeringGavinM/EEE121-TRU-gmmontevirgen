#include <iostream>
#include <vector>
#include <string>
#include <time.h>
using namespace std;

vector<string> parser(string splitMe){ // taken from https://www.scaler.com/topics/split-string-in-cpp/ 
    vector<string> splitted;
    char splitter=' ';
    int start=0, end=0;
    for(int x=0; x<=splitMe.size(); x++){
        if(splitMe[x]==splitter || x==splitMe.size()){
            end=x; //realize first word is over
            string temp;
            temp.append(splitMe, start, end-start); // append() adds a part of a string, in this if(checker==splitMe, to a x such that x.append(origstring, start,end)
            splitted.push_back(temp); //add to vector of strings
            start=end+1; //restart list to next word
        }
    }
    return splitted;
}
bool isNumber(string s){ //taken from a confused stackoverflow asker https://stackoverflow.com/questions/53436314/checking-if-a-string-is-a-valid-number-no-letters-at-all
    for(int i=0; i<s.length(); i++){ //the guy says it doesnt work but it does!?
        if(!isdigit(s[i])){
            return false;
            break;
        }
    }
    return true;
}
int inputCheck(vector<string> command){
    for (int i=0; i<command.size(); i++){cout << command[i] <<' ';} //oneliner to reprint user command
    if(command[0]=="EXIT"){
        cout << endl;
    }
    else{
        cout << endl << endl;
    }
    if(command[0]=="INIT"){
        if(command.size()==1){
            return 1; //default for error
        }
        try{
            if(command.size()==2 && stoi(command[1]) <=1){
                return 1;
            }
            if(command.size()==3 && (stoi(command[2]) <=1 || stoi(command[1]) <=1 )){
                return 1;
            }
            if(command.size()>3){
                return 1;
            }
            for(int i=1; i<command.size(); i++){ //handling nonnumber characters
                if(!isNumber(command[i])){
                    return 1;
                }
            }
        }
        catch(exception){
            return 1;
        }
    
        return 2;
    }
    if(command[0]=="PRINT"){
        if(command.size()>1){
            return 1;
        }
        return 3;
    }
    if(command[0]=="GET"){
        if(command.size()!=3){
            return 1;
        }
        try{
            for(int i=1; i<command.size(); i++){
                if(!isNumber(command[i])){
                    return 1;
                }
            }
        }
        catch(exception){
            return 1;
        }
        return 4;
    }
    if (command[0]=="SET"){
        if(command.size()!=4){
            return 1;
        }
        try{
            for(int i=1; i<command.size(); i++){
                if(!isNumber(command[i])){
                    return 1;
                }
            }
        }
        catch(exception){
            return 1;
        }
        return 5;
    }
    if (command[0]=="TRANSPOSE"){
        if(command.size()!=1){
            return 1;
        }
        return 6;
    }
    if (command[0]=="SWAP_ROWS"){
        if(command.size()!=3){
            return 1;
        }
        try{
            for(int i=1; i<command.size(); i++){ 
                if(!isNumber(command[i])){
                    return 1;
                }
            }
        }
        catch(exception){
            return 1;
        }
        return 7;
    }
    if (command[0]=="EXIT"){
        if(command.size()!=1){
            return 1;
        }
        return 8;
    }
    else{
        return 1;
    }
}

int main(){
    srand((unsigned) time(NULL));
    string unparsedCommand;
    bool check=true;
    bool existenceCheck=false; //existenceOfMatrixCheck
    int rows, columns;
    rows=0;
    columns=0;
    int random, i, j;
    vector<vector<int>> mat(rows, vector<int>(columns));

    while(check){
        std::cout << "> ";
        getline(cin,unparsedCommand);
        vector<string> command=parser(unparsedCommand);
        int checker=inputCheck(command);
        if(checker==1){
            cout << "UNSUPPORTED COMMAND" << endl << endl ;
            continue;
        }
        if(checker==8){
            break;
        }
        else if(checker==2){//init
            if(command.size()==2){
                command.push_back(command[1]);
            }
            try{
                rows=stoi(command[1]);
                columns=stoi(command[2]);
            }
            catch (exception){
                std::cout << "UNSUPPORTED COMMAND" << endl << endl;
                continue;
            }
            mat.resize(rows, vector<int>(columns));

            for(i=0;i<rows;i++){
                for(j=0;j<columns;j++){
                    mat[i][j]=rand()%100;                    
                }
            }
            
            std::cout << rows << "x" << columns << " MATRIX"<< endl << endl;
            existenceCheck=true;
        }
        else if(checker==3 && existenceCheck==false){
            std::cout << "UNSUPPORTED COMMAND" << endl << endl;
            continue;
        }

        else if(existenceCheck==true){
            if(checker==3){ //print
                for(int i = 0; i < rows; i++) 
                { 
                    for(int j = 0; j < columns; j++) 
                    { 
                        if(mat[i][j]<9){
                            cout << " "<< mat[i][j] << " "; 
                        } 
                        else{
                            cout << mat[i][j] << " ";
                        }
                    }
                    cout << endl; 
                } 
                cout << endl;
            }            
            
            else if(checker==4){ //get
                int c1,c2;
                c1=stoi(command[1]);
                c2=stoi(command[2]);
                if(c1<=rows && c2<=columns && command[1]!="0" && command[2]!="0"){
                    int r=stoi(command[1])-1;
                    int c=stoi(command[2])-1;
                    cout << "MATRIX[" << r+1 << "][" << c+1 << "] = " << mat[r][c] << endl << endl;
                }
                else{
                    std::cout << "UNSUPPORTED COMMAND" << endl << endl;
                    continue;
                }
            } 

            else if(checker==5){ //set
                int c1,c2;
                c1=stoi(command[1]);
                c2=stoi(command[2]);
                
                if(c1<=rows && c2<=columns && command[1]!="0" && command[2]!="0"){
                    int r=stoi(command[1])-1;
                    int c=stoi(command[2])-1;
                    mat[r][c]=stoi(command[3]);
                    cout << "MATRIX[" << r+1 << "][" << c+1 << "] = " << mat[r][c] << endl << endl;
                }
                else{
                    std::cout << "UNSUPPORTED COMMAND" << endl << endl;
                    continue;
                }
            }
            else if(checker==6){ //transpose
                vector<vector<int>> mat2(columns, vector<int>(rows));
                for(i=0; i<rows; i++){
                    for(j=0;j<columns;j++){
                        mat2[j][i]=mat[i][j];
                    }
                }
                mat.resize(columns, vector<int>(rows));
                mat=mat2;
                int temp;
                temp=rows;
                rows=columns;
                columns=temp;
                cout << rows << "x" << columns << " MATRIX" << endl << endl;
            }

            else if(checker==7){ //swap rows
                int row1 = stoi(command[1])-1;
                int row2 = stoi(command[2])-1;
                
                if(row1<=rows && row2<=rows && command[1]!="0" && command[2]!="0"){
                    vector<int> temprow = mat[row1];
                    mat[row1]=mat[row2];
                    mat[row2]=temprow;
                    cout << "SWAPPED ROWS " << command[1] << " AND " << command[2] << endl << endl; 
                }
                else{
                    std::cout << "UNSUPPORTED COMMAND" << endl << endl;
                    continue;
                }
            }
        }
        else{
            std::cout << "UNSUPPORTED COMMAND" << endl << endl;
            continue;
        } 
        }
    return 0;
}
    
