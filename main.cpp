#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <cstdlib>

using namespace std;
enum SignalColor {
    RED,
    YELLOW,
    GREEN
};

class TrafficJunction {
private:
    string directions[4];
    int currentGreenDirection;
    SignalColor currentState;
    int greenDuration;
    int yellowDuration;

    void clearScreen() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

public:
    TrafficJunction() {
        directions[0] = "North";
        directions[1] = "East";
        directions[2] = "South";
        directions[3] = "West";
        currentGreenDirection = 0;
        currentState = RED;
        greenDuration = 5;
        yellowDuration = 2;
    }

    void displayStatus(int secondsRemaining) {
        clearScreen();
        cout << "========================================" << endl;
        cout << "      TRAFFIC LIGHT MANAGEMENT SYSTEM    " << endl;
        cout << "========================================" << endl << endl;
        cout << "Current Junction Status:" << endl;
        cout << "----------------------------------------" << endl;

        for (int i = 0; i < 4; i++) {
            cout << directions[i];
            if (directions[i].length() < 6) {
                cout << "  ";
            }
            cout << " : ";
            if (i == currentGreenDirection) {
                if (currentState == GREEN) {
                    cout << "GREEN (" << secondsRemaining << ")" << endl;
                } else if (currentState == YELLOW) {
                    cout << "YELLOW (" << secondsRemaining << ")" << endl;
                }
            } else {
                cout << "RED" << endl;
            }
        }
        cout << "----------------------------------------" << endl;
        cout << "Simulation in progress..." << endl;
    }

    void startSimulation(int totalCycles) {
        cout << "\nStarting Traffic Light Simulation for " << totalCycles << " cycle(s)..." << endl;
        this_thread::sleep_for(chrono::seconds(1));

        for (int cycle = 1; cycle <= totalCycles; cycle++) {
            for (int dir = 0; dir < 4; dir++) {
                currentGreenDirection = dir;
                currentState = GREEN;
                for (int sec = greenDuration; sec > 0; sec--) {
                    displayStatus(sec);
                    this_thread::sleep_for(chrono::seconds(1));
                }
                currentState = YELLOW;
                for (int sec = yellowDuration; sec > 0; sec--) {
                    displayStatus(sec);
                    this_thread::sleep_for(chrono::seconds(1));
                }
            }
        }
        clearScreen();
        cout << "========================================" << endl;
        cout << "         SIMULATION COMPLETED           " << endl;
        cout << "========================================" << endl;
        cout << "Successfully completed " << totalCycles << " full cycle(s)." << endl << endl;
    }
};
int main() {
    TrafficJunction junction;
    int choice;
    int cycles;

    do {
        cout << "========================================" << endl;
        cout << "      TRAFFIC LIGHT SIMULATOR MENU      " << endl;
        cout << "========================================" << endl;
        cout << "1. Start Simulation" << endl;
        cout << "2. Exit" << endl;
        cout << "Enter your choice (1-2): ";

        if (!(cin >> choice)) {
            cout << "Invalid input! Exiting program." << endl;
            break;
        }

        switch (choice) {
            case 1:
                cout << "\nEnter number of cycles to run (e.g., 1, 2, 3): ";
                if (cin >> cycles && cycles > 0) {
                    junction.startSimulation(cycles);
                } else {
                    cout << "Invalid cycle count! Returning to menu.\n" << endl;
                }
                break;

            case 2:
                cout << "\nExiting Traffic Light Simulator. Goodbye!" << endl;
                break;

            default:
                cout << "\nInvalid choice! Please select option 1 or 2.\n" << endl;
                break;
        }

    } while (choice != 2);

    return 0;
}
