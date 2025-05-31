#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <algorithm>

enum LogLevel { INFO, DEBUG, WARNING, ERROR };

class Logger {
public:
    void log(LogLevel level, const std::string& message) {
        std::ofstream logFile("job_log.txt", std::ios::app);
        if (logFile.is_open()) {
            std::string levelStr;
            switch (level) {
                case INFO: levelStr = "[INFO]"; break;
                case DEBUG: levelStr = "[DEBUG]"; break;
                case WARNING: levelStr = "[WARNING]"; break;
                case ERROR: levelStr = "[ERROR]"; break;
            }
            logFile << levelStr << " " << message << std::endl;
            logFile.close();
        }
    }
};

class Job {
public:
    int jobID;
    int executionTime;
    int priority;

    Job(int id, int execTime, int prio) : jobID(id), executionTime(execTime), priority(prio) {}
};

class JobScheduler {
private:
    std::vector<Job> jobs;
    Logger logger;

public:
    void loadJobs(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            logger.log(ERROR, "File could not be opened.");
            return;
        }

        int id, execTime, prio;
        while (file >> id >> execTime >> prio) {
            jobs.emplace_back(id, execTime, prio);
        }
        logger.log(INFO, "Successfully loaded " + std::to_string(jobs.size()) + " jobs.");
        file.close();
    }

    void executeJobs(bool (*compare)(const Job&, const Job&)) {
        std::sort(jobs.begin(), jobs.end(), compare);
        int totalTime = 0;

        for (const auto& job : jobs) {
            logger.log(DEBUG, "Executing Job ID: " + std::to_string(job.jobID) + " | Priority: " + std::to_string(job.priority));
            std::this_thread::sleep_for(std::chrono::milliseconds(job.executionTime));
            totalTime += job.executionTime;
        }

        logger.log(INFO, "All jobs executed in " + std::to_string(totalTime) + "ms.");
    }

    void exportLog() {
        logger.log(INFO, "Log saved to job_log.txt.");
    }

    static bool fifoCompare(const Job& a, const Job& b) {
        return a.jobID < b.jobID;
    }

    static bool priorityCompare(const Job& a, const Job& b) {
        return a.priority > b.priority; // Higher priority first
    }
};

int main() {
    JobScheduler scheduler;
    int choice;

    while (true) {
        std::cout << "==== JobChain Scheduler ====\n";
        std::cout << "1. Load jobs from file\n";
        std::cout << "2. Choose scheduling algorithm\n";
        std::cout << "3. Execute jobs\n";
        std::cout << "4. Export log\n";
        std::cout << "5. Exit\n";
        std::cout << "> ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                scheduler.loadJobs("jobs.txt");
                break;
            case 2: {
                char algoChoice;
                std::cout << "Choose scheduling algorithm:\n";
                std::cout << "a. FIFO (Job ID)\n";
                std::cout << "b. Priority-based\n";
                std::cout << "> ";
                std::cin >> algoChoice;

                if (algoChoice == 'a') {
                    scheduler.executeJobs(JobScheduler::fifoCompare);
                } else if (algoChoice == 'b') {
                    scheduler.executeJobs(JobScheduler::priorityCompare);
                }
                break;
            }
            case 3:
                std::cout << "Please choose a scheduling algorithm first.\n";
                break;
            case 4:
                scheduler.exportLog();
                break;
            case 5:
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
