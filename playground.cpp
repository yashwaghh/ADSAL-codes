#include<iostream>
#include<stack>
using namespace std;
struct Node{
    char data;
    Node* left;
    Node* right;
};

Node* create(char x){
    Node * temp = new Node;
    temp->data  = x;
    temp->left= temp->right = NULL;
    return temp;
}

bool isOperator(char x){
    return (x=='+' || x=='-' || x=='*' || x=='/' || x=='^');
}


Node* build(string prefix){
    stack<Node*> st;
    for(int i=prefix.length()-1; i>=0; i--){
        char ch = prefix[i];

        Node* temp = create(ch);

        if(isOperator(ch)){
            temp->left = st.top(); st.pop();
            temp->right = st.top(); st.pop();
        }

        st.push(temp);
     }
     return st.top();
}


void postorder(Node* root){
    stack<Node*>s1,s2;

    s1.push(root);
    while(!s1.empty()){
        Node* temp = s1.top();
        s1.pop();
        s2.push(temp);

        if(temp->left) s1.push(temp->left);
        if(temp->left) s1.push(temp->right);
    }
    while(!s2.empty()){
        cout<<s2.top()->data;
        s2.pop();
    }
}