#include <iostream>
using namespace std;

struct Student {
    int rollno;
    int marks;
    int chain;
};

int hashFunction(int key) {
    return key % 10;
}

void insert(Student table[], int rollno, int marks) {
    int index = hashFunction(rollno);
    if (table[index].rollno == -1) {
        table[index].rollno = rollno;
        table[index].marks = marks;
        table[index].chain = -1;
        return;
    }

    int start = index;
    while (table[index].rollno != -1) {
        index = (index + 1) % 10;
        if (index == start) return;
    }

    table[index].rollno = rollno;
    table[index].marks = marks;
    table[index].chain = -1;
}

void display(Student table[]) {
    cout << "Index\tRollNo\tMarks\tChain\n";
    for (int i = 0; i < 10; i++) {
        if (table[i].rollno != -1)
            cout << i << "\t" << table[i].rollno << "\t" << table[i].marks << "\t" << table[i].chain << "\n";
        else
            cout << i << "\t---\t---\t---\n";
    }
}

int main() {
    Student table[10];
    for (int i = 0; i < 10; i++) {
        table[i].rollno = -1;
        table[i].marks = -1;
        table[i].chain = -1;
    }

    int rollnos[] = {31, 13, 14, 51, 16, 71, 48, 19};
    int marks[] = {85, 78, 90, 72, 88, 65, 91, 69};

    for (int i = 0; i < 8; i++) {
        insert(table, rollnos[i], marks[i]);
    }

    display(table);
    return 0;
}

