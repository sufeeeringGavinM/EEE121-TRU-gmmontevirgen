#include <iostream>
#include <vector>
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

vector<string> inputter(){
    string unparsed;
    cout << "> ";
    getline(cin,unparsed);
    vector<string> parsed=parser(unparsed);
    
    for (int i=0; i<parsed.size(); i++){cout << parsed[i] <<' ';} //oneliner to reprint user command
    cout<<endl<<endl;
    return parsed;
}

class Node {
    public:
        string data;
        vector<Node*> to;
        vector<Node*> from;
        int Tweight; // weight it takes to GO to this node
        Node(string data, Node* to = NULL, Node* from = NULL);
};  

Node::Node(string data, Node* to, Node* from):data(data),to(to),from(from) {}


int inputDetect(vector<string> command, vector<Node*> graph){
    if(command[0]=="DINIT"){
        if(command.size()==2){
            return 1;
        }
        else{
            return 0;
        }
    }
    if(command[0]=="UINIT"){
        if(command.size()==2){
            return 2;
        }
        else{
            return 0;
        }
    }
    if(command[0]=="VADD"){
        if(command.size()==2){
            return 3;
        }
        else{
            return 0;
        }
    }
     if(command[0]=="EADD"){
        if(command.size()==3){
            return 4;
        }
        else{
            return 0;
        }
    }
    if(command[0]=="VDEL"){
        if(command.size()==2){
            return 5;
        }
        else{
            return 0;
        }
    }
     if(command[0]=="EDEL"){
        if(command.size()==3){
            return 6;
        }
        else{
            return 0;
        }
    }
    if(command[0]=="MPRINT"){
        if(command.size()==1){
            return 7;
        }
        else{
            return 0;
        }
    }
     if(command[0]=="APRINT"){
        if(command.size()==1){
            return 8;
        }
        else{
            return 0;
        }
    }
     if(command[0]=="SPATH"){
        if(command.size()==3){
            return 9;
        }
        else{
            return 0;
        }
    }
    else{
        return 0;
    }
}

int main(){
    vector<Node*> graph;
    int noOfvertices;
    vector<string> command=inputter(); 
    bool directed;
    while(command[0]!="EXIT"){
        if (inputDetect(command,graph)==0){
            cout<<"UNSUPPORTED COMMAND"<<endl;
        }
        else if (inputDetect(command, graph)==1){ //DINIT
            directed=true;
            int noOfvertices=stoi(command[1]);
        }
        else if (inputDetect(command, graph)==2){ //UINIT
            directed=false;
            int noOfvertices=stoi(command[1]);
        }
        else if (inputDetect(command, graph)==3){ //VADD
            Node* newNode;
            newNode->data=command[1];
            graph.push_back(newNode);
        }
        else if (inputDetect(command, graph)==4){ //EADD //1st vertex to 2nd vertex IF directed
            if(directed){
                Node* toNode;
                Node* fromNode;
                for(int i=0; i < graph.size();i++){
                    if(graph[i]->data==command[1]){
                        fromNode=graph[i]; // find first vertex
                    }
                }
                for(int i=0; i < graph.size(); i++){
                    if(graph[i]->data==command[2]){ // find second vertex
                        toNode=graph[i];
                    }   
                }
                toNode->Tweight=stoi(command[3]);
                fromNode->to.push_back(toNode); 
                toNode->from.push_back(fromNode); //this and the command above essentially creates an edge
            }
            else{
                Node* toNode;
                Node* fromNode;
                for(int i=0; i < graph.size(); i++){
                    if(graph[i]->data==command[2]){ // find 2nd vertex
                        toNode=graph[i];
                    }  
                    
                }
                for(int i=0; i < graph.size();i++){
                    if(graph[i]->data==command[1]){
                        fromNode=graph[i];
                    }
                }

                toNode->Tweight=stoi(command[3]);
                fromNode->Tweight=stoi(command[3]);
                fromNode->to.push_back(toNode);
                toNode->from.push_back(fromNode);
                
                // an undirected graph is relaly just a fully bidirectional directed graph;
            }
        }
        else if (inputDetect(command, graph)==5){ //VDEL
            for(int i=0; i<graph.size(); i++){
                // iterate through toNodes and fromNodes of everything, find which ones contain the vertex to be deleted, delete them
                // then, only then can you delete the vertex
            }
        }
        else if (inputDetect(command, graph)==6){ //EDEL
            //iterate through toNodes and fromNodes like before, find which ones contain the vertices in the necessary from and to vectors, delete them.
            // dont delete vertex itself
        }
        else if (inputDetect(command, graph)==7){ //MPRINT
            // iDK  
        }
        else if (inputDetect(command, graph)==8){ //APRINT
            // IDK
        }
        else if (inputDetect(command, graph)==9){ //SPATH
            // something
        }
        command=inputter();
    }
}