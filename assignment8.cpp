#include <iostream>
using namespace std;

#define MAX 10
#define INF 9999

class OBST {

    int keys[MAX];
    int freq[MAX];

    int cost[MAX][MAX];

    int n;

public:

    void input() {

        cout << "Enter number of keys: ";
        cin >> n;

        cout << "Enter keys:\n";

        for(int i=0;i<n;i++)
            cin >> keys[i];

        cout << "Enter frequencies:\n";

        for(int i=0;i<n;i++)
            cin >> freq[i];
    }

    // Sum of frequencies
    int sum(int i, int j) {

        int s = 0;

        for(int k=i;k<=j;k++)
            s += freq[k];

        return s;
    }

    // Build OBST
    void build() {

        for(int i=0;i<n;i++)
            cost[i][i] = freq[i];

        // Length of chain
        for(int len=2; len<=n; len++) {

            for(int i=0; i<=n-len; i++) {

                int j = i + len - 1;

                cost[i][j] = INF;

                for(int r=i; r<=j; r++) {

                    int left = (r > i) ? cost[i][r-1] : 0;

                    int right = (r < j) ? cost[r+1][j] : 0;

                    int total =
                        left +
                        right +
                        sum(i,j);

                    if(total < cost[i][j])
                        cost[i][j] = total;
                }
            }
        }

        cout << "\nMinimum Search Cost = "
             << cost[0][n-1] << endl;
    }
};

// ================= MAIN =================

int main() {

    OBST t;

    t.input();

    t.build();

    return 0;
}