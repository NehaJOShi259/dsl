22 Questions

	1


#include <iostream>
#include <vector>
using namespace std;

const int TABLE_SIZE = 10;

struct Student {
    int roll;
    int marks;
};

struct HashEntry {
    Student student;
    bool isOccupied = false;
};

class HashTable {
    HashEntry table[TABLE_SIZE];

public:
    void insertWithoutReplacement(Student s) {
        int index = s.roll % TABLE_SIZE;
        while (table[index].isOccupied) {
            index = (index + 1) % TABLE_SIZE;
        }
        table[index].student = s;
        table[index].isOccupied = true;
    }

    int searchWithoutReplacement(int roll) {
        int index = roll % TABLE_SIZE;
        int count = 0;
        while (table[index].isOccupied) {
            count++;
            if (table[index].student.roll == roll) {
                cout << "Found Roll: " << table[index].student.roll << ", Marks: "
                     << table[index].student.marks << " in " << count << " comparisons\n";
                return index;
            }
            index = (index + 1) % TABLE_SIZE;
        }
        cout << "Not found in " << count << " comparisons\n";
        return -1;
    }

    void clearTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = HashEntry();
        }
    }

    void display() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (table[i].isOccupied)
                cout << i << " => Roll: " << table[i].student.roll 
                     << ", Marks: " << table[i].student.marks << '\n';
            else
                cout << i << " => Empty\n";
        }
    }
};

int main() {
    HashTable ht;
    vector<Student> students = {
        {31, 85}, {13, 90}, {14, 78}, {51, 88}, {16, 92},
        {71, 81}, {48, 75}, {19, 80}
    };

    cout << "Linear Probing with Chaining Without Replacement:\n";
    for (auto s : students)
        ht.insertWithoutReplacement(s);

    ht.display();

    // Example search
    ht.searchWithoutReplacement(71);

    return 0;
}


2.



#include <iostream>
#include <vector>
#include <list>
using namespace std;

const int TABLE_SIZE = 101;

struct Entry {
    string word;
    string meaning;
    Entry(string w, string m) : word(w), meaning(m) {}
};

class HashTable {
    vector<list<Entry>> table;

    int hashFunction(const string& key) {
        int hash = 0;
        for (char ch : key) {
            hash = (hash * 31 + ch) % TABLE_SIZE;
        }
        return hash;
    }

public:
    HashTable() : table(TABLE_SIZE) {}

    void insert(const string& word, const string& meaning) {
        int idx = hashFunction(word);
        for (auto& entry : table[idx]) {
            if (entry.word == word) {
                entry.meaning = meaning;
                return;
            }
        }
        table[idx].emplace_back(word, meaning);
    }

    bool search(const string& word, string& meaning) {
        int idx = hashFunction(word);
        for (auto& entry : table[idx]) {
            if (entry.word == word) {
                meaning = entry.meaning;
                return true;
            }
        }
        return false;
    }
};

int main() {
    HashTable dict;

    // Manually insert words and meanings
    dict.insert("apple", "a fruit");
    dict.insert("table", "an item of furniture");
    dict.insert("code", "a set of instructions");
    dict.insert("computer", "an electronic device");
    dict.insert("book", "a set of written pages");

    cout << "Dictionary loaded. Enter words to look up (type 'exit' to quit):\n";

    string word, meaning;
    while (true) {
        cout << "\nWord: ";
        cin >> word;
        if (word == "exit") break;

        if (dict.search(word, meaning)) {
            cout << "Meaning: " << meaning << endl;
        } else {
            cout << "Word not found in dictionary." << endl;
        }
    }

    return 0;
}


3 4 5 6  18


#include <iostream>
#include <queue>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// 1. Insert into BST
Node* insertBST(Node* root, int val) {
    if (!root) return new Node(val);
    if (val < root->data) root->left = insertBST(root->left, val);
    else root->right = insertBST(root->right, val);
    return root;
}

// 2. Traversals
void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

void preorder(Node* root) {
    if (root) {
        cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(Node* root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        cout << root->data << " ";
    }
}

void levelOrder(Node* root) {
    if (!root) return;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* node = q.front(); q.pop();
        cout << node->data << " ";
        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
    }
}

// 3. Height of Tree
int height(Node* root) {
    if (!root) return 0;
    return 1 + max(height(root->left), height(root->right));
}

// 4. Clone Tree
Node* clone(Node* root) {
    if (!root) return nullptr;
    Node* newNode = new Node(root->data);
    newNode->left = clone(root->left);
    newNode->right = clone(root->right);
    return newNode;
}

void deleteTree(Node*& root) {
    if (root) {
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
        root = nullptr;
    }
}

// 5. Mirror
Node* mirror(Node* root) {
    if (!root) return nullptr;
    Node* mirrored = new Node(root->data);
    mirrored->left = mirror(root->right);
    mirrored->right = mirror(root->left);
    return mirrored;
}

// 6. Build tree from inorder and preorder
int search(int inorder[], int start, int end, int val) {
    for (int i = start; i <= end; i++)
        if (inorder[i] == val) return i;
    return -1;
}

Node* buildTree(int inorder[], int preorder[], int inStart, int inEnd, int& preIndex) {
    if (inStart > inEnd) return nullptr;
    int rootVal = preorder[preIndex++];
    Node* root = new Node(rootVal);
    int inIndex = search(inorder, inStart, inEnd, rootVal);
    root->left = buildTree(inorder, preorder, inStart, inIndex - 1, preIndex);
    root->right = buildTree(inorder, preorder, inIndex + 1, inEnd, preIndex);
    return root;
}

// 7. Delete node in BST
Node* minValueNode(Node* root) {
    while (root && root->left) root = root->left;
    return root;
}

Node* deleteNode(Node* root, int key) {
    if (!root) return root;
    if (key < root->data) root->left = deleteNode(root->left, key);
    else if (key > root->data) root->right = deleteNode(root->right, key);
    else {
        if (!root->left) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (!root->right) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        Node* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// 8. Check if trees are equal
bool isEqual(Node* a, Node* b) {
    if (!a && !b) return true;
    if (!a || !b || a->data != b->data) return false;
    return isEqual(a->left, b->left) && isEqual(a->right, b->right);
}

int main() {
    Node* root = nullptr;
    root = insertBST(root, 50);
    insertBST(root, 30);
    insertBST(root, 70);
    insertBST(root, 20);
    insertBST(root, 40);
    insertBST(root, 60);
    insertBST(root, 80);

    cout << "Inorder: "; inorder(root); cout << endl;
    cout << "Preorder: "; preorder(root); cout << endl;
    cout << "Postorder: "; postorder(root); cout << endl;
    cout << "Level Order: "; levelOrder(root); cout << endl;

    cout << "Height: " << height(root) << endl;

    Node* cloned = clone(root);
    deleteTree(root);
    cout << "Original tree deleted. Cloned inorder: "; inorder(cloned); cout << endl;

    Node* mirrorTree = mirror(cloned);
    cout << "Mirror inorder: "; inorder(mirrorTree); cout << endl;

    int inorderArr[] = {20, 30, 40, 50, 60, 70, 80};
    int preorderArr[] = {50, 30, 20, 40, 70, 60, 80};
    int preIndex = 0;
    Node* built = buildTree(inorderArr, preorderArr, 0, 6, preIndex);
    cout << "Built Tree Inorder: "; inorder(built); cout << endl;

    built = deleteNode(built, 30);
    cout << "After deleting 30: "; inorder(built); cout << endl;

    cout << "Are cloned and mirror equal? " << (isEqual(cloned, mirrorTree) ? "Yes" : "No") << endl;

    return 0;
}


7, 8

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

class ThreadedBST {
    Node *root;

public:
    ThreadedBST() : root(nullptr) {}

    // Q7: Insert into a Threaded BST
    void insert(int key) {
        Node* ptr = root;
        Node* parent = nullptr;

        while (ptr != nullptr) {
            if (key == ptr->data) return; // Avoid duplicates
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
            newNode->left = parent->left;   // Thread to inorder predecessor
            newNode->right = parent;        // Thread to parent (successor)
            parent->lthread = false;
            parent->left = newNode;
        } else {
            newNode->right = parent->right; // Thread to inorder successor
            newNode->left = parent;         // Thread to parent (predecessor)
            parent->rthread = false;
            parent->right = newNode;
        }
    }

    // Q7: Inorder traversal using threads
    void inorder() {
        Node* curr = root;

        // Go to leftmost node
        while (curr && !curr->lthread)
            curr = curr->left;

        while (curr) {
            cout << curr->data << " ";
            if (curr->rthread) {
                curr = curr->right; // Move to inorder successor via thread
            } else {
                curr = curr->right;
                while (curr && !curr->lthread)
                    curr = curr->left;
            }
        }
        cout << endl;
    }

    // Q8: Insert into a normal BST (no threads used)
    void insertNormal(Node*& node, int key) {
        if (!node) {
            node = new Node(key);
            node->lthread = node->rthread = false; // Important: normal BST has no threads
            return;
        }

        if (key < node->data)
            insertNormal(node->left, key);
        else if (key > node->data)
            insertNormal(node->right, key);
    }

    // Q8: Convert normal BST to Threaded BST
    void convertBSTtoThreaded(Node* root) {
        Node* prev = nullptr;
        convertUtil(root, prev);
        this->root = root;
    }

    // Overloaded inorder for Q8 (on passed root)
    void inorder(Node* curr) {
        // Go to leftmost
        while (curr && !curr->lthread)
            curr = curr->left;

        while (curr) {
            cout << curr->data << " ";
            if (curr->rthread) {
                curr = curr->right;
            } else {
                curr = curr->right;
                while (curr && !curr->lthread)
                    curr = curr->left;
            }
        }
        cout << endl;
    }

private:
    // Utility to convert BST to Threaded BST
    void convertUtil(Node* curr, Node*& prev) {
        if (!curr) return;

        convertUtil(curr->left, prev);

        // Set left thread
        if (!curr->left) {
            curr->left = prev;
            curr->lthread = true;
        } else {
            curr->lthread = false;
        }

        // Set right thread of previous node
        if (prev && !prev->right) {
            prev->right = curr;
            prev->rthread = true;
        } else if (prev) {
            prev->rthread = false;
        }

        prev = curr;
        convertUtil(curr->right, prev);
    }
};


int main() {
    ThreadedBST tbst;

    // Q7: Insert in Threaded BST and print
    tbst.insert(20);
    tbst.insert(10);
    tbst.insert(30);
    tbst.insert(5);
    tbst.insert(15);

    cout << "[Q7] Inorder Traversal of Threaded BST: ";
    tbst.inorder();

    // Q8: Insert into normal BST, then convert to threaded BST
    Node* normalRoot = nullptr;
    tbst.insertNormal(normalRoot, 40);
    tbst.insertNormal(normalRoot, 25);
    tbst.insertNormal(normalRoot, 60);
    tbst.insertNormal(normalRoot, 10);
    tbst.insertNormal(normalRoot, 30);

    tbst.convertBSTtoThreaded(normalRoot);

    cout << "[Q8] Inorder Traversal after converting Normal BST to Threaded BST: ";
    tbst.inorder(normalRoot);

    return 0;
}


9.




#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

const int MAX = 100;
const char* FILENAME = "students.dat";

class Student {
public:
    int rollNo;
    char name[30];
    char division;
    char address[50];

    Student() {
        rollNo = -1;
        strcpy(name, "");
        division = '-';
        strcpy(address, "");
    }

    void input() {
        cout << "Enter Roll No: ";
        cin >> rollNo;
        cout << "Enter Name: ";
        cin.ignore();
        cin.getline(name, 30);
        cout << "Enter Division: ";
        cin >> division;
        cout << "Enter Address: ";
        cin.ignore();
        cin.getline(address, 50);
    }

    void display() {
        if (rollNo != -1) {
            cout << "Roll No: " << rollNo << ", Name: " << name
                 << ", Division: " << division << ", Address: " << address << endl;
        }
    }
};

void addStudent() {
    fstream file(FILENAME, ios::in | ios::out | ios::binary);
    Student s;
    s.input();
    int pos = s.rollNo;
    file.seekp(pos * sizeof(Student), ios::beg);
    file.write((char*)&s, sizeof(Student));
    file.close();
    cout << "Student added successfully.\n";
}

void searchStudent() {
    fstream file(FILENAME, ios::in | ios::binary);
    int roll;
    cout << "Enter Roll No to search: ";
    cin >> roll;
    Student s;
    file.seekg(roll * sizeof(Student), ios::beg);
    file.read((char*)&s, sizeof(Student));
    if (s.rollNo != -1)
        s.display();
    else
        cout << "Record not found.\n";
    file.close();
}

void deleteStudent() {
    fstream file(FILENAME, ios::in | ios::out | ios::binary);
    int roll;
    cout << "Enter Roll No to delete: ";
    cin >> roll;
    Student s;
    file.seekg(roll * sizeof(Student), ios::beg);
    file.read((char*)&s, sizeof(Student));
    if (s.rollNo != -1) {
        Student blank;
        file.seekp(roll * sizeof(Student), ios::beg);
        file.write((char*)&blank, sizeof(Student));
        cout << "Record deleted.\n";
    } else {
        cout << "Record not found.\n";
    }
    file.close();
}

void editStudent() {
    fstream file(FILENAME, ios::in | ios::out | ios::binary);
    int roll;
    cout << "Enter Roll No to edit: ";
    cin >> roll;
    Student s;
    file.seekg(roll * sizeof(Student), ios::beg);
    file.read((char*)&s, sizeof(Student));
    if (s.rollNo != -1) {
        cout << "Existing Record:\n";
        s.display();
        cout << "Enter new details:\n";
        s.input();
        file.seekp(roll * sizeof(Student), ios::beg);
        file.write((char*)&s, sizeof(Student));
        cout << "Record updated.\n";
    } else {
        cout << "Record not found.\n";
    }
    file.close();
}

void displayAll() {
    fstream file(FILENAME, ios::in | ios::binary);
    Student s;
    for (int i = 0; i < MAX; ++i) {
        file.seekg(i * sizeof(Student), ios::beg);
        file.read((char*)&s, sizeof(Student));
        if (s.rollNo != -1) s.display();
    }
    file.close();
}

int main() {
    // Pre-create a file with 100 empty student records
    fstream file(FILENAME, ios::out | ios::binary);
    Student s;
    for (int i = 0; i < MAX; ++i)
        file.write((char*)&s, sizeof(Student));
    file.close();

    int choice;
    do {
        cout << "\n--- Student Information System ---\n";
        cout << "1. Add Student\n2. Search Student\n3. Edit Student\n4. Delete Student\n5. Display All\n0. Exit\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: addStudent(); break;
            case 2: searchStudent(); break;
            case 3: editStudent(); break;
            case 4: deleteStudent(); break;
            case 5: displayAll(); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid option!\n";
        }
    } while (choice != 0);

    return 0;
}



10.


#include <iostream>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;

    Node(int val) : key(val), left(nullptr), right(nullptr), height(1) {}
};

int height(Node* node) {
    return node ? node->height : 0;
}

int getBalance(Node* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

Node* insert(Node* node, int key) {
    if (!node)
        return new Node(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node; // duplicate not allowed

    node->height = max(height(node->left), height(node->right)) + 1;
    int balance = getBalance(node);

    // LL Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // RR Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // LR Case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RL Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void inOrder(Node* root) {
    if (!root) return;
    inOrder(root->left);
    cout << root->key << " ";
    inOrder(root->right);
}

int main() {
    Node* root = nullptr;
    int keys[] = {10, 20, 30, 40, 50, 25};
    for (int key : keys)
        root = insert(root, key);

    cout << "Inorder traversal of the constructed AVL tree: ";
    inOrder(root);
    cout << endl;

    return 0;
}



11

#include<bits/stdc++.h>
using namespace std;

class DisjointSet{
    vector<int>parent ,size;
    
    public:
    
    DisjointSet(int n){
        parent.resize(n);
        size.resize(n,1);
        for(int i=0 ;i<n ;i++){
            parent[i]=i;
        }
    }
    
    int findUPar(int node){
        if(node==parent[node]) return node;
        return parent[node]= findUPar(parent[node]);
    }
    
    void unionBySize(int u ,int v){
        int u_ulp= findUPar(u);
        int v_ulp= findUPar(v);
        if(size[u_ulp]=size[v_ulp]) return;
        if(size[u_ulp]>size[v_ulp]){
            parent[v_ulp]= u_ulp;
            size[u_ulp]+=size[v_ulp];
        }
        else {
            parent[u_ulp]= v_ulp;
            size[v_ulp]+=size[u_ulp];
        }
    }
};

class Solution{
    public:
      int spanningTree(int V , vector<vector<int>>adj[]){
        vector<pair<int ,pair<int ,int>>>edges;
        
        
        for(int i=0 ;i<V ;i++){
            for(auto it: adj[i]){
                int adjNode= it[0];
                int w= it[1];
            if(i<adjNode){
                edges.push_back({w ,{i,adjNode}});
            }
            }
        }
        
            sort(edges.begin(), edges.end());
        
        DisjointSet ds(V);
           int mstWt = 0;
        
        for(auto it :edges){
            int wt= it.first;
            int u= it.second.first;
            int v= it.second.second;
            
            if(ds.findUPar(u)!=ds.findUPar(v)){
                    mstWt += wt;
                    ds.unionBySize(u,v);
            }
           
        }
         return mstWt;
    }
};

int main(){
   int V = 5; // Example: 5 vertices
    vector<vector<int>> adj[5];

    // Example Graph
    adj[0].push_back({1, 2});
    adj[0].push_back({3, 6});
    adj[1].push_back({0, 2});
    adj[1].push_back({2, 3});
    adj[1].push_back({3, 8});
    adj[1].push_back({4, 5});
    adj[2].push_back({1, 3});
    adj[2].push_back({4, 7});
    adj[3].push_back({0, 6});
    adj[3].push_back({1, 8});
    adj[4].push_back({1, 5});
    adj[4].push_back({2, 7});
      Solution sol;
    cout << "Minimum Spanning Tree Weight: " << sol.spanningTree(V, adj) << endl;

    return 0;

}


12


#include <bits/stdc++.h>
using namespace std;


class Solution{
    public:

vector<int>Dijkstra(int V , vector<vector<int>>adj[] ,int S){
    priority_queue<pair<int ,int> ,vector<pair<int ,int>> ,greater<pair<int,int>>>pq;
    
    vector<int>dis(V ,INT_MAX);
    
    dis[S]=0;
    
    pq.push({0,S});
    
    
    while(!pq.empty()){
        int distance= pq.top().first;
        int node= pq.top().second;
        pq.pop();
        
        for(auto it: adj[node]){
            int adjNode= it[0];
            int weight= it[1];
            
            if(distance+ weight < dis[adjNode]){
                dis[adjNode]= distance+weight;
                pq.push({dis[adjNode] ,adjNode});
            }
        }
    }
    return dis;
}
};

int main(){
    int V=9;
    vector<vector<int>>adj[9];
      adj[0].push_back({1, 4});
    adj[0].push_back({7, 8});
    adj[1].push_back({0, 4});
    adj[1].push_back({2, 8});
    adj[1].push_back({7, 11});
    adj[2].push_back({1, 8});
    adj[2].push_back({3, 7});
    adj[2].push_back({8, 2});
    adj[2].push_back({5, 4});
    adj[3].push_back({2, 7});
    adj[3].push_back({4, 9});
    adj[3].push_back({5, 14});
    adj[4].push_back({3, 9});
    adj[4].push_back({5, 10});
    adj[5].push_back({2, 4});
    adj[5].push_back({3, 14});
    adj[5].push_back({4, 10});
    adj[5].push_back({6, 2});
    adj[6].push_back({5, 2});
    adj[6].push_back({7, 1});
    adj[6].push_back({8, 6});
    adj[7].push_back({0, 8});
    adj[7].push_back({1, 11});
    adj[7].push_back({6, 1});
    adj[7].push_back({8, 7});
    adj[8].push_back({2, 2});
    adj[8].push_back({6, 6});
    adj[8].push_back({7, 7});

    Solution sol;
    vector<int> distances = sol.Dijkstra(V, adj, 0);

    cout << "Shortest distances from source vertex 0:\n";
    for (int i = 0; i < V; i++) {
        cout << "Vertex " << i << ": " << distances[i] << endl;
    }

    return 0;

}

13,20

#include <bits/stdc++.h>
using namespace std;

// ---------- DFS Topological Sort ----------
void dfs(int node, vector<vector<int>>& adj, vector<int>& vis, stack<int>& st) {
    vis[node] = 1;
    for (auto it : adj[node]) {
        if (!vis[it]) dfs(it, adj, vis, st);
    }
    st.push(node);
}

vector<int> TopoDFS(int V, vector<vector<int>>& adj) {
    vector<int> vis(V, 0);
    stack<int> st;

    for (int i = 0; i < V; i++) {
        if (!vis[i]) dfs(i, adj, vis, st);
    }

    vector<int> topo;
    while (!st.empty()) {
        topo.push_back(st.top());
        st.pop();
    }
    return topo;
}

// ---------- BFS Topological Sort (Kahn’s Algorithm) ----------
vector<int> TopoBFS(int V, vector<vector<int>>& adj) {
    vector<int> indegree(V, 0);
    
    for (int i = 0; i < V; i++) {
        for (auto it : adj[i]) {
            indegree[it]++;
        }
    }

    queue<int> q;
    for (int i = 0; i < V; i++) {
        if (indegree[i] == 0) q.push(i);
    }

    vector<int> topo;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        topo.push_back(node);

        for (auto it : adj[node]) {
            indegree[it]--;
            if (indegree[it] == 0) q.push(it);
        }
    }

    return topo;
}

int main() {
    int V = 6;
    vector<vector<int>> adj(V);

    // Edges
    adj[5].push_back(2);
    adj[5].push_back(0);
    adj[4].push_back(0);
    adj[4].push_back(1);
    adj[2].push_back(3);
    adj[3].push_back(1);

    // DFS-based Topological Sort
    vector<int> resultDFS = TopoDFS(V, adj);
    cout << "Topological Sort using DFS:\n";
    for (int node : resultDFS) cout << node << " ";
    cout << "\n";

    // BFS-based Topological Sort (Kahn's Algorithm)
    vector<int> resultBFS = TopoBFS(V, adj);
    cout << "Topological Sort using BFS (Kahn’s Algorithm):\n";
    for (int node : resultBFS) cout << node << " ";
    cout << "\n";

    return 0;
}



14

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Function to find the sum of weights of the Minimum Spanning Tree.
    int spanningTree(int V, vector<vector<int>> adj[]) {
        // Min-heap priority queue: {weight, node}
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector<int> vis(V, 0);  // Visited array
        int sum = 0;

        pq.push({0, 0}); // Start from node 0 with weight 0

        while (!pq.empty()) {
            auto it = pq.top();
            pq.pop();
            int node = it.second;
            int wt = it.first;

            if (vis[node]) continue;

            vis[node] = 1;
            sum += wt;

            for (auto& neighbor : adj[node]) {
                int adjNode = neighbor[0];
                int edgeWeight = neighbor[1];
                if (!vis[adjNode]) {
                    pq.push({edgeWeight, adjNode});
                }
            }
        }

        return sum;
    }
};

int main() {
    int V = 9;
    vector<vector<int>> adj[V];

    // Graph from the image (edges with weights)
    vector<vector<int>> edges = {
        {0, 1, 4}, {0, 7, 8}, {1, 2, 8}, {1, 7, 11},
        {2, 3, 7}, {2, 8, 2}, {2, 5, 4}, {3, 4, 9},
        {3, 5, 14}, {4, 5, 10}, {5, 6, 2}, {6, 8, 6},
        {6, 7, 1}, {7, 8, 7}
    };

    // Building the adjacency list
    for (auto& edge : edges) {
        int u = edge[0], v = edge[1], w = edge[2];
        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); // Undirected graph
    }

    Solution obj;
    int totalCost = obj.spanningTree(V, adj);
    cout << "The sum of all the edge weights in the MST: " << totalCost << endl;

    return 0;
}




15



#include<bits/stdc++.h>
using namespace std;
#define MAX 50

struct Node{
    int data;
    Node* left;
    Node* right;
    Node(int val){
        data = val;
        left = right = NULL;
    }
};

Node* construct(int r[][MAX], int i, int j){
    if(!r[i][j]) return NULL;
    Node* root = new Node(r[i][j]);
    root->left = construct(r,i,r[i][j]-1);
    root->right = construct(r,r[i][j]+1,j);
    return root;
}

Node* optimalbst(int p[], int q[], int n){
    int w[MAX][MAX], c[MAX][MAX], r[MAX][MAX];
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            w[i][j] = c[i][j] = r[i][j] = 0;
        }
    }
    for(int i=1;i<=n;i++){
        w[i][i] = q[i-1] + p[i] + q[i];
        c[i][i] = w[i][i];
        r[i][i] = i;
    }
    for(int sz = 2;sz<=n;++sz){
        for(int i=1;i+sz-1<=n;i++){
            int j = i+sz-1;
            w[i][j] = w[i][j-1] + p[j] + q[j];
            c[i][j] = INT_MAX;
            for(int k=i;k<=j;k++){
                int cost = w[i][j]+c[i][k-1]+c[k+1][j];
                if(cost<c[i][j]){
                    c[i][j] = cost;
                    r[i][j] = k;
                }
            }
        }
    }
    cout<<"Cost of optimal BST is: "<<c[1][n]<<endl;
    return construct(r,1,n);
}

void preorder(string words[], Node* node){
    if(!node) return;
    cout<<words[node->data]<<" ";
    preorder(words, node->left);
    preorder(words, node->right);
}

int main(){
    int n;
    cout<<"How many elements do you want? ";
    cin>>n;
    string words[n+1];
    for(int i=1;i<=n;i++) cin>>words[i];
    int p[n+1];
    int q[n+1];
    cout<<"Enter values of p: \n";
    for(int i=1;i<=n;i++){
        cout<<i<<": ";
        cin>>p[i];
    }
    cout<<"Enter values of q: \n";
    for(int i=0;i<=n;i++){
        cout<<i<<": ";
        cin>>q[i];
    }
    Node* root = optimalbst(p,q,n);
    cout<<"Preorder of Optimal Binary Search Tree: "<<endl;
    preorder(words, root);
    cout<<endl;
    return 0;
}








16

import java.util.Arrays;

public class HeapSort {

    public static void heapify(int[] arr, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left] > arr[largest])
            largest = left;

        if (right < n && arr[right] > arr[largest])
            largest = right;

        if (largest != i) {
            int temp = arr[i];
            arr[i] = arr[largest];
            arr[largest] = temp;

            heapify(arr, n, largest);
        }
    }

    public static void heapSort(int[] arr) {
        int n = arr.length;

        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(arr, n, i);

        for (int i = n - 1; i > 0; i--) {
            int temp = arr[0];
            arr[0] = arr[i];
            arr[i] = temp;

            heapify(arr, i, 0);
        }
    }

    public static void display(int[] arr) {
        for (int val : arr)
            System.out.print(val + " ");
        System.out.println();
    }

    public static void main(String[] args) {
        int[] arr = {10, 3, 76, 34, 23, 32};

        System.out.print("Original array: ");
        display(arr);

        heapSort(arr);

        System.out.print("Sorted array using Heap Sort: ");
        display(arr);
    }
}


17


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct Student {
    int rollNo;
    string name;
    char division;
    string address;
};

void addStudent() {
    ofstream file("students.txt", ios::app);
    Student s;
    cout << "Enter Roll No: "; cin >> s.rollNo;
    cout << "Enter Name: "; cin.ignore(); getline(cin, s.name);
    cout << "Enter Division: "; cin >> s.division;
    cout << "Enter Address: "; cin.ignore(); getline(cin, s.address);

    file << s.rollNo << " " << s.name << " " << s.division << " " << s.address << "\n";
    file.close();
    cout << "Student added successfully.\n";
}

void displayAll() {
    ifstream file("students.txt");
    Student s;
    cout << "\n--- Student Records ---\n";
    while (file >> s.rollNo) {
        file >> ws;
        getline(file, s.name, ' ');
        file >> s.division;
        file >> ws;
        getline(file, s.address);
        cout << "Roll No: " << s.rollNo << ", Name: " << s.name
             << ", Division: " << s.division << ", Address: " << s.address << "\n";
    }
    file.close();
}

void searchStudent() {
    ifstream file("students.txt");
    Student s;
    int roll;
    cout << "Enter Roll No to search: ";
    cin >> roll;
    bool found = false;
    while (file >> s.rollNo) {
        file >> ws;
        getline(file, s.name, ' ');
        file >> s.division;
        file >> ws;
        getline(file, s.address);
        if (s.rollNo == roll) {
            cout << "Found: " << s.rollNo << " " << s.name << " " << s.division << " " << s.address << "\n";
            found = true;
            break;
        }
    }
    if (!found) cout << "Student not found.\n";
    file.close();
}

void deleteStudent() {
    ifstream file("students.txt");
    ofstream temp("temp.txt");
    Student s;
    int roll;
    cout << "Enter Roll No to delete: ";
    cin >> roll;
    bool found = false;

    while (file >> s.rollNo) {
        file >> ws;
        getline(file, s.name, ' ');
        file >> s.division;
        file >> ws;
        getline(file, s.address);
        if (s.rollNo != roll) {
            temp << s.rollNo << " " << s.name << " " << s.division << " " << s.address << "\n";
        } else {
            found = true;
        }
    }
    file.close();
    temp.close();
    remove("students.txt");
    rename("temp.txt", "students.txt");
    if (found)
        cout << "Student deleted.\n";
    else
        cout << "Student not found.\n";
}

void editStudent() {
    ifstream file("students.txt");
    ofstream temp("temp.txt");
    Student s;
    int roll;
    cout << "Enter Roll No to edit: ";
    cin >> roll;
    bool found = false;

    while (file >> s.rollNo) {
        file >> ws;
        getline(file, s.name, ' ');
        file >> s.division;
        file >> ws;
        getline(file, s.address);

        if (s.rollNo == roll) {
            found = true;
            cout << "Enter new details:\n";
            cout << "Enter Name: "; cin.ignore(); getline(cin, s.name);
            cout << "Enter Division: "; cin >> s.division;
            cout << "Enter Address: "; cin.ignore(); getline(cin, s.address);
        }
        temp << s.rollNo << " " << s.name << " " << s.division << " " << s.address << "\n";
    }
    file.close();
    temp.close();
    remove("students.txt");
    rename("temp.txt", "students.txt");
    if (found)
        cout << "Student updated.\n";
    else
        cout << "Student not found.\n";
}

int main() {
    int choice;
    do {
        cout << "\n1. Add\n2. Display All\n3. Search\n4. Delete\n5. Edit\n0. Exit\nChoice: ";
        cin >> choice;
        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayAll(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: editStudent(); break;
            case 0: cout << "Exit\n"; break;
            default: cout << "Invalid\n";
        }
    } while (choice != 0);
    return 0;
}





19

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph {
    int n;
    vector<vector<int>> adjMatrix;
    vector<bool> visited;

public:
    Graph(int nodes) : n(nodes), adjMatrix(n, vector<int>(n, 0)), visited(n, false) {}

    void addEdge(int u, int v) {
        adjMatrix[u][v] = adjMatrix[v][u] = 1;
    }

    void DFS(int v) {
        visited[v] = true;
        cout << v << " ";
        for (int i = 0; i < n; i++) {
            if (adjMatrix[v][i] == 1 && !visited[i])
                DFS(i);
        }
    }

    void BFS(int start) {
        fill(visited.begin(), visited.end(), false);
        queue<int> q;
        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int v = q.front(); q.pop();
            cout << v << " ";
            for (int i = 0; i < n; i++) {
                if (adjMatrix[v][i] == 1 && !visited[i]) {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
    }

    int countConnectedComponents() {
        int components = 0;
        fill(visited.begin(), visited.end(), false);
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                DFS(i);
                components++;
                cout << endl;
            }
        }
        return components;
    }
};

int main() {
    int nodes, edges;
    cout << "Enter number of nodes and edges: ";
    cin >> nodes >> edges;

    Graph g(nodes);
    cout << "Enter edges (u v):\n";
    for (int i = 0; i < edges; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    cout << "\nDFS traversal (connected components shown):\n";
    int components = g.countConnectedComponents();
    cout << "Number of connected components: " << components << endl;

    cout << "\nBFS traversal from node 0:\n";
    g.BFS(0);

    cout << "\n\nGraph is " << (components == 1 ? "Connected" : "Not Connected") << endl;

    return 0;
}



21




#include <iostream>
using namespace std;

const int TABLE_SIZE = 10;

struct HashEntry {
    int pnr = -1;
    bool isOccupied = false;
};

class HashTable {
    HashEntry table[TABLE_SIZE];

public:
    void insertWithReplacement(int pnr) {
        int index = pnr % TABLE_SIZE;

        if (!table[index].isOccupied) {
            table[index].pnr = pnr;
            table[index].isOccupied = true;
        } else {
            int existingIndex = table[index].pnr % TABLE_SIZE;
            if (existingIndex != index) {
                // Replace and reinsert the existing element
                int temp = table[index].pnr;
                table[index].pnr = pnr;
                reinsert(temp);
            } else {
                // Linearly probe to find next empty slot
                int newIndex = (index + 1) % TABLE_SIZE;
                while (table[newIndex].isOccupied) {
                    newIndex = (newIndex + 1) % TABLE_SIZE;
                }
                table[newIndex].pnr = pnr;
                table[newIndex].isOccupied = true;
            }
        }
    }

    void reinsert(int pnr) {
        int index = pnr % TABLE_SIZE;
        while (table[index].isOccupied) {
            index = (index + 1) % TABLE_SIZE;
        }
        table[index].pnr = pnr;
        table[index].isOccupied = true;
    }

    void display() {
        cout << "\nFinal Hash Table:\n";
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (table[i].isOccupied)
                cout << i << " => " << table[i].pnr << endl;
            else
                cout << i << " => Empty" << endl;
        }
    }
};

int main() {
    HashTable ht;
    int pnrs[] = {11, 21, 31, 34, 55, 52, 33};

    for (int pnr : pnrs) {
        ht.insertWithReplacement(pnr);
    }

    ht.display();

    return 0;
}


22


#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
using namespace std;
const int MAX =10;

struct HuffmanNode{
    char ch;
    int freq;
    int left ,right;
};

HuffmanNode tree[MAX];
int nC=0;

struct Compare{
    bool operator()(int a ,int b){
        return tree[a].freq> tree[b].freq;
    }
};

int buildHT(unorderd_map<char ,int>&freqMap){
    priority_queue<int , vector<int> , Compare>pq;
    
    for(auto &pair : freqMap){
        tree[nC]= {pair.first ,pair.second ,-1 ,-1};
        pq.push(nC++);
    }
    
    while(!pq.empty()){
        int left= pq.top() ;pq.pop();
        int right=pq.top() ;pq.pop();
        
        tree[nC]= {'\0' ,tree[left].freq +tree[right].freq, left ,right};
        pq.push(nC++);
    }
    
    return pq.top();
}

void generateCodes(int node , string code , unordered_map<char ,string>&huffmanCodes){
    if(node==-1) return ;
    if(tree[node].ch!='\0'){
        huffmanCodes[tree[node].ch]=code;
        return;
    }
    generateCodes(tree[node].left , code+"0" + huffmanCodes);
    generateCodes(tree[node].right , code+"1" + huffmanCodes);
}

void encode(string text , unordered_map<char ,string> & huffmanCodes){
    string encoded="";
    for(char ch: text) encoded += huffmanCodes[ch];
    return encoded;
}

string decode(string encodedStr ,int root){
    string decoded= "";
    int current =root;

    for(char bit:encodedStr){
        current=(bit=='0')? tree[current].left :tree[current].right;
        if(tree[current].ch!='\0'){
            decoded= += tree[current].ch;
            current=root;
        }
        
    }
    return decoded;
}


int main() {
    unordered_map<char, int> freqMap = {
        {'a', 1}, {'b', 2}, {'c', 3}, {'d', 4},
        {'e', 5}, {'f', 6}, {'g', 7}, {'h', 8}
    };

    string text;
    cout << "Enter a string (only using characters a-h): ";
    cin >> text;

    int root = buildHuffmanTree(freqMap);

    unordered_map<char, string> huffmanCodes;
    generateCodes(root, "", huffmanCodes);

    cout << "\nHuffman Codes:\n";
    for (auto& pair : huffmanCodes)
        cout << pair.first << ": " << pair.second << endl;

    string encoded = encode(text, huffmanCodes);
    cout << "\nEncoded String: " << encoded << endl;

    string decoded = decode(encoded, root);
    cout << "Decoded String: " << decoded << endl;

    return 0;
}
