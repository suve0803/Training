#include "LinkedList.h"

// Add Employee to the end of the list
void LinkedList::addEmployee(int id, string name, float salary) {
    Node* newNode = new Node(Employee(id, name, salary));
    if (head == nullptr) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
    cout << "Employee added: " << name << endl;
}

// Display all employees
void LinkedList::displayAll() const {
    if (head == nullptr) {
        cout << "No employees to display.\n";
        return;
    }
    cout << "--- All Employees ---\n";
    Node* current = head;
    while (current != nullptr) {
        current->data.display();
        current = current->next;
    }
}

// Delete an employee by ID
bool LinkedList::deleteById(int id) {
    if (head == nullptr) return false;

    if (head->data.id == id) {
        Node* temp = head;
        head = head->next;
        delete temp;
        cout << "Employee with ID " << id << " deleted.\n";
        return true;
    }

    Node* current = head;
    while (current->next != nullptr && current->next->data.id != id) {
        current = current->next;
    }

    if (current->next == nullptr) return false;

    Node* temp = current->next;
    current->next = current->next->next;
    delete temp;
    cout << "Employee with ID " << id << " deleted.\n";
    return true;
}

// Search employees by name
void LinkedList::searchByName(const string& name) const {
    bool found = false;
    Node* current = head;

    cout << "--- Search Result ---\n";
    while (current != nullptr) {
        if (current->data.name == name) {
            current->data.display();
            found = true;
        }
        current = current->next;
    }

    if (!found) {
        cout << "No employee found with name: " << name << endl;
    }
}

// Update salary by ID
bool LinkedList::updateSalaryById(int id, float newSalary) {
    Node* current = head;

    while (current != nullptr) {
        if (current->data.id == id) {
            current->data.salary = newSalary;
            cout << "Salary updated for ID " << id << endl;
            return true;
        }
        current = current->next;
    }
    return false;
}

// Count total employees
int LinkedList::countEmployees() const {
    int count = 0;
    Node* current = head;

    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;


}




#include <iostream>
#include "LinkedList.h"

using namespace std;

void menu() {
    cout << "\n--- Employee Record Management ---\n";
    cout << "1. Add Employee\n";
    cout << "2. Display All Employees\n";
    cout << "3. Delete Employee by ID\n";
    cout << "4. Search Employee by Name\n";
    cout << "5. Update Salary by ID\n";
    cout << "6. Count Employees\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    LinkedList employeeList;
    int choice;

    do {
        menu();
        cin >> choice;

        switch (choice) {
            case 1: {
                int id;
                string name;
                float salary;
                cout << "Enter ID, Name, and Salary: ";
                cin >> id >> name >> salary;
                employeeList.addEmployee(id, name, salary);
                break;
            }
            case 2:
                employeeList.displayAll();
                break;
            case 3: {
                int id;
                cout << "Enter ID to delete: ";
                cin >> id;
                if (!employeeList.deleteById(id)) {
                    cout << "Employee with ID " << id << " not found.\n";
                }
                break;
            }
            case 4: {
                string name;
                cout << "Enter Name to search: ";
                cin >> name;
                employeeList.searchByName(name);
                break;
            }
            case 5: {
                int id;
                float salary;
                cout << "Enter ID and new Salary: ";
                cin >> id >> salary;
                if (!employeeList.updateSalaryById(id, salary)) {
                    cout << "Employee with ID " << id << " not found.\n";
                }
                break;
            }
            case 6:
                cout << "Total Employees: " << employeeList.countEmployees() << endl;
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}


#pragma once
#include "Employee.h"

class Node {
public:
    Employee data;
    Node* next;

    Node(Employee emp) : data(emp), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    // Methods
    void addEmployee(int id, string name, float salary);
    void displayAll() const;
    bool deleteById(int id);
    void searchByName(const string& name) const;
    bool updateSalaryById(int id, float newSalary);
    int countEmployees() const;
};


#pragma once
#include <iostream>
#include <string>
using namespace std;

// Employee Class
class Employee {
public:
    int id;
    string name;
    float salary;

    Employee(int empId, string empName, float empSalary)
        : id(empId), name(empName), salary(empSalary) {}

    void display() const {
        cout << "ID: " << id << ", Name: " << name << ", Salary: " << salary << endl;
    }
};






#include <iostream>
#include <string>
using namespace std;

class Employee {
public:
    int id;
    string name;
    float salary;
    Employee* next;

    Employee(int id, string name, float salary) {
        this->id = id;
        this->name = name;
        this->salary = salary;
        this->next = nullptr;
    }
};

class EmployeeLinkedList {
private:
    Employee* head;
    Employee* tail;

public:
    EmployeeLinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    // 1. Add Employee
    void addEmployee(int id, string name, float salary) {
        Employee* newEmployee = new Employee(id, name, salary);
        if (head == nullptr) {
            head = newEmployee;
            tail = newEmployee;
        } else {
            tail->next = newEmployee;
            tail = newEmployee;
        }
        cout << "Employee added: " << name << endl;
    }

    // 2. Display All Employees
    void displayAll() {
        if (head == nullptr) {
            cout << "No employees to display.\n";
            return;
        }
        cout << "--- All Employees ---\n";
        Employee* temp = head;
        while (temp != nullptr) {
            cout << "ID: " << temp->id << ", Name: " << temp->name << ", Salary: " << temp->salary << endl;
            temp = temp->next;
        }
    }

    // 3. Delete Employee by ID
    void deleteById(int id) {
        if (head == nullptr) {
            cout << "No employees to delete.\n";
            return;
        }

        if (head->id == id) {
            Employee* toDelete = head;
            head = head->next;
            delete toDelete;
            cout << "Employee with ID " << id << " deleted.\n";
            return;
        }

        Employee* temp = head;
        while (temp->next != nullptr && temp->next->id != id) {
            temp = temp->next;
        }

        if (temp->next == nullptr) {
            cout << "Employee with ID " << id << " not found.\n";
            return;
        }

        Employee* toDelete = temp->next;
        temp->next = temp->next->next;
        if (toDelete == tail) {
            tail = temp;
        }
        delete toDelete;
        cout << "Employee with ID " << id << " deleted.\n";
    }

    // 4. Search Employee by Name
    void searchByName(const string& name) {
        Employee* temp = head;
        bool found = false;
        cout << "--- Search Results ---\n";
        while (temp != nullptr) {
            if (temp->name == name) {
                cout << "ID: " << temp->id << ", Name: " << temp->name << ", Salary: " << temp->salary << endl;
                found = true;
            }
            temp = temp->next;
        }
        if (!found) {
            cout << "No employee found with name: " << name << endl;
        }
    }

    // 5. Update Salary by ID
    void updateSalaryById(int id, float newSalary) {
        Employee* temp = head;
        while (temp != nullptr) {
            if (temp->id == id) {
                temp->salary = newSalary;
                cout << "Salary updated for ID " << id << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Employee with ID " << id << " not found.\n";
    }

    // 6. Count Total Employees
    int countEmployees() {
        int count = 0;
        Employee* temp = head;
        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }
        return count;
    }
};

// Menu function
void menu() {
    cout << "\n--- Employee Record Management ---\n";
    cout << "1. Add Employee\n";
    cout << "2. Display All Employees\n";
    cout << "3. Delete Employee by ID\n";
    cout << "4. Search Employee by Name\n";
    cout << "5. Update Salary by ID\n";
    cout << "6. Count Employees\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
}

// Main function
int main() {
    EmployeeLinkedList employeeList;
    int choice;

    do {
        menu();
        cin >> choice;

        switch (choice) {
            case 1: {
                int id;
                string name;
                float salary;
                cout << "Enter ID, Name, and Salary: ";
                cin >> id >> name >> salary;
                employeeList.addEmployee(id, name, salary);
                break;
            }
            case 2:
                employeeList.displayAll();
                break;
            case 3: {
                int id;
                cout << "Enter ID to delete: ";
                cin >> id;
                employeeList.deleteById(id);
                break;
            }
            case 4: {
                string name;
                cout << "Enter Name to search: ";
                cin >> name;
                employeeList.searchByName(name);
                break;
            }
            case 5: {
                int id;
                float salary;
                cout << "Enter ID and new Salary: ";
                cin >> id >> salary;
                employeeList.updateSalaryById(id, salary);
                break;
            }
            case 6:
                cout << "Total Employees: " << employeeList.countEmployees() << endl;
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
