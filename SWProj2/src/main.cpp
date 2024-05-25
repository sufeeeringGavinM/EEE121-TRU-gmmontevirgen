#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 
#include <queue>
#include <climits>
#include <fstream>

using namespace std;

typedef pair<int,int> PII;

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
    return a.weight > b.weight;
}

vector<Edge> maxTree(int n, vector<Edge> edges){
    sort(edges.begin(),edges.end(),edgeComparer);
    UnionFind unionf(n);
    vector<Edge> Mst;
    for(int i=0; i<edges.size(); i++){
        if(unionf.unyon(edges[i].u, edges[i].v)){
            Mst.push_back(edges[i]);
        }
    }
    return Mst;
}

vector<vector<Edge>> adjCreator(int n, vector<Edge> edges){
    vector<vector<Edge>> adj(n);
    for(Edge edge : edges) {
        adj[edge.u].emplace_back(edge.u, edge.v, edge.weight);
        adj[edge.v].emplace_back(edge.v, edge.u, edge.weight); // Since the graph is undirected
    }
    return adj;
}

vector<vector<int>> closestAirports(int n, int k, vector<Edge> Adj){ 
    // this is really just djkistra but lets initialize distance of those with airports as 0
    vector<vector<Edge>> adj = adjCreator(n,Adj); //create adjlist
    
    vector<int> d_s(n, INT_MAX); //preinitialize to intmax
    vector<int> pre(n, -1);
    
    int u,w;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq; 

    for(int i=0; i<k;i++){
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

    for(int a=0; a<testcases; a++){
        cin >> ncities >> nwa >> nedges;
        
        //reinit stuff
        maxProfit=0;
        country.clear();
        air2air.clear();
        ProfitableFlights.clear();
        closestAirportss.clear();
        string line;
        vector<string> lines;
        string findme="";
        
        // generate city nodes in graph also filename is based on N K and M
        string filename = "graph-diagram-";
        filename+=to_string(a+1);
        filename+="-";
        filename+=to_string(ncities);
        filename+="-";
        filename+=to_string(nwa);
        filename+="-";
        filename+=to_string(nedges);
        filename+=".dot";
        ofstream dotfile(filename);
        
        dotfile << "strict graph G{";
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
        // we use djkistra
        
        closestAirportss=closestAirports(ncities,nwa,country);
        
        cout << "Shortest distance from each city to the nearest airport city:\n";
        for (int i = nwa; i < ncities; i++) {
            //cout << i << ": " << closestAirportss[0][i] << "\n";
            cout << i << ": " << closestAirportss[0][i] << "\n";
            vector<int> path=pathFinder(i,closestAirportss[1]);
            
            for(int j=0; j<path.size()-1;j++){ // find what edges and what weights to change for the graph.
                for(int z=0; z<country.size(); z++){
                    if((country[z].u == path[j] && country[z].v == path[j+1])||((country[z].v == path[j] && country[z].u == path[j+1]))){
                        dotfile << path[j] << " -- " << path[j+1] << " [label=" << country[z].weight << ", style=line, color=blue]" << endl;
                    }
                }
            }
        }

        dotfile << "}";

        dotfile.close();
    }
}