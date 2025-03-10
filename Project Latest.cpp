#include <iostream>
#include <string>

using namespace std;

// Structure to store admin information
struct Admin {
    string username;
    string password;
};

// Structure to store train information
struct Train {
    int trainID;
    string trainName;
    string route;
    int seats;
};

// Structure to store customer information
struct Customer {
    int customerID;
    string customerName;
    int reservedTrainID;
};

// Global variables
Admin admin = {"user", "user1234"};
Train trains[100];
Customer customers[100];
int trainCount = 0;
int customerCount = 0;
float fares[100];  //price

// Function for admin login
bool login() {
    string username, password;
    cout << "Admin Login\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    if (username == admin.username && password == admin.password) {
        cout << "Login successful!\n";
        return true;
    } else {
        cout << "Login failed. Please try again.\n";
        return false;
    }
}

// Function to display the admin menu
void displayAdminMenu() {
    cout << "\nAdmin Menu\n";
    cout << "1. Manage Trains\n";
    cout << "2. Manage Customers\n";
    cout << "3. Manage Finance\n";
    cout << "4. Manage Fares\n";
    cout << "5. Exit\n";
}

// Functions to manage trains
void addTrain() {
    cout << "Add Train\n";
    cout << "Enter Train ID: ";
    cin >> trains[trainCount].trainID;
    cout << "Enter Train Name: ";
    cin >> trains[trainCount].trainName;
    cout << "Enter Route: ";
    cin >> trains[trainCount].route;
    cout << "Enter Number of Seats: ";
    cin >> trains[trainCount].seats;
    trainCount++;
    cout << "Train added successfully.\n";
}

void deleteTrain() {
    int id;
    cout << "Remove Train\n";
    cout << "Enter Train ID to remove: ";
    cin >> id;
    for (int i = 0; i < trainCount; i++) {
        if (trains[i].trainID == id) {
            for (int j = i; j < trainCount - 1; j++) {
                trains[j] = trains[j + 1];
            }
            trainCount--;
            cout << "Train remove successfully.\n";
            return;
        }
    }
    cout << "Train not found.\n";
}

void updateTrainInfo() {
    int id;
    cout << "Update Train Info\n";
    cout << "Enter Train ID to update: ";
    cin >> id;
    for (int i = 0; i < trainCount; i++) {
        if (trains[i].trainID == id) {
            cout << "Enter new Train Name: ";
            cin >> trains[i].trainName;
            cout << "Enter new Route: ";
            cin >> trains[i].route;
            cout << "Enter new Number of Seats: ";
            cin >> trains[i].seats;
            cout << "Train info updated successfully.\n";
            return;
        }
    }
    cout << "Train not found.\n";
}

void manageTrains() {
    int choice;
    do {
        cout << "\nManage Trains\n";
        cout << "1. Add Train\n";
        cout << "2. Delete Train\n";
        cout << "3. Update Train Info\n";
        cout << "4. Back to Admin Menu\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                addTrain();
                break;
            case 2:
                deleteTrain();
                break;
            case 3:
                updateTrainInfo();
                break;
            case 4:
                cout << "Returning to Admin Menu...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);
}

// Functions to manage customers
void addCustomer() {
    cout << "Add Customer\n";
    cout << "Enter Customer ID: ";
    cin >> customers[customerCount].customerID;
    cout << "Enter Customer Name: ";
    cin >> customers[customerCount].customerName;
    customers[customerCount].reservedTrainID = -1; // No reservation initially
    customerCount++;
    cout << "Customer added successfully.\n";
}

void updateCustomerInfo() {
    int id;
    cout << "Update Customer Info\n";
    cout << "Enter Customer ID to update: ";
    cin >> id;
    for (int i = 0; i < customerCount; i++) {
        if (customers[i].customerID == id) {
            cout << "Enter new Customer Name: ";
            cin >> customers[i].customerName;
            cout << "Customer info updated successfully.\n";
            return;
        }
    }
    cout << "Customer not found.\n";
}

void manageCustomers() {
    int choice;
    do {
        cout << "\nManage Customers\n";
        cout << "1. Add Customer\n";
        cout << "2. Update Customer Info\n";
        cout << "3. Back to Admin Menu\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                addCustomer();
                break;
            case 2:
                updateCustomerInfo();
                break;
            case 3:
                cout << "Returning to Admin Menu...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 3);
}

// Functions to manage finance
void generateMonthlyReport() {
    cout << "Generate Monthly Financial Report\n";
    int totalSeats = 0, reservedSeats = 0;
    for (int i = 0; i < trainCount; i++) {
        totalSeats += trains[i].seats;
    }
    for (int i = 0; i < customerCount; i++) {
        if (customers[i].reservedTrainID != -1) {
            reservedSeats++;
        }
    }
    float revenue = reservedSeats * 500; // Example calculation: each reservation earns 500
    cout << "Total Trains: " << trainCount << "\n";
    cout << "Total Seats: " << totalSeats << "\n";
    cout << "Reserved Seats: " << reservedSeats << "\n";
    cout << "Monthly Revenue: Rs" << revenue << "\n";
}

void manageFinance() {
    int choice;
    do {
        cout << "\nManage Finance\n";
        cout << "1. Generate Monthly Report\n";
        cout << "2. Back to Admin Menu\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                generateMonthlyReport();
                break;
            case 2:
                cout << "Returning to Admin Menu...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 2);
}

// Functions to manage fares
void updateFares() {
    cout << "Update Fares\n";
    cout << "Enter new fares (for each train):\n";
    for (int i = 0; i < trainCount; i++) {
        cout << "Train ID " << trains[i].trainID << ": ";
        cin >> fares[i];
    }
    cout << "Fares updated successfully.\n";
}

void manageFares() {
    int choice;
    do {
        cout << "\nManage Fares\n";
        cout << "1. Update Fares\n";
        cout << "2. Back to Admin Menu\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                updateFares();
                break;
            case 2:
                cout << "Returning to Admin Menu...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 2);
}

// Admin menu function
void adminMenu() {
    int choice;
    do {
        displayAdminMenu();
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                manageTrains();
                break;
            case 2:
                manageCustomers();
                break;
            case 3:
                manageFinance();
                break;
            case 4:
                manageFares();
                break;
            case 5:
                cout << "Exit\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);
}

// Main function
int main() {
    if (login()) {
        adminMenu();
    } else {
        cout << "Invalid login.";
    }
    return 0;
}

