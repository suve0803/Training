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

    // A common method for all students
    void study() {
        cout << name << " is studying." << endl;
    }
};

// Derived class: UndergraduateStudent
class UndergraduateStudent : public Student {
private:
    string major;

public:
    // Constructor
    UndergraduateStudent(string studentName, int studentId, string studentMajor)
        : Student(studentName, studentId), major(studentMajor) {}

    // Override the pure virtual function
    void displayDetails() override {
        cout << "Undergraduate Student Details:" << endl;
        cout << "Name: " << name << endl;
        cout << "ID: " << id << endl;
        cout << "Major: " << major << endl;
    }

    void takeExam() {
        cout << name << " is taking an undergraduate exam." << endl;
    }
};

// Derived class: GraduateStudent
class GraduateStudent : public Student {
private:
    string researchTopic;

public:
    // Constructor
    GraduateStudent(string studentName, int studentId, string topic)
        : Student(studentName, studentId), researchTopic(topic) {}

    // Override the pure virtual function
    void displayDetails() override {
        cout << "Graduate Student Details:" << endl;
        cout << "Name: " << name << endl;
        cout << "ID: " << id << endl;
        cout << "Research Topic: " << researchTopic << endl;
    }

    void writeThesis() {
        cout << name << " is writing a thesis on " << researchTopic << "." << endl;
    }
};

// Additional class: Admin
class Admin {
public:
    void manageStudent(Student& student) {
        cout << "Admin is managing the details of the following student:" << endl;
        student.displayDetails();
    }

    void approveRequest(Student& student) {
        cout << "Admin has approved a request for " << student.getName() << "." << endl;
    }
};

// Add getter for Student name (to be used in Admin class)
class Student {
public:
    string getName() const { return name; }
};

int main() {
    // Create objects of derived classes
    UndergraduateStudent undergrad("Alice", 101, "Computer Science");
    GraduateStudent grad("Bob", 202, "Artificial Intelligence");

    // Create Admin object
    Admin admin;

    // Admin manages students
    admin.manageStudent(undergrad);
    admin.manageStudent(grad);

    cout << endl;

    // Student activities
    undergrad.study();
    undergrad.takeExam();

    cout << endl;

    grad.study();
    grad.writeThesis();

    return 0;
}
