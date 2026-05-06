#include <iostream>
#include <stack>
#include <string>
using namespace std;

// Node structure
struct Node {
    char data;
    Node* left;
    Node* right;
};

// Create node
Node* create(char x) {
    Node* temp = new Node;
    temp->data = x;
    temp->left = temp->right = NULL;
    return temp;
}

// Check operator
bool isOperator(char x) {
    return (x=='+' || x=='-' || x=='*' || x=='/' || x=='^');
}

// Build tree from prefix
Node* build(string prefix) {
    stack<Node*> st;

    for (int i = prefix.length() - 1; i >= 0; i--) {
        char ch = prefix[i];

        Node* temp = create(ch);

        if (isOperator(ch)) {
            temp->left = st.top(); st.pop();
            temp->right = st.top(); st.pop();
        }

        st.push(temp);
    }

    return st.top();
}

// Non-recursive postorder
void postorder(Node* root) {
    stack<Node*> s1, s2;

    s1.push(root);

    while (!s1.empty()) {
        Node* temp = s1.top(); s1.pop();
        s2.push(temp);

        if (temp->left)
            s1.push(temp->left);

        if (temp->right)
            s1.push(temp->right);
    }

    while (!s2.empty()) {
        cout << s2.top()->data;
        s2.pop();
    }
}

// Delete tree
void deleteTree(Node* root) {
    if (root == NULL) return;

    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// Main
int main() {
    string prefix;
    cout << "Enter the prefix string: ";
    getline(cin, prefix);

    if (prefix.empty()) {
        cout << "No prefix expression entered.\n";
        return 0;
    }

    Node* root = build(prefix);

    cout << "Postorder: ";
    postorder(root);

    deleteTree(root);

    return 0;
}