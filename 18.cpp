#include <iostream>
#include <stack>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
    Node(int val) : data(val), left(NULL), right(NULL) {}
};

class BST {
public:
    Node* root;
    BST() : root(NULL) {}

    Node* insert(Node* node, int val) {
        if (!node) return new Node(val);
        if (val < node->data) node->left = insert(node->left, val);
        else node->right = insert(node->right, val);
        return node;
    }

    void insert(int val) {
        root = insert(root, val);
    }

    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    void preorder(Node* node) {
        if (!node) return;
        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(Node* node) {
        if (!node) return;
        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }

    void inorderNonRecursive() {
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

    bool isEqual(Node* a, Node* b) {
        if (!a && !b) return true;
        if (!a || !b || a->data != b->data) return false;
        return isEqual(a->left, b->left) && isEqual(a->right, b->right);
    }
};

int main() {
    BST tree1, tree2;
    int n, val;

    cout << "Enter number of nodes for Tree 1: ";
    cin >> n;
    cout << "Enter values:\n";
    for (int i = 0; i < n; i++) {
        cin >> val;
        tree1.insert(val);
    }

    cout << "Enter number of nodes for Tree 2: ";
    cin >> n;
    cout << "Enter values:\n";
    for (int i = 0; i < n; i++) {
        cin >> val;
        tree2.insert(val);
    }

    cout << "\nTree 1 Inorder: "; tree1.inorder(tree1.root);
    cout << "\nTree 1 Preorder: "; tree1.preorder(tree1.root);
    cout << "\nTree 1 Postorder: "; tree1.postorder(tree1.root);
    cout << "\nTree 1 Inorder (non-recursive): "; tree1.inorderNonRecursive();

    cout << "\n\nAre Tree 1 and Tree 2 equal? ";
    cout << (tree1.isEqual(tree1.root, tree2.root) ? "Yes" : "No") << endl;

    return 0;
}
