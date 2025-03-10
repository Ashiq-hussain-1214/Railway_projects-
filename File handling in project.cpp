#include <iostream>
#include <string>
#include <fstream>
using namespace std;
// hello
const int MAX_TRAINS = 100;
const int MAX_RESERVATIONS = 100;

struct Train {
    int id;
    string name;
    int seats;
    string route;
    float fare;
};

struct Reservation {
    int id;
    int trainId;
    string customerName;
    int seatsReserved;
};

struct Admin {
    string username;
    string password;
};

Train trains[MAX_TRAINS];
Reservation reservations[MAX_RESERVATIONS];
int trainCount = 0;
int reservationCount = 0;
Admin admin;

void saveTrains() {
    ofstream outFile("trains.txt");
    for (int i = 0; i < trainCount; ++i) {
        outFile << trains[i].id << "\n" << trains[i].name << "\n" << trains[i].seats << "\n"
                << trains[i].route << "\n" << trains[i].fare << "\n";
    }
    outFile.close();
}

void loadTrains() {
    ifstream inFile("trains.txt");
    if (inFile) {
        while (inFile >> trains[trainCount].id) {
            inFile.ignore();
            getline(inFile, trains[trainCount].name);
            inFile >> trains[trainCount].seats;
            inFile.ignore();
            getline(inFile, trains[trainCount].route);
            inFile >> trains[trainCount].fare;
            trainCount++;
        }
        inFile.close();
    }
}

void saveReservations() {
    ofstream outFile("reservations.txt");
    for (int i = 0; i < reservationCount; ++i) {
        outFile << reservations[i].id << "\n" << reservations[i].trainId << "\n" << reservations[i].customerName << "\n" << reservations[i].seatsReserved << "\n";
    }
    outFile.close();
}

void loadReservations() {
    ifstream inFile("reservations.txt");
    if (inFile) {
        while (inFile >> reservations[reservationCount].id) {
            inFile >> reservations[reservationCount].trainId;
            inFile.ignore();
            getline(inFile, reservations[reservationCount].customerName);
            inFile >> reservations[reservationCount].seatsReserved;
            reservationCount++;
        }
        inFile.close();
    }
}

void saveAdmin() {
    ofstream outFile("admin.txt");
    outFile << admin.username << "\n" << admin.password << "\n";
    outFile.close();
}

void loadAdmin() {
    ifstream inFile("admin.txt");
    if (inFile) {
        getline(inFile, admin.username);
        getline(inFile, admin.password);
        inFile.close();
    }
}

void createAdminAccount() {
    cout << "Enter admin username: ";
    cin >> admin.username;
    cout << "Enter admin password: ";
    cin >> admin.password;
    saveAdmin();
    cout << "Admin account created successfully.\n";
}

bool loginAdmin() {
    string username, password;
    cout << "Enter admin username: ";
    cin >> username;
    cout << "Enter admin password: ";
    cin >> password;
    if (username == admin.username && password == admin.password) {
        return true;
    }
    return false;
}

void addTrain() {
    if (trainCount >= MAX_TRAINS) {
        cout << "Train limit reached. Cannot BOok more trains." << endl;
        return;
    }
    Train train;
    cout << "Enter Train ID: ";
    cin >> train.id;
    cout << "Enter Train Name: ";
    cin.ignore();
    getline(cin, train.name);
    cout << "Enter Number of Seats: ";
    cin >> train.seats;
    cout << "Enter Route: ";
    cin.ignore();
    getline(cin, train.route);
    cout << "Enter Fare: ";
    cin >> train.fare;
    trains[trainCount++] = train;
    saveTrains();
    cout << "Train added successfully." << endl;
}

void deleteTrain() {
    int id;
    cout << "Enter Train ID to delete: ";
    cin >> id;
    for (int i = 0; i < trainCount; ++i) {
        if (trains[i].id == id) {
            for (int j = i; j < trainCount - 1; ++j) {
                trains[j] = trains[j + 1];
            }
            trainCount--;
            saveTrains();
            cout << "Train deleted successfully." << endl;
            return;
        }
    }
    cout << "Train not found." << endl;
}

void updateTrainInfo() {
    int id;
    cout << "Enter Train ID to update: ";
    cin >> id;
    for (int i = 0; i < trainCount; ++i) {
        if (trains[i].id == id) {
            cout << "Enter New Train Name: ";
            cin.ignore();
            getline(cin, trains[i].name);
            cout << "Enter New Number of Seats: ";
            cin >> trains[i].seats;
            cout << "Enter New Route: ";
            cin.ignore();
            getline(cin, trains[i].route);
            cout << "Enter New Fare: ";
            cin >> trains[i].fare;
            saveTrains();
            cout << "Train updated successfully." << endl;
            return;
        }
    }
    cout << "Train not found." << endl;
}

void adminMenu() {
    int choice;
    do {
        cout << "\nAdmin Menu:\n";
        cout << "1. Manage Trains\n";
        cout << "2. Manage Customers\n";
        cout << "3. Manage Finance\n";
        cout << "4. Manage Fares\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                int trainChoice;
                cout << "\nManage Trains:\n";
                cout << "1. Add Train\n";
                cout << "2. Delete Train\n";
                cout << "3. Update Train Info\n";
                cout << "Enter choice: ";
                cin >> trainChoice;
                switch (trainChoice) {
                    case 1:
                        addTrain();
                        break;
                    case 2:
                        deleteTrain();
                        break;
                    case 3:
                        updateTrainInfo();
                        break;
                    default:
                        cout << "Invalid choice." << endl;
                }
                break;
            case 5:
                cout << "Exiting admin menu." << endl;
                break;
            default:
                cout << "Invalid choice." << endl;
        }
    } while (choice != 5);
}

int main() {
    loadTrains();
    loadReservations();
    loadAdmin();
    
    cout << "Railway Reservation System\n";
    
    if (admin.username.empty()) {
        createAdminAccount();
    } else {
        if (!loginAdmin()) {
            cout << "Invalid credentials. Exiting...\n";
            return 0;
        }
    }
    
    adminMenu();
    return 0;
}

