                      #include <iostream>
#include <string>
using namespace std;

// Base class: Vehicles
class Vehicles {
protected:
    float price;
public:
    void setPrice(float p) {
        price = p;
    }
    float getPrice() const {
        return price;
    }
};

// Derived class: Car
class Car : public Vehicles {
protected:
    int seatingCapacity;
    int numberOfDoors;
    string fuelType;
public:
    void setCarDetails(int seating, int doors, const string& fuel) {
        seatingCapacity = seating;
        numberOfDoors = doors;
        fuelType = fuel;
    }
    void displayCarDetails() const {
        cout << "Price: $" << price << endl;
        cout << "Seating Capacity: " << seatingCapacity << endl;
        cout << "Number of Doors: " << numberOfDoors << endl;
        cout << "Fuel Type: " << fuelType << endl;
    }
};

// Derived class: Motorcycle
class Motorcycle : public Vehicles {
protected:
    int numberOfCylinders;
    int numberOfGears;
    int numberOfWheels;
public:
    void setMotorcycleDetails(int cylinders, int gears, int wheels) {
        numberOfCylinders = cylinders;
        numberOfGears = gears;
        numberOfWheels = wheels;
    }
    void displayMotorcycleDetails() const {
        cout << "Price: $" << price << endl;
        cout << "Number of Cylinders: " << numberOfCylinders << endl;
        cout << "Number of Gears: " << numberOfGears << endl;
        cout << "Number of Wheels: " << numberOfWheels << endl;
    }
};

// Subclass: Audi
class Audi : public Car {
private:
    string modelType;
public:
    void setModelType(const string& model) {
        modelType = model;
    }
    void displayAudiDetails() const {
        displayCarDetails();
        cout << "Model Type: " << modelType << endl;
    }
};

// Subclass: Yamaha
class Yamaha : public Motorcycle {
private:
    string makeType;
public:
    void setMakeType(const string& make) {
        makeType = make;
    }
    void displayYamahaDetails() const {
        displayMotorcycleDetails();
        cout << "Make Type: " << makeType << endl;
    }
};

int main() {
    // Create an Audi car object
    Audi audiCar;
    audiCar.setPrice(50000);
    audiCar.setCarDetails(5, 4, "Petrol");
    audiCar.setModelType("A4");
    cout << "Audi Car Details:" << endl;
    audiCar.displayAudiDetails();

    cout << endl;

    // Create a Yamaha motorcycle object
    Yamaha yamahaBike;
    yamahaBike.setPrice(15000);
    yamahaBike.setMotorcycleDetails(2, 6, 2);
    yamahaBike.setMakeType("YZF R1");
    cout << "Yamaha Motorcycle Details:" << endl;
    yamahaBike.displayYamahaDetails();

    return 0;
}



#include <iostream>
using namespace std;

// Base class: Animal
class Animal {
public:
    virtual void make_sound() const {
        cout << "Animal makes a sound" << endl;
    }
};

// Subclass: Dog
class Dog : public Animal {
public:
    void make_sound() const override {
        cout << "Dog barks" << endl;
    }
};

// Subclass: Cat
class Cat : public Animal {
public:
    void make_sound() const override {
        cout << "Cat meows" << endl;
    }
};

int main() {
    // Create objects of subclasses
    Animal* animal1 = new Dog(); // Polymorphic behavior
    Animal* animal2 = new Cat(); // Polymorphic behavior

    // Call overridden methods
    animal1->make_sound(); // Calls Dog's make_sound
    animal2->make_sound(); // Calls Cat's make_sound

    // Clean up
    delete animal1;
    delete animal2;

    return 0;
}
