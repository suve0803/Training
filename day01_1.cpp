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
