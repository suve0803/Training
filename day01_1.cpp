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
        if (
