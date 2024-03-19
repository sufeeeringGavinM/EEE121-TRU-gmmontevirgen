#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <ctime>
#include <chrono>
#include <cmath>
#include <iomanip>
using namespace std;

int MAX_PARKING_CAPACITY = 50;
int PARKING_HISTORY_CAPACITY = 100;


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

//the below code on doubly linked nodes and lists are both just copy paste from the code from the slides with replaced variables
template <typename S>
class ParkEntryNode {
    public:
        S data;
        ParkEntryNode<S>* next;
        ParkEntryNode<S>* prev;
        ParkEntryNode(S data, ParkEntryNode* next = NULL, ParkEntryNode* prev = NULL);
    
    //template<typename T> friend class ParkEntryList;
};  


template<typename S>
ParkEntryNode<S>::ParkEntryNode(S data, ParkEntryNode* next,ParkEntryNode* prev):data(data),next(next),prev(prev) {}

template<typename T>
class ParkEntryList {
        
    public:
        ParkEntryNode<T>* head;
        ParkEntryNode<T>* tail;
        int size;
int logSize;
int historySize;
        ParkEntryList();
        void addFront(T val);
        void addBack(T val);
        T removeFront();
        T removeBack();
        T front();
        T back();
        int getSize();
        T find(string plato){
            ParkEntryNode<T>* temp = head;

            if(temp!=NULL){ //https://www.alphacodingskills.com/cpp/ds/cpp-doubly-linked-list-traversal.php yoinked
                while(temp!=NULL){
                    if(temp->data.plate==plato){
                        return temp->data;
                    }
                    temp=temp->next;
                }
            }
            else{
                cout<< "CAR NOT FOUND"<< endl << endl;
            }
        }
        void printList(){
            ParkEntryNode<T>* temp = head;

            if(temp!=NULL){
                temp=temp->next;
                while(temp!=tail){
                    if(temp->data.exitTime==-1){
                        temp->data.toCsv();
                        temp=temp->next;}
                    else{
                        temp=temp->next;
                    }
                }
            }
            else{
                cout << "EMPTY" <<endl<<endl;
            }
            cout<<endl;
            return;
        }
        void printLog(){
            ParkEntryNode<T>* temp = head;

            if(temp!=NULL){
                temp=temp->next;
                while(temp!=tail){
                    if(temp->data.exitTime!=-1){
                        temp->data.toCsv();
                        temp=temp->next;}
                    else{
                        temp=temp->next;
                    }
                }
            }
            else{
                cout << "EMPTY" <<endl<<endl;
            }
            cout<<endl;
            return;
        }
        void exit(string plato){
            ParkEntryNode<T>* temp=head;
            if(temp!=NULL){
                while(temp!=NULL){
                    if(temp->data.plate==plato){
                        if(historySize==PARKING_HISTORY_CAPACITY){      
                            removeBack();
                            T &currentCar=temp->data;
                            currentCar.logExit();
                            currentCar.getCost();
                            currentCar.toCsv();
historySize=PARKING_HISTORY_CAPACITY;
                        }
                        else{
                            T &currentCar=temp->data;
                            currentCar.logExit();
                            currentCar.getCost();
                            currentCar.toCsv();
                        }
                    }
                    temp=temp->next;
                }
            }
            else{
                cout<< "CAR NOT FOUND"<< endl << endl;
            }

        }
};

template<typename T>
ParkEntryList<T>::ParkEntryList() {
    this -> head = new ParkEntryNode<T>(T(),NULL,NULL);
    this -> tail = new ParkEntryNode<T>(T(),NULL,NULL);
    this -> head -> next = this -> tail;
    this -> tail -> prev = this -> head;
    this -> size = 0;
}

template<typename T>
void ParkEntryList<T>::addFront(T val) {
    ParkEntryNode<T>* tmpNode = new ParkEntryNode<T>(T(val),this -> head -> next,this -> head);
    this -> head -> next = tmpNode;
    tmpNode -> next -> prev = tmpNode;
    this -> size++;
}

template<typename T>
void ParkEntryList<T>::addBack(T val) {
    ParkEntryNode<T>* tmpNode = new ParkEntryNode<T>(T(val),this -> tail,this -> tail -> prev);
    this -> tail -> prev = tmpNode;
    tmpNode -> prev -> next = tmpNode;
    this -> size++;
}

template<typename T>
T ParkEntryList<T>::removeFront() {
    ParkEntryNode<T>* tmpNode = this -> head -> next;
    tmpNode -> next -> prev =  this -> head;
    this -> head -> next = tmpNode -> next;
    T tmpVal = tmpNode -> data;
    delete tmpNode;
    this -> size--;
    return tmpVal;
}

template<typename T>
T ParkEntryList<T>::removeBack() {
    ParkEntryNode<T>* tmpNode = this -> tail -> prev;
    tmpNode -> prev -> next = this -> tail;
    this -> tail -> prev = tmpNode -> prev; 
    T tmpVal = tmpNode -> data;
    delete tmpNode;
    this -> size--;
    return tmpVal;
}

template<typename T>
T ParkEntryList<T>::front() {
    return this -> head -> next -> data;
}

template<typename T>
T ParkEntryList<T>::back() {
    return this -> tail -> prev -> data;
}

template<typename T>
int ParkEntryList<T>::getSize() {
    return this -> size;
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

void inputDetect(vector<string> command, ParkEntryList<ParkingEntry> &database){
    if(command[0]=="PARK"){
        if(database.logSize==MAX_PARKING_CAPACITY){
            cout << "PARKING FULL"<<endl<<endl;
            return;   
        }
        if(command.size()==5){
            ParkingEntry newParkYipee;
            newParkYipee.plate=command[1];
            newParkYipee.manufacturer=command[2];
            newParkYipee.modelName=command[3];
            newParkYipee.modelYear=command[4];
            newParkYipee.logEntry();
            database.addFront(newParkYipee);
database.logSize++;
            return;
            }
        else{
            cout << "UNSUPPORTED COMMAND"<<endl<<endl;
            return;
        }
    }

    if(command[0]=="EXIT"){
        try{
            if(command.size()==2){
database.historySize++;
                database.exit(command[1]);
                database.logSize--;
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
            if(command.size()==2){
                database.find(command[1]).toCsv();
                cout<<endl;
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
            database.printList();
            return;
            // ParkEntryList<ParkingEntry> clone = ;
        }
        else{
            cout << "UNSUPPORTED COMMAND"<<endl<<endl;
            return;
        }
    }

    if(command[0]=="LOG"){
        if(command.size()==1){
            database.printLog();
            return;
            // ParkEntryList<ParkingEntry> clone = ;
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
    ParkEntryList<ParkingEntry> theDatabase;
    vector<ParkingEntry> VDatabase;
    while(true){ 
        inputDetect(inputter(), theDatabase);
    }

}