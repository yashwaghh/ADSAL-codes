#include <iostream>
#include <list>
#include <queue>
using namespace std;

#define MAX 10
#define INF 9999

class Graph {

    int vertices;

    list<pair<int,int>> adj[MAX];

public:

    Graph(int v) {
        vertices = v;
    }

    // Add edge
    void addEdge(int u, int v, int wt) {

        adj[u].push_back({v, wt});
        adj[v].push_back({u, wt});
    }

    // Dijkstra Algorithm
    void dijkstra(int start) {

        int dist[MAX];
        int visited[MAX] = {0};

        for(int i=0;i<vertices;i++)
            dist[i] = INF;

        dist[start] = 0;

        for(int i=0;i<vertices-1;i++) {

            int min = INF;
            int u;

            // Find minimum distance vertex
            for(int j=0;j<vertices;j++) {

                if(!visited[j] && dist[j] < min) {
                    min = dist[j];
                    u = j;
                }
            }

            visited[u] = 1;

            // Update neighbors
            for(auto x : adj[u]) {

                int v = x.first;
                int wt = x.second;

                if(!visited[v] && dist[u] + wt < dist[v]) {

                    dist[v] = dist[u] + wt;
                }
            }
        }

        cout << "\nShortest Time from Station " << start << ":\n";

        for(int i=0;i<vertices;i++) {

            cout << "To " << i << " = " << dist[i] << endl;
        }
    }

    // Reachable stations within time limit
    void reachableStations(int start, int limit) {

        int dist[MAX];
        int visited[MAX] = {0};

        for(int i=0;i<vertices;i++)
            dist[i] = INF;

        dist[start] = 0;

        for(int i=0;i<vertices-1;i++) {

            int min = INF;
            int u;

            for(int j=0;j<vertices;j++) {

                if(!visited[j] && dist[j] < min) {
                    min = dist[j];
                    u = j;
                }
            }

            visited[u] = 1;

            for(auto x : adj[u]) {

                int v = x.first;
                int wt = x.second;

                if(!visited[v] && dist[u] + wt < dist[v]) {

                    dist[v] = dist[u] + wt;
                }
            }
        }

        cout << "\nReachable Stations within Time "
             << limit << ":\n";

        for(int i=0;i<vertices;i++) {

            if(dist[i] <= limit)
                cout << i << " ";
        }

        cout << endl;
    }
};

// ================= MAIN =================

int main() {

    int v, e;

    cout << "Enter number of power stations: ";
    cin >> v;

    Graph g(v);

    cout << "Enter number of connections: ";
    cin >> e;

    cout << "Enter source destination time:\n";

    for(int i=0;i<e;i++) {

        int u, v, wt;

        cin >> u >> v >> wt;

        g.addEdge(u, v, wt);
    }

    int choice, start, limit;

    do {

        cout << "\n1. Dijkstra\n2. Reachable Stations\n3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {

            case 1:

                cout << "Enter starting station: ";
                cin >> start;

                g.dijkstra(start);

                break;

            case 2:

                cout << "Enter starting station: ";
                cin >> start;

                cout << "Enter time limit: ";
                cin >> limit;

                g.reachableStations(start, limit);

                break;
        }

    } while(choice != 3);

    return 0;
}