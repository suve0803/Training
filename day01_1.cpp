#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <thread>
#include <string>
#include <algorithm>

using namespace std;

enum LogginLevel
{
    INFO,
    DEBUG,
    WARNING,
    ERROR,
};

class Logger
{
    ofstream fileOut;

public:
    Logger(const char *f1)
    {
        try
        {
            fileOut.open(f1, ios::app);
            if (!fileOut.is_open())
            {
                throw "Error opening file";
            }
        }
        catch (string s)
        {
            cout << s;
            exit(0);
        }
    }

    const char *logleveltostring(int level)
    {
        switch (level)
        {
        case 0:
            return "INFO";
        case 1:
            return "DEBUG";
        case 2:
            return "WARNING";
        case 3:
            return "ERROR";
        default:
            return "UNKNOWN";
        }
    }

    void log(int level, const char *str)
    {
        fileOut << "[" << logleveltostring(level) << "] " << str << endl;
    }
};

class Job
{
protected:
    int jobId;
    int executionTime;
    int priority;

public:
    void setId(int JobId)
    {
        this->jobId = JobId;
    }
    int getId()
    {
        return jobId;
    }
    void setExecTime(int executionTime)
    {
        this->executionTime = executionTime;
    }
    int getExecTime()
    {
        return executionTime;
    }
    void setPriority(int priority)
    {
        this->priority = priority;
    }
    int getPriority()
    {
        return priority;
    }
    void displayJob()
    {
        cout << "Job ID: " << jobId << endl;
        cout << "Execution Time: " << executionTime << endl;
        cout << "Priority: " << priority << endl;
    }
    int executeJob(Logger &ob)
    {
        auto start = chrono::system_clock::now();
        this_thread::sleep_for(chrono::milliseconds(executionTime));
        auto end = chrono::system_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
        string msg = "Executing Job ID: " + to_string(jobId) + " | Priority: " + to_string(priority) + " | ExecTime " + to_string(duration.count()) + "ms";
        ob.log(DEBUG, msg.c_str());
        return duration.count();
    }
};

class Queue
{
protected:
    vector<Job> arr;
    int totalTime;
    bool isPriority;

public:
    Queue()
    {
        Job j;
        totalTime = 0;
        isPriority = false;
        ifstream inFile;
        try
        {
            inFile.open("job.txt", ios::in);
            if (!inFile.is_open())
                throw "File cannot be opened";
        }
        catch (const char *s)
        {
            cout << s << endl;
            exit(0);
        }
        int val;
        while (inFile >> val)
        {
            j.setId(val);
            inFile >> val;
            j.setExecTime(val);
            inFile >> val;
            j.setPriority(val);
            arr.push_back(j);
        }
    }

    void sortPriority()
    {
        sort(arr.begin(), arr.end(), [](const Job &a, const Job &b) {
            return a.getPriority() < b.getPriority();
        });
    }

    void executeQueue(Logger &ob)
    {
        if (isPriority)
        {
            sortPriority();
        }
        for (auto &i : arr)
        {
            totalTime += i.executeJob(ob);
        }
    }

    int getTotTime()
    {
        return totalTime;
    }

    void setPriority(bool isPriority)
    {
        this->isPriority = isPriority;
    }
};

int main()
{
    while (1)
    {
        cout << "===== Jobchain Scheduler =====\n";
        int options;
        cout << "1. Load jobs from file\n";
        cout << "2. Choose scheduling algorithm\n";
        cout << "   a. FIFO (job ID)\n";
        cout << "   b. Priority Based\n";
        cout << "3. Execute Jobs\n";
        cout << "4. Export Log\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> options;

        Queue q;
        Logger l("job_log.txt");

        char alg;
        string msg;
        switch (options)
        {
        case 1:
            l.log(INFO, "Successfully loaded Jobs");
            break;
        case 2:
            cin >> alg;
            if (alg == 'b')
            {
                q.setPriority(true);
                l.log(INFO, "Selected Priority Scheduling");
            }
            else
            {
                l.log(INFO, "Selected FIFO Scheduling");
            }
            break;
        case 3:
            q.executeQueue(l);
            msg = "All jobs executed in " + to_string(q.getTotTime()) + "ms";
            l.log(INFO, msg.c_str());
            break;
        case 4:
            l.log(INFO, "Log saved to job_log.txt");
            break;
        case 5:
            exit(0);
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    }
