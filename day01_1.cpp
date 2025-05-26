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

