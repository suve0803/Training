#include <iostream>
using namespace std;

class ArrayHandler {
private:
    int arr[100]; // Array to store elements
    int size;     // Size of the array

public:
    // Constructor to initialize size
    ArrayHandler() { size = 0; }

    // Method to set array elements
    void setArray() {
        cout << "Enter the size of the array: ";
        cin >> size;

        cout << "Enter " << size << " elements:\n";
        for (int i = 0; i < size; i++) {
            cin >> arr[i];
        }
    }

    // Method to find the largest element
    int findLargest() {
        int max = arr[0];
        for (int i = 1; i < size; i++) {
            if (arr[i] > max) {
                max = arr[i];
            }
        }
        return max;
    }

    // Method to sort array in ascending order
    void sortAscending() {
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    // Swap arr[j] and arr[j+1]
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }

    // Method to sort array in descending order
    void sortDescending() {
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (arr[j] < arr[j + 1]) {
                    // Swap arr[j] and arr[j+1]
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }

    // Method to display the array
    void display() {
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    ArrayHandler handler;
    handler.setArray();

    cout << "Original Array: ";
    handler.display();

    int largest = handler.findLargest();
    cout << "Largest Element: " << largest << endl;

    handler.sortAscending();
    cout << "Array in Ascending Order: ";
    handler.display();

    handler.sortDescending();
    cout << "Array in Descending Order: ";
    handler.display();

    return 0;
