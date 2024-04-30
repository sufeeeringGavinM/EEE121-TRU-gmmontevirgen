#include <iostream>
#include <vector>

using namespace std;

//just use vector of Stuff

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <ctime>
#include <chrono>
#include <cmath>
#include <iomanip>
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

vector<string> inputter(){
    string unparsed;
    cout << "> ";
    getline(cin,unparsed);
    vector<string> parsed=parser(unparsed);
    
    for (int i=0; i<parsed.size(); i++){cout << parsed[i] <<' ';} //oneliner to reprint user command
    cout<<endl<<endl;
    return parsed;
}


void inputDetect(vector<string> command, vector<vector<int>> graph){
    if(command[0]=="DINIT"){
     
    }
    if(command[0]=="UINIT"){

    }
     if(command[0]=="VADD"){
        
    }
     if(command[0]=="EADD"){
        
    }
     if(command[0]=="VDEL"){
        
    }
     if(command[0]=="EDEL"){
        
    }
     if(command[0]=="MPRINT"){
        
    }
     if(command[0]=="APRINT"){
        
    }
     if(command[0]=="SPATH"){
        
    }

}

int main(){
    vector<vector<vector<int>>> graphs;
    vector<string> command=inputter(){

    }

    }
}