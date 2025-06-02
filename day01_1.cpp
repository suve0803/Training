#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<chrono>
#include<algorithm>
#include<thread>
#include<sstream>
using namespace std;

enum logLevel {
    INFO = 0,
    DEBUG,
    WARNING,
    ERROR,
};

class Logger {
    ofstream fileOut;
public:
    Logger(char* f1) {
        try {
            fileOut.open(f1, ios::app);
            if (!fileOut.is_open()) {
                throw "Error in opening file";
            }
        }
        catch (string s) {
            cout << s;
            exit(0);
        }
    }

    const char* logleveltostring(int level) {
        switch (level) {
        case INFO:
            return "INFO";
        case DEBUG:
            return "DEBUG";
        case WARNING:
            return "WARNING";
        case ERROR:
            return "ERROR";
        default:
            return "UNKNOWN";
        }
    }

    void log(int level, const string& str) {
        fileOut << "[" << logleveltostring(level) << "] " << str << endl;
    }
};

class Job {
protected:
    int JobID;
    int executionTime;
    int priority;

public:
    void setId(int JobID) {
        this->JobID = JobID;
    }

    int getId() {
        return JobID;
    }

    void setExecTime(int executionTime) {
        this->executionTime = executionTime;
    }

    int getExecTime() {
        return executionTime;
    }

    void setPriority(int priority) {
        this->priority = priority;
    }

    int getPriority() {
        return priority;
    }

    void display() {
        cout << "Job ID: " << JobID << endl;
        cout << "Execution Time: " << executionTime << endl;
        cout << "Priority: " << priority << endl;
    }

    int executeJob(Logger& obj) {
        auto start = chrono::system_clock::now();
        this_thread::sleep_for(chrono::milliseconds(executionTime));
        auto end = chrono::system_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

        // Using std::ostringstream for string formatting
        ostringstream msg;
        msg << "Executing Job ID: " << JobID 
            << " | Priority: " << priority 
            << " | ExecTime: " << duration.count() << "ms";
        
        obj.log(DEBUG, msg.str());
        return duration.count();
    }
};

class Queue {
protected:
    vector<Job> arr;
    int totalTime;
    bool isPriority;

public:
    Queue() {
        Job j;
        totalTime = 0;
        int val;
        isPriority = false;
        ifstream inFile;
        try {
            inFile.open("job.txt", ios::in);
            if (!inFile.is_open()) {
                throw "File cannot be opened";
            }
        }
        catch (const char* s) {
            cout << s << endl;
            exit(0);
        }

        while (!inFile.eof()) {
            inFile >> val;
            j.setId(val);
            inFile >> val;
            j.setExecTime(val);
            inFile >> val;
            j.setPriority(val);
            arr.push_back(j);
        }
    }

    static bool compareJobs(const Job& obj1, const Job& obj2) {
        return obj1.getPriority() < obj2.getPriority();
    }

    void sortPriority() {
        sort(arr.begin(), arr.end(), compareJobs);
    }

    void executeQueue(Logger& obj) {
        if (isPriority) {
            sortPriority();
        }

        for (auto& i : arr) {
            totalTime += i.executeJob(obj);
        }
    }

    int getTotTime() {
        return totalTime;
    }

    void setPriority(bool isPriority) {
        this->isPriority = isPriority;
    }
};

int main() {
    Logger logger((char*)"log.txt");
    Queue queue;

    queue.setPriority(true); // Set true to enable priority-based execution.
    queue.executeQueue(logger);

    cout << "Total execution time: " << queue.getTotTime() << "ms" << endl;
    return 0;
