#include <iostream>
#include <vector>
using namespace std;

struct Student {
    int rollno;
    int marks;
    int chain;
    bool occupied;
};

int hashFunction(int key) {
    return key % 10;
}

void insert(Student table[], int rollno, int marks) {
    int index = hashFunction(rollno);
    if (!table[index].occupied) {
        table[index] = {rollno, marks, -1, true};
        return;
    }
    int original = index;
    while (table[index].occupied) {
        index = (index + 1) % 10;
        if (index == original) return;
    }
    table[index] = {rollno, marks, -1, true};
    int prev = hashFunction(rollno);
    while (table[prev].rollno % 10 != rollno % 10 || table[prev].chain != -1)
        prev = table[prev].chain;
    table[prev].chain = index;
}

void display(Student table[]) {
    cout << "Index\tRollNo\tMarks\tChain\n";
    for (int i = 0; i < 10; i++) {
        if (table[i].occupied)
            cout << i << "\t" << table[i].rollno << "\t" << table[i].marks << "\t" << table[i].chain << "\n";
        else
            cout << i << "\t---\t---\t---\n";
    }
}

int main() {
    Student table[10];
    for (int i = 0; i < 10; i++) table[i] = {-1, -1, -1, false};

    vector<pair<int, int>> students = {{31, 85}, {13, 78}, {14, 90}, {51, 72}, {16, 88}, {71, 65}, {48, 91}, {19, 69}};
    for (auto s : students) insert(table, s.first, s.second);

    display(table);
    return 0;
}
