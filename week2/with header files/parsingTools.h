#ifndef PARSINGTOOLS_H
#define PARSINGTOOLS_H

#include <iostream>
#include <vector>
#include <map>
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
vector<string> inputter(){
    string unparsed;
    cout << "> ";
    getline(cin,unparsed);
    vector<string> parsed=parser(unparsed);
    
    for (int i=0; i<parsed.size(); i++){cout << parsed[i] <<' ';} //oneliner to reprint user command
    cout<<endl<<endl;
    return parsed;
}

#endif