#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 
#include <queue>
#include <climits>
#include <fstream>

using namespace std;

struct Edge{
    int u;
    int v;
    int weight;

    Edge(int u, int v, int weight): u(u), v(v), weight(weight){}
};

class UnionFind{
    public:
        vector<int> parent, rank;
        UnionFind(int n): parent(n), rank(n,0){
            for(int i=0; i<n; i++){
                parent[i]=i;
            }
        }
        int find(int u){
            if(parent[u]!=u){
                parent[u]=find(parent[u]);
            }
            return parent[u];
        }
        bool unyon(int u, int v){
            int rootu=find(u);
            int rootv=find(v);
            if(rootu!=rootv){
                if(rank[rootu]>rank[rootv]){
                    parent[rootv]=rootu;
                }
                else if(rank[rootu]<rank[rootv]){
                    parent[rootu]=rootv;
                }
                else{
                    parent[rootv]=rootu;
                    rank[rootu]++;
                }
                return true;
            }
            return false;
        }
};

bool edgeComparer(Edge a, Edge b){
    if(a.weight != b.weight){
        return a.weight > b.weight;
    }
    else if(a.u != b.u){
        return a.u > b.u;
    }
    return a.v > b.v;
}

vector<Edge> maxTree(int nwa, vector<Edge> air2air){
    sort(air2air.begin(),air2air.end(),edgeComparer);
    UnionFind unionf(nwa);
    vector<Edge> Mst;
    for(int i=0; i<air2air.size(); i++){
        if(unionf.unyon(air2air[i].u, air2air[i].v)){
            Mst.push_back(air2air[i]);
        }
    }
    return Mst;
}

vector<vector<int>> closestAirports(int ncities, int nwa, vector<Edge> country){ //n is n of cities, k is n of 
    // this is really just djkistra but lets initialize distance of those with airports as 0
    vector<vector<Edge>> adj(ncities);
    for(int i=0; i<country.size(); i++) {
        adj[country[i].u].emplace_back(country[i].u, country[i].v, country[i].weight);
        adj[country[i].v].emplace_back(country[i].v, country[i].u, country[i].weight); // Since the graph is undirected
    } 

    vector<int> d_s(ncities, INT_MAX); //preinitialize to intmax, essentially infinity
    vector<int> pre(ncities, -1);
    
    int u,w;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq; 

    for(int i=0; i<nwa;i++){
        d_s[i]=0;
        pq.push({i,0});
    }

    while(!pq.empty()){
        u=pq.top().first;
        w=pq.top().second;
        pq.pop();

        if(w>d_s[u]) continue;

        for(int i=0; i<adj[u].size(); i++){
            Edge e = adj[u][i];
            if(d_s[e.v]>d_s[e.u]+e.weight) {
                d_s[e.v]=d_s[e.u]+e.weight; 
                pre[e.v]=e.u;
                pq.push({e.v,d_s[e.v]});
            }
        }
    }
    vector<vector<int>> package;
    package.push_back(d_s);
    package.push_back(pre);
    return package;
}

vector<int> pathFinder(int start, vector<int> pre){ //thisll make life easier for tracking what path each nonairport city takes
    vector<int> path;
    for(int i=start; i!=-1; i=pre[i]){
        path.push_back(i);
    }
    return path;
}

int main(){
    int testcases;
    int ncities, nwa, nedges; // n cities, n cities with airport, n edges
    int u, v, w;
    cin >> testcases;
    int maxProfit;
    vector<Edge> country; 
    vector<Edge> air2air; // cities with airport-to-airport will be moved here
    vector<Edge> ProfitableFlights;
    vector<vector<int>> closestAirportss;
    vector<int> path;

    for(int a=0; a<testcases; a++){
        cin >> ncities >> nwa >> nedges;
        
        //reinit stuff
        maxProfit=0; 
        country.clear();
        air2air.clear();
        ProfitableFlights.clear();
        closestAirportss.clear();

        if(ncities>=1000 || nedges >=100000 || nwa>=ncities || 2>=nwa || 2>=ncities){
            cout << "N, K, M do not meet limitations/requirements!" <<endl;
            cout << "N < 1000, M < 100000, 2 < K < N" <<endl;
            exit(69);
        }
        
        // generate city nodes in graph also filename is based on N K and M
        string filename = "graph-diagram-";
        // filename+=to_string(a+1);
        // filename+="-";
        // filename+=to_string(ncities);
        // filename+="-";
        // filename+=to_string(nwa);
        // filename+="-";
        // filename+=to_string(nedges);
        // filename+=".dot";
        filename+="testcase-";
        filename+=to_string(a+1);
        filename+=".dot";
        ofstream dotfile(filename);
        
        dotfile << "strict graph G{"; //strict so i dont have to find/replace every edge that turns out to be shortest distance to airport or max profit that i originally initialized as a simple gray dotted/solid line
                                      // i tried the "find/replace every line containing this edge" and it was too much of a headache!
        dotfile << "    fontname=\"Helvetica,Arial,sans-serif\"" <<endl;
        dotfile << "    node [fontname=\"Helvetica,Arial,sans-serif\",colorscheme=greens9]" <<endl;
        dotfile << "    edge [fontname=\"Helvetica,Arial,sans-serif\"]" << endl;
        for(int i=0; i<nwa; i++){
            dotfile << i <<" [label=\"City-" << i << "\", style=filled, color=8,fontcolor=white]" << endl;
        }
        for(int i=nwa; i<ncities; i++){
            dotfile << i <<" [label=\"City-" << i << "\", style=filled, color=5,fontcolor=white]" << endl;
        }

        // initialize edges
        for(int j=0; j<nedges; j++){
            cin >> u >> v >> w;
            if(u>=ncities || v>=ncities){
                cout<< "This edge right here: " << u <<" " << v << " " << endl; 
                cout<<"You inputted something beyond the number of cities!"<<endl;
                exit(69);
            }
            if(u==v || v==u){
                cout<<"This edge right here: "<< u <<" " << v << " " << endl; 
                cout<<"Why would you go from a city to itself???"<<endl;
                exit(69);
            }

            if(u<=nwa-1 && v<=nwa-1){
                country.insert(country.begin(),Edge(u,v,w)); //those at start will be those from airport to airport
                air2air.push_back(Edge(u,v,w));
                dotfile << u << " -- " << v << " [label=" << w << ", style=dashed, color=gray]" << endl;
            }
            else{
                country.push_back(Edge(u,v,w)); 
                dotfile << u << " -- " << v << " [label=" << w << ", style=line, color=gray]" << endl;
            }
        }

       
        // A. max profit (there are K-1 flights as there are K number of airports)
        // essentialy find maximum spanning tree, we can do this by just inversing the weights and doing minimum spanning tree alg

        ProfitableFlights=maxTree(nwa, air2air);
        cout<< "Test case #"<<a+1<< ":"<<endl;
        
        for (int j=0; j<ProfitableFlights.size(); j++) {
            maxProfit+=ProfitableFlights[j].weight;
        }
        cout<< "Airline Profit: " <<maxProfit<<endl;

        cout << "Flights:\n";
        for (int j=0; j<ProfitableFlights.size(); j++) {
            cout << ProfitableFlights[j].u << " " << ProfitableFlights[j].v << " " << ProfitableFlights[j].weight << endl;
            maxProfit+=ProfitableFlights[j].weight;
            dotfile << ProfitableFlights[j].u << " -- " << ProfitableFlights[j].v << " [label=" << ProfitableFlights[j].weight << ", style=dashed, color=blue]" << endl;
        }
        
        // B. distance of each city to nearest airport
        // we use djkistra, but each city with an airport  has a d_s of zero
        
        closestAirportss=closestAirports(ncities,nwa,country);
        
        cout << "Shortest distance from each city to the nearest airport city:\n";
        for (int i = nwa; i < ncities; i++) {
            //cout << i << ": " << closestAirportss[0][i] << "\n";
            if(closestAirportss[0][i]==INT_MAX){
                cout << i << ": " << "No shortest distance found" << "\n";
            }
            else{
                cout << i << ": " << closestAirportss[0][i] << "\n";
            }
                
            path=pathFinder(i,closestAirportss[1]);
            
            for(int j=0; j<path.size()-1;j++){ // find what edges and what weights to add for the graph based on the path
                for(int z=0; z<country.size(); z++){
                    if((country[z].u == path[j] && country[z].v == path[j+1])||((country[z].v == path[j] && country[z].u == path[j+1]))){
                        dotfile << path[j] << " -- " << path[j+1] << " [label=" << country[z].weight << ", style=line, color=blue]" << endl;
                    }
                    else if((country[z].u == path[j+1] && country[z].v == path[j])||((country[z].v == path[j+1] && country[z].u == path[j]))){
                        dotfile << path[j] << " -- " << path[j+1] << " [label=" << country[z].weight << ", style=line, color=blue]" << endl;
                    }
                }
            }
        }

        dotfile << "}";

        dotfile.close();
    }
}