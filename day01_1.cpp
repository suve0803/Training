#include <iostream>
#include <string>
using namespace std;

// Base class: Vehicle
class Vehicle {
protected:
    string make;
    string model;

public:
    // Constructor
    Vehicle(string make, string model) : make(make), model(model) {}

    // Methods
    void start() {
        cout << "Starting the " << make << " " << model << endl;
    }

    void stop() {
        cout << "Stopping the " << make << " " << model << endl;
    }
};

// Derived class: Car
class Car : public Vehicle {
private:
    int numberOfDoors;

public:
    // Constructor
    Car(string make, string model, int doors) : Vehicle(make, model), numberOfDoors(doors) {}

    // Method specific to Car
    void honk() {
        cout << "Honking the horn of the " << make << " " << model << endl;
    }
};

// Main class to demonstrate functionality
int main() {
    // Creating a generic vehicle
    Vehicle genericVehicle("Generic", "Vehicle");
    genericVehicle.start();
    genericVehicle.stop();

    cout << endl;

    // Creating a specific car
    Car car("Toyota", "Camry", 4);
    car.start();
    car.honk();
    car.stop();

    return 0;
}
