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
