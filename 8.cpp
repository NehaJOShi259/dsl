#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    bool lthread, rthread;

    Node(int val) : data(val), left(nullptr), right(nullptr), lthread(false), rthread(false) {}
};

// Function to insert a new node in the Binary Search Tree (BST)
Node* insert(Node* root, int key) {
    if (!root) return new Node(key);
    if (key < root->data) root->left = insert(root->left, key);
    else root->right = insert(root->right, key);
    return root;
}

// Inorder threading function
void inorderThreading(Node* root, Node*& prev) {
    if (!root) return;

    // Traverse the left subtree
    inorderThreading(root->left, prev);

    // Make the left thread (if there is no left child)
    if (!root->left) {
        root->left = prev;
        root->lthread = true;
    }

    // Make the right thread (if there is no right child)
    if (!root->right) {
        root->right = prev ? prev : root;
        root->rthread = true;
    }

    // Update the previous pointer
    prev = root;

    // Traverse the right subtree
    inorderThreading(root->right, prev);
}

// Function for inorder traversal of a threaded binary search tree
void inorderTraversal(Node* root) {
    // Find the leftmost node
    Node* current = root;
    while (current && current->left && !current->lthread)
        current = current->left;

    while (current) {
        // Print the current node's data
        cout << current->data << " ";

        // If there's a right thread, move to the successor
        if (current->rthread)
            current = current->right;
        else
            current = current->right ? current->right : nullptr;
    }
}

int main() {
    Node* root = nullptr;

    // Insert nodes into the Binary Search Tree
    int n, val;
    cout << "Enter number of nodes to insert: ";
    cin >> n;
    cout << "Enter " << n << " values:\n";
    for (int i = 0; i < n; i++) {
        cin >> val;
        root = insert(root, val);
    }

    // Convert BST to Inorder Threaded BST
    Node* prev = nullptr;
    inorderThreading(root, prev);

    // Perform inorder traversal of the threaded tree
    cout << "\nInorder Traversal of Threaded BST: ";
    inorderTraversal(root);
    cout << "\n";

    return 0;
}
