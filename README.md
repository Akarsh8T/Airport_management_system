# Airport Management System

This project is a simple command-line Aeroplane Management System that allows users to manage flight bookings. It includes functionalities to display available flights, book seats, cancel bookings, and display booked tickets.

## Table of Contents

- [Features](#features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Compilation](#compilation)
  - [Usage](#usage)
- [File Structure](#file-structure)
- [Contributing](#contributing)
- [License](#license)

## Features

- **Display Available Flights:** View a list of flights with the number of available seats.
- **Book Seats:** Reserve seats on a flight, entering passenger details and the booking user's username.
- **Cancel Booking:** Cancel a previously made booking.
- **Display Booked Tickets:** Display all booked tickets for a particular flight.

## Getting Started

### Prerequisites

- C compiler (e.g., GCC)

### Compilation

To compile the project, use the following command in your terminal:

```bash
gcc main.c -o aeroplane_management_system
```

### Usage

Run the compiled executable:

```bash
./Airport_management_system
```

Follow the on-screen instructions to navigate through the menu and use the functionalities of the system.

## File Structure

- `main.c`: Main source code file containing the implementation of the Airport Booking System.
- `flights.txt`: Text file storing flight details.


## Contributing

Contributions are welcome! If you'd like to contribute to the project, please follow these steps:

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/YourFeature`)
3. Commit your changes (`git commit -am 'Add some feature'`)
4. Push to the branch (`git push origin feature/YourFeature`)
5. Open a pull request

Please ensure your pull request adheres to the [code of conduct](CODE_OF_CONDUCT.md).

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
