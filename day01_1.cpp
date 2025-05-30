#include <iostream>
#include <fstream>

class Employee {
private:
    int id;
    char name[50];
    float salary;

public:
    // Function to get employee details from the user
    void inputDetails() {
        std::cout << "Enter Employee ID: ";
        std::cin >> id;
        std::cin.ignore();  // Ignore leftover newline character
        std::cout << "Enter Employee Name: ";
        std::cin.getline(name, 50);
        std::cout << "Enter Employee Salary: ";
        std::cin >> salary;
    }

    // Function to display employee details
    void displayDetails() const {
        std::cout << "ID: " << id
                  << ", Name: " << name
                  << ", Salary: " << salary << "\n";
    }

    // Function to save the employee details to a file
    void saveToFile(const std::string& filename) {
        std::ofstream outFile(filename, std::ios::app);
        if (!outFile) {
            std::cerr << "Error opening file for writing.\n";
            return;
        }
        outFile << id << " " << name << " " << salary << "\n";
        outFile.close();
        std::cout << "Employee details saved successfully.\n";
    }

    // Static function to display all records from the file
    static void displayRecords(const std::string& filename) {
        std::ifstream inFile(filename);
        if (!inFile) {
            std::cerr << "Error opening file for reading.\n";
            return;
        }

        int tempId;
        char tempName[50];
        float tempSalary;
        std::cout << "Employee Records:\n";
        while (inFile >> tempId >> tempName >> tempSalary) {
            std::cout << "ID: " << tempId
                      << ", Name: " << tempName
                      << ", Salary: " << tempSalary << "\n";
        }
        inFile.close();
    }
};

int main() {
    const std::string filename = "employees.txt";
    int choice;

    do {
        std::cout << "\nMenu:\n";
        std::cout << "1. Add Employee Details\n";
        std::cout << "2. Display All Employee Records\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                Employee emp;
                emp.inputDetails();
                emp.saveToFile(filename);
                break;
            }
            case 2:
                Employee::displayRecords(filename);
                break;
            case 3:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);

    return 0;
}
