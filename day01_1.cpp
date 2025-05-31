#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>
#include <functional>

using namespace std;

enum LogLevel { INFO, DEBUG, WARNING, ERROR };

// Job Class Definition
class Job {
public:
    int jobID;
    int executionTime;
    int priority;

    Job(int id, int time, int prio)
        : jobID(id), executionTime(time), priority(prio) {}
};

// Logger Class Definition
class Logger {
private:
    ofstream logFile;
    string logFileName;

public:
    Logger(const string& filename) : logFileName(filename) {
        logFile.open(logFileName, ios::out);
        if (!logFile) {
            cerr << "[ERROR] Failed to open log file.\n";
        }
    }

    ~Logger() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }

    void log(LogLevel level, const string& message) {
        static const char* levelNames[] = {"[INFO]", "[DEBUG]", "[WARNING]", "[ERROR]"};
        string logMessage = string(levelNames[level]) + " " + message;
        cout << logMessage << endl;
        if (logFile.is_open()) {
            logFile << logMessage << endl;
        }
    }
};

// FCFS Scheduling Algorithm
void fcfsScheduling(vector<Job>& jobs) {
    // No sorting is required; jobs execute in the input order.
}

// Priority Scheduling Algorithm
void priorityScheduling(vector<Job>& jobs) {
    sort(jobs.begin(), jobs.end(), [](const Job& a, const Job& b) {
        return a.priority > b.priority; // Higher priority first
    });
}

// Job Execution Function
void executeJobs(const vector<Job>& jobs, Logger& logger) {
    int totalExecutionTime = 0;

    for (const Job& job : jobs) {
        logger.log(DEBUG, "Executing Job ID: " + to_string(job.jobID) +
                          " | Priority: " + to_string(job.priority) +
                          " | Execution Time: " + to_string(job.executionTime) + "ms");

        this_thread::sleep_for(chrono::milliseconds(job.executionTime));
        totalExecutionTime += job.executionTime;
    }

    logger.log(INFO, "All jobs executed in " + to_string(totalExecutionTime) + "ms.");
}

// Load Jobs from File
vector<Job> loadJobs(const string& filename, Logger& logger) {
    ifstream file(filename);
    vector<Job> jobs;

    if (!file) {
        logger.log(ERROR, "Failed to open job file.");
        return jobs;
    }

    int id, time, priority;
    while (file >> id >> time >> priority) {
        jobs.emplace_back(id, time, priority);
    }

    logger.log(INFO, "Loaded " + to_string(jobs.size()) + " jobs from file.");
    return jobs;
}

// Main Function
int main() {
    Logger logger("job_log.txt");
    vector<Job> jobs;
    function<void(vector<Job>&)> schedulingStrategy = nullptr;

    while (true) {
        cout << "\n==== JobChain Scheduler ====\n";
        cout << "1. Load jobs from file\n";
        cout << "2. Choose scheduling algorithm\n";
        cout << "   a. FCFS (First Come, First Serve)\n";
        cout << "   b. Priority-based\n";
        cout << "3. Execute jobs\n";
        cout << "4. Exit\n";
        cout << "> ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                jobs = loadJobs("jobs.txt", logger);
                break;

            case 2: {
                char algChoice;
                cout << "Select algorithm (a: FCFS, b: Priority): ";
                cin >> algChoice;

                if (algChoice == 'a') {
                    schedulingStrategy = fcfsScheduling;
                    logger.log(INFO, "Selected FCFS scheduling.");
                } else if (algChoice == 'b') {
                    schedulingStrategy = priorityScheduling;
                    logger.log(INFO, "Selected Priority-based scheduling.");
                } else {
                    logger.log(WARNING, "Invalid selection for scheduling.");
                }
                break;
            }

            case 3:
                if (!jobs.empty() && schedulingStrategy) {
                    schedulingStrategy(jobs);
                    executeJobs(jobs, logger);
                } else {
                    logger.log(WARNING, "No jobs loaded or scheduling strategy not selected.");
                }
                break;

            case 4:
                logger.log(INFO, "Exiting JobChain Scheduler.");
                return 0;

            default:
                logger.log(WARNING, "Invalid menu choice.");
        }
    }
}
