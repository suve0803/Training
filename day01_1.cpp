#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Employee {
    int id;
    string name;
    float salary;

    // Function to display employee details
    void display() {
        cout << "ID: " << id << ", Name: " << name << ", Salary: " << salary << endl;
    }
};

void addEmployee(const string &filename);
void viewEmployees(const string &filename);
void updateEmployee(const string &filename);

int main() {
    string filename = "employees.txt";
    int choice;

    do {
        cout << "\nEmployee Management System\n";
        cout << "1. Add Employee\n";
        cout << "2. View Employees\n";
        cout << "3. Update Employee\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addEmployee(filename);
                break;
            case 2:
                viewEmployees(filename);
                break;
            case 3:
                updateEmployee(filename);
                break;
            case 4:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}

void addEmployee(const string &filename) {
    ofstream file(filename, ios::app); // Open file in append mode
    if (!file) {
        cerr << "Error opening file for writing.\n";
        return;
    }

    Employee emp;
    cout << "Enter Employee ID: ";
    cin >> emp.id;
    cin.ignore();
    cout << "Enter Employee Name: ";
    getline(cin, emp.name);
    cout << "Enter Employee Salary: ";
    cin >> emp.salary;

    // Write employee details to file
    file << emp.id << " " << emp.name << " " << emp.salary << endl;

    file.close();
    cout << "Employee added successfully.\n";
}

void viewEmployees(const string &filename) {
    ifstream file(filename); // Open file in read mode
    if (!file) {
        cerr << "Error opening file for reading.\n";
        return;
    }

    Employee emp;
    cout << "\nEmployee Details:\n";
    while (file >> emp.id >> emp.name >> emp.salary) {
        emp.display();
    }

    file.close();
}

void updateEmployee(const string &filename) {
    ifstream file(filename); // Open file in read mode
    if (!file) {
        cerr << "Error opening file for reading.\n";
        return;
    }

    vector<Employee> employees; // Store all employees in memory
    Employee emp;

    while (file >> emp.id >> emp.name >> emp.salary) {
        employees.push_back(emp);
    }
    file.close();

    int updateId;
    cout << "Enter Employee ID to update: ";
    cin >> updateId;

    bool found = false;
    for (auto &e : employees) {
        if (e.id == updateId) {
            found = true;
            cout << "Enter new name: ";
            cin.ignore();
            getline(cin, e.name);
            cout << "Enter new salary: ";
            cin >> e.salary;
            cout << "Employee details updated successfully.\n";
            break;
        }
    }

    if (!found) {
        cout << "Employee with ID " << updateId << " not found.\n";
        return;
    }

    // Write updated data back to file
    ofstream outFile(filename); // Open file in overwrite mode
    if (!outFile) {
        cerr << "Error opening file for writing.\n";
        return;
    }

    for (const auto &e : employees) {
        outFile << e.id << " " << e.name << " " << e.salary << endl;
    }

    outFile.close();
}
