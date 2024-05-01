#include <iostream>
#include <vector>
#include <string>
#include <climits>

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

struct Node {
    string data;
};  

struct Edge{
    Node* to;
    Node* from;
    int weight;
    int u;
    int v;
};

struct Graph{
    vector<Node*> vertices = {}; //I MEAN VERTICES BUT ITS TOO LATE TO CHANGE
    vector<Edge*> edges = {};
    int activeVertices=0;
    int activeEdges=0;
};

int inputDetect(vector<string> command){
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
        if(command.size()==4){
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
    Graph graph;
    vector<string> command=inputter(); 
    bool directed;
    vector<vector<int>> adjMatrix;
    bool initialized=false;
    int numberofVertices;

    while(command[0]!="EXIT"){
        if (inputDetect(command)==0){
            cout<<"UNSUPPORTED COMMAND"<<endl;
            command=inputter(); 
            continue;
        }
        if(!initialized){
            if (inputDetect(command)==1){ //DINIT
                directed=true;
                for(int i=0; i<stoi(command[1]); i++){
                    Node* newNode = new Node;
                    newNode->data=" "; //NOBODYS GONNA NAME A VECTOR NULL RIGHT???
                    graph.vertices.push_back(newNode);
                }
                adjMatrix.resize(stoi(command[1]), vector<int>(stoi(command[1])));
                initialized=true;
                numberofVertices=stoi(command[1]);
            }
            else if (inputDetect(command)==2){ //UINIT
                directed=false;
                for(int i=0; i<stoi(command[1]); i++){
                    Node* newNode = new Node;
                    newNode->data=" ";
                    graph.vertices.push_back(newNode);
                }
                adjMatrix.resize(stoi(command[1]), vector<int>(stoi(command[1])));
                initialized=true;
                numberofVertices=stoi(command[1]);
            }
            else{
                cout<<"UNSUPPORTED COMMAND"<<endl;
            }
        }
        
        else{
            if (inputDetect(command)==3){ //VADD
                bool duplicateChecker=false;
                if(graph.activeVertices!=numberofVertices){
                    for(int i=0; i<graph.vertices.size(); i++){
                        if(graph.vertices[i]->data==command[1]){
                            cout<<"DUPLICATE VERTEX"<<endl;
                            duplicateChecker=true;// CHECK DUPLICATES
                        }
                    }
                    if(!duplicateChecker){
                        for(int i=0; i<graph.vertices.size(); i++){
                            if(graph.vertices[i]->data==" "){
                                graph.vertices[i]->data=command[1];
                                graph.activeVertices++;
                                break;
                            }
                        }
                    }
                }
                else{
                    cout <<"GRAPH FULL"<<endl;
                }
            }
            else if (inputDetect(command)==4){ //EADD //1st vertex to 2nd vertex IF directed
                int PH1index;
                int PH2index;
                Node* PH1;
                Node* PH2;
                int vertChecker=0; // in an edge both vertices must be present
                bool alreadyThere=false;
                if(directed){
                    for(int i=0; i<graph.vertices.size(); i++){
                        if(graph.vertices[i]->data == command[1]){
                            PH1=graph.vertices[i];
                            PH1index=i;
                            vertChecker++;
                        }
                        if(graph.vertices[i]->data == command[2]){
                            PH2=graph.vertices[i];
                            PH2index=i;
                            vertChecker++;
                        }
                    }
                    for(int i=0; i<graph.edges.size(); i++){
                        if((graph.edges[i]->from->data==command[1] && graph.edges[i]->to->data==command[2])){
                            alreadyThere=true;
                        }
                    }
                    if(vertChecker==2 && !alreadyThere){
                        Edge* newEdge= new Edge;
                        newEdge->from=PH1;
                        newEdge->to=PH2;
                        newEdge->weight=stoi(command[3]);
                        graph.edges.push_back(newEdge);
                        adjMatrix[PH1index][PH2index]=stoi(command[3]);
                        graph.activeEdges++;
                    }
                    else{
                        cout<<"VECTOR/S NOT FOUND OR PERHAPS, EDGE ALREADY EXISTS!"<<endl;
                    }
                }
                else{
                    for(int i=0; i<graph.vertices.size(); i++){
                        if(graph.vertices[i]->data == command[1]){
                            PH1=graph.vertices[i];
                            PH1index=i;
                            vertChecker++;
                        }
                        if(graph.vertices[i]->data == command[2]){
                            PH2=graph.vertices[i];
                            PH2index=i;
                            vertChecker++;
                        }
                        
                    }
                    for(int i=0; i<graph.edges.size(); i++){
                        if((graph.edges[i]->to->data==command[1] && graph.edges[i]->from->data==command[2]) || (graph.edges[i]->from->data==command[1] && graph.edges[i]->to->data==command[2])){
                            alreadyThere=true;
                        }
                    }
                    if(vertChecker==2 && !alreadyThere){
                        Edge* newEdge= new Edge;
                        newEdge->from=PH1;
                        newEdge->to=PH2;
                        newEdge->weight=stoi(command[3]);
                        graph.edges.push_back(newEdge);
                        
                        //undirected = bidirectional
                        newEdge= new Edge;
                        newEdge->from=PH2;
                        newEdge->to=PH1;
                        newEdge->weight=stoi(command[3]);
                        graph.edges.push_back(newEdge);
                        adjMatrix[PH1index][PH2index]=stoi(command[3]);
                        adjMatrix[PH2index][PH1index]=stoi(command[3]);
                        graph.activeEdges++; // yet those two directions are considered one edge
                    }
                    else{
                        cout<<"VECTOR/S NOT FOUND OR PERHAPS, EDGE ALREADY EXISTS!"<<endl;
                    }   
                }
                
            }
            else if (inputDetect(command)==5){ //VDEL
                bool Found=false;
                int EdgesFound=0;
                
                for(int i=0; i<graph.vertices.size(); i++){ //delete vertex itself
                    if(graph.vertices[i]->data==command[1]){
                        graph.vertices.erase(graph.vertices.begin()+i);
                        graph.activeVertices--;
                        Found=true;
                        for(int j=0; j < graph.vertices.size(); j++){
                            adjMatrix[i][j]=0;
                            adjMatrix[j][i]=0;
                        }
                        Node* newNode= new Node;
                        newNode->data=" ";
                        graph.vertices.push_back(newNode);
                    } 
                }
                for(int i=0; i<graph.edges.size(); i++){
                    if(graph.edges[i]->to->data == command[1] || graph.edges[i]->from->data == command[1]){
                        EdgesFound++;
                    }
                }
                if(EdgesFound>0){
                    if(directed){
                        graph.activeEdges-=EdgesFound;
                    }
                    else{
                        graph.activeEdges--;
                    }
                }
                for(int i=0; i<graph.edges.size(); i++){ //delete edges associated with vertex to delete
                    if(graph.edges[i]->from->data == command[1]){
                        graph.edges.erase(graph.edges.begin()+i);
                    }
                }
                for(int i=0; i<graph.edges.size(); i++){ //delete edges associated with vertex to delete
                    if(graph.edges[i]->to->data == command[1]){
                        graph.edges.erase(graph.edges.begin()+i);
                    }
                }
                if(!Found){
                    cout <<"VECTOR/S NOT FOUND" <<endl;
                }
                
            }
            else if (inputDetect(command)==6){ //EDEL
                bool Found=false;
                int oneIndex;
                int twoIndex;
                if(directed){
                    for(int i=0; i<graph.edges.size(); i++){
                        if(graph.edges[i]->from->data==command[1] && graph.edges[i]->to->data==command[2]){
                            graph.edges.erase(graph.edges.begin()+i);
                            graph.activeEdges--;
                            Found=true;
                            break;
                        }
                        // find index of first and second vector given
                    }
                    if(Found==true){
                        for(int i=0; i<graph.vertices.size(); i++){
                            if(graph.vertices[i]->data==command[1]){
                                oneIndex=i;
                            }
                            if(graph.vertices[i]->data==command[2]){
                                twoIndex=i;
                            }
                        }
                        adjMatrix[oneIndex][twoIndex]=0;
                    }
                }
                else{
                    for(int i=0; i<graph.edges.size(); i++){
                        if((graph.edges[i]->from->data==command[1] && graph.edges[i]->to->data==command[2])){
                            graph.edges.erase(graph.edges.begin()+i); 
                            Found=true;
                        }
                        
                    }
                    for(int i=0; i<graph.edges.size(); i++){
                        if((graph.edges[i]->to->data==command[1] && graph.edges[i]->from->data==command[2])){
                            graph.edges.erase(graph.edges.begin()+i);
                            Found=true;
                        }
                    }
                    if(Found){
                        for(int i=0; i<graph.vertices.size(); i++){
                            if(graph.vertices[i]->data==command[1]){
                                oneIndex=i;
                            }
                            if(graph.vertices[i]->data==command[2]){
                                twoIndex=i;
                            }
                        }
                        adjMatrix[oneIndex][twoIndex]=0;
                        adjMatrix[twoIndex][oneIndex]=0;
                        graph.activeEdges--;
                    }
                }
                if(Found==false){
                    cout << "VECTOR/S NOT FOUND" << endl; 
                }
            }
            else if (inputDetect(command)==7){ //MPRINT
                cout << "|V| = " << graph.activeVertices << ",  " << "|E| = " << graph.activeEdges << endl;
                cout << "      ";
                for(int i=0; i<graph.activeVertices; i++){
                    cout << "[" << graph.vertices[i]->data << "]" << "      ";
                }
                cout<<endl;
                for(int i=0; i<graph.activeVertices;i++){
                    cout << "[" << graph.vertices[i]->data << "]";
                  
                    for(int j=0; j<graph.activeVertices;j++){
                        cout<< "    " << adjMatrix[i][j]<<"    ";
                    }
                    cout<<endl;
                }
                
            }
            else if (inputDetect(command)==8){ //APRINT
                bool checker=false;
                cout << "|V| = " << graph.activeVertices << ",  " << "|E| = " << graph.activeEdges << endl;
                for(int i=0; i<graph.activeVertices; i++){
                    cout << "[" << graph.vertices[i]->data<<"]"<<" -> ";
                    cout << "[" ;
                    for(int j=0; j<graph.edges.size(); j++){
                        if(graph.edges[j]->from->data==graph.vertices[i]->data){
                            if(checker){
                                    cout<<", ";
                                    cout<<"("<< graph.edges[j]->to->data<<", "<<graph.edges[j]->weight<<")";
                            }
                            else{
                                cout<<"("<< graph.edges[j]->to->data<<", "<<graph.edges[j]->weight<<")";
                                checker=true;
                            }
                        }      
                    }
                    checker=false; 
                    cout << "]" << endl;
                }
                
            }
            else if (inputDetect(command)==9){ //SPATH
                int foundit=0;
                int src;
                for(int i=0; i<graph.vertices.size(); i++){
                    if((graph.vertices[i]->data==command[1])){
                        src=i;
                        foundit++;
                    }        
                    if((graph.vertices[i]->data==command[2])){
                        foundit++;
                    }
                }
                if(foundit==2){
                    int V=graph.activeVertices;
                    int E=graph.activeEdges;
                    vector<string> narrowWayThrough;
                    vector<int> dist(V);
                    vector<string> pre(V);
                    int u,v;
                    string uu, vv;
                    int weight;
                    
                    for(int i=0; i<V; i++){
                        dist[i]=INT_MAX;
                    }
                    dist[src]=0;
                    for(int i=1;i<=V-1;i++){
                        for(int j=0; j<E; j++){
                            uu = graph.edges[j]->from->data;
                            vv= graph.edges[j]->to->data;
                            for(int i=0; i<graph.vertices.size(); i++){
                                if(graph.vertices[i]->data==uu){
                                    u=i; //find nth vertex
                                }
                                if(graph.vertices[i]->data==vv){
                                    v=i; 
                                }   
                            }
                            weight=graph.edges[j]->weight;
                            if(dist[u]!=INT_MAX && dist[u] + weight < dist[v]){
                                dist[v]=dist[u]+weight;
                                pre[v]=graph.vertices[u]->data; 
                            }
                        }
                    }
               
                    cout << "v    d[v]   pre[v]]" << endl;
                    for (int i = 0; i < V; i++){
                        if(dist[i]!=INT_MAX)
                            cout << graph.vertices[i]->data <<  "     " <<  dist[i] << "     "<<  pre[i] << endl;
                        else
                            cout << graph.vertices[i]->data <<  "     " <<  'X' << "     "<<  pre[i] << endl;
                    }
                    string nextVertex=command[2];
                    cout<<"Shortest path from " << command[1] << " to " << command[2] << " is: ";
                    int i=0;
                    int maxcycles=0;
                    while(nextVertex!=command[1]){
                        if(graph.vertices[i]->data==nextVertex){
                            nextVertex=pre[i];
                            narrowWayThrough.push_back(graph.vertices[i]->data);
                        }
                        if(nextVertex==command[1]){
                            narrowWayThrough.push_back(nextVertex);
                            break;
                        }
                        if(i==graph.activeVertices-1){
                            i=0;
                        }
                        i++;
                        maxcycles++;
                        if(maxcycles>V*V){
                            cout << "NO WAY THROUGH" <<endl;
                            break;
                        }
                    }
                    for(int i=0; i<narrowWayThrough.size()-1;i++){
                        cout<<narrowWayThrough[i]<< " -> ";
                    }
                    cout<<narrowWayThrough[narrowWayThrough.size()-1];
                    cout<<endl;
                
                }
                else{
                    cout<<"VECTOR/S NOT FOUND"<<endl;
                }
            }
        }
        command=inputter();
    }
} 