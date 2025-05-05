#include <iostream>
#include <list>
#include <vector>
using namespace std;

const int TABLE_SIZE = 26;

int hashFunction(string word) {
    return word[0] - 'a';
}

void insert(vector<list<string>> &table, string word) {
    int index = hashFunction(word);
    table[index].push_back(word);
}

bool search(vector<list<string>> &table, string word) {
    int index = hashFunction(word);
    for (auto &w : table[index])
        if (w == word)
            return true;
    return false;
}

int main() {
    vector<list<string>> table(TABLE_SIZE);
    vector<string> words = {
        "apple", "banana", "grape", "orange", "peach", "plum", "berry", "melon", "kiwi", "lemon",
        "mango", "guava", "apricot", "pear", "cherry", "fig", "date", "lime", "papaya", "tamarind",
        "coconut", "nectarine", "blueberry"
    };

    for (string w : words) insert(table, w);

    string input;
    cout << "Enter words to check spelling (type 'exit' to stop):\n";
    while (true) {
        cin >> input;
        if (input == "exit") break;
        if (search(table, input))
            cout << "Correct spelling.\n";
        else
            cout << "Incorrect spelling.\n";
    }
    return 0;
}
