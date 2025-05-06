#include<bits/stdc++.h>
using namespace std;

int hashFunction(const string &word) {
    return word[0] - 'a';
}

int main() {
    vector<list<string>> table(26);
    vector<string> words = {
        "apple", "banana", "grape", "orange", "peach", "plum", "berry", "melon",
        "kiwi", "lemon", "mango", "guava", "apricot", "pear", "cherry", "fig",
        "date", "lime", "papaya", "tamarind", "coconut", "nectarine", "blueberry"
    };

    for (const string &w : words)
        table[hashFunction(w)].push_back(w);

    string word;
    cout << "Enter word (type 'exit' to stop):\n";
    while (cin >> word && word != "exit") {
        bool found = false;
        for (const string &w : table[hashFunction(word)])
            if (w == word) found = true;
        cout << (found ? "Correct\n" : "Incorrect\n");
    }
    return 0;
}

