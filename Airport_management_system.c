#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FLIGHTS 4
#define MAX_SEATS 60
#define FILENAME "flights.txt"

struct Passenger {
    char name[50];
    int age;
    char passportNo[20];
    char bookedBy[50];  // Username who booked the seat
};

struct Flight {
    int flightNumber;
    char flightName[50];
    char destination[50];
    int availableSeats;
    struct Passenger passengers[MAX_SEATS];
};

struct User {
    char username[50];
    char password[50];
};

void displayMenu() {
    printf("\n========= Aeroplane Management System =========\n");
    printf("1. Display Available Flights\n");
    printf("2. Book Seats\n");
    printf("3. Cancel Booking\n");
    printf("4. Display Booked Tickets\n");
    printf("5. Exit\n");
    printf("==============================================\n");
}

void displayFlights(struct Flight flights[], int numFlights) {
    printf("\nAvailable Flights:\n");
    for (int i = 0; i < numFlights; i++) {
        printf("Flight %d: %s to %s - %d seats available\n",
            flights[i].flightNumber, flights[i].flightName, flights[i].destination, flights[i].availableSeats);
    }
}

void saveFlightDetailsToFile(struct Flight flights[], int numFlights) {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < numFlights; i++) {
        for (int j = 0; j < MAX_SEATS; j++) {
            struct Passenger *p = &flights[i].passengers[j];
            if (p->age != 0) {
                fprintf(file, "FlightNo:%d, SeatNo:%d ,Name:%s, Age:%d ,PassprtNo:%s, booked by: %s\n", flights[i].flightNumber, j + 1, p->name, p->age, p->passportNo, p->bookedBy);
            }
        }
    }

    fclose(file);
}

void bookSeats(struct Flight *flight, const char *username) {
    int numTickets;
    printf("Enter number of tickets to book: ");
    scanf("%d", &numTickets);

    if (numTickets > flight->availableSeats) {
        printf("Not enough available seats.\n");
        return;
    }

    for (int i = 0; i < numTickets; i++) {
        int seatNumber;
        printf("Enter Seat Number to book (1-%d): ", MAX_SEATS);
        scanf("%d", &seatNumber);

        if (seatNumber < 1 || seatNumber > MAX_SEATS) {
            printf("Invalid seat number.\n");
            i--;
            continue;
        }

        if (flight->passengers[seatNumber - 1].age != 0) {
            printf("Seat already booked.\n");
            i--;
            continue;
        }

        struct Passenger passenger;
        printf("Enter Passenger Name: ");
        scanf("%s", passenger.name);
        printf("Enter Passenger Age: ");
        scanf("%d", &passenger.age);
        printf("Enter Passport Number: ");
        scanf("%s", passenger.passportNo);
        strcpy(passenger.bookedBy, username);

        flight->passengers[seatNumber - 1] = passenger;
        flight->availableSeats--;

        printf("Seat %d booked successfully for %s.\n", seatNumber, passenger.name);
    }

    saveFlightDetailsToFile(flight, MAX_FLIGHTS);
}

void cancelBooking(struct Flight *flight, const char *username) {
    int seatNumber;
    printf("Enter Seat Number to cancel booking (1-%d): ", MAX_SEATS);
    scanf("%d", &seatNumber);

    if (seatNumber < 1 || seatNumber > MAX_SEATS) {
        printf("Invalid seat number.\n");
        return;
    }

    if (strcmp(flight->passengers[seatNumber - 1].bookedBy, username) != 0) {
        printf("You cannot cancel a seat that you haven't booked.\n");
        return;
    }

    flight->passengers[seatNumber - 1].age = 0;
    flight->availableSeats++;

    printf("Booking cancelled successfully.\n");

    saveFlightDetailsToFile(flight, MAX_FLIGHTS);
}

void displayBookedTickets(struct Flight *flight) {
    printf("\nBooked Tickets:\n");
    for (int i = 0; i < MAX_SEATS; i++) {
        if (flight->passengers[i].age != 0) {
            printf("Seat %d: %s, Age: %d, Passport No: %s, Booked By: %s\n", i + 1, flight->passengers[i].name,
                   flight->passengers[i].age, flight->passengers[i].passportNo, flight->passengers[i].bookedBy);
        }
    }
}

int authenticate(struct User users[], int numUsers, char *username) {
    char password[50];
    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    for (int i = 0; i < numUsers; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("Authentication successful. Welcome, %s!\n", username);
            return 1;
        }
    }
    printf("Authentication failed. Please try again.\n");
    return 0;
}

void loadFlights(struct Flight flights[], int numFlights) {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("No previous data found, starting with default data.\n");
        return;
    }

    for (int i = 0; i < numFlights; i++) {
        for (int j = 0; j < MAX_SEATS; j++) {
            flights[i].passengers[j].age = 0;
        }
    }

    int flightNumber, seatNumber, age;
    char name[50], passportNo[20], bookedBy[50];

    while (fscanf(file, "%d %d %s %d %s %s", &flightNumber, &seatNumber, name, &age, passportNo, bookedBy) == 6) {
        for (int i = 0; i < numFlights; i++) {
            if (flights[i].flightNumber == flightNumber) {
                struct Passenger *p = &flights[i].passengers[seatNumber - 1];
                strcpy(p->name, name);
                p->age = age;
                strcpy(p->passportNo, passportNo);
                strcpy(p->bookedBy, bookedBy);
                flights[i].availableSeats--;
            }
        }
    }
    fclose(file);
}

int main() {
    struct Flight flights[MAX_FLIGHTS] = {
        {1, "Air India", "New York", MAX_SEATS},
        {2, "British Airways", "London", MAX_SEATS},
        {3, "Emirates", "Dubai", MAX_SEATS},
        {4, "Singapore Airlines", "Singapore", MAX_SEATS}
    };

    struct User users[] = { {"admin", "password123"}, {"user", "pass"} };
    int numUsers = sizeof(users) / sizeof(users[0]);

    char username[50];
    if (!authenticate(users, numUsers, username)) {
        return 0;
    }

    loadFlights(flights, MAX_FLIGHTS); // Load flights from file

    int choice;
    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        int flightNumber;
        switch (choice) {
            case 1:
                displayFlights(flights, MAX_FLIGHTS);
                break;
            case 2:
                printf("Enter Flight Number to book seats: ");
                scanf("%d", &flightNumber);
                if (flightNumber < 1 || flightNumber > MAX_FLIGHTS) {
                    printf("Invalid flight number.\n");
                } else {
                    bookSeats(&flights[flightNumber - 1], username);
                }
                break;
            case 3:
                printf("Enter Flight Number to cancel booking: ");
                scanf("%d", &flightNumber);
                if (flightNumber < 1 || flightNumber > MAX_FLIGHTS) {
                    printf("Invalid flight number.\n");
                } else {
                    cancelBooking(&flights[flightNumber - 1], username);
                }
                break;
            case 4:
                printf("Enter Flight Number to display booked tickets: ");
                scanf("%d", &flightNumber);
                if (flightNumber < 1 || flightNumber > MAX_FLIGHTS) {
                    printf("Invalid flight number.\n");
                } else {
                    displayBookedTickets(&flights[flightNumber - 1]);
                }
                break;
            case 5:
                printf("Exiting...\n");
                saveFlightDetailsToFile(flights, MAX_FLIGHTS);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

