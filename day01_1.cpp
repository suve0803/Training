/*task manager*/
#include <iostream>
#include <string>
using namespace std;

// Node structure for Task
class Task {
private:
    int taskID;
    string taskName;
    string taskStatus;
    Task* next;

public:
    Task(int id, const string& name, const string& status) : taskID(id), taskName(name), taskStatus(status), next(nullptr) {}

    int getTaskID() const { return taskID; }
    string getTaskName() const { return taskName; }
    string getTaskStatus() const { return taskStatus; }
    Task* getNext() const { return next; }
    void setNext(Task* nextTask) { next = nextTask; }

    void setTaskStatus(const string& status) { taskStatus = status; }
};

// Linked List class for Task Management
class TaskManager {
private:
    Task* head;

public:
    TaskManager() : head(nullptr) {}

    ~TaskManager() {
        Task* current = head;
        while (current != nullptr) {
            Task* temp = current;
            current = current->getNext();
            delete temp;
        }
    }

    void addTask(int id, const string& name, const string& status = "Pending") {
        Task* newTask = new Task(id, name, status);
        if (head == nullptr) {
            head = newTask;
        } else {
            Task* temp = head;
            while (temp->getNext() != nullptr) {
                temp = temp->getNext();
            }
            temp->setNext(newTask);
        }
        cout << "Task '" << name << "' added successfully!" << endl;
    }

    void displayTasks() const {
        if (head == nullptr) {
            cout << "No tasks to display." << endl;
            return;
        }

        cout << "Current Tasks:" << endl;
        Task* temp = head;
        while (temp != nullptr) {
            cout << "ID: " << temp->getTaskID()
                 << ", Name: " << temp->getTaskName()
                 << ", Status: " << temp->getTaskStatus() << endl;
            temp = temp->getNext();
        }
    }

    void deleteTask(int id) {
        if (head == nullptr) {
            cout << "Task list is empty. Cannot delete task." << endl;
            return;
        }

        // If the task to delete is the head
        if (head->getTaskID() == id) {
            Task* temp = head;
            head = head->getNext();
            cout << "Task '" << temp->getTaskName() << "' deleted successfully!" << endl;
            delete temp;
            return;
        }

        Task* current = head;
        Task* previous = nullptr;
        while (current != nullptr && current->getTaskID() != id) {
            previous = current;
            current = current->getNext();
        }

        if (current == nullptr) {
            cout << "Task with ID " << id << " not found." << endl;
        } else {
            previous->setNext(current->getNext());
            cout << "Task '" << current->getTaskName() << "' deleted successfully!" << endl;
            delete current;
        }
    }

    void updateTaskStatus(int id, const string& newStatus) {
        Task* temp = head;
        while (temp != nullptr) {
            if (temp->getTaskID() == id) {
                temp->setTaskStatus(newStatus);
                cout << "Task '" << temp->getTaskName() << "' status updated to '" << newStatus << "'." << endl;
                return;
            }
            temp = temp->getNext();
        }
        cout << "Task with ID " << id << " not found." << endl;
    }
};

// Main Function
int main() {
    TaskManager taskManager;
    int choice;

    while (true) {
        cout << "\nTask Manager Menu:";
        cout << "\n1. Add Task";
        cout << "\n2. Display Tasks";
        cout << "\n3. Delete Task";
        cout << "\n4. Update Task Status";
        cout << "\n5. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        if (choice == 1) {
            int id;
            string name, status;
            cout << "Enter Task ID: ";
            cin >> id;
            cin.ignore(); // Ignore trailing newline
            cout << "Enter Task Name: ";
            getline(cin, name);
            cout << "Enter Task Status (Default: Pending): ";
            getline(cin, status);
            if (status.empty()) status = "Pending";
            taskManager.addTask(id, name, status);
        } else if (choice == 2) {
            taskManager.displayTasks();
        } else if (choice == 3) {
            int id;
            cout << "Enter Task ID to delete: ";
            cin >> id;
            taskManager.deleteTask(id);
        } else if (choice == 4) {
            int id;
            string newStatus;
            cout << "Enter Task ID to update status: ";
            cin >> id;
            cin.ignore(); // Ignore trailing newline
            cout << "Enter new status: ";
            getline(cin, newStatus);
            taskManager.updateTaskStatus(id, newStatus);
        } else if (choice == 5) {
            cout << "Exiting Task Manager. Goodbye!" << endl;
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
