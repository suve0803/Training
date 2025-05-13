#include <iostream>
#include <string>
using namespace std;

// Constants
const int MAX_STUDENTS = 100;

// Function declarations
void addStudent(int ids[], string names[], int ages[], string departments[], float grades[], int& count);
void viewStudents(const int ids[], const string names[], const int ages[], const string departments[], const float grades[], int count);
void updateStudent(int ids[], string names[], int ages[], string departments[], float grades[], int count);
void deleteStudent(int ids[], string names[], int ages[], string departments[], float grades[], int& count);
void listDepartmentStudents(const int ids[], const string names[], const int ages[], const string departments[], const float grades[], int count);
void generateDepartmentReports(const string departments[], int count);

int main() {
    // Fixed-size arrays to store student data
    int ids[MAX_STUDENTS];
    string names[MAX_STUDENTS];
    int ages[MAX_STUDENTS];
    string departments[MAX_STUDENTS];
    float grades[MAX_STUDENTS];
    int studentCount = 0;  // Current number of students

    int choice;

    do {
        cout << "\n--- College Admission Management System ---\n";
        cout << "1. Add Student\n";
        cout << "2. View All Students\n";
        cout << "3. Update Student\n";
        cout << "4. Delete Student\n";
        cout << "5. List Students by Department\n";
        cout << "6. Generate Department Reports\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent(ids, names, ages, departments, grades, studentCount);
                break;
            case 2:
                viewStudents(ids, names, ages, departments, grades, studentCount);
                break;
            case 3:
                updateStudent(ids, names, ages, departments, grades, studentCount);
                break;
            case 4:
                deleteStudent(ids, names, ages, departments, grades, studentCount);
                break;
            case 5:
                listDepartmentStudents(ids, names, ages, departments, grades, studentCount);
                break;
            case 6:
                generateDepartmentReports(departments, studentCount);
                break;
            case 7:
                cout << "Exiting the program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 7);

    return 0;
}

// Function to add a new student
void addStudent(int ids[], string names[], int ages[], string departments[], float grades[], int& count) {
    if (count >= MAX_STUDENTS) {
        cout << "Maximum number of students reached. Cannot add more.\n";
        return;
    }

    cout << "Enter Student ID: ";
    cin >> ids[count];
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, names[count]);
    cout << "Enter Age: ";
    cin >> ages[count];
    cin.ignore();
    cout << "Enter Department: ";
    getline(cin, departments[count]);
    cout << "Enter Grade: ";
    cin >> grades[count];

    count++;
    cout << "Student added successfully!\n";
}

// Function to view all students
void viewStudents(const int ids[], const string names[], const int ages[], const string departments[], const float grades[], int count) {
    if (count == 0) {
        cout << "No student records found.\n";
        return;
    }

    cout << "\n--- All Students ---\n";
    for (int i = 0; i < count; i++) {
        cout << "ID: " << ids[i] << ", Name: " << names[i] << ", Age: " << ages[i]
             << ", Department: " << departments[i] << ", Grade: " << grades[i] << "\n";
    }
}

// Function to update student details
void updateStudent(int ids[], string names[], int ages[], string departments[], float grades[], int count) {
    int id;
    cout << "Enter Student ID to update: ";
    cin >> id;

    for (int i = 0; i < count; i++) {
        if (ids[i] == id) {
            cout << "Enter new details for the student:\n";
            cout << "Name: ";
            cin.ignore();
            getline(cin, names[i]);
            cout << "Age: ";
            cin >> ages[i];
            cin.ignore();
            cout << "Department: ";
            getline(cin, departments[i]);
            cout << "Grade: ";
            cin >> grades[i];

            cout << "Student details updated successfully!\n";
            return;
        }
    }

    cout << "Student with ID " << id << " not found.\n";
}

// Function to delete a student
void deleteStudent(int ids[], string names[], int ages[], string departments[], float grades[], int& count) {
    int id;
    cout << "Enter Student ID to delete: ";
    cin >> id;

    for (int i = 0; i < count; i++) {
        if (ids[i] == id) {
            for (int j = i; j < count - 1; j++) {
                ids[j] = ids[j + 1];
                names[j] = names[j + 1];
                ages[j] = ages[j + 1];
                departments[j] = departments[j + 1];
                grades[j] = grades[j + 1];
            }
            count--;
            cout << "Student deleted successfully.\n";
            return;
        }
    }

    cout << "Student with ID " << id << " not found.\n";
}

// Function to list students by department
void listDepartmentStudents(const int ids[], const string names[], const int ages[], const string departments[], const float grades[], int count) {
    string department;
    cout << "Enter Department: ";
    cin.ignore();
    getline(cin, department);

    cout << "\n--- Students in Department: " << department << " ---\n";
    bool found = false;
    for (int i = 0; i < count; i++) {
        if (departments[i] == department) {
            cout << "ID: " << ids[i] << ", Name: " << names[i] << ", Age: " << ages[i]
                 << ", Grade: " << grades[i] << "\n";
            found = true;
        }
    }

    if (!found) {
        cout << "No students found in department: " << department << ".\n";
    }
}

// Function to generate department reports
void generateDepartmentReports(const string departments[], int count) {
    if (count == 0) {
        cout << "No students to generate reports.\n";
        return;
    }

    cout << "\n--- Department Reports ---\n";
    for (int i = 0; i < count; i++) {
        int deptCount = 1;
        if (i == 0 || departments[i] != departments[i - 1]) {
            for (int j = i + 1; j < count; j++) {
                if (departments[i] == departments[j]) {
                    deptCount++;
                }
            }
            cout << "Department: " << departments[i] << ", Total Students: " << deptCount << "\n";
        }
    }
}
