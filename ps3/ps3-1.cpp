#include <iostream>
#include <cmath>

using namespace std;

const int ALTITUDE_STEPS = 6;
const int TEMPERATURE_STEPS = 4;
const double MIN_ALTITUDE = 0.0;
const double MAX_ALTITUDE = 10000.0;
const double MIN_TEMPERATURE = -20.0;
const double MAX_TEMPERATURE = 40.0;

double interpolate(double x, double x1, double x2, double y1, double y2) {
    return y1 + (x - x1) * (y2 - y1) / (x2 - x1);
}

double bilinearInterpolate(double alt, double temp, const double table[ALTITUDE_STEPS][TEMPERATURE_STEPS]) {
    int altIndex = static_cast<int>(alt / 2000);
    int tempIndex = static_cast<int>((temp + 20) / 20);
    
    double alt1 = altIndex * 2000.0;
    double alt2 = (altIndex + 1) * 2000.0;
    double temp1 = tempIndex * 20.0 - 20.0;
    double temp2 = (tempIndex + 1) * 20.0 - 20.0;
    
    double q11 = table[altIndex][tempIndex];
    double q12 = table[altIndex][tempIndex + 1];
    double q21 = table[altIndex + 1][tempIndex];
    double q22 = table[altIndex + 1][tempIndex + 1];
    
    double r1 = interpolate(temp, temp1, temp2, q11, q12);
    double r2 = interpolate(temp, temp1, temp2, q21, q22);
    
    return interpolate(alt, alt1, alt2, r1, r2);
}

int main() {
    double table[ALTITUDE_STEPS][TEMPERATURE_STEPS] = {
        {830.0, 770.0, 705.0, 640.0},
        {720.0, 655.0, 595.0, 535.0},
        {645.0, 585.0, 525.0, 465.0},
        {530.0, 475.0, 415.0, 360.0},
        {420.0, 365.0, 310.0, 250.0},
        {310.0, 255.0, 200.0, 145.0}
    };

    double altitude, temperature;

    while (true) {
        cout << "Enter altitude (0-10000 ft): ";
        cin >> altitude;
        cout << "Enter temperature (-20 to 40 C): ";
        cin >> temperature;

        if (altitude < MIN_ALTITUDE || altitude > MAX_ALTITUDE ||
            temperature < MIN_TEMPERATURE || temperature > MAX_TEMPERATURE) {
            cout << "Invalid input. Please enter values within the specified ranges.\n";
            continue;
        }

        double climbRate = bilinearInterpolate(altitude, temperature, table);
        cout << "Expected maximum rate of climb: " << climbRate << " ft/min\n";
        break;
    }

    return 0;
}


