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

class ParkingEntry{
    public:
        string plate;
        string manufacturer;
        string modelName;
        string modelYear;
        
        time_t entryTime;
        time_t exitTime=(time_t)(-1);

        int totalhours = round((difftime(time(0), entryTime))/3600); // difference between two time_t types in seconds/ divided by 3600;
        int totalCost;
        
        void toCsv();
        void getCost();
        void logEntry();
        void logExit();
};

void ParkingEntry::toCsv(){
    
    cout<<plate<<",";
    cout<<std::put_time(std::localtime(&entryTime), "%H:%M:%S") <<","; //find out whatever this is
    
    if(exitTime==-1){
        cout<< "NONE" <<",";  
    }
    else{
        cout<<std::put_time(std::localtime(&exitTime), "%H:%M:%S") <<",";
    }
    totalhours = round((difftime(time(0), entryTime))/3600);
    cout<<round(totalhours)<<",";
    getCost();
    cout<< "P"<<totalCost<<",";
    cout<<std::put_time(std::localtime(&entryTime), "%a,%m/%d/%y") <<",";
    cout<<manufacturer<<",";
    cout<<modelName<<",";
    cout<<modelYear<<endl;
}   //<<time2->tm_hour<<":"<<time2->tm_min<<":"<<time2->tm_sec<< FOR TIME

void ParkingEntry::logEntry(){
    entryTime=std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()); //https://stackoverflow.com/a/27856440
}

void ParkingEntry::logExit(){
    
    exitTime=std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
}

void ParkingEntry::getCost(){
    totalhours = round((difftime(time(0), entryTime))/3600);
    if(totalhours<3){  // FREE PARKING!!
        totalCost=0;
        return;
    }
    if(totalhours==3){ // No free parking 
        totalCost=50;
        return;
    } 
    else{ //theft
        totalCost=50;
        totalCost+=((round(totalhours)-3)*20);
        return;
    }
}

void inputDetect(vector<string> command, map<string, ParkingEntry> &database, map<string,ParkingEntry> &history){
    if(command[0]=="PARK"){
        if(database.size()==500){
            cout << "MAXIMUM PARKING REACHED!"<<endl<<endl;
            return;   
        }
        if(command.size()==5){
            ParkingEntry newParkYipee;
            newParkYipee.plate=command[1];
            newParkYipee.manufacturer=command[2];
            newParkYipee.modelName=command[3];
            newParkYipee.modelYear=command[4];
            newParkYipee.logEntry();
            database.insert({newParkYipee.plate, newParkYipee});
            return;
            }
        else{
            cout << "UNSUPPORTED COMMAND"<<endl<<endl;
            return;
        }
    }

    if(command[0]=="EXIT"){
        try{
            if(command.size()==2 && database.find(command[1])!=database.end()){
                ParkingEntry &currentCar=database.find(command[1])->second;
                
                currentCar.logExit();
                currentCar.getCost();
                currentCar.toCsv();

                auto moveIt=database.extract(command[1]); // a way to move from one map to another https://stackoverflow.com/a/52541208
                history.insert(std::move(moveIt)); //
                cout<<endl;
                return;
                }
            else{
                cout << "UNSUPPORTED COMMAND"<<endl<<endl;
                return;
            }
        }
        catch(int& num){
            cout << "UNSUPPORTED COMMAND"<<endl<<endl;
            return;
        }
    }

    if(command[0]=="FIND"){
        try{
            if(command.size()==2 && database.find(command[1])!=database.end()){
              database.at(command[1]).toCsv(); 
              cout<<endl;
              return;
            }
            else{
                cout << "CAR NOT FOUND"<<endl<<endl;
                return;
            }
        }
        catch(int num){
            cout<<"UNSUPPORTED COMMAND"<<endl<<endl;
            return;
        }
    }

    if(command[0]=="LIST"){
        if(command.size()==1){
            if(database.size()!=0){
                for(auto & [ke,ve]: database){
                    ve.toCsv();
                }
                cout<<endl;
                return;
            }
            else{
                cout<< "EMPTY CURRENT DATABASE :(" << endl<<endl;
                return;
            }
        }
        else{
            cout << "UNSUPPORTED COMMAND"<<endl<<endl;
            return;
        }
    }

    if(command[0]=="LOG"){
        if(history.size()==1000){
            cout << "PARKING LOG DATABASE REACHED MAX!" <<endl<<endl;
        }
        if(command.size()==1){
            if(history.size()!=0){
                for(auto & [k,v]: history){
                    v.toCsv();
                }
                cout<<endl;
                return;
            }
            else{
                cout<< "EMPTY LOG :(" << endl<<endl;
                return;
            }
        }
        else{
            cout << "UNSUPPORTED COMMAND"<<endl<<endl;
            return;
        }
    }

    if(command[0]=="QUIT"){
        exit(0);
    }

    else{
        cout << "UNSUPPORTED COMMAND"<<endl<<endl;
        return;
    }

}

int main(){
    map<string, ParkingEntry> theDatabase;
    map<string, ParkingEntry> History;
    while(true){
        inputDetect(inputter(), theDatabase, History);
    }

}