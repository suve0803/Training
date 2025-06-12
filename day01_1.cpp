#include <iostream>
#include <unordered_map>
#include <set>
#include <vector>
#include <string>
#include <mutex>
#include <queue>

// Auction Class
class Auction {
private:
    std::string itemName;
    double minPrice;
    double highestBid = 0.0;
    std::string highestBidder = "None";
    std::mutex auctionMutex;

    std::priority_queue<std::pair<double, std::string>> bids; // Stores all bids

public:
    Auction(const std::string& name, double price) : itemName(name), minPrice(price) {}

    bool placeBid(const std::string& bidderName, double bidAmount) {
        std::lock_guard<std::mutex> lock(auctionMutex); // Lock for thread safety

        if (bidAmount <= highestBid || bidAmount < minPrice) {
            std::cout << "Bid too low for item: " << itemName << "\n";
            return false;
        }

        highestBid = bidAmount;
        highestBidder = bidderName;
        bids.push({bidAmount, bidderName});
        std::cout << "Bid placed by " << bidderName << " for $" << bidAmount << " on " << itemName << "\n";
        return true;
    }

    void closeAuction() {
        std::lock_guard<std::mutex> lock(auctionMutex);

        if (highestBidder == "None") {
            std::cout << "Auction closed for " << itemName << ". No bids were placed.\n";
        } else {
            std::cout << "Auction closed for " << itemName << ". Winner: " << highestBidder
                      << " with a bid of $" << highestBid << "\n";
        }
    }
};

// Auction Manager Class
class AuctionManager {
private:
    std::unordered_map<std::string, Auction> auctions; // Store all auctions
    std::set<std::string> completedAuctions; // Track completed auctions

public:
    void addAuction(const std::string& id, const std::string& name, double minPrice) {
        if (auctions.find(id) != auctions.end()) {
            std::cout << "Auction ID already exists.\n";
            return;
        }
        auctions[id] = Auction(name, minPrice);
        std::cout << "Auction added for item: " << name << " with minimum price $" << minPrice << "\n";
    }

    void placeBid(const std::string& id, const std::string& bidderName, double bidAmount) {
        auto it = auctions.find(id);
        if (it == auctions.end()) {
            std::cout << "Auction ID not found.\n";
            return;
        }
        it->second.placeBid(bidderName, bidAmount);
    }

    void closeAuction(const std::string& id) {
        auto it = auctions.find(id);
        if (it == auctions.end()) {
            std::cout << "Auction ID not found.\n";
            return;
        }
        it->second.closeAuction();
        completedAuctions.insert(id);
        auctions.erase(it); // Remove auction once closed
    }

    void showCompletedAuctions() {
        std::cout << "Completed Auctions:\n";
        for (const auto& id : completedAuctions) {
            std::cout << "- " << id << "\n";
        }
    }
};

// Simple Auction CLI
void auctionCLI() {
    AuctionManager manager;
    int choice;

    do {
        std::cout << "\nAuction Menu:\n"
                  << "1. Add Auction\n"
                  << "2. Place Bid\n"
                  << "3. Close Auction\n"
                  << "4. Show Completed Auctions\n"
                  << "5. Exit\n"
                  << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1) {
            std::string id, name;
            double price;
            std::cout << "Enter Auction ID: ";
            std::cin >> id;
            std::cin.ignore(); // Clear newline
            std::cout << "Enter Item Name: ";
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
            std::cout << "Enter Auction ID: ";
            std::cin >> id;
            manager.closeAuction(id);
        } else if (choice == 4) {
            manager.showCompletedAuctions();
        } else if (choice == 5) {
            std::cout << "Goodbye!\n";
        } else {
            std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);
}

int main() {
    auctionCLI();
    return 0;
}





#include <iostream>
#include <string>
#include <map>
#include <fstream>
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
    std::mutex auctionMutex; // To handle concurrent bids safely

public:
    Auction(const std::string& itemName, double minPrice)
        : itemName(itemName), minPrice(minPrice), highestBid(0), highestBidder("None") {}

    // Method to place a bid
    bool placeBid(const std::string& bidderName, double bidAmount, std::ofstream& logFile) {
        std::lock_guard<std::mutex> lock(auctionMutex); // Lock to prevent race conditions

        // Check if auction is already closed
        if (highestBidder == "CLOSED") {
            logFile << "[INFO] Auction is closed. Bid rejected for item: " << itemName << "\n";
            return false;
        }

        // Check if bid is too low
        if (bidAmount <= highestBid || bidAmount < minPrice) {
            logFile << "[INFO] Bid too low. Bid rejected for item: " << itemName << "\n";
            return false;
        }

        // Update the highest bid and bidder
        highestBid = bidAmount;
        highestBidder = bidderName;
        logFile << "[SUCCESS] Bid placed! " << bidderName << " is leading with $" 
                << bidAmount << " on item: " << itemName << "\n";
        return true;
    }

    // Method to close the auction
    void closeAuction(std::ofstream& logFile) {
        std::lock_guard<std::mutex> lock(auctionMutex);

        // If already closed, log and return
        if (highestBidder == "CLOSED") {
            logFile << "[INFO] Auction already closed for item: " << itemName << "\n";
            return;
        }

        // Log the auction result
        if (highestBidder == "None") {
            logFile << "[RESULT] Auction closed for item: " << itemName << ". No bids placed.\n";
        } else {
            logFile << "[RESULT] Auction closed for item: " << itemName 
                    << ". Winner: " << highestBidder << " with bid: $" << highestBid << "\n";
        }

        highestBidder = "CLOSED"; // Mark the auction as closed
    }
};

// AuctionManager class
class AuctionManager {
private:
    std::map<std::string, Auction> auctions; // Stores all auctions
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

    void addAuction(const std::string& auctionID, const std::string& itemName, double minPrice) {
        if (auctions.find(auctionID) != auctions.end()) {
            std::cout << "[ERROR] Auction ID already exists.\n";
            logFile << "[ERROR] Failed to add auction. Duplicate Auction ID: " << auctionID << "\n";
            return;
        }

        auctions[auctionID] = Auction(itemName, minPrice);
        logFile << "[INFO] Auction added: " << itemName 
                << " (ID: " << auctionID << ") with minimum price $" << minPrice << "\n";
        std::cout << "Auction added successfully: " << itemName << " with minimum price $" << minPrice << "\n";
    }

    void placeBid(const std::string& auctionID, const std::string& bidderName, double bidAmount) {
        auto it = auctions.find(auctionID);
        if (it != auctions.end()) {
            it->second.placeBid(bidderName, bidAmount, logFile);
        } else {
            std::cout << "[ERROR] Invalid auction ID. Bid not placed.\n";
        }
    }

    void startAuctionTimer(const std::string& auctionID, int seconds) {
        if (auctions.find(auctionID) == auctions.end()) {
            std::cout << "[ERROR] Invalid auction ID. Timer not started.\n";
            return;
        }

        std::thread([this, auctionID, seconds]() {
            std::this_thread::sleep_for(std::chrono::seconds(seconds));
            auctions[auctionID].closeAuction(logFile);
        }).detach(); // Detach to run independently
    }

    void viewLog() {
        std::ifstream log("auction_log.txt");
        if (!log.is_open()) {
            std::cout << "[ERROR] Could not open log file for viewing.\n";
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
            std::cout << "[ERROR] Invalid choice. Please try again.\n";
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
#include <map>
#include <fstream>
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
    Auction(const std::string& itemName, double minPrice)
        : itemName(itemName), minPrice(minPrice), highestBid(0), highestBidder("None") {}

    bool placeBid(const std::string& bidderName, double bidAmount, std::ofstream& logFile) {
        std::lock_guard<std::mutex> lock(auctionMutex);

        if (highestBidder == "CLOSED") {
            logFile << "Auction is closed. Bid rejected for item: " << itemName << "\n";
            return false;
        }
        if (bidAmount <= highestBid || bidAmount < minPrice) {
            logFile << "Bid too low. Bid rejected for item: " << itemName << "\n";
            return false;
        }

        highestBid = bidAmount;
        highestBidder = bidderName;
        logFile << "Bid placed! " << bidderName << " is leading with $" << bidAmount << " on item: " << itemName << "\n";
        return true;
    }

    void closeAuction(std::ofstream& logFile) {
        std::lock_guard<std::mutex> lock(auctionMutex);

        if (highestBidder == "CLOSED") {
            logFile << "Auction already closed for item: " << itemName << "\n";
            return;
        }

        if (highestBidder == "None") {
            logFile << "Auction closed for item: " << itemName << ". No bids placed.\n";
        } else {
            logFile << "Auction closed for item: " << itemName << ". Winner: " << highestBidder << " with bid: $" << highestBid << "\n";
        }

        highestBidder = "CLOSED"; // Marks the auction as closed
    }
};

// AuctionManager class
class AuctionManager {
private:
    std::map<std::string, Auction> auctions;
    std::ofstream logFile;

public:
    AuctionManager(const std::string& logFileName) {
        logFile.open(logFileName, std::ios::app);
        if (!logFile.is_open()) {
            std::cerr << "Error opening log file.\n";
            exit(1);
        }
    }

    ~AuctionManager() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }

    void addAuction(const std::string& auctionID, const std::string& itemName, double minPrice) {
        auctions[auctionID] = Auction(itemName, minPrice);
        logFile << "Auction added: " << itemName << " (ID: " << auctionID << ") with minimum price $" << minPrice << "\n";
        std::cout << "Auction added successfully!\n";
    }

    void placeBid(const std::string& auctionID, const std::string& bidderName, double bidAmount) {
        if (auctions.find(auctionID) != auctions.end()) {
            auctions[auctionID].placeBid(bidderName, bidAmount, logFile);
        } else {
            std::cout << "Invalid auction ID. Bid not placed.\n";
        }
    }

    void startAuctionTimer(const std::string& auctionID, int seconds) {
        if (auctions.find(auctionID) == auctions.end()) {
            std::cout << "Invalid auction ID. Timer not started.\n";
            return;
        }

        std::thread([this, auctionID, seconds]() {
            std::this_thread::sleep_for(std::chrono::seconds(seconds));
            auctions[auctionID].closeAuction(logFile);
        }).detach();
    }

    void viewLog() {
        std::ifstream log("auction_log.txt");
        if (!log.is_open()) {
            std::cout << "Error opening log file.\n";
            return;
        }
        std::string line;
        while (getline(log, line)) {
            std::cout << line << "\n";
        }
    }
};

// Simple CLI
void auctionCLI() {
    AuctionManager manager("auction_log.txt");
    int choice;

    do {
        std::cout << "\n1. Add Auction\n2. Place Bid\n3. Start Auction Timer\n4. View Logs\n5. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        if (choice == 1) {
            std::string id, name;
            double price;
            std::cout << "Enter Auction ID: ";
            std::cin >> id;
            std::cout << "Enter Item Name: ";
            std::cin.ignore();
            getline(std::cin, name);
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
            std::cout << "Exiting... Goodbye!\n";
        } else {
            std::cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 5);
}

// Main function
int main() {
    auctionCLI();
    return 0;
}






.#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>

class Task {
public:
    Task(const std::string& id = "", int load = 0) : id(id), load(load) {}

    std::string getId() const {
        return id;
    }

    int getLoad() const {
        return load;
    }

    bool isValid() const {
        return !id.empty(); // Check if the task is valid based on its ID
    }

private:
    std::string id;
    int load;
};

class TaskQueue {
public:
    void push(Task task) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            tasks.push(task);
        }
        cv.notify_one();
    }

    Task pop() {
        std::lock_guard<std::mutex> lock(mtx);
        if (tasks.empty()) {
            return Task(); // Return a default Task if empty
        }
        Task task = tasks.front();
        tasks.pop();
        return task;
    }

    void waitForTask() {
        while (true) {
            {
                std::lock_guard<std::mutex> lock(mtx);
                if (!tasks.empty()) {
                    return; // Exit if tasks are available
                }
            }
            // Busy wait until a task is available
            std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Sleep briefly to avoid busy-waiting too aggressively
        }
    }

private:
    std::queue<Task> tasks; // Use a regular queue for tasks
    std::mutex mtx;
    std::condition_variable cv;
};

class LoadBalancer {
public:
    LoadBalancer(const std::string& filename) {
        readTasksFromFile(filename);
    }

    void start(int cpuCount) {
        // Create CPU threads
        for (int i = 1; i <= cpuCount; ++i) {
            cpus.emplace_back(&LoadBalancer::cpuWorker, this, i);
        }

        // Wait for all threads to finish
        for (auto &cpu : cpus) {
            cpu.join();
        }

        std::cout << "All tasks completed.\n";
    }

private:
    std::vector<std::thread> cpus;
    TaskQueue taskQueue;

    void readTasksFromFile(const std::string& filename) {
        std::ifstream inputFile(filename);
        if (!inputFile.is_open()) {
            std::cerr << "Error opening input file.\n";
            exit(1);
        }

        std::string line;
        int cpuCount = 0;

        // Read CPU count
        std::getline(inputFile, line);
        std::istringstream(line.substr(6)) >> cpuCount;

        // Read tasks
        while (std::getline(inputFile, line)) {
            std::string taskId = line.substr(0, line.find(':'));
            int load = std::stoi(line.substr(line.find_last_of(' ') + 1));
            taskQueue.push(Task(taskId, load));
        }

        inputFile.close();
    }

    void cpuWorker(int cpuId) {
        while (true) {
            Task task; // Create a default task

            // Wait for a task to be available
            taskQueue.waitForTask();

            // Attempt to pop a task
            task = taskQueue.pop();

            // Check if the task is valid
            if (!task.isValid()) {
                break; // Exit if no more valid tasks
            }

            // Simulate task processing
            std::cout << "CPU-" << cpuId << " picked Task " << task.getId() << " (Load: " << task.getLoad() << ")\n";
            std::this_thread::sleep_for(std::chrono::seconds(task.getLoad()));
            std::cout << "CPU-" << cpuId << " finished Task " << task.getId() << "\n";
        }
    }
};

int main() {
    LoadBalancer loadBalancer("input.txt");
    loadBalancer.start(3); // Start with 3 CPUs (or read from the file)
    return 0;
}




#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <stdexcept>

class Task {
public:
    Task(const std::string& id, int load) : id(id), load(load) {}

    std::string getId() const {
        return id;
    }

    int getLoad() const {
        return load;
    }

private:
    std::string id;
    int load;
};

class TaskQueue {
public:
    void push(Task task) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            tasks.push(task);
        }
        cv.notify_one();
    }

    Task pop() {
        std::lock_guard<std::mutex> lock(mtx);
        if (tasks.empty()) {
            throw std::runtime_error("No tasks available"); // Throw exception if empty
        }
        Task task = tasks.front();
        tasks.pop();
        return task;
    }

    void waitForTask() {
        while (true) {
            {
                std::lock_guard<std::mutex> lock(mtx);
                if (!tasks.empty()) {
                    return; // Exit if tasks are available
                }
            }
            // Busy wait until a task is available
            std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Sleep briefly to avoid busy-waiting too aggressively
        }
    }

private:
    std::queue<Task> tasks; // Use a regular queue for tasks
    std::mutex mtx;
    std::condition_variable cv;
};

class LoadBalancer {
public:
    LoadBalancer(const std::string& filename) {
        readTasksFromFile(filename);
    }

    void start(int cpuCount) {
        // Create CPU threads
        for (int i = 1; i <= cpuCount; ++i) {
            cpus.emplace_back(&LoadBalancer::cpuWorker, this, i);
        }

        // Wait for all threads to finish
        for (auto &cpu : cpus) {
            cpu.join();
        }

        std::cout << "All tasks completed.\n";
    }

private:
    std::vector<std::thread> cpus;
    TaskQueue taskQueue;

    void readTasksFromFile(const std::string& filename) {
        std::ifstream inputFile(filename);
        if (!inputFile.is_open()) {
            std::cerr << "Error opening input file.\n";
            exit(1);
        }

        std::string line;
        int cpuCount = 0;

        // Read CPU count
        std::getline(inputFile, line);
        std::istringstream(line.substr(6)) >> cpuCount;

        // Read tasks
        while (std::getline(inputFile, line)) {
            std::string taskId = line.substr(0, line.find(':'));
            int load = std::stoi(line.substr(line.find_last_of(' ') + 1));
            taskQueue.push(Task(taskId, load));
        }

        inputFile.close();
    }

    void cpuWorker(int cpuId) {
        while (true) {
            Task task("", 0); // Create a default task

            // Wait for a task to be available
            taskQueue.waitForTask();

            try {
                // Attempt to pop a task
                task = taskQueue.pop();
            } catch (const std::runtime_error& e) {
                break; // Exit if no more tasks
            }

            // Simulate task processing
            std::cout << "CPU-" << cpuId << " picked Task " << task.getId() << " (Load: " << task.getLoad() << ")\n";
            std::this_thread::sleep_for(std::chrono::seconds(task.getLoad()));
            std::cout << "CPU-" << cpuId << " finished Task " << task.getId() << "\n";
        }
    }
};

int main() {
    LoadBalancer loadBalancer("input.txt");
    loadBalancer.start(3); // Start with 3 CPUs (or read from the file)
    return 0;
}






#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <stdexcept>

class Task {
public:
    Task(const std::string& id, int load) : id(id), load(load) {}

    std::string getId() const {
        return id;
    }

    int getLoad() const {
        return load;
    }

    // Comparison operator for priority queue
    bool operator<(const Task& other) const {
        return load < other.load; // Higher load has higher priority
    }

private:
    std::string id;
    int load;
};

class TaskQueue {
public:
    void push(Task task) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            tasks.push(task);
        }
        cv.notify_one();
    }

    Task pop() {
        std::lock_guard<std::mutex> lock(mtx);
        if (tasks.empty()) {
            throw std::runtime_error("No tasks available"); // Throw exception if empty
        }
        Task task = tasks.top();
        tasks.pop();
        return task;
    }

    void waitForTask() {
        while (true) {
            {
                std::lock_guard<std::mutex> lock(mtx);
                if (!tasks.empty()) {
                    return; // Exit if tasks are available
                }
            }
            // Busy wait until a task is available
            std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Sleep briefly to avoid busy-waiting too aggressively
        }
    }

private:
    std::priority_queue<Task> tasks; // Use priority queue for tasks
    std::mutex mtx;
    std::condition_variable cv;
};

class LoadBalancer {
public:
    LoadBalancer(const std::string& filename) {
        readTasksFromFile(filename);
    }

    void start(int cpuCount) {
        // Create CPU threads
        for (int i = 1; i <= cpuCount; ++i) {
            cpus.emplace_back(&LoadBalancer::cpuWorker, this, i);
        }

        // Wait for all threads to finish
        for (auto &cpu : cpus) {
            cpu.join();
        }

        std::cout << "All tasks completed.\n";
    }

private:
    std::vector<std::thread> cpus;
    TaskQueue taskQueue;

    void readTasksFromFile(const std::string& filename) {
        std::ifstream inputFile(filename);
        if (!inputFile.is_open()) {
            std::cerr << "Error opening input file.\n";
            exit(1);
        }

        std::string line;
        int cpuCount = 0;

        // Read CPU count
        std::getline(inputFile, line);
        std::istringstream(line.substr(6)) >> cpuCount;

        // Read tasks
        while (std::getline(inputFile, line)) {
            std::string taskId = line.substr(0, line.find(':'));
            int load = std::stoi(line.substr(line.find_last_of(' ') + 1));
            taskQueue.push(Task(taskId, load));
        }

        inputFile.close();
    }

    void cpuWorker(int cpuId) {
        while (true) {
            Task task("", 0); // Create a default task

            // Wait for a task to be available
            taskQueue.waitForTask();

            try {
                // Attempt to pop a task
                task = taskQueue.pop();
            } catch (const std::runtime_error& e) {
                break; // Exit if no more tasks
            }

            // Simulate task processing
            std::cout << "CPU-" << cpuId << " picked Task " << task.getId() << " (Load: " << task.getLoad() << ")\n";
            std::this_thread::sleep_for(std::chrono::seconds(task.getLoad()));
            std::cout << "CPU-" << cpuId << " finished Task " << task.getId() << "\n";
        }
    }
};

int main() {
    LoadBalancer loadBalancer("input.txt");
    loadBalancer.start(3); // Start with 3 CPUs (or read from the file)
    return 0;
}





#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>

struct Task {
    std::string id;
    int load;
};

class TaskQueue {
public:
    void push(Task task) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            tasks.push(task);
        }
        cv.notify_one();
    }

    bool pop(Task &task) {
        std::lock_guard<std::mutex> lock(mtx);
        if (tasks.empty()) {
            return false;
        }
        task = tasks.front();
        tasks.pop();
        return true;
    }

    bool isEmpty() {
        std::lock_guard<std::mutex> lock(mtx);
        return tasks.empty();
    }

    void waitForTask() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this] { return !tasks.empty(); });
    }

private:
    std::queue<Task> tasks;
    std::mutex mtx;
    std::condition_variable cv;
};

void cpuWorker(int cpuId, TaskQueue &taskQueue) {
    while (true) {
        Task task;

        // Wait for a task to be available
        taskQueue.waitForTask();

        // Attempt to pop a task
        if (!taskQueue.pop(task)) {
            break; // Exit if no more tasks
        }

        // Simulate task processing
        std::cout << "CPU-" << cpuId << " picked Task " << task.id << " (Load: " << task.load << ")\n";
        std::this_thread::sleep_for(std::chrono::seconds(task.load));
        std::cout << "CPU-" << cpuId << " finished Task " << task.id << "\n";
    }
}

int main() {
    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error opening input file.\n";
        return 1;
    }

    std::string line;
    int cpuCount = 0;
    TaskQueue taskQueue;

    // Read CPU count
    std::getline(inputFile, line);
    std::istringstream(line.substr(6)) >> cpuCount;

    // Read tasks
    while (std::getline(inputFile, line)) {
        std::string taskId = line.substr(0, line.find(':'));
        int load = std::stoi(line.substr(line.find_last_of(' ') + 1));
        taskQueue.push({taskId, load});
    }

    inputFile.close();

    // Create CPU threads
    std::vector<std::thread> cpus;
    for (int i = 1; i <= cpuCount; ++i) {
        cpus.emplace_back(cpuWorker, i, std::ref(taskQueue));
    }

    // Wait for all threads to finish
    for (auto &cpu : cpus) {
        cpu.join();
    }

    std::cout << "All tasks completed.\n";
    return 0;
}




#include <iostream>
#include <fstream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <string>
#include <sstream>

struct Task {
    std::string id;
    int load;
};

std::queue<Task> taskQueue;
std::mutex queueMutex;
std::condition_variable queueCV;
bool tasksRemaining = true;

void cpuWorker(int cpuId) {
    while (true) {
        Task currentTask;
        bool hasTask = false;

        // Fetch task from queue
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            if (!taskQueue.empty()) {
                currentTask = taskQueue.front();
                taskQueue.pop();
                hasTask = true;
            } else if (!tasksRemaining) {
                return;
            }
        }

        if (hasTask) {
            // Log task assignment
            std::cout << "CPU-" << cpuId << " picked Task " << currentTask.id
                      << " (Load: " << currentTask.load << ")\n";

            // Simulate task execution
            std::this_thread::sleep_for(std::chrono::seconds(currentTask.load));

            // Log task completion
            std::cout << "CPU-" << cpuId << " finished Task " << currentTask.id << "\n";

            // Notify other threads that may be waiting for tasks
            queueCV.notify_all();
        } else {
            // If no task was available, wait for notification
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}

int main() {
    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Error: Unable to open input file.\n";
        return 1;
    }

    int cpuCount = 0;
    std::string line;

    // Parse CPU count
    std::getline(inputFile, line);
    std::istringstream cpuStream(line);
    cpuStream.ignore(6); // Skip "CPUs: "
    cpuStream >> cpuCount;

    // Parse tasks
    while (std::getline(inputFile, line)) {
        std::istringstream taskStream(line);
        Task task;
        std::string loadStr;

        std::getline(taskStream, task.id, ':');
        taskStream.ignore(6); // Skip " Load "
        taskStream >> task.load;

        taskQueue.push(task);
    }

    inputFile.close();

    // Launch CPU threads
    std::vector<std::thread> threads;
    for (int i = 1; i <= cpuCount; ++i) {
        threads.emplace_back(cpuWorker, i);
    }

    // Wait for all tasks to be assigned
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        tasksRemaining = false;
    }
    queueCV.notify_all();

    // Wait for threads to complete
    for (auto& thread : threads) {
        thread.join();
    }

    std::cout << "All tasks completed.\n";
    return 0;
}




#include<iostream>
#include<thread>
#include<mutex>
#include<string>


std::mutex mtx;
void printFB(std::string s, int n, int tNo)
{
	for (static int i = 1; i <= n;)
	{
		std::lock_guard<std::mutex> lock(mtx);
		if (i == n + 1)
			break;
		if (tNo == 3 && i % 3 == 0 && i % 5 == 0)
		{
			std::cout << s << std::endl;
			i++;
		}
		 if (tNo == 1 && i % 3 == 0 && i % 5 != 0)
		{
			std::cout << s << std::endl;
			i++;

		}
		 if (tNo == 2 && i % 5 == 0 && i % 3 != 0)
		{
			std::cout << s << std::endl;
			i++;

		}
		 if (tNo == 4 && i % 5 != 0 && i % 3 != 0)
		{
			std::cout << i << std::endl;
			i++;

		}
	}
}

int main()
{
	std::thread t1(printFB, "Fizz", 20, 1);
	std::thread t2(printFB, "Buzz", 20, 2);
	std::thread t3(printFB, "FizzBuzz", 20, 3);
	std::thread t4(printFB, "", 20, 4);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
}



#include<iostream>
#include<thread>
#include<mutex>

std::mutex mtx;
void dispLetter(char c)
{
	static int count = 0;
	for (int i = 0; i < 5;)
	{
		mtx.lock();
		if (count % 3 == 0 && c == 'A')
		{
			std::cout << c;
			++i;
			count++;
		}
		else if (count % 3 == 1 && c == 'B')
		{
			std::cout << c;
			++i;
			count++;
		}
		else if (count % 3 == 2 && c == 'C')
		{
			std::cout << c;
			++i;
			count++;
		}
		mtx.unlock();
	}
}

int main()
{
	std::thread t1(dispLetter, 'A');
	std::thread t2(dispLetter, 'B');
	std::thread t3(dispLetter, 'C');
	t1.join();
	t2.join();
	t3.join();
	return 0;
}



#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;
bool pingTurn = true; // Shared flag to determine whose turn it is

// Function to print "Ping" or "Pong"
void printPingPong(const std::string& word, bool isPing) {
    for (int i = 0; i < 10; ++i) {
        while (true) { // Keep checking until it's this thread's turn
            mtx.lock(); // Lock the mutex to safely access shared data
            if (pingTurn == isPing) { // Check if it's this thread's turn
                std::cout << word << " ";
                pingTurn = !pingTurn; // Toggle the turn
                mtx.unlock(); // Unlock the mutex before breaking
                break; // Exit the loop after printing
            }
            mtx.unlock(); // Unlock the mutex if not this thread's turn
        }
    }
}

int main() {
    // Create two threads for Ping and Pong
    std::thread t1(printPingPong, "Ping", true);  // Ping thread
    std::thread t2(printPingPong, "Pong", false); // Pong thread

    // Wait for both threads to finish
    t1.join();
    t2.join();

    return 0;
}




#include <iostream>
#include <thread>
#include <mutex>

int counter = 0;
std::mutex mtx;

void incrementCounter(int n) {
    for (int i = 0; i < n; ++i) {
        std::lock_guard<std::mutex> lock(mtx);
        ++counter;
    }
}

int main() {
    const int numThreads = 5;
    const int increments = 1000;
    std::thread threads[numThreads];

    for (int i = 0; i < numThreads; ++i) {
        threads[i] = std::thread(incrementCounter, increments);
    }

    for (int i = 0; i < numThreads; ++i) {
        threads[i].join();
    }

    std::cout << "Final Counter Value: " << counter << std::endl;

    return 0;
}



#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool isBalanced(const string& expression) {
    stack<char> s;

    for (char ch : expression) {
        if (ch == '(' || ch == '{' || ch == '[') {
            s.push(ch);
        } else if (ch == ')' || ch == '}' || ch == ']') {
            if (s.empty()) {
                return false; // Closing parenthesis without a match
            }
            char top = s.top();
            if ((ch == ')' && top == '(') ||
                (ch == '}' && top == '{') ||
                (ch == ']' && top == '[')) {
                s.pop(); // Match found
            } else {
                return false; // Mismatched parenthesis
            }
        }
    }

    return s.empty(); // If stack is empty, all parentheses are balanced
}

int main() {
    string expression;
    cout << "Enter an expression: ";
    cin >> expression;

    if (isBalanced(expression)) {
        cout << "Balanced" << endl;
    } else {
        cout << "Not Balanced" << endl;
    }

    return 0;
}



c
las
ss
 Solution {
public:
    vector<int> nextGreaterElement(vector<int>& findNums, vector<int>& nums) {
        vector<int> ans;
        for(int findNum : findNums){
            vector<int>::iterator it = find(nums.begin(), nums.end(), findNum);
            if(it==nums.end() or it==nums.end()-1){
                ans.push_back(-1);
            }else{
                int i = 0;
                for(i = it-nums.begin(); i < nums.size(); i++){
                    if(nums[i] > findNum){
                        ans.push_back(nums[i]);
                        break;
                    }
                }
                if(i==nums.size()){
                    ans.push_back(-1);
                }
            }
        }
        return ans;
    }
};




#include <iostream>
#include <stack>
#include <string>
using namespace std;

class BrowserHistory {
private:
    stack<string> backStack;
    stack<string> forwardStack;
    string currentPage;

public:
    BrowserHistory() : currentPage("Home") {} // Default to "Home"

    void visit(const string& url) {
        if (!currentPage.empty()) {
            backStack.push(currentPage);
        }
        currentPage = url;
        while (!forwardStack.empty()) {
            forwardStack.pop();
        }
        cout << "Current page: " << currentPage << endl;
    }

    void back() {
        if (backStack.empty()) {
            cout << "No page to go back to." << endl;
            return;
        }
        forwardStack.push(currentPage);
        currentPage = backStack.top();
        backStack.pop();
        cout << "Current page: " << currentPage << endl;
    }

    void forward() {
        if (forwardStack.empty()) {
            cout << "No page to go forward to." << endl;
            return;
        }
        backStack.push(currentPage);
        currentPage = forwardStack.top();
        forwardStack.pop();
        cout << "Current page: " << currentPage << endl;
    }
};

int main() {
    BrowserHistory browser;

    string command;
    while (getline(cin, command)) {
        if (command.rfind("visit", 0) == 0) {
            browser.visit(command.substr(6)); // Extract URL after "visit "
        } else if (command == "back") {
            browser.back();
        } else if (command == "forward") {
            browser.forward();
        } else if (command == "exit") {
            break;
        } else {
            cout << "Invalid command!" << endl;
        }
    }

    return 0;
}
