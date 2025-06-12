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
