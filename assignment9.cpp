#include <iostream>
using namespace std;

#define MAX 10

struct Request {
    string issue;
    int priority;
};

class PriorityQueue {

    Request q[MAX];
    int rear;

public:

    PriorityQueue() {
        rear = -1;
    }

    // Insert request
    void insert(string name, int p) {

        if(rear == MAX-1) {
            cout << "Queue Full\n";
            return;
        }

        rear++;

        q[rear].issue = name;
        q[rear].priority = p;

        cout << "Request Added\n";
    }

    // Process highest priority request
    void process() {

        if(rear == -1) {
            cout << "Queue Empty\n";
            return;
        }

        int highest = 0;

        // Find highest priority
        for(int i=1; i<=rear; i++) {

            if(q[i].priority < q[highest].priority)
                highest = i;
        }

        cout << "\nProcessing Request: "
             << q[highest].issue
             << endl;

        // Shift elements
        for(int i=highest; i<rear; i++) {
            q[i] = q[i+1];
        }

        rear--;
    }

    // Display queue
    void display() {

        if(rear == -1) {
            cout << "Queue Empty\n";
            return;
        }

        cout << "\nRequests in Queue:\n";

        for(int i=0; i<=rear; i++) {

            cout << q[i].issue
                 << " Priority: "
                 << q[i].priority
                 << endl;
        }
    }
};

int main() {

    PriorityQueue pq;

    int choice, p;
    string name;

    do {

        cout << "\n1.Insert Request";
        cout << "\n2.Process Request";
        cout << "\n3.Display";
        cout << "\n4.Exit\n";

        cin >> choice;

        switch(choice) {

            case 1:

                cout << "Enter Issue Name: ";
                cin >> name;

                cout << "Enter Priority ";
                cout << "(1-Urgent, 2-Moderate, 3-Routine): ";

                cin >> p;

                pq.insert(name, p);

                break;

            case 2:

                pq.process();

                break;

            case 3:

                pq.display();

                break;
        }

    } while(choice != 4);

    return 0;
}