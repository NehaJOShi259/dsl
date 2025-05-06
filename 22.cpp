#include <iostream>
#include <string>
using namespace std;

struct Node {
    char ch;
    int freq;
    Node *left, *right;
};

struct MinHeap {
    Node* heap[100];
    int size = 0;

    void insert(Node* n) {
        int i = size++;
        while (i && n->freq < heap[(i - 1) / 2]->freq) {
            heap[i] = heap[(i - 1) / 2];
            i = (i - 1) / 2;
        }
        heap[i] = n;
    }

    Node* extractMin() {
        Node* root = heap[0];
        heap[0] = heap[--size];
        int i = 0, smallest;
        while (2 * i + 1 < size) {
            int left = 2 * i + 1;
            int right = left + 1;
            smallest = left;
            if (right < size && heap[right]->freq < heap[left]->freq)
                smallest = right;
            if (heap[i]->freq <= heap[smallest]->freq) break;
            swap(heap[i], heap[smallest]);
            i = smallest;
        }
        return root;
    }
};

void getCodes(Node* root, string code, string codes[256]) {
    if (!root) return;
    if (!root->left && !root->right)
        codes[(int)root->ch] = code;
    getCodes(root->left, code + "0", codes);
    getCodes(root->right, code + "1", codes);
}

int main() {
    char chars[] = {'a','b','c','d','e','f','g','h'};
    int freqs[] = {1,2,3,4,5,6,7,8};
    int n = 8;

    MinHeap heap;

    for (int i = 0; i < n; i++) {
        Node* node = new Node;
        node->ch = chars[i];
        node->freq = freqs[i];
        node->left = node->right = NULL;
        heap.insert(node);
    }

    while (heap.size > 1) {
        Node* left = heap.extractMin();
        Node* right = heap.extractMin();
        Node* merged = new Node;
        merged->ch = '#';
        merged->freq = left->freq + right->freq;
        merged->left = left;
        merged->right = right;
        heap.insert(merged);
    }

    Node* root = heap.extractMin();
    string codes[256];
    getCodes(root, "", codes);

    cout << "Huffman Codes:\n";
    for (int i = 0; i < n; i++)
        cout << chars[i] << ": " << codes[(int)chars[i]] << "\n";

    string input;
    cout << "Enter string to encode (a-h): ";
    cin >> input;

    cout << "Encoded: ";
    for (int i = 0; i < input.length(); i++)
        cout << codes[(int)input[i]];
    cout << endl;

    return 0;
}
