#include <iostream>
using namespace std;

struct Student {
    int rollno = -1;
    int marks = -1;
};

int hashFunction(int rollno) {
    return rollno % 10;
}

void insert(Student table[], int rollno, int marks) {
    int index = hashFunction(rollno);

    while (table[index].rollno != -1) {
        index = (index + 1) % 10;
    }

    table[index].rollno = rollno;
    table[index].marks = marks;
}

void display(Student table[]) {
    cout << "Index\tRollNo\tMarks\n";
    for (int i = 0; i < 10; i++) {
        if (table[i].rollno != -1)
            cout << i << "\t" << table[i].rollno << "\t" << table[i].marks << "\n";
        else
            cout << i << "\t---\t---\n";
    }
}

int main() {
    Student table[10];

    insert(table, 31, 85);
    insert(table, 13, 78);
    insert(table, 14, 90);
    insert(table, 51, 72);
    insert(table, 16, 88);
    insert(table, 71, 65);
    insert(table, 48, 91);
    insert(table, 19, 69);

    display(table);

    return 0;
}


