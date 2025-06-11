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
