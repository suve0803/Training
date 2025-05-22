#include <iostream>
#include <string>
using namespace std;

class Item {
private:
    int id;
    string name;
    double price;
    int quantity;

public:
    // Function to set item details
    void setDetails(int itemId, string itemName, double itemPrice, int itemQuantity) {
        id = itemId;
        name = itemName;
        price = itemPrice;
        quantity = itemQuantity;
    }

    // Function to display item details
    void display() {
        cout << "ID: " << id << ", Name: " << name << ", Price: " << price
             << ", Quantity: " << quantity << endl;
    }

    // Getter functions
    int getId() { return id; }
    string getName() { return name; }
    double getPrice() { return price; }
    int getQuantity() { return quantity; }

    // Update quantity after sale
    void reduceQuantity(int qty) { quantity -= qty; }
};

class RetailShop {
private:
    Item inventory[100]; // Array to store items
    int itemCount;       // Number of items in the inventory

public:
    // Constructor to initialize item count
    RetailShop() { itemCount = 0; }

    // Function to add an item to inventory
    void addItem() {
        int id, quantity;
        string name;
        double price;

        cout << "Enter item ID: ";
        cin >> id;
        cout << "Enter item name: ";
        cin >> name;
        cout << "Enter item price: ";
        cin >> price;
        cout << "Enter item quantity: ";
        cin >> quantity;

        inventory[itemCount].setDetails(id, name, price, quantity);
        itemCount++;
        cout << "Item added successfully!\n";
    }

    // Function to display all items
    void displayInventory() {
        cout << "\nInventory:\n";
        for (int i = 0; i < itemCount; i++) {
            inventory[i].display();
        }
    }

    // Function to search for an item by ID
    void searchItem() {
        int id;
        cout << "Enter item ID to search: ";
        cin >> id;

        for (int i = 0; i < itemCount; i++) {
            if (inventory[i].getId() == id) {
                cout << "Item found:\n";
                inventory[i].display();
                return;
            }
        }
        cout << "Item not found!\n";
    }

    // Function to sell an item
    void sellItem() {
        int id, quantity;
        cout << "Enter item ID to sell: ";
        cin >> id;
        cout << "Enter quantity: ";
        cin >> quantity;

        for (int i = 0; i < itemCount; i++) {
            if (inventory[i].getId() == id) {
                if (inventory[i].getQuantity() >= quantity) {
                    double totalPrice = inventory[i].getPrice() * quantity;
                    inventory[i].reduceQuantity(quantity);
                    cout << "Sale successful! Total price: " << totalPrice << endl;
                } else {
                    cout << "Insufficient stock!\n";
                }
                return;
            }
        }
        cout << "Item not found!\n";
    }
};

int main() {
    RetailShop shop;
    int choice;

    do {
        cout << "\nRetail Shop Menu:\n";
        cout << "1. Add Item to Inventory\n";
        cout << "2. Display Inventory\n";
        cout << "3. Search Item\n";
        cout << "4. Sell Item\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            shop.addItem();
            break;
        case 2:
            shop.displayInventory();
            break;
        case 3:
            shop.searchItem();
            break;
        case 4:
            shop.sellItem();
            break;
        case 5:
            cout << "Exiting the system.\n";
            break;
        default:
            cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
