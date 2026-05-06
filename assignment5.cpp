#include <iostream>
#include <queue>
#include <list>
using namespace std;

#define MAX 10

class Graph {
    int adjMatrix[MAX][MAX];
    list<int> adjList[MAX];
    int vertices;

public:

    Graph(int v) {
        vertices = v;

        for(int i=0;i<MAX;i++) {
            for(int j=0;j<MAX;j++) {
                adjMatrix[i][j] = 0;
            }
        }
    }

    // Add edge
    void addEdge(int u, int v) {

        // For DFS (Adjacency Matrix)
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;

        // For BFS (Adjacency List)
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    // DFS using adjacency matrix
    void DFS(int start) {

        int visited[MAX] = {0};

        cout << "DFS Traversal: ";

        dfsUtil(start, visited);

        cout << endl;
    }

    void dfsUtil(int node, int visited[]) {

        visited[node] = 1;

        cout << node << " ";

        for(int i=0;i<vertices;i++) {

            if(adjMatrix[node][i] == 1 && visited[i] == 0) {
                dfsUtil(i, visited);
            }
        }
    }

    // BFS using adjacency list
    void BFS(int start) {

        int visited[MAX] = {0};

        queue<int> q;

        visited[start] = 1;

        q.push(start);

        cout << "BFS Traversal: ";

        while(!q.empty()) {

            int node = q.front();
            q.pop();

            cout << node << " ";

            for(int x : adjList[node]) {

                if(visited[x] == 0) {

                    visited[x] = 1;

                    q.push(x);
                }
            }
        }

        cout << endl;
    }
};

// ================= MAIN =================

int main() {

    int v, e;

    cout << "Enter number of landmarks(nodes): ";
    cin >> v;

    Graph g(v);

    cout << "Enter number of roads(edges): ";
    cin >> e;

    cout << "Enter connected landmarks:\n";

    for(int i=0;i<e;i++) {

        int u, v;

        cin >> u >> v;

        g.addEdge(u, v);
    }

    int choice, start;

    do {

        cout << "\n1. DFS\n2. BFS\n3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {

            case 1:
                cout << "Enter starting landmark: ";
                cin >> start;

                g.DFS(start);
                break;

            case 2:
                cout << "Enter starting landmark: ";
                cin >> start;

                g.BFS(start);
                break;
        }

    } while(choice != 3);

    return 0;
}