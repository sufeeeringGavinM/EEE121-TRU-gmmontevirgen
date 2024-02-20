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
            end=x; //realize word is over
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

// everything above was copy pasted from previous activity


class matrix{
    private:
        int rows, columns;
        vector<vector<int> > mat;
    public:
        vector<string> command;
        matrix(vector<string> command);

        int inputCheck();
        void init();
        void print();
        void get();
        void set();
        void transpose();
        void swap_rows();
};

matrix::matrix(vector<string> command){
    (*this).command=command;
}

int matrix::inputCheck(){
    if(mat.empty()){ //only check for init and exit
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
        if (command[0]=="EXIT"){
            if(command.size()!=1){
                return 1;
            }
            exit(0);
        }
        else{
            return 1;
        }
    }
    else{
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
            exit(0);
        }
        else{
            return 1;
        }
    }
}
void matrix::init(){
    srand((unsigned) time(NULL));
    if(command.size()==2){
        command.push_back(command[1]);
    }
    try{
        rows=stoi(command[1]);
        columns=stoi(command[2]);
    }
    catch (exception){
        std::cout << "UNSUPPORTED COMMAND" << endl << endl;
        return;
    }
    mat.resize(rows, vector<int>(columns));

    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            mat[i][j]=rand()%100;                    
        }
    }
    
    std::cout << rows << "x" << columns << " MATRIX"<< endl << endl;
}
void matrix::print(){
    for(int i=0; i<rows; i++) 
        { 
            for(int j=0; j<columns; j++) 
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
void matrix::get(){
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
        return;
    }
}
void matrix::set(){
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
        return;
    }
}
void matrix::transpose(){
    vector<vector<int> > mat2(columns, vector<int>(rows));
    for(int i=0; i<rows; i++){
        for(int j=0;j<columns;j++){
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
void matrix::swap_rows(){
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
        return;
    }
}


class matrixMxN: public matrix{
    private:
        int rows,columns;
        vector<vector<int> > mat;
    public:
        matrixMxN(vector<string> command);
};

matrixMxN::matrixMxN(vector<string> command) : matrix(command){
    (*this).command=command;
    rows=stoi(command[1]);
    columns=stoi(command[2]);
}

class matrixNxN: public matrix{
    private:
        int rows, columns;
        
        vector<vector<int> > mat;
    public:
        matrixNxN(vector<string> command);
};

matrixNxN::matrixNxN(vector<string> command) : matrix(command){
    (*this).command=command;
    rows=stoi(command[1]);
    columns=stoi(command[1]);
}

int main(){
    string unparsed;
    string empty;
    matrix Matrix=parser(empty);
    while(true){
        std::cout << "> ";
        getline(cin,unparsed);
        vector<string> parsed=parser(unparsed);
        for (int i=0; i<parsed.size(); i++){cout << parsed[i] <<' ';} //oneliner to reprint user command
        cout<<endl<<endl;
        Matrix.command=parser(unparsed);
        if(Matrix.inputCheck()==1){
            std::cout << "UNSUPPORTED COMMAND" << endl << endl;
        }
        else{
            switch(Matrix.inputCheck()){
                case 1:
                    std::cout << "UNSUPPORTED COMMAND" << endl << endl;
                    break;
                case 2:{
                    switch(Matrix.command.size()){
                        case 2:
                            {matrixNxN RealMatrix(Matrix.command); //rows and cols
                            Matrix=RealMatrix;
                            cout<< typeid(RealMatrix).name()<<endl;
                            break;}
                        case 3:
                            {matrixMxN RealMatrix(Matrix.command);
                            Matrix=RealMatrix;
                            break;}
                    }
                    Matrix.init();
                    break;}
                case 3:
                    {Matrix.print();
                    break;}
                case 4:
                   { Matrix.get();
                    break;}
                case 5:
                    {Matrix.set();
                    break;}
                case 6:
                    {Matrix.transpose();
                    break;}
                case 7:
                    {Matrix.swap_rows();
                    break;}
            }
        }
        cout<< typeid(Matrix).name()<<endl;
        
    }
    return 0;
}