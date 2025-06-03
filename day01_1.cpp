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
