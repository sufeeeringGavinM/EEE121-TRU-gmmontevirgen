#include <iostream>
#include <vector>
#include <map>
#include <string>

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
vector<string> inputter(){
    string unparsed;
    cout << "> ";
    getline(cin,unparsed);
    vector<string> parsed=parser(unparsed);
    
    for (int i=0; i<parsed.size(); i++){cout << parsed[i] <<' ';} //oneliner to reprint user command
    cout<<endl<<endl;
    return parsed;
}

class matrix{ 
    public:
        string name;
        int rows, columns;
        vector<vector<int> > mat;
        vector<string> command;
        map<string, vector<vector<int> >> enderChest;
        matrix();
        int inputCheck();
        void getCommand(vector<string> command);
        void init();
        void print();
        void get();
        void set();
        void transpose();
        void swap_rows();
        void addition();
        void subtraction();
};

matrix::matrix(){
}

void matrix::getCommand(vector<string> command){
    (*this).command=command;
}
int matrix::inputCheck(){
    if(mat.empty()){ //only check for init and exit
        if(command[0]=="INIT"){
            if(command.size()<3){
                std::cout << "UNSUPPORTED COMMAND" << endl << endl; //default for error
            }
            try{
                if(command.size()==3){ 
                    if(stoi(command[2])<1){
                        std::cout << "UNSUPPORTED COMMAND" << endl << endl;
                    }
                }
                
                if(command.size()==4){
                    if (stoi(command[3]) <1 || stoi(command[2]) <1){
                    std::cout << "UNSUPPORTED COMMAND" << endl << endl;
                    }
                }
                if(command.size()>4){
                    std::cout << "UNSUPPORTED COMMAND" << endl << endl;
                }
                for(int i=2; i<command.size(); i++){ //handling nonnumber characters
                    if(!isNumber(command[i])){
                        std::cout << "UNSUPPORTED COMMAND" << endl << endl;
                    }
                }
            }
            catch(exception){
                std::cout << "UNSUPPORTED COMMAND" << endl << endl;
            }
            (*this).init();
            return 0;
        }
        if (command[0]=="EXIT"){
            if(command.size()!=1){
                std::cout << "UNSUPPORTED COMMAND" << endl << endl;
            }
            //alkwejfiowejiowjfaeiowejwfaeiojifjiwjfe// 
            exit(0);
            return 0;
        }
        else{
            std::cout << "UNSUPPORTED COMMAND" << endl << endl;
        }
    }
    else{
        if(command[0]=="INIT"){
            if(command.size()<3){
                std::cout << "UNSUPPORTED COMMAND" << endl << endl;return 1; //default for error
            }
            try{
                if(command.size()==3){ 
                    if(stoi(command[2])<1){
                        std::cout << "UNSUPPORTED COMMAND" << endl << endl;
                    }
                }
                if(command.size()==4){
                    if (stoi(command[3]) <1 || stoi(command[2]) <1){
                    std::cout << "UNSUPPORTED COMMAND" << endl << endl;
                    }
                }
                if(command.size()>4){
                    std::cout << "UNSUPPORTED COMMAND" << endl << endl;
                }
                for(int i=2; i<command.size(); i++){ //handling nonnumber characters
                    if(!isNumber(command[i])){
                        std::cout << "UNSUPPORTED COMMAND" << endl << endl;
                    }
                }
            }
            catch(exception){
                std::cout << "UNSUPPORTED COMMAND" << endl << endl;return 1;
            }
            (*this).init();
            return 0;
        }
        if(command[0]=="PRINT"){
            if(command.size()!=2){
                std::cout << "UNSUPPORTED COMMAND" << endl << endl;return 1;
            }
            (*this).print();
            return 0;
        }
        if(command[0]=="GET"){
            if(command.size()!=4){
                std::cout << "UNSUPPORTED COMMAND" << endl << endl;return 1;
            }
            try{
                for(int i=2; i<command.size(); i++){
                    if(!isNumber(command[i])){
                        std::cout << "UNSUPPORTED COMMAND" << endl << endl;return 1;
                    }
                }
            }
            catch(exception){
                std::cout << "UNSUPPORTED COMMAND" << endl << endl; return 1;
            }
            (*this).get();
            return 0;
        }
        if (command[0]=="SET"){
            if(command.size()!=5){
                std::cout << "UNSUPPORTED COMMAND" << endl << endl; return 1;
            }
            try{
                for(int i=2; i<command.size(); i++){
                    if(!isNumber(command[i])){
                        std::cout << "UNSUPPORTED COMMAND" << endl << endl; return 1;
                    }
                }
            }
            catch(exception){
                std::cout << "UNSUPPORTED COMMAND" << endl << endl; return 1;
            }
            (*this).set();
            return 0;
        }
        if (command[0]=="TRANSPOSE"){
            if(command.size()!=2){
                std::cout << "UNSUPPORTED COMMAND" << endl << endl; return 1;
            }
            (*this).transpose();
            return 0;
        }
        if (command[0]=="SWAP_ROWS"){
            if(command.size()!=4){
                std::cout << "UNSUPPORTED COMMAND" << endl << endl; return 1;
            }
            try{
                for(int i=2; i<command.size(); i++){ 
                    if(!isNumber(command[i])){
                        std::cout << "UNSUPPORTED COMMAND" << endl << endl;
                        return 1;
                    }
                }
            }
            catch(exception){
                std::cout << "UNSUPPORTED COMMAND" << endl << endl;
                return 1;
            }
            (*this).swap_rows();
            return 0;
        }
        if(command[1]=="+"){
            try{
                if(command.size()!=3){
                    std::cout << "UNSUPPORTED COMMAND" << endl << endl;
                    return 1;
                }
                if((enderChest.count(command[0])==0) || (enderChest.count(command[2])==0)){
                    std::cout << "UNSUPPORTED COMMAND" << endl << endl;
                    return 1;
                }
                int R1=enderChest.find(command[0])->second.size();
                    int C1=enderChest.find(command[0])->second[0].size();
                    int R2=enderChest.find(command[2])->second.size();
                    int C2=enderChest.find(command[2])->second[0].size();
                if( (R1!=R2) || (C1!=C2)){
                    std::cout << "UNSUPPORTED COMMAND" << endl << endl;
                    return 1;
                }
                (*this).addition();
                return 0;
            }
            catch(exception){
                std::cout << "UNSUPPORTED COMMAND" << endl << endl;
                return 1;
            }
        }
        if(command[1]=="-"){
            try{
                if(command.size()!=3){
                    std::cout << "UNSUPPORTED COMMAND" << endl << endl;
                    return 1;
                }
                if((enderChest.count(command[0])==0) || (enderChest.count(command[2])==0)){
                    std::cout << "UNSUPPORTED COMMAND" << endl << endl;
                    return 1;
                }
                int R1=enderChest.find(command[0])->second.size();
                    int C1=enderChest.find(command[0])->second[0].size();
                    int R2=enderChest.find(command[2])->second.size();
                    int C2=enderChest.find(command[2])->second[0].size();
                if( (R1!=R2) || (C1!=C2)){
                    std::cout << "UNSUPPORTED COMMAND" << endl << endl;
                    return 1;
                }
                (*this).subtraction();
                return 0;
            }
            catch(exception){
                std::cout << "UNSUPPORTED COMMAND" << endl << endl;
                return 1;
            }
        }
        if (command[0]=="EXIT"){
            if(command.size()!=1){
                std::cout << "UNSUPPORTED COMMAND" << endl << endl;
                return 1;
            }
            exit(0);
            return 0;
            ///w99w9w 999 iii oooo ooo!!//
        }
        else{
            std::cout << "UNSUPPORTED COMMAND" << endl << endl;
            return 1;
        }
    }
}
void matrix::init(){
    srand((unsigned) time(NULL));
    if(command.size()==3){
        command.push_back(command[2]);
    }
    try{
        rows=stoi(command[2]);
        columns=stoi(command[3]);
    }
    catch (exception){
        return;
    }
    mat.clear();
    mat.resize(rows, vector<int>(columns));

    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            mat[i][j]=rand()%100;                    
        }
    }
    enderChest[command[1]]=mat;
    std::cout << "Matrix " << command[1] << " : " << rows << "x" << columns << endl << endl;
}
void matrix::print(){
    try{
    mat=enderChest.find(command[1])->second; //https://www.geeksforgeeks.org/map-find-function-in-c-stl/
    rows=mat.size();
    columns=mat[0].size();
    enderChest.find(command[1])->second.resize(rows, vector<int>(columns));
    for(int i=0; i<rows; i++){ 
            for(int j=0; j<columns; j++) 
            { 
                if(mat[i][j]<9){
                    cout << " " << enderChest.find(command[1])->second[i][j] << " "; 
                } 
                else{
                    cout << enderChest.find(command[1])->second[i][j] << " ";
                }
            }
            cout << endl; 
        } 
        cout << endl;
    }
    catch(exception){
        std::cout << "UNSUPPORTED COMMAND" << endl << endl;
    }
}
void matrix::get(){
    try{
        int c1,c2;
        c1=stoi(command[2]);
        c2=stoi(command[3]);
        if(c1<=rows && c2<=columns && command[2]!="0" && command[3]!="0"){
            int r=stoi(command[2])-1;
            int c=stoi(command[3])-1;
            cout << command[1] << "[" << r+1 << "][" << c+1 << "] = " << enderChest.find(command[1])->second[r][c] << endl << endl;
        }
        else{
            std::cout << "UNSUPPORTED COMMAND" << endl << endl;
            return;
        }
    }
    catch(exception){
        std::cout << "UNSUPPORTED COMMAND" << endl << endl;
    }
}
void matrix::set(){
    try{
        int c1,c2;
        c1=stoi(command[2]);
        c2=stoi(command[3]);
        if(c1<=rows && c2<=columns && command[2]!="0" && command[3]!="0"){
            int r=stoi(command[2])-1;
            int c=stoi(command[3])-1;
            enderChest.find(command[1])->second[r][c]=stoi(command[4]);
            cout << command[1] << "[" << r+1 << "][" << c+1 << "] = " << enderChest.find(command[1])->second[r][c] << endl << endl;
        }
        else{
            std::cout << "UNSUPPORTED COMMAND" << endl << endl;
            return;
        }
    }
    catch(exception){
        std::cout << "UNSUPPORTED COMMAND" << endl << endl;
    }
}
void matrix::transpose(){
    try{
        mat=enderChest.find(command[1])->second;
        rows=mat.size();
        columns=mat[0].size();
        vector<vector<int> > mat2(columns, vector<int>(rows));
        for(int i=0; i<rows; i++){
            for(int j=0;j<columns;j++){
                mat2[j][i]=mat[i][j];
            }
        }
        enderChest.find(command[1])->second.clear();
        enderChest.find(command[1])->second.resize(columns, vector<int>(rows));
        enderChest.find(command[1])->second=mat2;
        cout << rows << "x" << columns << " MATRIX" << endl << endl;
        }
    catch(exception){
        std::cout << "UNSUPPORTED COMMAND" << endl << endl;
    }
}
void matrix::swap_rows(){
    try{
        int row1 = stoi(command[2])-1;
        int row2 = stoi(command[3])-1;

        if(row1<=rows && row2<=rows && command[2]!="0" && command[3]!="0"){
            vector<int> temprow = enderChest.find(command[1])->second[row1];
            enderChest.find(command[1])->second[row1]=enderChest.find(command[1])->second[row2];
            enderChest.find(command[1])->second[row2]=temprow;
            cout << "SWAPPED ROWS " << command[1] << " AND " << command[2] << endl << endl; 
        }
        else{
            std::cout << "UNSUPPORTED COMMAND" << endl << endl;
            return;
        }
    }
    catch(exception){
        std::cout << "UNSUPPORTED COMMAND" << endl << endl;
    }
}
void matrix::addition(){
    rows=enderChest.find(command[2])->second.size();
    columns=enderChest.find(command[2])->second[0].size();
    vector<vector<int> > result(rows, vector<int>(columns));
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            result[i][j]=enderChest.find(command[0])->second[i][j]+enderChest.find(command[2])->second[i][j];           
        }
    }
    enderChest["RESULT"]=result;
    cout << "Matrix Addition : " << rows << "x" << columns << endl << endl;

}
void matrix::subtraction(){
    rows=enderChest.find(command[2])->second.size();
    columns=enderChest.find(command[2])->second[0].size();
    vector<vector<int> > result(rows, vector<int>(columns));
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            result[i][j]=enderChest.find(command[0])->second[i][j]-enderChest.find(command[2])->second[i][j];           
        }
    }
    enderChest["RESULT"]=result;
    cout << "Matrix Subtraction : " << rows << "x" << columns << endl << endl;

}

class matrixMxN: public matrix{
    private:
        int rows,columns;
        vector<vector<int> > mat;
    public:
        matrixMxN(vector<string> command);
};

matrixMxN::matrixMxN(vector<string> command) : matrix(){
    rows=stoi(command[2]); 
    columns=stoi(command[3]);
}

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

int main(){
    matrix Matrix;
    while(true){
        Matrix.getCommand(inputter());
        Matrix.inputCheck();
    }
    return 0;
}