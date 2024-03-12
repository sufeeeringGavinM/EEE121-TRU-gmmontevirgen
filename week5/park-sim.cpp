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
int binarySearch(vector<ParkingEntry> database, int l, int r, string x)
{
    if (r >= l) {
        int mid = l+(r-l)/2;
        cout<<"MID-"<<mid<<" : ";
        database[mid].toCsv();
        if (database[mid].plate == x){ //edge case
            return mid;
        }

        if (database[mid].plate > x){ //assuming sorted, so if element we're looking for is not to the right it can only be to the left 
            return binarySearch(database, l, mid - 1, x);
        }
        return binarySearch(database, mid + 1, r, x); //same thing as above but to other side
    }
 
    // We reach here when element is not
    // present in array
    return -1;
}
int partition(vector<ParkingEntry> &databaseV, int belo, int abov){ //code is mostly just from powerpoint
    int piv=stoi(databaseV[abov-1].modelYear);
    int i=belo;
    int j=abov - 2;
        
    if(databaseV[i].modelYear.empty()==false){ //for partitions where nothing further must be done
        cout<<"PVT-"<<piv<< " PARTITION: ";
        }
    i=belo;
    j=abov-2;
    while(i<=j){
        if(stoi(databaseV[j].modelYear)<piv && stoi(databaseV[i].modelYear)>piv){
            swap(databaseV[i],databaseV[j]);
            i++;
            j--;
        }
        else if(stoi(databaseV[i].modelYear)<=piv){
            i++;
        }
        else{
            j--;
        }
    }
    if(databaseV[i].modelYear>databaseV[abov-1].modelYear){
        swap(databaseV[i],databaseV[abov-1]);
    }
    for(belo;belo<abov;belo++){
        cout<<databaseV[belo].modelYear<<" ";
    }
    cout<<endl;
    return i;
    

}
void qsort(vector<ParkingEntry> &databaseV, int belo, int abov){
    
    if(belo<(abov-1)){
        int p = partition(databaseV, belo, abov);
        qsort(databaseV,belo,p);
        qsort(databaseV,p+1,abov);
    }
    return;
}
void inputDetect(vector<string> command, map<string, ParkingEntry> &database, map<string,ParkingEntry> &history, vector<ParkingEntry> &databaseV){
    if(command[0]=="PARK"){
        if(database.size()==10000){
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
            databaseV.push_back(newParkYipee);
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
            if(databaseV.size()!=0){
                for(int x=0; x<databaseV.size(); x++){
                    databaseV[x].toCsv();
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
    if(command[0]=="BFIND"){
        //SORTS first
        for(int i=0; i<databaseV.size()-1; i++){
            for(int j=0; j<databaseV.size()-i-1; j++){
                if(databaseV[j].plate>databaseV[j+1].plate){
                    ParkingEntry temp = databaseV[j];
                    databaseV[j]=databaseV[j+1];
                    databaseV[j+1]=temp;  
                    // cout<<"ITER" <<i+1<<" : ";
                    // databaseV[j].toCsv();
                }
            }
            
        }
        database.clear();
        for(ParkingEntry& i : databaseV ){ //REINSERT EVERYRTHING INTO MAP DATABASE
            database.insert({i.plate, i});
        }
        if(command.size()!=2){
            cout << "UNSUPPORTED COMMAND"<<endl<<endl;
            return;
        }
        else{
            int where=binarySearch(databaseV, 0, databaseV.size()-1, command[1]);
            if(where==-1){
                cout <<"PLATE NOT FOUND"<<endl<<endl;
                return;
            }
            else{
                cout<<endl;
                databaseV[where].toCsv();
                cout<<endl;
                return;
            }
        }

    }
    if(command[0]=="BSORT"){
        int counter=0;
        if(command.size()!=1){
            cout << "UNSUPPORTED COMMAND"<<endl<<endl;
            return;
        }
        else{//the bubble sort
            for(int i=0; i<databaseV.size()-1; i++){
                for(int j=0; j<databaseV.size()-i-1; j++){
                    if(databaseV[j].plate>databaseV[j+1].plate){
                        ParkingEntry temp = databaseV[j];
                        databaseV[j]=databaseV[j+1];
                        databaseV[j+1]=temp;  
                        // cout<<"ITER" <<i+1<<" : ";
                        // databaseV[j].toCsv();
                    }
                }
                
            }
            database.clear();
            for(ParkingEntry& i : databaseV ){ //REINSERT EVERYRTHING INTO MAP DATABASE
                database.insert({i.plate, i});
            }
            return;
        }

    }

     if(command[0]=="QSORT"){
        int counter=0;
        
        if(command.size()!=1){
            cout << "UNSUPPORTED COMMAND"<<endl<<endl;
        }

        else{
            cout<<"UNSORTED LIST: ";
            for(int i=0; i<databaseV.size();i++){
                cout<<databaseV[i].modelYear<<" ";
            } 
             cout<<endl;
            qsort(databaseV,0,databaseV.size());
            cout<<"SORTED LIST: ";
            for(int i=0; i<databaseV.size();i++){
                cout<<databaseV[i].modelYear<<" ";
            } 
            cout<<endl;
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
    vector<ParkingEntry> VDatabase;
    while(true){ 
        inputDetect(inputter(), theDatabase, History, VDatabase);
    }

}