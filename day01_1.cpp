user.h

#pragma once
#include <iostream>
#include <string>
using namespace std;

class User {
	string password;
protected:
	string username;
public:
	User(string name,string id):username(name),password(password){}
	void virtual display() = 0;
	string getUsername() {
		return this->username;
	}
	bool checkCredentials(string username, string password) {
		if (this->username != username || this->password != password) {
			return false;
		}
		return true;
	}
};

class Buyer : public User {
public:
	void display() {
		cout << username << endl;
	}
};

class Seller : public User {
public:
	void display() {
		cout << username << endl;
	}
};




bid.h
#pragma once
#include <iostream>
#include <chrono>
using namespace std;

class Bid {
	string bidId;
	int amount;
	chrono::system_clock::time_point time;
public:
	Bid(string id, int amt) :bidId(id), amount(amt), time(chrono::system_clock::now()){}

	bool operator<(Bid& other) {
		return amount < other.amount;
	}
};



aution.h
#pragma once
#include <iostream>
#include <queue>
#include <mutex>
#include <Bid.h>
using namespace std;

class Auction {
	string itemId;
	string seller;
	int minPrice;
	bool status;
	priority_queue<Bid>bids;
	mutex mtx;
	chrono::system_clock::time_point limit;
};




#include <iostream>

#include <thread>

#include <unordered_map>

#include <map>

#include <vector>

#include <queue>

#include <mutex>

#include <set>

#include <fstream>

#include <chrono>

#include <ctime>

#include <string>



using namespace std;



class User {

public:

    string userId;

    string name;

    User(string id, string n) : userId(id), name(n) {}

    virtual void menu() = 0;

};



class Buyer : public User {

public:

    Buyer(string id, string name) : User(id, name) {}

    void menu() override {

        cout << "Buyer Menu: You can place bids.\n";

    }

};



class Seller : public User {

public:

    Seller(string id, string name) : User(id, name) {}

    void menu() override {

        cout << "Seller Menu: You can create auctions.\n";

    }

};



class Bid {

public:

    string bidderId;

    double amount;

    chrono::system_clock::time_point timestamp;



    Bid(string id, double amt)

        : bidderId(id), amount(amt), timestamp(chrono::system_clock::now()) {}



    bool operator<(const Bid& other) const {

        return amount < other.amount;

    }

};





class Auction {

public:

    string itemId;

    string sellerId;

    double minPrice;

    bool active;

    priority_queue<Bid> bids;

    set<string> activeBidders;

    mutex auctionMutex;

    chrono::system_clock::time_point endTime;



    Auction(string item, string seller, double price, int durationSeconds)

        : itemId(item), sellerId(seller), minPrice(price), active(true) {

        endTime = chrono::system_clock::now() + chrono::seconds(durationSeconds);

    }



    bool isActive() {

        lock_guard<mutex> lock(auctionMutex);

        return active && chrono::system_clock::now() < endTime;

    }



    void placeBid(const Bid& bid) {

        lock_guard<mutex> lock(auctionMutex);

        if (isActive() && bid.amount >= minPrice) {

            bids.push(bid);

            activeBidders.insert(bid.bidderId);

            cout << "Bid placed: " << bid.bidderId << " -> $" << bid.amount << endl;

            logBid(bid);

        }

        else {

            cout << "Bid rejected for item " << itemId << endl;

        }

    }



    void closeAuction() {

        lock_guard<mutex> lock(auctionMutex);

        if (!active) return;

        active = false;

        ofstream file("results.txt", ios::app);

        file << "Auction Closed for Item: " << itemId << "\n";

        if (!bids.empty()) {

            Bid topBid = bids.top();

            file << "Winner: " << topBid.bidderId << " with $" << topBid.amount << "\n";

        }

        else {

            file << "No bids received.\n";

        }

        file.close();

    }



    void logBid(const Bid& bid) {

        ofstream log("bids_log.txt", ios::app);

        auto time = chrono::system_clock::to_time_t(bid.timestamp);

        log << "Item: " << itemId << ", Bidder: " << bid.bidderId

            << ", Amount: $" << bid.amount << ", Time: " << ctime(&time);

        log.close();

    }

};



unordered_map<string, shared_ptr<Auction>> auctions;

mutex globalMutex;



void auctionScheduler() {

    while (true) {

        this_thread::sleep_for(chrono::seconds(5));

        lock_guard<mutex> lock(globalMutex);

        for (auto& auc : auctions) {

            if (!auc.second->isActive()) {

                auc.second->closeAuction();

            }

        }

    }

}





int main() {

    thread scheduler(auctionScheduler);

    scheduler.detach();



    cout << "Welcome to OAP_SIM\n";

    string id, name, role;

    cout << "Enter ID: "; cin >> id;

    cout << "Enter Name: "; cin >> name;

    cout << "Are you Buyer or Seller? "; cin >> role;



    User* user = nullptr;

    if (role == "Buyer")

        user = new Buyer(id, name);

    else if (role == "Seller")

        user = new Seller(id, name);

    else {

        cout << "Invalid role!\n";

        return 1;

    }



    user->menu();



    while (true) {

        int choice;

        cout << "\n1. Create Auction\n2. Place Bid\n3. Exit\nChoice: ";

        cin >> choice;



        if (choice == 1 && role == "Seller") {

            string itemId;

            double price;

            int duration;

            cout << "Item ID: "; cin >> itemId;

            cout << "Min Price: "; cin >> price;

            cout << "Duration (sec): "; cin >> duration;

            lock_guard<mutex> lock(globalMutex);

            auctions[itemId] = make_shared<Auction>(itemId, id, price, duration);

            cout << "Auction created for item: " << itemId << "\n";

        }

        else if (choice == 2 && role == "Buyer") {

            string itemId;

            double amount;

            cout << "Item ID: "; cin >> itemId;

            cout << "Bid Amount: "; cin >> amount;

            lock_guard<mutex> lock(globalMutex);

            if (auctions.find(itemId) != auctions.end()) {

                auctions[itemId]->placeBid(Bid(id, amount));         

            }

            else {

                cout << "Auction not found.\n";

            }

        }

        else if (choice == 3) {

            break;

        }

        else {

            cout << "Invalid choice or action for this role.\n";

        }

    }



    delete user;

    return 0;

}







#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <memory>
#include <mutex>
#include <thread>
#include <chrono>

// Auction class
class Auction {
private:
    std::string itemName;
    double minPrice;
    double highestBid;
    std::string highestBidder;
    std::mutex auctionMutex;

public:
    // Constructor
    Auction(const std::string& name, double price)
        : itemName(name), minPrice(price), highestBid(0.0), highestBidder("None") {}

    // Deleted copy constructor and assignment operator (due to std::mutex)
    Auction(const Auction&) = delete;
    Auction& operator=(const Auction&) = delete;

    // Place a bid
    bool placeBid(const std::string& bidderName, double bidAmount, std::ofstream& logFile) {
        std::lock_guard<std::mutex> lock(auctionMutex);
        if (highestBidder == "CLOSED") {
            logFile << "[INFO] Auction is closed. Bid rejected for item: " << itemName << "\n";
            return false;
        }
        if (bidAmount <= highestBid || bidAmount < minPrice) {
            logFile << "[INFO] Bid too low. Bid rejected for item: " << itemName << "\n";
            return false;
        }
        highestBid = bidAmount;
        highestBidder = bidderName;
        logFile << "[SUCCESS] Bid placed! " << bidderName << " is leading with $"
                << bidAmount << " on item: " << itemName << "\n";
        return true;
    }

    // Close auction
    void closeAuction(std::ofstream& logFile) {
        std::lock_guard<std::mutex> lock(auctionMutex);
        if (highestBidder == "CLOSED") {
            logFile << "[INFO] Auction already closed for item: " << itemName << "\n";
            return;
        }
        if (highestBidder == "None") {
            logFile << "[RESULT] Auction closed for item: " << itemName << ". No bids placed.\n";
        } else {
            logFile << "[RESULT] Auction closed for item: " << itemName
                    << ". Winner: " << highestBidder << " with bid: $" << highestBid << "\n";
        }
        highestBidder = "CLOSED";
    }
};

// AuctionManager class
class AuctionManager {
private:
    std::unordered_map<std::string, std::unique_ptr<Auction>> auctions;
    std::ofstream logFile;

public:
    AuctionManager(const std::string& logFileName) {
        logFile.open(logFileName, std::ios::app);
        if (!logFile.is_open()) {
            std::cerr << "Error: Could not open log file. Exiting...\n";
            exit(1);
        }
    }

    ~AuctionManager() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }

    void addAuction(const std::string& id, const std::string& name, double minPrice) {
        if (auctions.find(id) != auctions.end()) {
            std::cout << "[ERROR] Auction ID already exists.\n";
            logFile << "[ERROR] Duplicate Auction ID: " << id << "\n";
            return;
        }
        auctions[id] = std::make_unique<Auction>(name, minPrice);
        logFile << "[INFO] Auction added: " << name << " (ID: " << id
                << ") with minimum price $" << minPrice << "\n";
        std::cout << "Auction added successfully: " << name << " with minimum price $" << minPrice << "\n";
    }

    void placeBid(const std::string& id, const std::string& bidderName, double bidAmount) {
        auto it = auctions.find(id);
        if (it != auctions.end()) {
            it->second->placeBid(bidderName, bidAmount, logFile);
        } else {
            std::cout << "[ERROR] Invalid Auction ID.\n";
        }
    }

    void startAuctionTimer(const std::string& id, int seconds) {
        if (auctions.find(id) == auctions.end()) {
            std::cout << "[ERROR] Invalid Auction ID.\n";
            return;
        }
        std::thread([this, id, seconds]() {
            std::this_thread::sleep_for(std::chrono::seconds(seconds));
            auctions[id]->closeAuction(logFile);
        }).detach();
    }

    void viewLog() {
        std::ifstream log("auction_log.txt");
        if (!log.is_open()) {
            std::cout << "[ERROR] Could not open log file.\n";
            return;
        }
        std::string line;
        while (std::getline(log, line)) {
            std::cout << line << "\n";
        }
    }
};

// Simple CLI
void auctionCLI() {
    AuctionManager manager("auction_log.txt");
    int choice;

    do {
        std::cout << "\nMenu:\n"
                  << "1. Add Auction\n"
                  << "2. Place Bid\n"
                  << "3. Start Auction Timer\n"
                  << "4. View Logs\n"
                  << "5. Exit\n"
                  << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1) {
            std::string id, name;
            double price;
            std::cout << "Enter Auction ID: ";
            std::cin >> id;
            std::cout << "Enter Item Name: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << "Enter Minimum Price: ";
            std::cin >> price;
            manager.addAuction(id, name, price);
        } else if (choice == 2) {
            std::string id, bidder;
            double amount;
            std::cout << "Enter Auction ID: ";
            std::cin >> id;
            std::cout << "Enter Bidder Name: ";
            std::cin >> bidder;
            std::cout << "Enter Bid Amount: ";
            std::cin >> amount;
            manager.placeBid(id, bidder, amount);
        } else if (choice == 3) {
            std::string id;
            int duration;
            std::cout << "Enter Auction ID: ";
            std::cin >> id;
            std::cout << "Enter Timer Duration (in seconds): ";
            std::cin >> duration;
            manager.startAuctionTimer(id, duration);
        } else if (choice == 4) {
            manager.viewLog();
        } else if (choice == 5) {
            std::cout << "Exiting program. Goodbye!\n";
        } else {
            std::cout << "[ERROR] Invalid choice.\n";
        }
    } while (choice != 5);
}

// Main function
int main() {
    auctionCLI();
    return 0;
    }





#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <thread>
#include <mutex>
#include <queue>
#include <vector>

// Auction class
class Auction {
private:
    std::string itemName;
    double minPrice;
    double highestBid;
    std::string highestBidder;
    std::mutex auctionMutex; // To handle concurrent bids safely

public:
    // Default Constructor
    Auction() : itemName(""), minPrice(0.0), highestBid(0.0), highestBidder("None") {}

    // Parameterized Constructor
    Auction(const std::string& name, double price) 
        : itemName(name), minPrice(price), highestBid(0.0), highestBidder("None") {}

    // Place a bid
    bool placeBid(const std::string& bidderName, double bidAmount, std::ofstream& logFile) {
        std::lock_guard<std::mutex> lock(auctionMutex);

        if (highestBidder == "CLOSED") {
            logFile << "[INFO] Auction is closed. Bid rejected for item: " << itemName << "\n";
            return false;
        }

        if (bidAmount <= highestBid || bidAmount < minPrice) {
            logFile << "[INFO] Bid too low. Bid rejected for item: " << itemName << "\n";
            return false;
        }

        highestBid = bidAmount;
        highestBidder = bidderName;
        logFile << "[SUCCESS] New highest bid of $" << bidAmount 
                << " placed by " << bidderName << " for item: " << itemName << "\n";
        return true;
    }

    // Close the auction
    void closeAuction(std::ofstream& logFile) {
        std::lock_guard<std::mutex> lock(auctionMutex);

        if (highestBidder == "CLOSED") {
            logFile << "[INFO] Auction already closed for item: " << itemName << "\n";
            return;
        }

        if (highestBidder == "None") {
            logFile << "[RESULT] No bids placed for item: " << itemName << "\n";
        } else {
            logFile << "[RESULT] Auction closed for item: " << itemName 
                    << ". Winner: " << highestBidder 
                    << " with bid: $" << highestBid << "\n";
        }

        highestBidder = "CLOSED";
    }
};

// AuctionManager class
class AuctionManager {
private:
    std::unordered_map<std::string, Auction> auctions; // Stores all auctions
    std::ofstream logFile;

public:
    AuctionManager(const std::string& logFileName) {
        logFile.open(logFileName, std::ios::app);
        if (!logFile.is_open()) {
            std::cerr << "Error: Could not open log file.\n";
            exit(1);
        }
    }

    ~AuctionManager() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }

    void addAuction(const std::string& id, const std::string& name, double minPrice) {
        if (auctions.find(id) != auctions.end()) {
            std::cout << "[ERROR] Auction ID already exists.\n";
            return;
        }
        auctions[id] = Auction(name, minPrice);
        logFile << "[INFO] Auction added: " << name << " (ID: " << id << ") with min price: $" << minPrice << "\n";
        std::cout << "Auction added successfully.\n";
    }

    void placeBid(const std::string& id, const std::string& bidderName, double bidAmount) {
        if (auctions.find(id) == auctions.end()) {
            std::cout << "[ERROR] Invalid Auction ID.\n";
            return;
        }
        auctions[id].placeBid(bidderName, bidAmount, logFile);
    }

    void startAuctionTimer(const std::string& id, int seconds) {
        if (auctions.find(id) == auctions.end()) {
            std::cout << "[ERROR] Invalid Auction ID.\n";
            return;
        }

        std::thread([this, id, seconds]() {
            std::this_thread::sleep_for(std::chrono::seconds(seconds));
            auctions[id].closeAuction(logFile);
        }).detach();
    }

    void viewLogs() const {
        std::ifstream log("auction_log.txt");
        if (!log.is_open()) {
            std::cout << "[ERROR] Could not open log file.\n";
            return;
        }
        std::string line;
        while (std::getline(log, line)) {
            std::cout << line << "\n";
        }
    }
};

// Simple CLI for the AuctionManager
void auctionCLI() {
    AuctionManager manager("auction_log.txt");
    int choice;

    do {
        std::cout << "\nMenu:\n"
                  << "1. Add Auction\n"
                  << "2. Place Bid\n"
                  << "3. Start Auction Timer\n"
                  << "4. View Logs\n"
                  << "5. Exit\n"
                  << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1) {
            std::string id, name;
            double minPrice;
            std::cout << "Enter Auction ID: ";
            std::cin >> id;
            std::cout << "Enter Item Name: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << "Enter Minimum Price: ";
            std::cin >> minPrice;
            manager.addAuction(id, name, minPrice);
        } else if (choice == 2) {
            std::string id, bidder;
            double amount;
            std::cout << "Enter Auction ID: ";
            std::cin >> id;
            std::cout << "Enter Bidder Name: ";
            std::cin >> bidder;
            std::cout << "Enter Bid Amount: ";
            std::cin >> amount;
            manager.placeBid(id, bidder, amount);
        } else if (choice == 3) {
            std::string id;
            int duration;
            std::cout << "Enter Auction ID: ";
            std::cin >> id;
            std::cout << "Enter Timer Duration (seconds): ";
            std::cin >> duration;
            manager.startAuctionTimer(id, duration);
        } else if (choice == 4) {
            manager.viewLogs();
        } else if (choice == 5) {
            std::cout << "Exiting the program. Goodbye!\n";
        } else {
            std::cout << "[ERROR] Invalid choice. Try again.\n";
        }
    } while (choice != 5);
}

// Main function
int main() {
    auctionCLI();
    return 0;
}
