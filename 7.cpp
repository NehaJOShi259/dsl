#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
    bool lthread, rthread;

    Node(int val) {
        data = val;
        left = right = nullptr;
        lthread = rthread = true;
    }
};

// Insert a node into the Threaded BST
Node* insert(Node* root, int key) {
    Node* ptr = root;
    Node* parent = nullptr;

    while (ptr != nullptr) {
        if (key == ptr->data) {
            cout << "Duplicate key not allowed.\n";
            return root;
        }

        parent = ptr;

        if (key < ptr->data) {
            if (!ptr->lthread)
                ptr = ptr->left;
            else
                break;
        } else {
            if (!ptr->rthread)
                ptr = ptr->right;
            else
                break;
        }
    }

    Node* newNode = new Node(key);

    if (parent == nullptr) {
        root = newNode;
    } else if (key < parent->data) {
        newNode->left = parent->left;
        newNode->right = parent;
        parent->lthread = false;
        parent->left = newNode;
    } else {
        newNode->right = parent->right;
        newNode->left = parent;
        parent->rthread = false;
        parent->right = newNode;
    }

    return root;
}

// Inorder traversal without recursion or stack
void inorder(Node* root) {
    Node* curr = root;

    while (curr != nullptr && !curr->lthread)
        curr = curr->left;

    while (curr != nullptr) {
        cout << curr->data << " ";

        if (curr->rthread)
            curr = curr->right;
        else {
            curr = curr->right;
            while (curr != nullptr && !curr->lthread)
                curr = curr->left;
        }
    }
}

int main() {
    Node* root = nullptr;
    int n, val;

    cout << "Enter number of nodes to insert: ";
    cin >> n;
    cout << "Enter node values:\n";
    for (int i = 0; i < n; i++) {
        cin >> val;
        root = insert(root, val);
    }

    cout << "\nInorder Traversal: ";
    inorder(root);
    cout << "\n";

    return 0;
}
