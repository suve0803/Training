#include <iostream>
using namespace std;

// Base class: Animal
class Animal {
public:
    void make_sound() {
        cout << "Animal makes a sound" << endl;
    }
};

// Derived class: Dog
class Dog : public Animal {
public:
    void make_sound() {
        cout << "Dog barks" << endl;
    }
};

// Derived class: Cat
class Cat : public Animal {
public:
    void make_sound() {
        cout << "Cat meows" << endl;
    }
};

int main() {
    // Creating objects of derived classes
    Dog dog;
    Cat cat;

    // Calling overridden methods
    cout << "Dog's sound: ";
    dog.make_sound();

    cout << "Cat's sound: ";
    cat.make_sound();

    return 0;
