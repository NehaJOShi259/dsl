#include <iostream>
using namespace std;

const int SIZE = 10;

struct Student {
    int pnr;
    int marks;
    int chain;

    Student() {
        pnr = -1;
        marks = -1;
        chain = -1;
    }
};

class HashTable {
    Student table[SIZE];

    int hash(int key) {
        return key % SIZE;
    }

public:
    void insert(int pnr, int marks) {
        int index = hash(pnr);

        if (table[index].pnr == -1) {
            table[index].pnr = pnr;
            table[index].marks = marks;
            return;
        }

        int homeIndex = hash(table[index].pnr);

        // Replacement needed
        if (homeIndex != index) {
            // Find empty slot
            int newIndex = (index + 1) % SIZE;
            while (table[newIndex].pnr != -1 && newIndex != index)
                newIndex = (newIndex + 1) % SIZE;

            if (table[newIndex].pnr != -1) {
                cout << "Hash table full!\n";
                return;
            }

            // Replace and reinsert displaced element
            Student temp = table[index];
            table[index].pnr = pnr;
            table[index].marks = marks;
            table[index].chain = -1;

            // Update chain links
            int prev = homeIndex;
            while (table[prev].chain != index)
                prev = table[prev].chain;
            table[prev].chain = newIndex;

            table[newIndex] = temp;
            return;
        }

        // Linear probing + chaining
        int i = (index + 1) % SIZE;
        while (table[i].pnr != -1 && i != index)
            i = (i + 1) % SIZE;

        if (table[i].pnr != -1) {
            cout << "Hash table full!\n";
            return;
        }

        table[i].pnr = pnr;
        table[i].marks = marks;
        table[i].chain = -1;

        int last = index;
        while (table[last].chain != -1)
            last = table[last].chain;

        table[last].chain = i;
    }

    void display() {
        cout << "Index\tPNR\tMarks\tChain\n";
        for (int i = 0; i < SIZE; i++)
            cout << i << "\t" << table[i].pnr << "\t" << table[i].marks << "\t" << table[i].chain << "\n";
    }

    void search(int pnr) {
        int i = hash(pnr);
        while (i != -1) {
            if (table[i].pnr == pnr) {
                cout << "Found: PNR=" << pnr << ", Marks=" << table[i].marks << "\n";
                return;
            }
            i = table[i].chain;
        }
        cout << "PNR not found\n";
    }
};

int main() {
    HashTable h;
    int pnrList[] = {11, 21, 31, 34, 55, 52, 33};
    int marksList[] = {70, 80, 90, 65, 75, 85, 60};

    for (int i = 0; i < 7; i++)
        h.insert(pnrList[i], marksList[i]);

    h.display();

    int key;
    cout << "Enter PNR to search: ";
    cin >> key;
    h.search(key);

    return 0;
}
