#include <iostream>
#include <forward_list>
#include <string>

// Function to clean messages starting with "DELETED:"
void cleanMessages(std::forward_list<std::string>& messages) {
    auto previous = messages.before_begin(); // Points before the start of the list
    for (auto current = messages.begin(); current != messages.end(); ) {
        // Check if the message starts with "DELETED:"
        if (current->substr(0, 8) == "DELETED:") { 
            current = messages.erase_after(previous); // Remove the current message
        } else {
            previous = current; // Move previous to current
            ++current;          // Move current to the next element
        }
    }
}

int main() {
    // Input chat history
    std::forward_list<std::string> messages = {
        "Hi", "Hello", "DELETED: Spam", "How are you?", "DELETED: Abuse"
    };

    // Clean deleted messages
    cleanMessages(messages);

    // Display the cleaned chat history
    std::cout << "Cleaned Chat History:\n";
    for (const std::string& message : messages) {
        std::cout << message << "\n";
    }

    return 0;
}



#include <iostream>
#include <vector>
#include <string>

// Custom function to convert a character to lowercase
char toLowerChar(char ch) {
    if (ch >= 'A' && ch <= 'Z') {
        return ch + ('a' - 'A');
    }
    return ch;
}

// Custom function to convert a string to lowercase
std::string toLowerString(const std::string& str) {
    std::string lowerStr;
    for (char ch : str) {
        lowerStr += toLowerChar(ch);
    }
    return lowerStr;
}

// Custom function to sort a vector of strings lexicographically
void sortStrings(std::vector<std::string>& vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        for (size_t j = i + 1; j < vec.size(); ++j) {
            if (vec[i] > vec[j]) {
                std::string temp = vec[i];
                vec[i] = vec[j];
                vec[j] = temp;
            }
        }
    }
}

// Custom function to remove duplicates from a sorted vector
void removeDuplicates(std::vector<std::string>& vec) {
    std::vector<std::string> uniqueVec;
    for (size_t i = 0; i < vec.size(); ++i) {
        if (i == 0 || vec[i] != vec[i - 1]) {
            uniqueVec.push_back(vec[i]);
        }
    }
    vec = uniqueVec;
}

int main() {
    // Input words
    std::vector<std::string> words = {"Apple", "banana", "apple", "Orange", "BANANA", "grape"};

    // Convert all words to lowercase
    for (std::string& word : words) {
        word = toLowerString(word);
    }

    // Sort the words
    sortStrings(words);

    // Remove duplicates
    removeDuplicates(words);

    // Print the result
    std::cout << "[";
    for (size_t i = 0; i < words.size(); ++i) {
        std::cout << "\"" << words[i] << "\"";
        if (i < words.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;

    return 0;
}



#include <iostream>
#include <list>
#include <string>

int main() {
    std::list<std::string> textBuffer;  // Text buffer
    int cursorPosition = 0;             // Cursor position as an index
    std::string command, line;

    while (true) {
        std::cout << "Enter command (INSERT/UP/DOWN/PRINT/EXIT): ";
        std::cin >> command;

        if (command == "INSERT") {
            std::cin.ignore();          // Ignore leftover newline
            std::cout << "Enter line to insert: ";
            std::getline(std::cin, line);

            auto it = textBuffer.begin();            // Find the current position
            for (int i = 0; i < cursorPosition; ++i) {
                ++it;
            }

            textBuffer.insert(it, line);             // Insert the line at the position
            ++cursorPosition;                        // Move cursor after the inserted line
        } 
        else if (command == "UP") {
            if (cursorPosition > 0) {                // Check if not at the top
                --cursorPosition;                    // Move cursor up
            } else {
                std::cout << "Already at the top.\n";
            }
        } 
        else if (command == "DOWN") {
            if (cursorPosition < textBuffer.size()) { // Check if not at the bottom
                ++cursorPosition;                    // Move cursor down
            } else {
                std::cout << "Already at the bottom.\n";
            }
        } 
        else if (command == "PRINT") {
            std::cout << "Text Buffer:\n";
            for (const auto& line : textBuffer) {
                std::cout << line << "\n";           // Print all lines
            }
        } 
        else if (command == "EXIT") {
            break;                                   // Exit the loop
        } 
        else {
            std::cout << "Invalid command. Try again.\n";
        }
    }

    return 0;
}





#include <iostream>
#include <list>
#include <string>

class TextEditor {
public:
    TextEditor() : cursor_pos(0) {}

    void insert(const std::string& text) {
        // Advance to cursor position
        auto it = getIteratorAt(cursor_pos);
        lines.insert(it, text);
        cursor_pos++; // Move cursor after inserted line
    }

    void moveUp() {
        if (cursor_pos > 0) {
            cursor_pos--;
        }
    }

    void moveDown() {
        if (cursor_pos < lines.size()) {
            cursor_pos++;
        }
    }

    void print() const {
        for (const auto& line : lines) {
            std::cout << line << "\n";
        }
    }

private:
    std::list<std::string> lines;
    size_t cursor_pos; // Position of cursor in [0 .. lines.size()]

    // Helper to get iterator at position pos by advancing from begin()
    std::list<std::string>::iterator getIteratorAt(size_t pos) {
        auto it = lines.begin();
        for (size_t i = 0; i < pos; i++) {
            ++it;
        }
        return it;
    }
};

int main() {
    TextEditor editor;
    std::string command;

    while (std::getline(std::cin, command)) {
        if (command.find("INSERT ") == 0) {
            std::string text = command.substr(7);
            editor.insert(text);
        } else if (command == "UP") {
            editor.moveUp();
        } else if (command == "DOWN") {
            editor.moveDown();
        } else if (command == "PRINT") {
            editor.print();
            break;
        }
    }

    return 0;
}






problem 4: Sliding Window Logger (Beginner Version)

#include <iostream>
#include <forward_list>
#include <string>

// Function to add a log
void addLog(std::forward_list<std::string>& logs, const std::string& log, int& currentSize, int maxSize) {
    logs.push_front(log); // Add new log at the front
    currentSize++;        // Increment size

    // If size exceeds the limit, remove the last log
    if (currentSize > maxSize) {
        auto it = logs.before_begin(); // Iterator before the start
        for (auto jt = logs.begin(); jt != logs.end(); ++jt) {
            if (std::next(jt) == logs.end()) { // Found the last element
                logs.erase_after(it);          // Remove it
                currentSize--;                 // Decrement size
                break;
            }
            it = jt;
        }
    }
}

// Function to display logs
void showLogs(const std::forward_list<std::string>& logs) {
    for (const auto& log : logs) {
        std::cout << log << std::endl;
    }
}

int main() {
    std::forward_list<std::string> logs;
    int maxSize = 3; // Maximum log size
    int currentSize = 0;

    // Adding logs
    addLog(logs, "LogA", currentSize, maxSize);
    addLog(logs, "LogB", currentSize, maxSize);
    addLog(logs, "LogC", currentSize, maxSize);
    addLog(logs, "LogD", currentSize, maxSize);
    addLog(logs, "LogE", currentSize, maxSize);

    // Showing logs
    std::cout << "Logs (most recent to oldest):" << std::endl;
    showLogs(logs);

    return 0;
}


#include <iostream>
#include <deque>
#include <string>

// Visit a new page
void visitPage(std::deque<std::string>& back, std::deque<std::string>& forward, const std::string& url) {
    back.push_back(url); // Add to back history
    forward.clear();     // Clear forward history
    std::cout << "Visited: " << url << std::endl;
}

// Go back to the previous page
void goBack(std::deque<std::string>& back, std::deque<std::string>& forward) {
    if (back.size() > 1) {               // Ensure there is a page to go back to
        forward.push_front(back.back()); // Move current page to forward history
        back.pop_back();                 // Remove it from back history
        std::cout << "Back to: " << back.back() << std::endl;
    } else {
        std::cout << "No more pages to go back to!" << std::endl;
    }
}

// Go forward to the next page
void goForward(std::deque<std::string>& back, std::deque<std::string>& forward) {
    if (!forward.empty()) {            // Ensure there is a page to go forward to
        back.push_back(forward.front()); // Move the forward page to back history
        std::cout << "Forward to: " << forward.front() << std::endl;
        forward.pop_front();            // Remove it from forward history
    } else {
        std::cout << "No forward history!" << std::endl;
    }
}

// Show the current page
void showCurrentPage(const std::deque<std::string>& back) {
    if (!back.empty()) {
        std::cout << "Current page: " << back.back() << std::endl;
    } else {
        std::cout << "No current page!" << std::endl;
    }
}

int main() {
    std::deque<std::string> back;    // Backward history
    std::deque<std::string> forward; // Forward history

    // Simulating browser commands
    visitPage(back, forward, "google.com");
    visitPage(back, forward, "github.com");
    visitPage(back, forward, "stackoverflow.com");

    goBack(back, forward); // Back to github.com
    goBack(back, forward); // Back to google.com
    goForward(back, forward); // Forward to github.com
    showCurrentPage(back); // Current: github.com

    visitPage(back, forward, "openai.com"); // Clear forward history

    goForward(back, forward); // No forward history
    goBack(back, forward);    // Back to github.com
    showCurrentPage(back);    // Current: github.com

    return 0;
}

Output

Visited: google.com
Visited: github.com
Visited: stackoverflow.com
Back to: github.com
Back to: google.com
Forward to: github.com
Current page: github.com
Visited: openai.com
No forward history!
Back to: github.com
Current page: github.com


---

Explanation for Beginners

1. Problem 4: Sliding Window Logger

std::forward_list is a simple singly-linked list.

Logs are added to the front (most recent at the front).

If the log count exceeds the maximum size, the oldest log (last node) is removed manually using iterators.



2. Problem 5: Undo/Redo Browser Simulator

std::deque is used because it supports fast insertion and deletion at both ends.

back stores the browsing history in reverse (most recent at the back).

forward stores the forward history for redo operations. When a new page is visited, forward history is cleared.



    void removeTask(std::list<std::string>& tasks, const std::string& task) {
    bool found = false;
    for (auto it = tasks.begin(); it != tasks.end(); /* no increment here */) {
        if (*it == task) {
            it = tasks.erase(it); // Erase returns an iterator to the next element
            found = true;
        } else {
            ++it; // Move to the next element if no erasure
        }
    }

    if (found) {
        std::cout << "Removed task(s): " << task << std::endl;
    } else {
        std::cout << "Task not found: " << task << std::endl;
    }
}





include <iostream>
#include <list>
#include <string>
#include <algorithm>

void addTask(std::list<std::string>& tasks, const std::string& task) {
    tasks.push_back(task); // Add to the end
}

void addUrgentTask(std::list<std::string>& tasks, const std::string& task) {
    tasks.push_front(task); // Add to the front
}

void removeTask(std::list<std::string>& tasks, const std::string& task) {
    // Check if the task exists and remove it
    auto it = std::find(tasks.begin(), tasks.end(), task);
    if (it != tasks.end()) {
        tasks.erase(it);
    } else {
        std::cout << "Task not found: " << task << std::endl;
    }
}

void showTasks(const std::list<std::string>& tasks) {
    // Display all tasks
    for (const auto& task : tasks) {
        std::cout << task << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::list<std::string> tasks;
    std::string command, task;

    while (true) {
        std::cout << "Enter a command (add, urgent, remove, show, exit): ";
        std::cin >> command;

        if (command == "add") {
            std::cin.ignore(); // Ignore leftover newline
            std::cout << "Enter task: ";
            std::getline(std::cin, task);
            addTask(tasks, task);
        } else if (command == "urgent") {
            std::cin.ignore(); // Ignore leftover newline
            std::cout << "Enter task: ";
            std::getline(std::cin, task);
            addUrgentTask(tasks, task);
        } else if (command == "remove") {
            std::cin.ignore(); // Ignore leftover newline
            std::cout << "Enter task to remove: ";
            std::getline(std::cin, task);
            removeTask(tasks, task);
        } else if (command == "show") {
            showTasks(tasks);
        } else if (command == "exit") {
            break;
        } else {
            std::cout << "Invalid command. Try again." << std::endl;
        }
    }

    return 0;
}



#include <iostream>
#include <list>

void bubbleSort(std::list<int>& list) {
    bool swapped;
    do {
        swapped = false;
        auto current = list.begin();
        auto next = std::next(current);

        while (next != list.end()) {
            if (*current > *next) {
                // Swap using a temporary variable
                int temp = *current;
                *current = *next;
                *next = temp;

                swapped = true;
            }
            current = next;
            next = std::next(current);
        }
    } while(swapped);
}

int main() {
    std::list<int> myList = {5, 2, 8, 1, 9, 4};
    bubbleSort(myList);

    // Output the sorted list
    for (int num : myList) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}


#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

template<typename Container>
int godNumber(const Container& s) {
    int frequency[10] = {0};
    
    // Count frequency of each digit
    for (auto ch : s) {
        if (ch >= '0' && ch <= '9') {
            frequency[ch - '0']++;
        }
    }

    // Initialize max and min definite values
    int maxDefiniteValue = -1; // Start with a value lower than any possible definite value
    int minDefiniteValue = 1000; // Start with a value higher than any possible definite value

    // Calculate definite values and update max/min
    for (int digit = 0; digit <= 9; digit++) {
        if (frequency[digit] > 0) {
            int definiteValue = digit * frequency[digit];
            maxDefiniteValue = max(maxDefiniteValue, definiteValue);
            minDefiniteValue = min(minDefiniteValue, definiteValue);
        }
    }

    // If only one digit type, return its definite value
    if (maxDefiniteValue == minDefiniteValue) {
        return maxDefiniteValue;
    }

    return maxDefiniteValue - minDefiniteValue;
}

int main() {
    string s;
    cin >> s;

    cout << godNumber(s) << endl;

    // Example usage with vector<char>
    vector<char> chars(s.begin(), s.end());
    cout << "God Number from vector<char>: " << godNumber(chars) << endl;

    return 0;
}




#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

int godNumber(const string& s) {
    // Frequency array for digits 0-9
    vector<int> frequency(10, 0);

    // Count frequency of each digit
    for (char ch : s) {
        frequency[ch - '0']++;
    }

    // Calculate definite values
    vector<int> definiteValues;
    for (int digit = 0; digit <= 9; digit++) {
        if (frequency[digit] > 0) {
            definiteValues.push_back(digit * frequency[digit]);
        }
    }

    // If only one type of character present, return that definite value
    if (definiteValues.size() == 1) {
        return definiteValues[0];
    }

    // Find maximum and minimum definite values
    int maxVal = *max_element(definiteValues.begin(), definiteValues.end());
    int minVal = *min_element(definiteValues.begin(), definiteValues.end());

    // Return the difference - God Number
    return abs(maxVal - minVal);
}

int main() {
    string s;
    cin >> s;
    cout << godNumber(s) << endl;
    return 0;
}



#include <iostream>
#include <string>
#include <algorithm>
#include <limits>
#include <vector>

using namespace std;

template<typename Container>
int godNumber(const Container& s) {
    int frequency[10] = {0};
    for (auto ch : s) {
        if (ch >= '0' && ch <= '9') {
            frequency[ch - '0']++;
        }
        else {
            // Ignore or handle invalid chars if needed
        }
    }

    int maxDefiniteValue = numeric_limits<int>::min();
    int minDefiniteValue = numeric_limits<int>::max();

    for (int digit = 0; digit <= 9; digit++) {
        if (frequency[digit] > 0) {
            int definiteValue = digit * frequency[digit];
            maxDefiniteValue = max(maxDefiniteValue, definiteValue);
            minDefiniteValue = min(minDefiniteValue, definiteValue);
        }
    }

    // If only one digit type, return its definite value
    if (maxDefiniteValue == minDefiniteValue) {
        return maxDefiniteValue;
    }

    return maxDefiniteValue - minDefiniteValue;
}

int main() {
    string s;
    cin >> s;

    cout << godNumber(s) << endl;

    // Example usage with vector<char>
    vector<char> chars(s.begin(), s.end());
    cout << "God Number from vector<char>: " << godNumber(chars) << endl;

    return 0;
}




#include <iostream>
#include <vector>
#include <algorithm> // For sort

int main() {
    // Step 1: Input scores from the user
    std::vector<int> scores;
    int score;
    std::cout << "Enter scores (-1 to stop): ";
    while (true) {
        std::cin >> score;
        if (score == -1) break; // Stop when -1 is entered
        scores.push_back(score);
    }

    // Step 2: Sort scores in descending order using a basic comparison function
    std::sort(scores.begin(), scores.end(), [](int a, int b) {
        return a > b; // Sort in descending order
    });

    // Step 3: Display all scores
    std::cout << "All Scores (Sorted): ";
    for (size_t i = 0; i < scores.size(); ++i) {
        std::cout << scores[i] << " ";
    }
    std::cout << std::endl;

    // Step 4: Display top 3 scores
    std::cout << "Top 3 Scores: ";
    for (size_t i = 0; i < 3 && i < scores.size(); ++i) {
        std::cout << scores[i] << " ";
    }
    std::cout << std::endl;

    // Step 5: Remove duplicate scores manually
    std::vector<int> unique_scores;
    for (size_t i = 0; i < scores.size(); ++i) {
        // Add score to unique_scores if it is not already present
        if (unique_scores.empty() || scores[i] != unique_scores[unique_scores.size() - 1]) {
            unique_scores.push_back(scores[i]);
        }
    }

    // Step 6: Display unique scores
    std::cout << "Unique Scores (Sorted): ";
    for (size_t i = 0; i < unique_scores.size(); ++i) {
        std::cout << unique_scores[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}



#include <iostream>

// Function to calibrate sensor readings
void calibrateSensor(float readings[], size_t size, float calibration_factor) {
    for (size_t i = 0; i < size; ++i) {
        readings[i] += calibration_factor; // Apply the calibration factor
    }
}

// Function to calculate the average of sensor readings
float calculateAverage(const float readings[], size_t size) {
    float sum = 0.0f;
    for (size_t i = 0; i < size; ++i) {
        sum += readings[i]; // Accumulate the readings
    }
    return sum / size; // Return the average
}

// Function to process all sensors: calibrate and compute averages
void processSensors(
    float sensor_readings[][5], 
    size_t num_sensors, 
    size_t readings_per_sensor, 
    const float calibration_factors[]
) {
    for (size_t i = 0; i < num_sensors; ++i) {
        calibrateSensor(sensor_readings[i], readings_per_sensor, calibration_factors[i]); // Calibrate readings
        float average = calculateAverage(sensor_readings[i], readings_per_sensor);       // Calculate average
        std::cout << "Sensor " << (i + 1) 
                  << " Average (calibrated): " << average << std::endl;
    }
}

int main() {
    // Step 1: Define sensor readings as a 2D C-style array
    float sensor_readings[3][5] = {
        {20.0, 21.0, 22.0, 20.5, 19.8}, // Sensor 1 readings
        {30.0, 30.2, 29.8, 30.1, 30.3}, // Sensor 2 readings
        {25.0, 26.0, 24.0, 25.5, 26.2}  // Sensor 3 readings
    };

    // Step 2: Define calibration factors as a 1D C-style array
    float calibration_factors[3] = {0.5, -0.3, 1.2};

    // Step 3: Process sensors
    processSensors(sensor_readings, 3, 5, calibration_factors);

    return 0;
}



#include <iostream>

// Define constants for the number of sensors and readings
const size_t NUM_SENSORS = 3;
const size_t NUM_READINGS = 5;

// Function to calibrate sensor readings
void calibrateSensor(float readings[], size_t size, float calibration_factor) {
    for (size_t i = 0; i < size; ++i) {
        readings[i] += calibration_factor; // Apply calibration factor
    }
}

// Function to calculate the average of an array of readings
float calculateAverage(const float readings[], size_t size) {
    float sum = 0.0f;
    for (size_t i = 0; i < size; ++i) {
        sum += readings[i];
    }
    return sum / size; // Return the average
}

// Function to process all sensors: calibrate and compute averages
void processSensors(
    float sensor_readings[NUM_SENSORS][NUM_READINGS],
    const float calibration_factors[NUM_SENSORS]
) {
    for (size_t i = 0; i < NUM_SENSORS; ++i) {
        calibrateSensor(sensor_readings[i], NUM_READINGS, calibration_factors[i]); // Calibrate readings
        float average = calculateAverage(sensor_readings[i], NUM_READINGS);      // Calculate average
        std::cout << "Sensor " << (i + 1) 
                  << " Average (calibrated): " << average << std::endl;
    }
}

int main() {
    // Step 1: Define sensor readings
    float sensor_readings[NUM_SENSORS][NUM_READINGS] = {
        {20.0, 21.0, 22.0, 20.5, 19.8}, // Sensor 1 readings
        {30.0, 30.2, 29.8, 30.1, 30.3}, // Sensor 2 readings
        {25.0, 26.0, 24.0, 25.5, 26.2}  // Sensor 3 readings
    };

    // Step 2: Define calibration factors
    float calibration_factors[NUM_SENSORS] = {0.5, -0.3, 1.2};

    // Step 3: Process sensors
    processSensors(sensor_readings, calibration_factors);

    return 0;
}
