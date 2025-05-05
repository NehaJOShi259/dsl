#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Build tree from inorder and preorder
Node* buildTree(vector<int>& inorder, vector<int>& preorder, int inStart, int inEnd, int& preIndex, unordered_map<int, int>& inMap) {
    if (inStart > inEnd) return nullptr;

    int rootVal = preorder[preIndex++];
    Node* root = new Node(rootVal);
    int inIndex = inMap[rootVal];

    root->left = buildTree(inorder, preorder, inStart, inIndex - 1, preIndex, inMap);
    root->right = buildTree(inorder, preorder, inIndex + 1, inEnd, preIndex, inMap);

    return root;
}

// Recursive traversals
void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void preorder(Node* root) {
    if (!root) return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

// Non-recursive traversals
void inorderNR(Node* root) {
    stack<Node*> s;
    Node* curr = root;
    while (curr || !s.empty()) {
        while (curr) {
            s.push(curr);
            curr = curr->left;
        }
        curr = s.top(); s.pop();
        cout << curr->data << " ";
        curr = curr->right;
    }
}

void preorderNR(Node* root) {
    if (!root) return;
    stack<Node*> s;
    s.push(root);
    while (!s.empty()) {
        Node* curr = s.top(); s.pop();
        cout << curr->data << " ";
        if (curr->right) s.push(curr->right);
        if (curr->left) s.push(curr->left);
    }
}

void postorderNR(Node* root) {
    if (!root) return;
    stack<Node*> s1, s2;
    s1.push(root);
    while (!s1.empty()) {
        Node* curr = s1.top(); s1.pop();
        s2.push(curr);
        if (curr->left) s1.push(curr->left);
        if (curr->right) s1.push(curr->right);
    }
    while (!s2.empty()) {
        cout << s2.top()->data << " ";
        s2.pop();
    }
}

int main() {
    vector<int> inorderVec  = {2, 3, 4, 6, 7, 9, 13, 15, 17, 18, 20};
    vector<int> preorderVec = {15, 6, 3, 2, 4, 7, 13, 9, 18, 17, 20};

    unordered_map<int, int> inMap;
    for (int i = 0; i < inorderVec.size(); i++)
        inMap[inorderVec[i]] = i;

    int preIndex = 0;
    Node* root = buildTree(inorderVec, preorderVec, 0, inorderVec.size() - 1, preIndex, inMap);

    cout << "Recursive Traversals:\n";
    cout << "Inorder   : "; inorder(root); cout << "\n";
    cout << "Preorder  : "; preorder(root); cout << "\n";
    cout << "Postorder : "; postorder(root); cout << "\n";

    cout << "\nNon-Recursive Traversals:\n";
    cout << "Inorder   : "; inorderNR(root); cout << "\n";
    cout << "Preorder  : "; preorderNR(root); cout << "\n";
    cout << "Postorder : "; postorderNR(root); cout << "\n";

    return 0;
}
