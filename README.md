# Railway Management System

## Project Overview
The Railway Management System is a robust application developed in C++ using *Object-Oriented Programming (OOP)* principles and the *Raylib* library for graphical user interface (GUI). The system is designed to manage train schedules, customer details, and reservations efficiently. It incorporates file handling for persistent data storage and retrieval.

## Features

### Train Management
- *Add Trains*: Add new train details, including train number, name, starting point, destination, and timings.
- *Search Trains*: Search for trains by name.
- *Delete Trains*: Remove trains from the system.
- *List Trains*: View all trains in the system.

### Customer Management
- *Add Customers*: Save customer details such as name, age, and contact information.
- *List Customers*: View all customer records.

### File Handling
- Save train and customer data to files for persistence.
- Retrieve train and customer data from files during program startup.

### GUI
The GUI is developed using the *Raylib* library, providing a user-friendly and interactive experience. The interface includes menus and forms for input and navigation.

## Installation

### Prerequisites
1. *C++ Compiler*: Ensure you have a C++ compiler (like GCC or MSVC) installed.
2. *Raylib Library*: Install the Raylib library for GUI development.
    - For installation, visit: [Raylib Installation Guide](https://github.com/raysan5/raylib/wiki/Working-on-Your-First-Raylib-Project)

## Usage

1. Launch the application.
2. Login using username and password for admin account
      Username:admin
      Password:admin
3. Use the menu options to navigate:
    - Manage trains: Add, search, delete, or view trains.
    - Manage customers: Add or view customer details.
4. Exit the application to save data automatically.

---

## Contribution
Contributions are welcome! To contribute:
1. Fork the repository.
2. Create a new branch:
    bash
    git checkout -b feature-name
    
3. Commit your changes:
    bash
    git commit -m "Description of changes"
    
4. Push to the branch:
    bash
    git push origin feature-name
    
5. Create a pull request.

---

## License
This project is licensed under the MIT License. See the LICENSE file for more details.

---

## Acknowledgments
- [Raylib](https://www.raylib.com/) for the easy-to-use graphics library.
- Community contributors for their support and inspiration.