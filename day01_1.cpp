#include <iostream>
#include <string>
using namespace std;

class Flight {
private:
    string flightNumber; // Flight number
    int totalSeats;      // Total number of seats on the flight
    int bookedSeats;     // Number of seats already booked

public:
    // Getter and setter for flightNumber
    void setFlightNumber(const string& number) {
        flightNumber = number;
    }

    string getFlightNumber() const {
        return flightNumber;
    }

    // Getter and setter for totalSeats
    void setTotalSeats(int seats) {
        totalSeats = seats;
    }

    int getTotalSeats() const {
        return totalSeats;
    }

    // Getter and setter for bookedSeats
    void setBookedSeats(int seats) {
        bookedSeats = seats;
    }

    int getBookedSeats() const {
        return bookedSeats;
    }

    // Method to book seats
    bool bookSeats(int seats) {
        if (seats > 0 && bookedSeats + seats <= totalSeats) {
            bookedSeats += seats;
            return true; // Booking successful
        }
        return false; // Booking failed
    }

    // Method to show availability
    int getAvailableSeats() const {
        return totalSeats - bookedSeats;
    }

    void displayDetails() const {
        cout << "Flight: " << flightNumber
             << " | Seats Available: " << getAvailableSeats() << endl;
    }
};

int main() {
    // Create a flight object
    Flight f1;
    f1.setFlightNumber("AI203");
    f1.setTotalSeats(100);
    f1.setBookedSeats(0);

    // Test Case 1
    cout << "\nTest Case 1:\n";
    if (f1.bookSeats(30)) {
        cout << "30 seats booked successfully.\n";
    } else {
        cout << "Booking failed.\n";
    }
    f1.displayDetails();

    // Test Case 2
    cout << "\nTest Case 2:\n";
    if (f1.bookSeats(80)) {
        cout << "80 seats booked successfully.\n";
    } else {
        cout << "Booking failed.\n";
    }
    f1.displayDetails();

    return 0;
}




#include <iostream>
#include <string>
using namespace std;

class HotelRoom {
private:
    int roomNumber;       // Room number
    string type;          // Room type (AC/Non-AC)
    bool isBooked;        // Booking status

public:
    // Setters
    void setRoomNumber(int number) {
        roomNumber = number;
    }

    void setType(const string& roomType) {
        type = roomType;
    }

    void setIsBooked(bool status) {
        isBooked = status;
    }

    // Getters
    int getRoomNumber() const {
        return roomNumber;
    }

    string getType() const {
        return type;
    }

    bool getIsBooked() const {
        return isBooked;
    }

    // Method to book the room
    void bookRoom() {
        if (getIsBooked()) {
            cout << "Room " << getRoomNumber() << " (" << getType() << ") is already booked.\n";
        } else {
            setIsBooked(true);
            cout << "Room " << getRoomNumber() << " (" << getType() << ") is now booked.\n";
        }
    }

    // Method to show the booking status
    void showStatus() const {
        cout << "Room " << getRoomNumber() << " (" << getType() << ") is "
             << (getIsBooked() ? "booked.\n" : "available.\n");
    }
};

int main() {
    // Create a room object and set its details
    HotelRoom h1;
    h1.setRoomNumber(201);
    h1.setType("AC");
    h1.setIsBooked(false);

    // Test Case 1
    cout << "Test Case 1:\n";
    h1.bookRoom();        // Book the room
    h1.showStatus();      // Show the room status

    // Test Case 2
    cout << "\nTest Case 2:\n";
    h1.bookRoom();        // Attempt to book an already booked room
    h1.showStatus();      // Show the room status

    return 0;
}





#include <iostream>
#include <string>
using namespace std;

class DeliveryTip {
private:
    string orderID;      // Order ID
    float billAmount;    // Food bill amount
    float distance;      // Delivery distance in km
    float tip;           // Calculated tip

public:
    // Setter for orderID
    void setOrderID(const string& id) {
        orderID = id;
    }

    // Getter for orderID
    string getOrderID() const {
        return orderID;
    }

    // Setter for billAmount
    void setBillAmount(float bill) {
        billAmount = bill;
    }

    // Getter for billAmount
    float getBillAmount() const {
        return billAmount;
    }

    // Setter for distance
    void setDistance(float dist) {
        distance = dist;
    }

    // Getter for distance
    float getDistance() const {
        return distance;
    }

    // Getter for tip
    float getTip() const {
        return tip;
    }

    // Method to calculate the tip
    void calculateTip() {
        if (distance < 5) {
            tip = billAmount * 0.05; // 5% of bill
        } else if (distance <= 10) {
            tip = billAmount * 0.10; // 10% of bill
        } else {
            tip = billAmount * 0.15;
