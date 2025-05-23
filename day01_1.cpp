#include <iostream>
#include <string>
#define MAX 5

using namespace std;

// Employee Class
class Employee {
private:
    int id;
    string name;

public:
    // Setter methods
    void setId(int eid) { id = eid; }
    void setName(string ename) { name = ename; }

    // Getter methods
    int getId() const { return id; }
    string getName() const { return name; }

    // Display Employee details
    void display() const {
        cout << "ID: " << id << ", Name: " << name << endl;
    }
};

// Stack Class for Employee Objects
class StackOp {
private:
    int top;
    Employee arr[MAX]; // Array of Employee objects

public:
    // Constructor
    StackOp() { top = -1; }

    // Add an Employee to the stack
    bool push(const Employee &emp) {
        if (top == MAX - 1) {
            cout << "Stack is full. Cannot add more employees.\n";
            return false;
        }
        arr[++top] = emp; // Add employee to stack
        cout << "Employee added successfully.\n";
        return true;
    }

    // Remove an Employee from the stack
    bool pop() {
        if (top == -1) {
            cout << "Stack is empty. No employee to remove.\n";
            return false;
        }
        cout << "Removed Employee: ";
        arr[top--].display(); // Display and remove the top employee
        return true;
    }

    // Display all Employees in the stack
    void display() const {
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
};

// Main Function
int main() {
    StackOp stack;

    // Adding employees
    Employee emp1, emp2, emp3;
    emp1.setId(101);
    emp1.setName("Alice");
    stack.push(emp1);

    emp2.setId(102);
    emp2.setName("Bob");
    stack.push(emp2);

    emp3.setId(103);
    emp3.setName("Charlie");
    stack.push(emp3);

    // Display stack
    cout << "\nCurrent Stack:\n";
    stack.display();

    // Removing employees
    stack.pop();
    cout << "\nAfter Removing Top Employee:\n";
    stack.display();

    stack.pop();
    stack.pop();
    stack
