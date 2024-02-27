#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <ctime>
#include <chrono>
#include <cmath>
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

class ParkingEntry{
    public:
        string plate;
        string manufacturer;
        string modelName;
        string modelYear;
        
        time_t entrydate;
        time_t entryTime;
        time_t exitTime=0;
        double totalhours=0;
        int totalCost=0;
        
        void toCsv();
        void getCost();
        void logEntry();
        void logExit();
};

void ParkingEntry::toCsv(){
    tm *time=localtime(&entryTime);
    tm *time2=localtime(&exitTime);
    cout<<plate<<",";
    cout<<time->tm_hour<<":"<<time->tm_min<<":"<<time->tm_sec<<","; //find out whatever this is
    
    cout<<time2->tm_hour<<":"<<time2->tm_min<<":"<<time2->tm_sec<<",";
    cout<<totalhours<<",";
    cout<<totalCost<<",";
    cout<<entrydate<<",";
    cout<<manufacturer<<",";
    cout<<modelName<<",";
    cout<<modelYear<<endl;
}   //<<time2->tm_hour<<":"<<time2->tm_min<<":"<<time2->tm_sec<< FOR TIME

void ParkingEntry::logEntry(){
    entryTime=time(NULL);
}

void ParkingEntry::logExit(){
    exitTime=time(NULL);
}

void ParkingEntry::getCost(){
    totalhours = (difftime(exitTime, entryTime))/3600;
    if(totalhours<=3){
        totalCost=50;
    }
    else{
        totalCost=50;
        totalCost+=(round(totalhours)*20);
    }
}

ParkingEntry inputDetect(vector<string> command, map<string, ParkingEntry> &database, map<string,ParkingEntry> &history){
    if(command[0]=="PARK"){
        ParkingEntry newParkYipee;
        newParkYipee.plate=command[1];
        newParkYipee.manufacturer=command[2];
        newParkYipee.modelName=command[3];
        newParkYipee.modelYear=command[4];
        newParkYipee.logEntry();
        database.insert({newParkYipee.plate, newParkYipee});
        return newParkYipee;
    }

    if(command[0]=="EXIT"){
        try{
            ParkingEntry currentCar=database.find(command[1])->second;
            currentCar.toCsv();
            currentCar.logExit();
            auto moveIt=database.extract(command[1]); // a way to move from one map to another https://stackoverflow.com/a/52541208
            history.insert(std::move(moveIt)); //
            currentCar.logExit();
            currentCar.getCost();
            ParkingEntry foo;
            return foo;
            }
        catch(int num){
            cout << "UNSUPPORTED COMMAND"<<endl;
        }
    }

    if(command[0]=="FIND"){
        try{
            database.at(command[1]).toCsv();
            ParkingEntry foo;
            return foo;
        }
        catch(int num){
            cout<<"CAR NOT FOUND"<<endl;
        }
    }

    if(command[0]=="LIST"){
        for(auto & [k,v]: database){
            v.toCsv();
        }
    }

    if(command[0]=="LOG"){

    }

    if(command[0]=="QUIT"){

    }

}

int main(){
    map<string, ParkingEntry> theDatabase;
    map<string, ParkingEntry> History;
    vector<string> command;
    while(true){
        inputDetect(inputter(), theDatabase, History);
    }

}