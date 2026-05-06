#include <iostream>
#include <algorithm>
using namespace std;

#define MAX 20

// Edge structure
struct Edge {
    int src, dest, cost;
};

// Compare edges by cost
bool compare(Edge a, Edge b) {
    return a.cost < b.cost;
}

class Graph {

    Edge edge[MAX];

    int parent[MAX];

    int vertices, edges;

public:

    Graph(int v, int e) {

        vertices = v;
        edges = e;

        for(int i=0;i<vertices;i++)
            parent[i] = i;
    }

    // Add edge
    void addEdge(int i, int s, int d, int c) {

        edge[i].src = s;
        edge[i].dest = d;
        edge[i].cost = c;
    }

    // Find parent
    int find(int x) {

        while(parent[x] != x)
            x = parent[x];

        return x;
    }

    // Union
    void unite(int x, int y) {

        parent[x] = y;
    }

    // Kruskal Algorithm
    void kruskal() {

        sort(edge, edge + edges, compare);

        int minCost = 0;

        cout << "\nSelected Routes:\n";

        for(int i=0;i<edges;i++) {

            int p1 = find(edge[i].src);
            int p2 = find(edge[i].dest);

            // No cycle
            if(p1 != p2) {

                cout << edge[i].src
                     << " - "
                     << edge[i].dest
                     << " : "
                     << edge[i].cost
                     << endl;

                minCost += edge[i].cost;

                unite(p1, p2);
            }
        }

        cout << "\nMinimum Total Cost = "
             << minCost << endl;
    }
};

// ================= MAIN =================

int main() {

    int v, e;

    cout << "Enter number of warehouses: ";
    cin >> v;

    cout << "Enter number of routes: ";
    cin >> e;

    Graph g(v, e);

    cout << "Enter source destination cost:\n";

    for(int i=0;i<e;i++) {

        int s, d, c;

        cin >> s >> d >> c;

        g.addEdge(i, s, d, c);
    }

    int choice;

    do {

        cout << "\n1. Find Minimum Cost Network";
        cout << "\n2. Exit\n";

        cin >> choice;

        switch(choice) {

            case 1:
                g.kruskal();
                break;
        }

    } while(choice != 2);

    return 0;
}