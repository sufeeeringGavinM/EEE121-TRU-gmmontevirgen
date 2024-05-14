#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <algorithm>
#include <queue>
#include <map>
#include <set>

using namespace std;
typedef pair<int,int> PII;

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
    bool KMSTflag=false;
    
    Edge(Node* to, Node* from, int weight):to(to),from(from),weight(weight)
    {}
};

struct pptEdge{
    int u;
    int v;
    int weight;
    bool KMSTflag=false;
    

    pptEdge(int u, int v, int weight): u(u), v(v), weight(weight){}
};

struct Graph{
    vector<Node*> vertices = {}; //I MEAN VERTICES BUT ITS TOO LATE TO CHANGE
    vector<Edge> edges = {};
    int activeVertices=0;
    int activeEdges=0;
};

struct unfind{ //unionfind 
    vector<int> parent;

    unfind(int n):parent(n) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unionSets(int x, int y) {
        int xkwisatz = find(x);
        int yhaderach = find(y);

        if (xkwisatz != yhaderach) {
            parent[xkwisatz] = yhaderach; //the kwisatz haderach is the KEY union
        }
    }
};

vector<vector<string>> mergeStuff(vector<vector<string>>& vectors) { //didnt wanna use "merge()"" might cause dumb errors
    int n = vectors.size();
    unfind FINDHER(n);

    // union similar vectors
    for (int i=0; i<n; i++) {
        for (int j=i+1; j<n; j++) {
            for (string& elem1 : vectors[i]) {
                if (find(vectors[j].begin(), vectors[j].end(), elem1) != vectors[j].end()) {
                    FINDHER.unionSets(i,j);
                    break;
                }
            }
        }
    }

    // merge similar vetors
    vector<vector<string>> mergedVectors(n);
    for (int i=0; i<n; i++) {
        int root = FINDHER.find(i);
        mergedVectors[root].insert(mergedVectors[root].end(), vectors[i].begin(), vectors[i].end());
    }

    // remove dupes
    for (int i=0;i<mergedVectors.size();i++) {
        sort(mergedVectors[i].begin(),mergedVectors[i].end());
        mergedVectors[i].erase(unique(mergedVectors[i].begin(), mergedVectors[i].end()), mergedVectors[i].end());
    }

    // remove emptyes
    for(int i=0; i<mergedVectors.size();i++){
        if(mergedVectors[i].empty()){
            mergedVectors.erase(mergedVectors.begin() + i);
            i--;
        }
    }

    return mergedVectors;
}

//straight from ppt

class EdgeComparator {
    public:
        bool operator()(const pptEdge &e1, const pptEdge &e2) {
                if(e1.weight != e2.weight) {
                    return e1.weight > e2.weight;
                } else if(e1.u != e2.u) {
                    return e1.u > e2.u;
                }
                return e1.v > e2.v;
            }
};

int* parent;
int* rnk;

void MakeSet(int N) {
    parent = new int[N];
    rnk = new int[N];

    for(int i = 0; i < N; i++) {
        parent[i] = i;
        rnk[i] = 0;
    }
}

int FindSet(int x) {
    if(parent[x] != x) {
        x = FindSet(parent[x]);
        parent[x] = x;
    }
    return x;
}

void Union(int x, int y) {
    x = FindSet(x);
    y = FindSet(y);

    if(x != y) {
        if(rnk[x] > rnk[y]) {
            parent[y] = x;
        } else {
            parent[x] = y;
            if(rnk[x] == rnk[y]) {
               rnk[y]++;
            }
        }
    }
}

void PrintSets(int N, Graph graph) {
    map<int, set<int>> sets;

    for(int i=0; i<N; i++) {
        int rep = FindSet(i);
        sets[rep].insert(i);
    }

    for(const auto& set:sets) { //iteratre through map
        cout << "{";
        for(int element:set.second) {
            cout << graph.vertices[element]->data << ", ";
        }
        cout <<"\b"<< "\b}, ";
    }
    cout<<"\b"<<'\b'; //remove shit-looking commas
}

//until here

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
    if(command[0]=="DSETS"){
        if(command.size()==1){
            return 11;
        }
        else{
            return 0;
        }
    }

    if(command[0]=="GENMST"){
        if(command.size()==1){
            return 12;
        }
        else{
            return 0;
        }
    }
    if(command[0]=="MST-MPRINT"){
        if(command.size()==1){
            return 13;
        }
        else{
            return 0;
        }
    }
    if(command[0]=="MST-APRINT"){
        if(command.size()==1){
            return 14;
        }
        else{
            return 0;
        }
    }

    if(command[0]=="KMST"){
        if(command.size()==1){
            return 15;
        }
        else{
            return 0;
        }
    }
    if(command[0]=="KMST-MPRINT"){
        if(command.size()==1){
            return 16;
        }
        else{
            return 0;
        }
    }
    if(command[0]=="KMST-APRINT"){
        if(command.size()==1){
            return 17;
        }
        else{
            return 0;
        }
    }  
    else{
        return 0;
    }
};

int main(){
    bool kmstexists=false;
    Graph graph;
    vector<string> command=inputter(); 
    bool directed;
    vector<vector<pptEdge>> G;
    vector<vector<int>> adjMatrix;
    vector<vector<int>> mstMatrix;
    vector<vector<int>> kmstMatrix;
    Graph kmstgraph;
    Graph mstgraph;
    bool initialized=false;
    int numberofVertices;
    bool mstexists=false;
    int V;

    vector<Edge> mstedging;

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
                    newNode->data=" "; //NOBODYS GONNA NAME A VERTEX NOTHING RIGHT???
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
                                if(command[1]!=" "){
                                    graph.vertices[i]->data=command[1];
                                    graph.activeVertices++;
                                    break;
                                }
                                else{
                                    cout<<"please dont name the vertex nothing";
                                }
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
                        if((graph.edges[i].from->data==command[1] && graph.edges[i].to->data==command[2])){
                            alreadyThere=true;
                        }
                    }
                    if(vertChecker==2 && !alreadyThere){
                        Edge newEdge= Edge(PH1, PH2, stoi(command[3]));
                        graph.edges.push_back(newEdge);
                        adjMatrix[PH1index][PH2index]=stoi(command[3]);
                        graph.activeEdges++;
                    }
                    else{
                        cout<<"VERTEX/ICES NOT FOUND OR PERHAPS, EDGE ALREADY EXISTS!"<<endl;
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
                        if((graph.edges[i].to->data==command[1] && graph.edges[i].from->data==command[2]) || (graph.edges[i].from->data==command[1] && graph.edges[i].to->data==command[2])){
                            alreadyThere=true;
                        }
                    }
                    if(vertChecker==2 && !alreadyThere){
                        Edge newEdge= Edge(PH1,PH2,stoi(command[3]));
                        
                        graph.edges.push_back(newEdge);
                        
                        //undirected = bidirectional
                        Edge newEdge2= Edge(PH2,PH1,stoi(command[3]));
                        graph.edges.push_back(newEdge2);
                        adjMatrix[PH1index][PH2index]=stoi(command[3]);
                        adjMatrix[PH2index][PH1index]=stoi(command[3]);
                        graph.activeEdges++; // yet those two directions are considered one edge
                    }
                    else{
                        cout<<"VERTEX/ICES NOT FOUND OR PERHAPS, EDGE ALREADY EXISTS!"<<endl;
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
                    if(graph.edges[i].to->data == command[1] || graph.edges[i].from->data == command[1]){
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
                    if(graph.edges[i].from->data == command[1]){
                        graph.edges.erase(graph.edges.begin()+i);
                    }
                }
                for(int i=0; i<graph.edges.size(); i++){ //delete edges associated with vertex to delete
                    if(graph.edges[i].to->data == command[1]){
                        graph.edges.erase(graph.edges.begin()+i);
                    }
                }
                if(!Found){
                    cout <<"VERTEX NOT FOUND" <<endl;
                }
                
            }
            else if (inputDetect(command)==6){ //EDEL
                bool Found=false;
                int oneIndex;
                int twoIndex;
                if(directed){
                    for(int i=0; i<graph.edges.size(); i++){
                        if(graph.edges[i].from->data==command[1] && graph.edges[i].to->data==command[2]){
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
                        if((graph.edges[i].from->data==command[1] && graph.edges[i].to->data==command[2])){
                            graph.edges.erase(graph.edges.begin()+i); 
                            Found=true;
                        }
                        
                    }
                    for(int i=0; i<graph.edges.size(); i++){
                        if((graph.edges[i].to->data==command[1] && graph.edges[i].from->data==command[2])){
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
                    cout << "VERTEX/S NOT FOUND" << endl; 
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
                        if(graph.edges[j].from->data==graph.vertices[i]->data){
                            if(checker){
                                    cout<<", ";
                                    cout<<"("<< graph.edges[j].to->data<<", "<<graph.edges[j].weight<<")";
                            }
                            else{
                                cout<<"("<< graph.edges[j].to->data<<", "<<graph.edges[j].weight<<")";
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
                    V=graph.activeVertices;
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
                            uu = graph.edges[j].from->data;
                            vv= graph.edges[j].to->data;
                            for(int i=0; i<graph.vertices.size(); i++){
                                if(graph.vertices[i]->data==uu){
                                    u=i; //find nth vertex
                                }
                                if(graph.vertices[i]->data==vv){
                                    v=i; 
                                }   
                            }
                            weight=graph.edges[j].weight;
                            if(dist[u]!=INT_MAX && dist[u] + weight < dist[v]){
                                dist[v]=dist[u]+weight;
                                pre[v]=graph.vertices[u]->data; 
                                cout << "v    d[v]   pre[v]]" << endl;
                                for (int i = 0; i < V; i++){
                                    if(dist[i]!=INT_MAX)
                                        cout << graph.vertices[i]->data <<  "     " <<  dist[i] << "     "<<  pre[i] << endl;
                                    else
                                        cout << graph.vertices[i]->data <<  "     " <<  'X' << "     "<<  pre[i] << endl;
                                }
                            }
                        }
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
                    if(maxcycles<=V*V){
                        for(int i=0; i<narrowWayThrough.size()-1;i++){
                            cout<<narrowWayThrough[i]<< " -> ";
                        }
                        cout<<narrowWayThrough[narrowWayThrough.size()-1];
                    }
                    cout<<endl;
                
                }
                else{
                    cout<<"VERTEX/S NOT FOUND"<<endl;
                }
            }
            else if (inputDetect(command)==11){ //DSETS
                Node* currentNode;
                vector<string> cousins; //feydrauthaharkonnene
                vector<string> noincest;
                vector<vector<string>> dsets;
                vector<vector<string>> actualDsets;
                for(int j=0; j<graph.activeVertices; j++){
                    Node* currentNode = graph.vertices[j];
                    dsets.resize(j+1);
                    dsets[j].push_back(currentNode->data); //initial sets
                }
                for(int i=0; i<graph.edges.size(); i++){
                    for(int j=0; j<dsets.size(); j++){
                        if((graph.edges[i].from->data == dsets[j][0]) && (find(dsets[j].begin(),dsets[j].end(), graph.edges[i].to->data)==dsets[j].end())){
                            dsets[j].push_back(graph.edges[i].to->data);
                        }
                        if((graph.edges[i].to->data == dsets[j][0]) && (find(dsets[j].begin(),dsets[j].end(), graph.edges[i].from->data)==dsets[j].end())){
                            dsets[j].push_back(graph.edges[i].from->data);
                        }
                    }
                }        
                actualDsets=mergeStuff(dsets);

                for(int z=0; z<actualDsets.size(); z++){
                    cout << "{";
                    for(int x=0; x<actualDsets[z].size(); x++){
                        if(x!=actualDsets[z].size()-1){
                            cout << actualDsets[z][x] << ", ";
                            }
                        else{
                            cout << actualDsets[z][x];
                        }
                    }
                    cout <<"} ";
                }
                cout<<endl;
            }
            else if(inputDetect(command) == 12) { // genmst
                if(directed) {
                    cout << "PRIM'S ALG DOESN'T WORK ON DIRECTED GRAPHS! RESTART THE ENTIRE PROGRAM" <<endl <<endl;
                }
                else{
                    int N=graph.vertices.size();
                    mstexists=true;
                    vector<int> d_s;
                    vector<bool> inMST;
                    vector<int> pre;
                    vector<Edge> mstEdges;
                    int currentweight;
                    int u;
                    int v;
                    int w;
                    int counter = 0;
                    int MST_val = 0;

                    G.clear();
                    G.resize(N);
                    d_s.clear();
                    d_s.resize(N);
                    pre.clear();
                    pre.resize(N);

                    priority_queue<PII,vector<PII>,greater<PII> > pq;
                    priority_queue<PII,vector<PII>,greater<PII> > pq2;

                    for(int i=0; i<graph.edges.size(); i++){
                        for(int j=0; j<graph.vertices.size(); j++){
                            if(graph.edges[i].from->data==graph.vertices[j]->data){
                                u=j;
                            }
                            if(graph.edges[i].to->data==graph.vertices[j]->data){
                                v=j;
                            }
                        }
                        w=graph.edges[i].weight;
                        G[u].push_back(pptEdge(u,v,w));
                        G[v].push_back(pptEdge(v,u,w));
                    }
                    for(int i=0; i<N; i++){
                        d_s[i]=INT_MAX;
                        pre[i]=-1;
                    }

                    d_s[0]=0;
                    pq.push(make_pair(d_s[0],0));
                    
                    while(!pq.empty() && counter != N) {
                        u = pq.top().second;
                        w = pq.top().first;
                        pq.pop();

                        d_s[u] = 0;
                        MST_val += w;
                        counter++;

                        for(int i = 0; i < G[u].size(); i++) {
                            pptEdge e = G[u][i];
                            if(d_s[e.v] > e.weight) {
                                d_s[e.v] = e.weight;
                                pre[e.v] = e.u;
                                pq.push(make_pair(d_s[e.v],e.v));
                                pq2=pq;
                                cout<<"[";
                                while(!pq2.empty()){
                                    cout<< "(" << graph.vertices[pq2.top().second]->data << ", ";
                                    cout<< pq2.top().first << "), ";
                                    pq2.pop();
                                }
                                cout<<'\b'<<'\b';
                                cout<< "]";
                                cout<<endl;
                                cout << "v    d[v]   pre[v]]" << endl;
                                for (int z = 0; z < N; z++){
                                    if(d_s[z]!=INT_MAX)
                                        {if(pre[z]==-1)
                                            cout << graph.vertices[z]->data <<  "     " <<  d_s[z] << "     "<< "-" << endl;
                                        else
                                             cout << graph.vertices[z]->data <<  "     " <<  d_s[z] << "     "<< graph.vertices[pre[z]]->data << endl;}
                                    else{
                                        if(pre[z]==-1)
                                            cout << graph.vertices[z]->data <<  "     " <<  "X" << "     "<< "-" << endl;
                                        else
                                             cout << graph.vertices[z]->data <<  "     " <<  "X" << "     "<< graph.vertices[pre[z]]->data << endl;}

                                }
                                cout<<endl;
                            }
                        } 
                    }
                    bool diditwork=true;
                    for(int u=0; u<d_s.size(); u++){
                        if(d_s[u]==INT_MAX){
                            diditwork=false;
                            mstexists=false;
                            cout<<"YOUR STUFF IS NOT CONNECTED!!"<<endl;
                        }
                    }
                    if(diditwork){//alas
                        pq2=pq;
                        cout<<"[";
                        while(!pq2.empty()){
                            cout<< "(" << graph.vertices[pq2.top().second]->data << ", ";
                            cout<< pq2.top().first << "), ";
                            pq2.pop();
                        }
                        cout<<'\b'<<'\b';
                        cout<< "]"<<endl;

                        cout << "v    d[v]   pre[v]]" << endl;
                    
                        for (int z = 0; z < N; z++){
                            if(d_s[z]!=INT_MAX){
                                if(pre[z]==-1)
                                    cout << graph.vertices[z]->data <<  "     " <<  d_s[z] << "     "<< "-" << endl;
                                else{
                                    cout << graph.vertices[z]->data <<  "     " <<  d_s[z] << "     "<< graph.vertices[pre[z]]->data << endl;
                                    for(int k=0; k<graph.activeEdges; k++){
                                        
                                        if((graph.edges[k].from->data == graph.vertices[z]->data) &&  (graph.edges[k].to->data == graph.vertices[pre[z]]->data)){
                                            currentweight=graph.edges[k].weight;
                                        
                                        }
                                    }
                                    mstgraph.edges.push_back(Edge(graph.vertices[z],graph.vertices[pre[z]],currentweight));
                                    mstgraph.edges.push_back(Edge(graph.vertices[pre[z]],graph.vertices[z],currentweight));
                                }
                            }
                            else{
                                if(pre[z]==-1)
                                    cout << graph.vertices[z]->data <<  "     " <<  "X" << "     "<< "-" << endl;
                                else{
                                    cout << graph.vertices[z]->data <<  "     " <<  "X" << "     "<< graph.vertices[pre[z]]->data << endl;
                                    
                                }
                            }
                        }

                        cout<<"Weight is " << MST_val << endl; 
                        
                        for(int i=0; i<mstgraph.edges.size(); i++){
                            if(find(mstgraph.vertices.begin(),mstgraph.vertices.end(), mstgraph.edges[i].to)==mstgraph.vertices.end()){
                                mstgraph.vertices.push_back(mstgraph.edges[i].to);
                            }
                            if(find(mstgraph.vertices.begin(),mstgraph.vertices.end(), mstgraph.edges[i].from)==mstgraph.vertices.end()){
                                mstgraph.vertices.push_back(mstgraph.edges[i].from);
                            }
                        }
                        int a,b;
                        mstMatrix.resize(mstgraph.vertices.size(), vector<int>(mstgraph.vertices.size()));
                        for(int i=0; i<mstgraph.edges.size(); i++){
                            for(int j=0; j<mstgraph.vertices.size();j++){
                                if(mstgraph.edges[i].from->data==mstgraph.vertices[j]->data){
                                    a=j;
                                }
                                if(mstgraph.edges[i].to->data==mstgraph.vertices[j]->data){
                                    b=j;
                                }
                            }
                            mstMatrix[a][b]=mstgraph.edges[i].weight;
                            mstMatrix[b][a]=mstgraph.edges[i].weight;
                        }
                        cout << endl;
                    }
                }
            }
            else if(inputDetect(command)==13){
                if(mstexists==false){
                    cout <<"RUN GENMST FIRST! OR MAKE SURE YOU CAN ACTUALLY MAKE A SPANNING TREE WITH THAT!"<<endl<<endl;
                }
                else{
                    cout << "|V| = " << mstgraph.vertices.size() << ",  " << "|E| = " << mstgraph.edges.size()/2 << endl;
                    cout << "      ";
                    for(int i=0; i<mstgraph.vertices.size(); i++){
                        cout << "[" << mstgraph.vertices[i]->data << "]" << "      ";
                    }
                    cout<<endl;
                    for(int i=0; i<mstgraph.vertices.size();i++){
                        cout << "[" << mstgraph.vertices[i]->data << "]";
                        
                        for(int j=0; j<mstgraph.vertices.size();j++){
                            cout<< "    " << mstMatrix[i][j]<<"    ";
                        }
                        cout<<endl;
                    }
                    cout<<endl;
                }
            }
            else if(inputDetect(command)==14){
                if(!mstexists){
                    cout <<"RUN GENMST FIRST! OR MAKE SURE YOU CAN ACTUALLY MAKE A SPANNING TREE WITH THAT!"<<endl<<endl;
                }
                else{
                    bool checker=false;
                    cout << "|V| = " << mstgraph.vertices.size() << ",  " << "|E| = " << mstgraph.edges.size()/2 << endl;
                    for(int i=0; i<mstgraph.vertices.size(); i++){
                        cout << "[" << mstgraph.vertices[i]->data<<"]"<<" -> ";
                        cout << "[" ;
                        for(int j=0; j<mstgraph.edges.size(); j++){
                            if(mstgraph.edges[j].from->data==mstgraph.vertices[i]->data){
                                if(checker){
                                        cout<<", ";
                                        cout<<"("<< mstgraph.edges[j].to->data<<", "<<mstgraph.edges[j].weight<<")";
                                }
                                else{
                                    cout<<"("<< mstgraph.edges[j].to->data<<", "<<mstgraph.edges[j].weight<<")";
                                    checker=true;
                                }
                            }      
                        }
                        checker=false; 
                        cout << "]" << endl;
                    }
                    cout<<endl;
                }
            }
            else if(inputDetect(command)==15){
                if(!directed){
                    int counter=0;
                    int u, v, j;
                    int N=graph.vertices.size();
                    vector<pptEdge> KMST;
                    priority_queue<pptEdge,vector<pptEdge>,EdgeComparator> q;
                    priority_queue<pptEdge,vector<pptEdge>,EdgeComparator> q3;
                    priority_queue<pptEdge,vector<pptEdge>,EdgeComparator> q2;
                    vector<bool> truth(graph.edges.size());
            
                    int reqweight;
                    
                    int KMSTval=0;
                    MakeSet(graph.vertices.size());

                    for(int i=0; i<graph.edges.size(); i+=2){
                        for(int j=0; j<graph.vertices.size(); j++){
                            if(graph.vertices[j]->data==graph.edges[i].from->data){
                                u=j;
                            }
                            if(graph.vertices[j]->data==graph.edges[i].to->data){
                                v=j;
                            }
                        }
                        q.push(pptEdge(u, v, graph.edges[i].weight));
                        q3.push(pptEdge(u, v, graph.edges[i].weight));//how else am i suposed to iterate over a priority queue :/
                        truth[i]=false;
                    }
                    q2=q3;
                    j=0; //truthtracker
                    int k=0;   
                    cout<<"PQ: " << " edge     key    MST-flag" <<endl;
                    while(!q2.empty()){ 
                        cout<<"     ("<<graph.vertices[q2.top().v]->data << ", " << graph.vertices[q2.top().u]->data << ")   " << q2.top().weight << "     " << boolalpha << truth[k] << endl;
                        q2.pop();
                        k+=1;
                    }
                    cout<<"DS: " <<"[";
                    PrintSets(N,graph);
                    cout<<"]"<<endl;
                    q2=q3;
                    cout<<endl;
                    while(!q.empty() && counter < N-1){                                           
                        pptEdge e=q.top();
                        pptEdge e2=q3.top();
                        truth[j]=true;
                        j+=1;
                        
                        if(FindSet(e.u)!=FindSet(e.v)){

                            cout<<"PQ: ";
                            cout << " edge     key    MST-flag" <<endl; 
                            k=0;   
                            while(!q2.empty()){ 
                                cout<<"     ("<<graph.vertices[q2.top().v]->data << ", " << graph.vertices[q2.top().u]->data << ")   " << q2.top().weight << "     " << boolalpha << truth[k] << endl;
                                q2.pop();
                                k+=1;
                            }
                            
                            KMSTval+=e.weight;
                            KMST.push_back(e);

                            counter++;
                            Union(e.u,e.v);
                            cout<<"DS: " <<"[";
                            PrintSets(N,graph);
                            cout<<"]"<<endl;
                            cout<<endl;
                            
                        }
                        
                        q.pop();    
                        q2=q3;

                    }
                    


                    if(counter == N-1){
                        cout << "KMST total weight: " << KMSTval << endl;
                        cout << "Edges in KMST: ";
                        for(int i = 0; i < KMST.size(); i++) {
                            cout << "(" << graph.vertices[KMST[i].v]->data << ", " << graph.vertices[KMST[i].u]->data << ", " <<KMST[i].weight<< ") ";
                        }
                        cout<<endl;
                        kmstexists=true;
                    }
                    else{
                        cout <<"NO KMST!"<<endl;
                    }
                    delete[] rnk;
                    delete[] parent;

                    //for the KMSTmatrix and adj matrix;
                    // most are just copypastes from genmst
                    for(int i=0; i<KMST.size(); i++){
                        kmstgraph.edges.push_back(Edge(graph.vertices[KMST[i].u], graph.vertices[KMST[i].v],KMST[i].weight));
                    }
                    for(int i=0; i<kmstgraph.edges.size(); i++){
                        if(find(kmstgraph.vertices.begin(),kmstgraph.vertices.end(), kmstgraph.edges[i].to)==kmstgraph.vertices.end()){
                            kmstgraph.vertices.push_back(kmstgraph.edges[i].to);
                        }
                        if(find(kmstgraph.vertices.begin(),kmstgraph.vertices.end(), kmstgraph.edges[i].from)==kmstgraph.vertices.end()){
                            kmstgraph.vertices.push_back(kmstgraph.edges[i].from);
                        }
                    }

                    int a,b;
                    kmstMatrix.resize(kmstgraph.vertices.size(), vector<int>(kmstgraph.vertices.size()));
                    for(int i=0; i<kmstgraph.edges.size(); i++){
                        for(int j=0; j<kmstgraph.vertices.size();j++){
                            if(kmstgraph.edges[i].from->data==kmstgraph.vertices[j]->data){
                                a=j;
                            }
                            if(kmstgraph.edges[i].to->data==kmstgraph.vertices[j]->data){
                                b=j;
                            }
                        }
                        kmstMatrix[a][b]=kmstgraph.edges[i].weight;
                        kmstMatrix[b][a]=kmstgraph.edges[i].weight;
                    }
                    cout << endl;

                }
                else{
                    cout<<"ONLY UNDIRECTED GRAPHS ALLOWED!"<<endl<<endl;
                }
            }
            //the stuff below are really just copy pastes of mst-aprint and mst-mprint but mst is kmst
            else if(inputDetect(command)==16){
                if(kmstexists==false){
                    cout <<"RUN KMST FIRST! OR MAKE SURE YOU CAN ACTUALLY MAKE A SPANNING TREE WITH THAT!"<<endl<<endl;
                }
                else{
                    cout << "|V| = " << kmstgraph.vertices.size() << ",  " << "|E| = " << kmstgraph.edges.size() << endl;
                    cout << "      ";
                    for(int i=0; i<kmstgraph.vertices.size(); i++){
                        cout << "[" << kmstgraph.vertices[i]->data << "]" << "      ";
                    }
                    cout<<endl;
                    for(int i=0; i<kmstgraph.vertices.size();i++){
                        cout << "[" << kmstgraph.vertices[i]->data << "]";
                        
                        for(int j=0; j<kmstgraph.vertices.size();j++){
                            cout<< "    " << kmstMatrix[i][j]<<"    ";
                        }
                        cout<<endl;
                    }
                    cout<<endl;
                }
            }
            else if(inputDetect(command)==17){
                if(!kmstexists){
                    cout <<"RUN KMST FIRST! OR MAKE SURE YOU CAN ACTUALLY MAKE A SPANNING TREE WITH THAT!"<<endl<<endl;
                }
                else{
                    bool checker=false;
                    cout << "|V| = " << kmstgraph.vertices.size() << ",  " << "|E| = " << kmstgraph.edges.size() << endl;
                    for(int i=0; i<kmstgraph.vertices.size(); i++){
                        cout << "[" << kmstgraph.vertices[i]->data<<"]"<<" -> ";
                        cout << "[" ;
                        for(int j=0; j<kmstgraph.edges.size(); j++){
                            if(kmstgraph.edges[j].from->data==kmstgraph.vertices[i]->data){
                                if(checker){
                                        cout<<", ";
                                        cout<<"("<< kmstgraph.edges[j].to->data<<", "<<kmstgraph.edges[j].weight<<")";
                                }
                                else{
                                    cout<<"("<< kmstgraph.edges[j].to->data<<", "<<kmstgraph.edges[j].weight<<")";
                                    checker=true;
                                }
                            }      
                        }
                        checker=false; 
                        cout << "]" << endl;
                    }
                    cout<<endl;
                }
            }

        }
        command=inputter();
    }
}