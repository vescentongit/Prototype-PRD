#include <bits/stdc++.h>
using namespace std;

typedef struct Edge{
    int to;
    double distance;
    double slope;
    bool hasRoof;   // apakah jalan ini ada atapnya?
} Edge;

typedef struct Node{
    string name;
    double x;         // meter dr titik referensi (kanan/kiri)
    double y;         // meter dr titik referensi (depan/belakang)
    double elevation; // ketinggian dalam meter (atas/bawah)
    vector<Edge> edges;
} Node;

typedef struct Graph{
    vector<Node> nodes;

    void addNode(string name, double x, double y, double elevation){
        Node n;
        n.name = name;
        n.x = x;
        n.y = y;
        n.elevation = elevation;
        nodes.push_back(n);
    }

    double hitungJarak(int from, int to){
        double dx = nodes[to].x - nodes[from].x;
        double dy = nodes[to].y - nodes[from].y;
        return sqrt(dx*dx + dy*dy);
    }

    double hitungSlope(int from, int to){
        double jarak = hitungJarak(from, to);
        if(jarak == 0) return 0;
        double dElev = abs(nodes[to].elevation - nodes[from].elevation);
        return (dElev / jarak) * 100;
    }

    void addEdge(int from, int to, bool hasRoof){
        Edge e;
        e.to       = to;
        e.distance = hitungJarak(from, to);
        e.slope    = hitungSlope(from, to);
        e.hasRoof  = hasRoof;
        nodes[from].edges.push_back(e);
    }

    int findNode(string name){
        for(int i = 0; i < nodes.size(); i++){
            if(nodes[i].name == name) return i;
        }
        return -1;
    }

} Graph;

typedef struct State{
    int node;
    double cost;

    bool operator>(const State& other) const {
        return cost > other.cost;
    }
} State;


vector<int> dijkstra(Graph& g, int start, int goal, double slopeWeight, bool isRaining){
    int n = g.nodes.size();

    vector<double> dist(n, numeric_limits<double>::max());
    vector<int> prev(n, -1);
    priority_queue<State, vector<State>, greater<State>> pq;

    dist[start] = 0.0;
    pq.push({start, 0});

    while(!pq.empty()){
        State current = pq.top();
        pq.pop();

        if(current.node == goal) break;

        for(auto &edge : g.nodes[current.node].edges){
            double roofPenalty = (isRaining && !edge.hasRoof) ? 99999 : 0;
            double cost = edge.distance + roofPenalty + slopeWeight * edge.slope;
            double newDist = dist[current.node] + cost;

            if(newDist < dist[edge.to]){
                dist[edge.to] = newDist;
                prev[edge.to] = current.node;
                pq.push({edge.to, newDist});
            }
        }
    }

    vector<int> path;
    for(int at = goal; at != -1; at = prev[at]){
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    return path;
}