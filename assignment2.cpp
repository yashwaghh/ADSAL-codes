#include <iostream>
#include <string>
using namespace std;

// Node structure
struct Node {
    string name;
    Node* child;
    Node* sibling;
};

// Function to create a new node
Node* createNode(string name) {
    Node* temp = new Node;
    temp->name = name;
    temp->child = NULL;
    temp->sibling = NULL;
    return temp;
}

// Function to add child to a parent node
void addChild(Node* parent, Node* newNode) {

    // If no child exists
    if (parent->child == NULL) {
        parent->child = newNode;
    }
    else {
        // Traverse siblings
        Node* temp = parent->child;

        while (temp->sibling != NULL) {
            temp = temp->sibling;
        }

        temp->sibling = newNode;
    }
}

// Function to print tree using DFS traversal
void printTree(Node* root, int level = 0) {

    if (root == NULL)
        return;

    // Indentation for hierarchy
    for (int i = 0; i < level; i++) {
        cout << "   ";
    }

    cout << "- " << root->name << endl;

    // Print child
    printTree(root->child, level + 1);

    // Print sibling
    printTree(root->sibling, level);
}

// Function to delete tree and free memory
void deleteTree(Node* root) {

    if (root == NULL)
        return;

    deleteTree(root->child);
    deleteTree(root->sibling);

    delete root;
}

int main() {

    int ch, sec, sub;

    // Create root node
    Node* book = createNode("Book");

    cout << "Enter number of chapters: ";
    cin >> ch;

    cin.ignore();

    // Chapters
    for (int i = 0; i < ch; i++) {

        string cname;

        cout << "\nEnter chapter name: ";
        getline(cin, cname);

        Node* chapter = createNode(cname);

        addChild(book, chapter);

        cout << "Enter number of sections in " << cname << ": ";
        cin >> sec;

        cin.ignore();

        // Sections
        for (int j = 0; j < sec; j++) {

            string sname;

            cout << "Enter section name: ";
            getline(cin, sname);

            Node* section = createNode(sname);

            addChild(chapter, section);

            cout << "Enter number of subsections in " << sname << ": ";
            cin >> sub;

            cin.ignore();

            // Subsections
            for (int k = 0; k < sub; k++) {

                string subname;

                cout << "Enter subsection name: ";
                getline(cin, subname);

                Node* subsection = createNode(subname);

                addChild(section, subsection);
            }
        }
    }

    // Display tree
    cout << "\n========== BOOK TREE ==========\n";

    printTree(book);

    // Free memory
    deleteTree(book);

    return 0;
}