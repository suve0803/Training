   #include <iostream>
#include <string>
#define MAX 5

using namespace std;

class Employee {
private:
    int id;
    string name;

public:
    // Constructor to initialize Employee
    Employee(int eid = 0, string ename = "") : id(eid), name(ename) {}

    // Getters
    int getId() const { return id; }
    string getName() const { return name; }

    // Display Employee details
    void display() const {
        cout << "ID: " << id << ", Name: " << name << endl;
    }
};

class StackOp {
private:
    int top;
    Employee arr[MAX]; // Array of Employee objects
public:
    StackOp();
    bool push(const Employee &);
    bool pop();
    void display() const;
};

// Constructor
StackOp::StackOp() : top(-1) {}

// Push operation
bool StackOp::push(const Employee &emp) {
    if (top == MAX - 1) {
        cout << "Stack is full. Cannot add more employees.\n";
        return false;
    }
    arr[++top] = emp; // Add employee to stack
    cout << "Employee added successfully.\n";
    return true;
}

// Pop operation
bool StackOp::pop() {
    if (top == -1) {
        cout << "Stack is empty. No employee to remove.\n";
        return false;
    }
    cout << "Removed Employee: ";
    arr[top--].display(); // Display and remove the top employee
    return true;
}

// Display stack contents
void StackOp::display() const {
    if (top == -1) {
        cout << "Stack is empty. No employees to display.\n";
        return;
    }
    cout << "==== Employee List ====\n";
    for (int i = top; i >= 0; i--) {
        arr[i].display();
    }
    cout << endl;
}

// Main function
int main() {
    StackOp s;
    s.push(Employee(101, "Alice"));
    s.push(Employee(102, "Bob"));
    s.push(Employee(103, "Charlie"));
    s.push(Employee(104, "Diana"));
    s.push(Employee(105, "Eve"));
    s.push(Employee(106, "Frank")); // Exceeding stack size

    cout << "\nCurrent Stack:\n";
    s.display();

    s.pop(); // Remove top employee
    s.display();

    s.pop();
    s.pop();
    s.pop();
    s.pop();
    s.pop(); // Trying to pop from empty stack

    return 0;
}
