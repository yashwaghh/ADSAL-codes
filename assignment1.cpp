#include <iostream>
#include <list>
using namespace std;

#define SIZE 10

// Product structure
struct Product {
    int id;
    string name;
    int qty;
};

// ================= CHAINING =================
class Chaining {
    list<Product> table[SIZE];

public:
    int hash(int key) {
        return key % SIZE;
    }

    void insert() {
        Product p;
        cout << "Enter ID Name Qty: ";
        cin >> p.id >> p.name >> p.qty;

        int index = hash(p.id);
        table[index].push_back(p);
    }

    void display() {
        for (int i = 0; i < SIZE; i++) {
            cout << i << ": ";
            for (auto x : table[i]) {
                cout << x.id << "->";
            }
            cout << "NULL\n";
        }
    }

    void search(int key) {
        int index = hash(key);
        for (auto x : table[index]) {
            if (x.id == key) {
                cout << "Found: " << x.name << " " << x.qty << endl;
                return;
            }
        }
        cout << "Not Found\n";
    }
};

// ================= LINEAR PROBING =================
class Linear {
    Product table[SIZE];
    int flag[SIZE]; // 0 = empty, 1 = filled

public:
    Linear() {
        for (int i = 0; i < SIZE; i++)
            flag[i] = 0;
    }

    int hash(int key) {
        return key % SIZE;
    }

    void insert() {
        Product p;
        cout << "Enter ID Name Qty: ";
        cin >> p.id >> p.name >> p.qty;

        int index = hash(p.id);

        while (flag[index] == 1) {
            index = (index + 1) % SIZE;
        }

        table[index] = p;
        flag[index] = 1;
    }

    void display() {
        for (int i = 0; i < SIZE; i++) {
            if (flag[i] == 1)
                cout << i << ": " << table[i].id << endl;
            else
                cout << i << ": EMPTY\n";
        }
    }

    void search(int key) {
        int index = hash(key);
        int start = index;

        while (flag[index] == 1) {
            if (table[index].id == key) {
                cout << "Found: " << table[index].name << endl;
                return;
            }
            index = (index + 1) % SIZE;
            if (index == start) break;
        }
        cout << "Not Found\n";
    }
};

// ================= MAIN =================
int main() {
    Chaining c;
    Linear l;

    int ch, type, key;

    do {
        cout << "\n1.Insert\n2.Display\n3.Search\n4.Exit\n";
        cout << "Enter choice: ";
        cin >> ch;

        if (ch == 4) break;

        cout << "1.Chaining  2.Linear: ";
        cin >> type;

        if (ch == 1) {
            if (type == 1) c.insert();
            else l.insert();
        }
        else if (ch == 2) {
            if (type == 1) c.display();
            else l.display();
        }
        else if (ch == 3) {
            cout << "Enter ID: ";
            cin >> key;
            if (type == 1) c.search(key);
            else l.search(key);
        }

    } while (1);

    return 0;
}