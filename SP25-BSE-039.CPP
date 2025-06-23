#include <iostream>
#include <iomanip>
using namespace std;

const int coaches = 5;
const int rows = 6;
const int seatsPerRow = 4;

struct Seat {
    int seatNo;
    bool isBooked;
    bool isReserved;
};

void initializeTrain(Seat* train[coaches][rows][seatsPerRow]) {
    int counter = 1;
    for (int c = 0; c < coaches; c++) {
        for (int r = 0; r < rows; r++) {
            for (int s = 0; s < seatsPerRow; s++) {
                train[c][r][s] = new Seat;
                train[c][r][s]->seatNo = counter++;
                train[c][r][s]->isBooked = false;
                train[c][r][s]->isReserved = false;
            }
        }
    }

    // Har coach ki last row staff ke liye reserved
    for (int c = 0; c < coaches; c++) {
        for (int s = 0; s < seatsPerRow; s++) {
            train[c][rows - 1][s]->isBooked = true;
            train[c][rows - 1][s]->isReserved = true;
        }
    }
}

void displayCoach(Seat* coach[rows][seatsPerRow], int coachNo) {
    cout << "\n------------ COACH " << coachNo + 1 << " Seat Layout ------------\n";
    for (int r = 0; r < rows; r++) {
        cout << "Row " << setw(2) << r + 1 << ": ";
        for (int s = 0; s < seatsPerRow; s++) {
            if (coach[r][s]->isReserved)
                cout << "[X] ";  // Reserved seats show X regardless of booking
            else if (coach[r][s]->isBooked)
                cout << "[B] ";  // B = Booked by customer
            else
                cout << "[O] ";  // O = Vacant
        }
        cout << endl;
    }
}

void bookSeat(Seat* train[coaches][rows][seatsPerRow], int c, int r, int s) {
    if (train[c][r][s]->isReserved) {
        cout << "This seat is reserved for staff. Cannot be booked.\n";
    }
    else if (train[c][r][s]->isBooked) {
        cout << "Seat already booked. Try another.\n";
    }
    else {
        train[c][r][s]->isBooked = true;
        cout << "Seat booked successfully! (Coach " << c + 1 << ", Row " << r + 1 << ", Seat " << s + 1 << ")\n";
    }
}

void cancelSeat(Seat* train[coaches][rows][seatsPerRow], int c, int r, int s) {
    if (train[c][r][s]->isReserved) {
        cout << "This seat is reserved for staff. Cannot be cancelled.\n";
    }
    else if (!train[c][r][s]->isBooked) {
        cout << "Seat is already vacant.\n";
    }
    else {
        train[c][r][s]->isBooked = false;
        cout << "Booking cancelled for Seat (Coach " << c + 1 << ", Row " << r + 1 << ", Seat " << s + 1 << ")\n";
    }
}

void displayFullTrain(Seat* train[coaches][rows][seatsPerRow]) {
    for (int c = 0; c < coaches; c++)
        displayCoach(train[c], c);
}

void cleanUp(Seat* train[coaches][rows][seatsPerRow]) {
    for (int c = 0; c < coaches; c++)
        for (int r = 0; r < rows; r++)
            for (int s = 0; s < seatsPerRow; s++)
                delete train[c][r][s];
}

int main() {
    Seat* train[coaches][rows][seatsPerRow];
    initializeTrain(train);

    cout << "\n================== Welcome to Train Reservation System ==================\n";

    int choice;
    do {
        cout << "\n---------------- MENU ----------------\n";
        cout << "1. Show Full Train\n";
        cout << "2. Book a Seat\n";
        cout << "3. Cancel a Booking\n";
        cout << "4. Exit\n";
        cout << "Select Option: ";
        cin >> choice;

        if (choice == 1) {
            displayFullTrain(train);
        }
        else if (choice == 2) {
            int c, r, s;
            cout << "Enter Coach (1-" << coaches << "): ";
            cin >> c;
            cout << "Enter Row (1-" << rows << "): ";
            cin >> r;
            cout << "Enter Seat (1-" << seatsPerRow << "): ";
            cin >> s;
            if (c >= 1 && c <= coaches && r >= 1 && r <= rows && s >= 1 && s <= seatsPerRow)
                bookSeat(train, c - 1, r - 1, s - 1);
            else
                cout << "Invalid Seat Details!\n";
        }
        else if (choice == 3) {
            int c, r, s;
            cout << "Enter Coach (1-" << coaches << "): ";
            cin >> c;
            cout << "Enter Row (1-" << rows << "): ";
            cin >> r;
            cout << "Enter Seat (1-" << seatsPerRow << "): ";
            cin >> s;
            if (c >= 1 && c <= coaches && r >= 1 && r <= rows && s >= 1 && s <= seatsPerRow)
                cancelSeat(train, c - 1, r - 1, s - 1);
            else
                cout << "Invalid Seat Details!\n";
        }
        else if (choice != 4)
            cout << "Invalid option. Try again.\n";

    } while (choice != 4);

    cleanUp(train);

    cout << "\nThank you for using the system. Safe journey!\n";
    return 0;
}
