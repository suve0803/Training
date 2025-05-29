#include <iostream>
using namespace std;

// Template class: Calculator
template <typename T>
class Calculator {
private:
    T num1, num2;

public:
    // Constructor
    Calculator(T a, T b) : num1(a), num2(b) {}

    // Functions for basic operations
    T add() {
        return num1 + num2;
    }

    T subtract() {
        return num1 - num2;
    }

    T multiply() {
        return num1 * num2;
    }

    T divide() {
        if (num2 != 0) {
            return num1 / num2;
        } else {
            cout << "Error: Division by zero!" << endl;
            return 0;
        }
    }

    // Function to display the numbers
    void displayNumbers() {
        cout << "Number 1: " << num1 << ", Number 2: " << num2 << endl;
    }
};

int main() {
    // Integer Calculator
    Calculator<int> intCalc(10, 5);
    cout << "Integer Calculator:" << endl;
    intCalc.displayNumbers();
    cout << "Addition: " << intCalc.add() << endl;
    cout << "Subtraction: " << intCalc.subtract() << endl;
    cout << "Multiplication: " << intCalc.multiply() << endl;
    cout << "Division: " << intCalc.divide() << endl;

    cout << endl;

    // Floating-point Calculator
    Calculator<double> doubleCalc(12.5, 4.2);
    cout << "Floating-Point Calculator:" << endl;
    doubleCalc.displayNumbers();
    cout << "Addition: " << doubleCalc.add() << endl;
    cout << "Subtraction: " << doubleCalc.subtract() << endl;
    cout << "Multiplication: " << doubleCalc.multiply() << endl;
    cout << "Division: " << doubleCalc.divide() << endl;

    return 0;
}
