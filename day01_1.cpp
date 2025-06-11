class Solution {
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
