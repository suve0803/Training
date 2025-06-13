#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

unordered_map<string, string> userDatabase;

void loadUsers() {
    ifstream file("users.txt");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string username, password;
        getline(ss, username, ':');
        getline(ss, password);
        userDatabase[username] = password;
    }
}

void saveUser(const string& username, const string& password) {
    ofstream file("users.txt", ios::app);
    file << username << ":" << password << endl;
}

bool authenticateUser(const string& username, const string& password) {
    return userDatabase.find(username) != userDatabase.end() && userDatabase[username] == password;
}

void signUp() {
    string username, password;
    cout << "Enter new username: ";
    cin >> username;
    cout << "Enter new password: ";
    cin >> password;
    saveUser(username, password);
    cout << "Registration successful!" << endl;
}

bool login() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    if (authenticateUser(username, password)) {
        cout << "Login successful!" << endl;
        return true;
    } else {
        cout << "Invalid credentials!" << endl;
        return false;
    }
}

struct CDRRecord {
    string msisdn;
    string operatorBrand;
    string operatorMNC;
    string callType;
    int duration;
    double download;
    double upload;
    string thirdPartyMSISDN;
    string thirdPartyOperatorMNC;
};

vector<CDRRecord> parseCDRFile(const string& filename) {
    vector<CDRRecord> records;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        CDRRecord record;
        getline(ss, record.msisdn, '|');
        getline(ss, record.operatorBrand, '|');
        getline(ss, record.operatorMNC, '|');
        getline(ss, record.callType, '|');
        ss >> record.duration;
        ss.ignore(1, '|');
        ss >> record.download;
        ss.ignore(1, '|');
        ss >> record.upload;
        ss.ignore(1, '|');
        getline(ss, record.thirdPartyMSISDN, '|');
        getline(ss, record.thirdPartyOperatorMNC);
        records.push_back(record);
    }
    return records;
}

void generateReports(const vector<CDRRecord>& records) {
    unordered_map<string, unordered_map<string, double>> customerData;
    unordered_map<string, unordered_map<string, double>> operatorData;

    for (const auto& record : records) {
        string customerKey = record.msisdn + "|" + record.operatorBrand;
        string operatorKey = record.operatorMNC;

        // Update customer data
        if (record.callType == "MOC") {
            customerData[customerKey]["Outgoing Voice"] += record.duration;
        } else if (record.callType == "MTC") {
            customerData[customerKey]["Incoming Voice"] += record.duration;
        } else if (record.callType == "SMS-MO") {
            customerData[customerKey]["Outgoing SMS"] += 1;
        } else if (record.callType == "SMS-MT") {
            customerData[customerKey]["Incoming SMS"] += 1;
        } else if (record.callType == "GPRS") {
            customerData[customerKey]["Download"] += record.download;
            customerData[customerKey]["Upload"] += record.upload;
        }

        // Update operator data
        if (record.callType == "MOC") {
            operatorData[operatorKey]["Outgoing Voice"] += record.duration;
        } else if (record.callType == "MTC") {
            operatorData[operatorKey]["Incoming Voice"] += record.duration;
        } else if (record.callType == "SMS-MO") {
            operatorData[operatorKey]["Outgoing SMS"] += 1;
        } else if (record.callType == "SMS-MT") {
            operatorData[operatorKey]["Incoming SMS"] += 1;
        } else if (record.callType == "GPRS") {
            operatorData[operatorKey]["Download"] += record.download;
            operatorData[operatorKey]["Upload"] += record.upload;
        }
    }

    // Print customer data
    for (const auto& customer : customerData) {
        cout << "# Customer Data Base: " << customer.first << endl;
        for (const auto& service : customer.second) {
            cout << "  " << service.first << ": " << service.second << endl;
        }
        cout << endl;
    }

    // Print operator data
    for (const auto& op : operatorData) {
        cout << "# Operator Data Base: " << op.first << endl;
        for (const auto& service : op.second) {
            cout << "  " << service.first << ": " << service.second << endl;
        }
        cout << endl;
    }
}

int main() {
    loadUsers();
    int choice;
    do {
        cout << "1. Sign Up\n2. Login\n3. Exit\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                signUp();
                break;
            case 2:
                if (login()) {
                    string filename;
                    cout << "Enter CDR file name: ";
                    cin >> filename;
                    vector<CDRRecord> records = parseCDRFile(filename);
                    generateReports(records);
                }
                break;
            case 3:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 3);
    return 0;
}
