    #include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Employee {
private:
    int id;
    string name;
    float salary;

public:
    Employee() : id(0), salary(0.0) {}

    // Input employee details
    void inputDetails() {
        cout << "Enter Employee ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Employee Name: ";
        getline(cin, name);
        cout << "Enter Employee Salary: ";
        cin >> salary;
    }

    // Display employee details
    void displayDetails() const {
        cout << "ID: " << id << ", Name: " << name << ", Salary: " << salary << endl;
    }

    // Get ID for comparison
    int getID() const { return id; }

    // Update employee details
    void updateDetails() {
        cout << "Enter new name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter new salary: ";
        cin >> salary;
    }

    // Write employee data to a file
    void writeToFile(ofstream &outFile) const {
        outFile << id << " " << name << " " << salary << endl;
    }

    // Read employee data from a file
    void readFromFile(ifstream &inFile) {
        inFile >> id >> name >> salary;
    }
};

class EmployeeManager {
private:
    vector<Employee> employees;
    string filename;

    void loadFromFile() {
        employees.clear();
        ifstream file(filename);
        if (file.is_open()) {
            Employee emp;
            while (!file.eof()) {
                emp.readFromFile(file);
                if (file) { // Avoid adding an incomplete or extra object
                    employees.push_back(emp);
                }
            }
            file.close();
        }
    }

    void saveToFile() const {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto &emp : employees) {
                emp.writeToFile(file);
            }
            file.close();
        }
    }

public:
    EmployeeManager(const string &file) : filename(file) {}

    void addEmployee() {
        Employee emp;
        emp.inputDetails();
        employees.push_back(emp);
        saveToFile();
        cout << "Employee added successfully.\n";
    }

    void viewEmployees() const {
        if (employees.empty()) {
            cout << "No employees to display.\n";
            return;
        }
        cout << "\nEmployee Details:\n";
        for (const auto &emp : employees) {
            emp.displayDetails();
        }
    }

    void updateEmployee() {
        int id;
        cout << "Enter Employee ID to update: ";
        cin >> id;

        for (auto &emp : employees) {
            if (emp.getID() == id) {
                cout << "Updating Employee Details:\n";
                emp.updateDetails();
                saveToFile();
                cout << "Employee updated successfully.\n";
                return;
            }
        }

        cout << "Employee with ID " << id << " not found.\n";
    }
};

int main() {
    EmployeeManager manager("employees.txt");
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
            manager.addEmployee();
            break;
        case 2:
            manager.viewEmployees();
            break;
        case 3:
            manager.updateEmployee();
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
