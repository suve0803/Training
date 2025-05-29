#include <iostream>
#include <string>
using namespace std;

// Abstract class: Student
class Student {
protected:
    string name;
    int id;

public:
    // Constructor
    Student(string studentName, int studentId) : name(studentName), id(studentId) {}

    // Pure virtual function
    virtual void displayDetails() = 0; // This makes the class abstract
};

// Derived class: UndergraduateStudent
class UndergraduateStudent : public Student {
public:
    // Constructor
    UndergraduateStudent(string studentName, int studentId)
        : Student(studentName, studentId) {}

    // Override the pure virtual function
    void displayDetails() override {
        cout << "Undergraduate Student Details:" << endl;
        cout << "Name: " << name << endl;
        cout << "ID: " << id << endl;
    }
};

// Derived class: GraduateStudent
class GraduateStudent : public Student {
public:
    // Constructor
    GraduateStudent(string studentName, int studentId)
        : Student(studentName, studentId) {}

    // Override the pure virtual function
    void displayDetails() override {
        cout << "Graduate Student Details:" << endl;
        cout << "Name: " << name << endl;
        cout << "ID: " << id << endl;
    }
};

int main() {
    // Create objects of derived classes
    UndergraduateStudent undergrad("Alice", 101);
    GraduateStudent grad("Bob", 202);

    // Display details
    undergrad.displayDetails();
    cout << endl;
    grad.displayDetails();

    return 0;
}
