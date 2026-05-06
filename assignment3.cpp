#include<iostream>
#include<string>
#include<limits>

using namespace std;

struct Node {
    string name;
    Node* child;
    Node* sibling;
};

// Create Node
Node* create(string name) {

    Node* temp = new Node;

    temp->name = name;
    temp->child = NULL;
    temp->sibling = NULL;

    return temp;
}

// Add Child
void addChild(Node* parent, Node* newNode) {

    if (parent->child == NULL) {
        parent->child = newNode;
    }
    else {

        Node* temp = parent->child;

        while (temp->sibling != NULL) {
            temp = temp->sibling;
        }

        temp->sibling = newNode;
    }
}

// Print Tree
void printTree(Node* root, int level = 0) {

    if (root == NULL)
        return;

    for (int i = 0; i < level; i++) {
        cout << "   ";
    }

    cout << root->name << endl;

    printTree(root->child, level + 1);
    printTree(root->sibling, level);
}

// Search Employee
bool search(Node* root, string key) {

    if (root == NULL)
        return false;

    if (root->name == key)
        return true;

    return search(root->child, key) ||
           search(root->sibling, key);
}

// Find Node
Node* findNode(Node* root, string key) {

    if (root == NULL)
        return NULL;

    if (root->name == key)
        return root;

    Node* found = findNode(root->child, key);

    if (found)
        return found;

    return findNode(root->sibling, key);
}

// Height / Longest Chain
int height(Node* root) {

    if (root == NULL)
        return 0;

    int maxChildHeight = 0;

    Node* temp = root->child;

    while (temp != NULL) {

        maxChildHeight = max(maxChildHeight,
                             height(temp));

        temp = temp->sibling;
    }

    return maxChildHeight + 1;
}

// Least Senior Employee
void leastSenior(Node* root,
                 int level,
                 int &maxLevel,
                 string &res) {

    if (root == NULL)
        return;

    if (level > maxLevel) {

        maxLevel = level;
        res = root->name;
    }

    leastSenior(root->child,
                level + 1,
                maxLevel,
                res);

    leastSenior(root->sibling,
                level,
                maxLevel,
                res);
}

int main() {

    Node* CEO = NULL;

    int choice;

    string name, parent;

    do {

        cout << "\n===== COMPANY HIERARCHY =====\n";

        cout << "1. Set CEO\n";
        cout << "2. Add Employee\n";
        cout << "3. Display Hierarchy\n";
        cout << "4. Longest Chain\n";
        cout << "5. Least Senior Employee\n";
        cout << "6. Search Employee\n";
        cout << "7. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        // Set CEO
        case 1:

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter CEO name: ";

            getline(cin, name);

            CEO = create(name);

            cout << "CEO Added Successfully\n";

            break;

        // Add Employee
        case 2:

            if (CEO == NULL) {

                cout << "Set CEO first\n";
                break;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter employee name: ";
            getline(cin, name);

            cout << "Enter manager name: ";
            getline(cin, parent);

            {
                Node* p = findNode(CEO, parent);

                if (p == NULL) {

                    cout << "Manager not found\n";
                }
                else {

                    addChild(p, create(name));

                    cout << "Employee added successfully\n";
                }
            }

            break;

        // Display Tree
        case 3:

            if (CEO == NULL)
                cout << "No hierarchy created\n";
            else
                printTree(CEO);

            break;

        // Longest Chain
        case 4:

            if (CEO == NULL)
                cout << "No hierarchy created\n";
            else
                cout << "Longest Chain: "
                     << height(CEO)
                     << endl;

            break;

        // Least Senior Employee
        case 5:

            if (CEO == NULL) {

                cout << "No hierarchy created\n";
            }
            else {

                int maxLevel = -1;

                string res;

                leastSenior(CEO,
                             0,
                             maxLevel,
                             res);

                cout << "Least Senior Employee: "
                     << res
                     << endl;
            }

            break;

        // Search Employee
        case 6:

            if (CEO == NULL) {

                cout << "No hierarchy created\n";
                break;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter employee name to search: ";

            getline(cin, name);

            if (search(CEO, name))
                cout << "Employee Found\n";
            else
                cout << "Employee Not Found\n";

            break;

        case 7:

            cout << "Exiting Program...\n";

            break;

        default:

            cout << "Invalid Choice\n";
        }

    } while (choice != 7);

    return 0;
}