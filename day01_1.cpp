#include <iostream>
using namespace std;

class ArrayHandler {
private:
    int arr[100]; // Array to store elements
    int size;     // Size of the array

public:
    // Method to initialize the array and its size
    void initialize() {
        cout << "Enter the size of the array: ";
        cin >> size;

        cout << "Enter " << size << " elements:\n";
        for (int i = 0; i < size; i++) {
            cin >> arr[i];
        }
    }

    // Method to find the largest element
    int findLargest() {
        int maxElement = arr[0];
        for (int i = 1; i < size; i++) {
            if (arr[i] > maxElement) {
                maxElement = arr[i];
            }
        }
        return maxElement;
    }

    // Method to sort the array in ascending order (selection sort)
    void sortAscending() {
        for (int i = 0; i < size - 1; i++) {
            int minIndex = i;
            for (int j = i + 1; j < size; j++) {
                if (arr[j] < arr[minIndex]) {
                    minIndex = j;
                }
            }
            // Swap the found minimum element with the current element
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }

    // Method to sort the array in descending order (selection sort)
    void sortDescending() {
        for (int i = 0; i < size - 1; i++) {
            int maxIndex = i;
            for (int j = i + 1; j < size; j++) {
                if (arr[j] > arr[maxIndex]) {
                    maxIndex = j;
                }
            }
            // Swap the found maximum element with the current element
            int temp = arr[i];
            arr[i] = arr[maxIndex];
            arr[maxIndex] = temp;
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
    handler.initialize();

    cout << "\nOriginal Array: ";
    handler.display();

    cout << "Largest Element: " << handler.findLargest() << endl;

    handler.sortAscending();
    cout << "Array in Ascending Order: ";
    handler.display();

    handler.sortDescending();
    cout << "Array in Descending Order: ";
    handler.display();

    return 0;
