#define _CRT_SECURE_NO_WARNINGS

#include "raylib.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <vector>
#include <cstring>
#include <memory>
#include <sstream>
using namespace std;

// GUI-specific constants
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;
const int BUTTON_WIDTH = 200;
const int BUTTON_HEIGHT = 40;
const int INPUT_BOX_WIDTH = 300;
const int INPUT_BOX_HEIGHT = 40;

// Forward declarations
class Details;
class Registration;
class Ticket;

// GUI State management
struct GuiState
{
    bool isLoggedIn = false;
    bool isAdmin = false;
    bool showLoginScreen = true;
    bool showMainMenu = false;
    bool showCustomerDetails = false;
    bool showTrainBooking = false;
    bool showTickets = false;
    bool showAddTrain = false;
    bool showRemoveTrain = false;
    Rectangle usernameBox = { SCREEN_WIDTH / 2 - INPUT_BOX_WIDTH / 2, 300, INPUT_BOX_WIDTH, INPUT_BOX_HEIGHT };
    Rectangle passwordBox = { SCREEN_WIDTH / 2 - INPUT_BOX_WIDTH / 2, 370, INPUT_BOX_WIDTH, INPUT_BOX_HEIGHT };
    Rectangle trainNameBox = { SCREEN_WIDTH / 2 - INPUT_BOX_WIDTH / 2, 300, INPUT_BOX_WIDTH, INPUT_BOX_HEIGHT };
    char username[50] = "";
    char password[50] = "";
    char trainName[50] = "";
    bool usernameEditMode = false;
    bool passwordEditMode = false;
    bool trainNameEditMode = false;
    char customerName[50] = "";
    char customerAge[10] = "";
    char customerGender[20] = "";
    char customerPhone[20] = "";
    char customerBirthPref[20] = "";
    string errorMessage = "";
    bool showError = false;
    bool nameEditMode = false;
    bool ageEditMode = false;
    bool genderEditMode = false;
    bool phoneEditMode = false;
    bool birthPrefEditMode = false;
    Rectangle ageBox = { SCREEN_WIDTH / 2 - INPUT_BOX_WIDTH / 2, 220, INPUT_BOX_WIDTH, INPUT_BOX_HEIGHT };
    Rectangle genderBox = { SCREEN_WIDTH / 2 - INPUT_BOX_WIDTH / 2, 290, INPUT_BOX_WIDTH, INPUT_BOX_HEIGHT };
    Rectangle phoneBox = { SCREEN_WIDTH / 2 - INPUT_BOX_WIDTH / 2, 360, INPUT_BOX_WIDTH, INPUT_BOX_HEIGHT };
    Rectangle birthPrefBox = { SCREEN_WIDTH / 2 - INPUT_BOX_WIDTH / 2, 430, INPUT_BOX_WIDTH, INPUT_BOX_HEIGHT };

    // Generic input handling
    struct InputBox {
        Rectangle rect;
        char text[50];
        bool editMode;
        const char* label;
    };

    // Input boxes for customer details
    InputBox nameInput = {
        { SCREEN_WIDTH / 2 - INPUT_BOX_WIDTH / 2, 150, INPUT_BOX_WIDTH, INPUT_BOX_HEIGHT },
        "", false, "Name:"
    };
    InputBox ageInput = {
        { SCREEN_WIDTH / 2 - INPUT_BOX_WIDTH / 2, 220, INPUT_BOX_WIDTH, INPUT_BOX_HEIGHT },
        "", false, "Age:"
    };
    InputBox genderInput = {
        { SCREEN_WIDTH / 2 - INPUT_BOX_WIDTH / 2, 290, INPUT_BOX_WIDTH, INPUT_BOX_HEIGHT },
        "", false, "Gender:"
    };
    InputBox phoneInput = {
        { SCREEN_WIDTH / 2 - INPUT_BOX_WIDTH / 2, 360, INPUT_BOX_WIDTH, INPUT_BOX_HEIGHT },
        "", false, "Phone:"
    };
    InputBox birthPrefInput = {
        { SCREEN_WIDTH / 2 - INPUT_BOX_WIDTH / 2, 430, INPUT_BOX_WIDTH, INPUT_BOX_HEIGHT },
        "", false, "Birth Preference:"
    };

    InputBox trainSelectInput = {
        { 50, 500, INPUT_BOX_WIDTH, INPUT_BOX_HEIGHT },
        "", false, "Select Train Number:"
    };

    InputBox pnrSearchInput = {
        { 50, 120, INPUT_BOX_WIDTH, INPUT_BOX_HEIGHT },
        "", false, "Enter PNR:"
    };

    // Input boxes for adding trains
    InputBox trainNameInput = {
        { 50, 150, INPUT_BOX_WIDTH, INPUT_BOX_HEIGHT },
        "", false, "Train Name:"
    };
    InputBox trainNumberInput = {
        { 50, 220, INPUT_BOX_WIDTH, INPUT_BOX_HEIGHT },
        "", false, "Train Number:"
    };
    InputBox sourceInput = {
        { 50, 290, INPUT_BOX_WIDTH, INPUT_BOX_HEIGHT },
        "", false, "Source Station:"
    };
    InputBox destinationInput = {
        { 50, 360, INPUT_BOX_WIDTH, INPUT_BOX_HEIGHT },
        "", false, "Destination Station:"
    };
    InputBox departureInput = {
        { 50, 430, INPUT_BOX_WIDTH, INPUT_BOX_HEIGHT },
        "", false, "Departure Time:"
    };
    InputBox fareInput = {
        { 50, 500, INPUT_BOX_WIDTH, INPUT_BOX_HEIGHT },
        "", false, "Fare Amount:"
    };

    bool showBookingConfirmation = false;
    string selectedTrain;
    string selectedTrainNumber;
    string selectedFare;

    // Add a confirmation dialog box
    Rectangle confirmationBox = {
        SCREEN_WIDTH / 2 - 300,
        SCREEN_HEIGHT / 2 - 200,
        600,
        400
    };
};

class Details
{
public:
    static string name[6], gender[6], bp[6];
    static int age[6], cId[6], pnr, n;
    int phoneNo;
    char arr[100];

    void information();
    bool saveToFile(const GuiState& state);
};

bool Details::saveToFile(const GuiState& state)
{
    time_t now = time(0);
    char dt[26];
    strftime(dt, sizeof(dt), "%Y-%m-%d %H:%M:%S", localtime(&now));

    string filename = "customer_details.txt";
    ofstream file(filename, ios::app);

    if (file.is_open())
    {
        // Generate unique PNR
        static int pnrCounter = 10000;
        pnr = ++pnrCounter;

        // Save customer info
        n = 1; // Single customer entry
        name[0] = state.customerName;
        age[0] = stoi(state.customerAge);
        gender[0] = state.customerGender;
        bp[0] = state.customerBirthPref;
        cId[0] = pnr;

        file << pnr << ","
            << state.customerName << ","
            << state.customerAge << ","
            << state.customerGender << ","
            << state.customerPhone << ","
            << state.customerBirthPref << ","
            << dt << "\n";

        file.close();
        return true;
    }
    return false;
}

// Static member initialization
string Details::name[6];
string Details::gender[6];
string Details::bp[6];
int Details::age[6];
int Details::cId[6];
int Details::pnr;
int Details::n;

class Registration : public Details
{
public:
    static int choice;
    static float charges;
    void trains();
};

float Registration::charges;
int Registration::choice;

class Ticket : public Registration
{
public:
    void Bill();
    void database();
    void dispBill();
    void dispDatabase();
    void deletedata();
};

void Ticket::Bill() {
    ofstream fout("tickets.txt", ios::app);
    time_t now = time(0);
    char* dt = ctime(&now);

    fout << Details::pnr << ","
        << Details::name[0] << ","
        << Details::age[0] << ","
        << Details::gender[0] << ","
        << Details::bp[0] << ","
        << Registration::charges << ","
        << dt;
    fout.close();
}

void Ticket::database() {
    ofstream db("database.txt", ios::app);
    time_t now = time(0);
    char* dt = ctime(&now);

    db << Details::pnr << ","
        << Details::name[0] << ","
        << Details::age[0] << ","
        << Details::gender[0] << ","
        << Details::bp[0] << ","
        << Registration::choice << ","
        << Registration::charges << ","
        << dt;
    db.close();
}

void Ticket::dispBill() {
    ifstream fin("tickets.txt");
    string line;
    bool found = false;

    while (getline(fin, line)) {
        stringstream ss(line);
        string pnrStr;
        getline(ss, pnrStr, ',');

        if (stoi(pnrStr) == Details::pnr) {
            found = true;
            vector<string> fields;
            string field;

            while (getline(ss, field, ',')) {
                fields.push_back(field);
            }

            cout << "\n\t\t_TICKET_\n"
                << "\n\tPNR: " << pnrStr
                << "\n\tPassenger Name: " << fields[0]
                << "\n\tAge: " << fields[1]
                << "\n\tGender: " << fields[2]
                << "\n\tBerth Preference: " << fields[3]
                << "\n\tCharges: Rs." << fields[4]
                << "\n\tBooking Time: " << fields[5]
                << "\n\t_\n";
            break;
        }
    }
    fin.close();

    if (!found) {
        cout << "\n\tTicket not found!\n";
    }
}

void Ticket::dispDatabase() {
    ifstream db("database.txt");
    string line;

    cout << "\n\t\t_DATABASE_\n\n";
    while (getline(db, line)) {
        stringstream ss(line);
        vector<string> fields;
        string field;

        while (getline(ss, field, ',')) {
            fields.push_back(field);
        }

        cout << "\tPNR: " << fields[0]
            << "\n\tPassenger: " << fields[1]
            << "\n\tAge: " << fields[2]
            << "\n\tGender: " << fields[3]
            << "\n\tBerth: " << fields[4]
            << "\n\tTrain Choice: " << fields[5]
            << "\n\tCharges: Rs." << fields[6]
            << "\n\tBooking Time: " << fields[7]
            << "\n\t_\n\n";
    }
    db.close();
}

void Ticket::deletedata() {
    int pnrToDelete;
    cout << "\n\tEnter PNR to delete: ";
    cin >> pnrToDelete;

    // Update tickets.txt
    ifstream ticketsIn("tickets.txt");
    ofstream ticketsTemp("tickets_temp.txt");
    string line;
    bool found = false;

    while (getline(ticketsIn, line)) {
        stringstream ss(line);
        string pnrStr;
        getline(ss, pnrStr, ',');

        if (stoi(pnrStr) != pnrToDelete) {
            ticketsTemp << line << endl;
        }
        else {
            found = true;
        }
    }

    ticketsIn.close();
    ticketsTemp.close();

    // Update database.txt
    ifstream dbIn("database.txt");
    ofstream dbTemp("database_temp.txt");

    while (getline(dbIn, line)) {
        stringstream ss(line);
        string pnrStr;
        getline(ss, pnrStr, ',');

        if (stoi(pnrStr) != pnrToDelete) {
            dbTemp << line << endl;
        }
    }

    dbIn.close();
    dbTemp.close();

    // Replace original files with temp files
    remove("tickets.txt");
    rename("tickets_temp.txt", "tickets.txt");
    remove("database.txt");
    rename("database_temp.txt", "database.txt");

    if (found) {
        cout << "\n\tTicket with PNR " << pnrToDelete << " deleted successfully.\n";
    }
    else {
        cout << "\n\tTicket not found!\n";
    }
}


class RailwayGui
{
private:
    GuiState state;
    Details details;
    Registration reg;
    Ticket ticket;

    void DrawLoginScreen();
    void DrawMainMenu();
    void DrawCustomerDetailsScreen();
    void DrawTrainBookingScreen();
    void DrawTicketsScreen();
    void DrawAddTrainScreen();
    void DrawRemoveTrainScreen();
    void UpdateGui();

    void DrawInputBox(GuiState::InputBox& input) {
        DrawRectangleRec(input.rect, LIGHTGRAY);
        DrawRectangleLinesEx(input.rect, 2, input.editMode ? RED : DARKGRAY);
        DrawText(input.label, input.rect.x, input.rect.y - 20, 20, DARKGRAY);
        DrawText(input.text, input.rect.x + 5, input.rect.y + 10, 20, DARKGRAY);
    }

    void HandleInputBox(GuiState::InputBox& input) {
        Vector2 mousePoint = GetMousePosition();

        // Handle mouse selection
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            input.editMode = CheckCollisionPointRec(mousePoint, input.rect);
        }

        // Handle text input when active
        if (input.editMode) {
            int key = GetCharPressed();
            while (key > 0) {
                if ((key >= 32) && (key <= 125) && (strlen(input.text) < 49)) {
                    input.text[strlen(input.text)] = (char)key;
                    input.text[strlen(input.text) + 1] = '\0';
                }
                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE) && strlen(input.text) > 0) {
                input.text[strlen(input.text) - 1] = '\0';
            }
        }
    }

public:
    RailwayGui()
    {
        InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Railways Management System");
        SetTargetFPS(60);
        InitializeMockData();
    }

    ~RailwayGui()
    {
        CloseWindow();
    }

    void Run()
    {
        while (!WindowShouldClose())
        {
            UpdateGui();

            BeginDrawing();
            ClearBackground(RAYWHITE);

            if (state.showLoginScreen)
                DrawLoginScreen();
            else if (state.showMainMenu)
                DrawMainMenu();
            else if (state.showCustomerDetails)
                DrawCustomerDetailsScreen();
            else if (state.showTrainBooking)
                DrawTrainBookingScreen();
            else if (state.showTickets)
                DrawTicketsScreen();
            else if (state.showAddTrain)
                DrawAddTrainScreen();
            else if (state.showRemoveTrain)
                DrawRemoveTrainScreen();

            EndDrawing();
        }
    }

    void InitializeMockData() {

        // Create mock train data
        ofstream trainFile("trains.txt", ios::trunc);
        if (trainFile.is_open()) {
            trainFile << "SEECS Express,1001,SEECS,S3H,06:00,1500\n"
                << "SNS Express,1002,SNS,Main Office,08:30,1200\n"
                << "NBS Express,1003,NBS,C1,10:45,800\n"
                << "S3H Express,1004,S3H,SEECS,14:15,1300\n"
                << "SADA Express,1005,SADA,TUADA,16:30,1100\n";
            trainFile.close();
        }
    }
};

void RailwayGui::DrawLoginScreen()
{
    DrawText("Railways Login", SCREEN_WIDTH / 2 - MeasureText("Railways Login", 40) / 2, 200, 40, DARKBLUE);

    DrawRectangleRec(state.usernameBox, LIGHTGRAY);
    DrawRectangleLinesEx(state.usernameBox, 2, state.usernameEditMode ? RED : DARKGRAY);
    DrawText("Username:", state.usernameBox.x, state.usernameBox.y - 20, 20, DARKGRAY);
    DrawText(state.username, state.usernameBox.x + 5, state.usernameBox.y + 10, 20, DARKGRAY);

    string s = string(strlen(state.password), '*');

    DrawRectangleRec(state.passwordBox, LIGHTGRAY);
    DrawRectangleLinesEx(state.passwordBox, 2, state.passwordEditMode ? RED : DARKGRAY);
    DrawText("Password:", state.passwordBox.x, state.passwordBox.y - 20, 20, DARKGRAY);
    DrawText(s.c_str(), state.passwordBox.x + 5, state.passwordBox.y + 10, 20, DARKGRAY);

    Rectangle loginButton = { SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, 450, BUTTON_WIDTH, BUTTON_HEIGHT };
    DrawRectangleRec(loginButton, BLUE);
    DrawText("Login", loginButton.x + BUTTON_WIDTH / 2 - MeasureText("Login", 20) / 2,
        loginButton.y + BUTTON_HEIGHT / 2 - 10, 20, WHITE);
}

void RailwayGui::DrawMainMenu()
{
    DrawText("Railways - Main Menu", 50, 50, 40, DARKBLUE);

    vector<const char*> menuItems = {
        "Customer Details",
        "Train Booking",
        "Tickets and Charges",
        "Add Train",
        "Remove Train",
        "Exit" };

    for (size_t i = 0; i < menuItems.size(); i++)
    {
        Rectangle btnRect = { 50.0f, 150.0f + i * 60, BUTTON_WIDTH, BUTTON_HEIGHT };
        DrawRectangleRec(btnRect, BLUE);
        DrawText(menuItems[i], btnRect.x + 10, btnRect.y + 10, 20, WHITE);
    }
}

// Implementation of other draw methods would go here...

void RailwayGui::DrawCustomerDetailsScreen()
{
    DrawText("Customer Details", SCREEN_WIDTH / 2 - MeasureText("Customer Details", 40) / 2, 50, 40, DARKBLUE);

    // Draw all input boxes
    DrawInputBox(state.nameInput);
    DrawInputBox(state.ageInput);
    DrawInputBox(state.genderInput);
    DrawInputBox(state.phoneInput);
    DrawInputBox(state.birthPrefInput);

    // Submit and Back buttons with consistent positioning
    Rectangle submitButton = { SCREEN_WIDTH / 2 - BUTTON_WIDTH - 20, 500, BUTTON_WIDTH, BUTTON_HEIGHT };
    Rectangle backButton = { SCREEN_WIDTH / 2 + 20, 500, BUTTON_WIDTH, BUTTON_HEIGHT };

    DrawRectangleRec(submitButton, BLUE);
    DrawText("Submit", submitButton.x + BUTTON_WIDTH / 2 - MeasureText("Submit", 20) / 2,
        submitButton.y + BUTTON_HEIGHT / 2 - 10, 20, WHITE);

    DrawRectangleRec(backButton, RED);
    DrawText("Back", backButton.x + BUTTON_WIDTH / 2 - MeasureText("Back", 20) / 2,
        backButton.y + BUTTON_HEIGHT / 2 - 10, 20, WHITE);

    // Display error message if any
    if (state.showError) {
        DrawText(state.errorMessage.c_str(), SCREEN_WIDTH / 2 - MeasureText(state.errorMessage.c_str(), 20) / 2,
            550, 20, RED);
    }
}



void RailwayGui::DrawTrainBookingScreen()
{
    DrawText("Train Booking", SCREEN_WIDTH / 2 - MeasureText("Train Booking", 40) / 2, 50, 40, DARKBLUE);

    // Available trains section
    DrawText("Available Trains", 50, 120, 30, DARKBLUE);

    // Headers
    int headerY = 170;
    DrawRectangle(50, headerY - 10, SCREEN_WIDTH - 100, 40, DARKBLUE);
    DrawText("Train No.", 70, headerY, 20, WHITE);
    DrawText("Train Name", 200, headerY, 20, WHITE);
    DrawText("Source", 400, headerY, 20, WHITE);
    DrawText("Destination", 600, headerY, 20, WHITE);
    DrawText("Time", 800, headerY, 20, WHITE);
    DrawText("Fare", 950, headerY, 20, WHITE);

    // Read and display trains from file
    ifstream trainFile("trains.txt");
    string line;
    int trainY = headerY + 50;
    int count = 0;

    while (getline(trainFile, line)) {
        stringstream ss(line);
        vector<string> fields;
        string field;

        while (getline(ss, field, ',')) {
            fields.push_back(field);
        }

        // Alternate row colors and highlight selected train
        Rectangle trainRect = { 50, trainY - 5, SCREEN_WIDTH - 100, 40 };
        if (state.selectedTrain == fields[0]) {
            DrawRectangleRec(trainRect, SKYBLUE);
        }
        else if (count % 2 == 0) {
            DrawRectangleRec(trainRect, RAYWHITE);
        }
        else {
            DrawRectangleRec(trainRect, LIGHTGRAY);
        }

        // Draw train details
        DrawText(fields[1].c_str(), 70, trainY, 20, DARKGRAY);     // Train Number
        DrawText(fields[0].c_str(), 200, trainY, 20, DARKGRAY);    // Name
        DrawText(fields[2].c_str(), 400, trainY, 20, DARKGRAY);    // Source
        DrawText(fields[3].c_str(), 600, trainY, 20, DARKGRAY);    // Destination
        DrawText(fields[4].c_str(), 800, trainY, 20, DARKGRAY);    // Time
        DrawText(("Rs. " + fields[5]).c_str(), 950, trainY, 20, DARKGRAY); // Fare

        trainY += 40;
        count++;
    }
    trainFile.close();

    // Book and Back buttons
    Rectangle bookButton = { SCREEN_WIDTH / 2 - BUTTON_WIDTH - 20, SCREEN_HEIGHT - 70, BUTTON_WIDTH, BUTTON_HEIGHT };
    Rectangle backButton = { SCREEN_WIDTH / 2 + 20, SCREEN_HEIGHT - 70, BUTTON_WIDTH, BUTTON_HEIGHT };

    DrawRectangleRec(bookButton, state.selectedTrain.empty() ? GRAY : GREEN);
    DrawText("Book", bookButton.x + BUTTON_WIDTH / 2 - MeasureText("Book", 20) / 2,
        bookButton.y + BUTTON_HEIGHT / 2 - 10, 20, WHITE);

    DrawRectangleRec(backButton, RED);
    DrawText("Back", backButton.x + BUTTON_WIDTH / 2 - MeasureText("Back", 20) / 2,
        backButton.y + BUTTON_HEIGHT / 2 - 10, 20, WHITE);

    // Draw booking confirmation dialog if active
    if (state.showBookingConfirmation) {
        // Semi-transparent background
        DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, { 0, 0, 0, 120 });

        // Confirmation dialog box
        DrawRectangleRec(state.confirmationBox, WHITE);
        DrawRectangleLinesEx(state.confirmationBox, 2, DARKBLUE);

        // Dialog content
        DrawText("Confirm Booking",
            state.confirmationBox.x + 300 - MeasureText("Confirm Booking", 30) / 2,
            state.confirmationBox.y + 20, 30, DARKBLUE);

        DrawText("Selected Train Details:",
            state.confirmationBox.x + 20,
            state.confirmationBox.y + 70, 20, DARKGRAY);

        DrawText(("Train: " + state.selectedTrain).c_str(),
            state.confirmationBox.x + 20,
            state.confirmationBox.y + 100, 20, DARKGRAY);

        DrawText(("Train Number: " + state.selectedTrainNumber).c_str(),
            state.confirmationBox.x + 20,
            state.confirmationBox.y + 130, 20, DARKGRAY);

        DrawText(("Fare: Rs. " + state.selectedFare).c_str(),
            state.confirmationBox.x + 20,
            state.confirmationBox.y + 160, 20, DARKGRAY);

        // Confirm and Cancel buttons
        Rectangle confirmButton = {
            state.confirmationBox.x + 100,
            state.confirmationBox.y + 300,
            BUTTON_WIDTH,
            BUTTON_HEIGHT
        };
        Rectangle cancelButton = {
            state.confirmationBox.x + 300,
            state.confirmationBox.y + 300,
            BUTTON_WIDTH,
            BUTTON_HEIGHT
        };

        DrawRectangleRec(confirmButton, GREEN);
        DrawText("Confirm", confirmButton.x + BUTTON_WIDTH / 2 - MeasureText("Confirm", 20) / 2,
            confirmButton.y + BUTTON_HEIGHT / 2 - 10, 20, WHITE);

        DrawRectangleRec(cancelButton, RED);
        DrawText("Cancel", cancelButton.x + BUTTON_WIDTH / 2 - MeasureText("Cancel", 20) / 2,
            cancelButton.y + BUTTON_HEIGHT / 2 - 10, 20, WHITE);
    }

    // Display error message if any
    if (state.showError) {
        DrawText(state.errorMessage.c_str(),
            SCREEN_WIDTH / 2 - MeasureText(state.errorMessage.c_str(), 20) / 2,
            SCREEN_HEIGHT - 120, 20, RED);
    }
}

void RailwayGui::DrawTicketsScreen()
{
    DrawText("Tickets and Charges", SCREEN_WIDTH / 2 - MeasureText("Tickets and Charges", 40) / 2, 50, 40, DARKBLUE);

    // Draw PNR search box
    DrawInputBox(state.pnrSearchInput);

    // Search button
    Rectangle searchButton = { 50 + INPUT_BOX_WIDTH + 20, 120, BUTTON_WIDTH, BUTTON_HEIGHT };
    DrawRectangleRec(searchButton, BLUE);
    DrawText("Search", searchButton.x + BUTTON_WIDTH / 2 - MeasureText("Search", 20) / 2,
        searchButton.y + BUTTON_HEIGHT / 2 - 10, 20, WHITE);

    // Ticket Display Area
    Rectangle ticketArea = { 50, 180, SCREEN_WIDTH - 100, SCREEN_HEIGHT - 300 };
    DrawRectangleRec(ticketArea, LIGHTGRAY);
    DrawRectangleLinesEx(ticketArea, 2, DARKGRAY);

    // Headers with separating lines
    int headerY = 200;
    int columnX[] = { 70, 200, 400, 600, 800, 950 };
    const char* headers[] = { "PNR", "Name", "Train", "Date", "Status", "Charges" };

    // Draw header background
    DrawRectangle(50, headerY - 10, SCREEN_WIDTH - 100, 40, DARKBLUE);

    // Draw headers
    for (int i = 0; i < 6; i++) {
        DrawText(headers[i], columnX[i], headerY, 20, WHITE);
    }

    // If searching for specific PNR
    if (strlen(state.pnrSearchInput.text) > 0) {
        ifstream file("tickets.txt");
        string line;
        bool found = false;
        int dataY = headerY + 50;

        while (getline(file, line)) {
            stringstream ss(line);
            vector<string> fields;
            string field;

            while (getline(ss, field, ',')) {
                fields.push_back(field);
            }

            if (fields[0] == state.pnrSearchInput.text) {
                found = true;

                // Highlight the found ticket
                DrawRectangle(51, dataY - 5, SCREEN_WIDTH - 102, 40, LIGHTGRAY);

                // Draw ticket details
                DrawText(fields[0].c_str(), columnX[0], dataY, 20, DARKBLUE);  // PNR
                DrawText(fields[1].c_str(), columnX[1], dataY, 20, DARKBLUE);  // Name
                DrawText("SEECS Express", columnX[2], dataY, 20, DARKBLUE);    // Train
                DrawText(fields[6].c_str(), columnX[3], dataY, 20, DARKBLUE);  // Date
                DrawText("Confirmed", columnX[4], dataY, 20, GREEN);           // Status
                DrawText(("Rs. " + fields[5]).c_str(), columnX[5], dataY, 20, DARKBLUE); // Charges
                break;
            }
        }
        file.close();

        if (!found) {
            state.errorMessage = "No ticket found with PNR: " + string(state.pnrSearchInput.text);
            state.showError = true;
        }
    }
    // If not searching, show recent tickets
    else {
        ifstream file("tickets.txt");
        string line;
        int dataY = headerY + 50;
        int count = 0;

        while (getline(file, line) && count < 8) { // Show up to 8 recent tickets
            stringstream ss(line);
            vector<string> fields;
            string field;

            while (getline(ss, field, ',')) {
                fields.push_back(field);
            }

            // Alternate row colors
            if (count % 2 == 0) {
                DrawRectangle(51, dataY - 5, SCREEN_WIDTH - 102, 40, RAYWHITE);
            }
            else {
                DrawRectangle(51, dataY - 5, SCREEN_WIDTH - 102, 40, LIGHTGRAY);
            }

            // Draw ticket details
            DrawText(fields[0].c_str(), columnX[0], dataY, 20, DARKGRAY);  // PNR
            DrawText(fields[1].c_str(), columnX[1], dataY, 20, DARKGRAY);  // Name
            DrawText("SEECS Express", columnX[2], dataY, 20, DARKGRAY);    // Train
            DrawText(fields[6].c_str(), columnX[3], dataY, 20, DARKGRAY);  // Date
            DrawText("Confirmed", columnX[4], dataY, 20, GREEN);           // Status
            DrawText(("Rs. " + fields[5]).c_str(), columnX[5], dataY, 20, DARKGRAY); // Charges

            dataY += 40;
            count++;
        }
        file.close();
    }

    // Back button
    Rectangle backButton = { SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT - 70, BUTTON_WIDTH, BUTTON_HEIGHT };
    DrawRectangleRec(backButton, RED);
    DrawText("Back", backButton.x + BUTTON_WIDTH / 2 - MeasureText("Back", 20) / 2,
        backButton.y + BUTTON_HEIGHT / 2 - 10, 20, WHITE);

    // Display error message if any
    if (state.showError) {
        DrawText(state.errorMessage.c_str(),
            SCREEN_WIDTH / 2 - MeasureText(state.errorMessage.c_str(), 20) / 2,
            SCREEN_HEIGHT - 120, 20, RED);
    }
}

void RailwayGui::DrawAddTrainScreen()
{
    DrawText("Add New Train", SCREEN_WIDTH / 2 - MeasureText("Add New Train", 40) / 2, 50, 40, DARKBLUE);

    // Draw all input boxes
    DrawInputBox(state.trainNameInput);
    DrawInputBox(state.trainNumberInput);
    DrawInputBox(state.sourceInput);
    DrawInputBox(state.destinationInput);
    DrawInputBox(state.departureInput);
    DrawInputBox(state.fareInput);

    // Add and Back buttons with consistent positioning
    Rectangle addButton = { SCREEN_WIDTH / 2 - BUTTON_WIDTH - 20, 570, BUTTON_WIDTH, BUTTON_HEIGHT };
    Rectangle backButton = { SCREEN_WIDTH / 2 + 20, 570, BUTTON_WIDTH, BUTTON_HEIGHT };

    DrawRectangleRec(addButton, GREEN);
    DrawText("Add Train", addButton.x + BUTTON_WIDTH / 2 - MeasureText("Add Train", 20) / 2,
        addButton.y + BUTTON_HEIGHT / 2 - 10, 20, WHITE);

    DrawRectangleRec(backButton, RED);
    DrawText("Back", backButton.x + BUTTON_WIDTH / 2 - MeasureText("Back", 20) / 2,
        backButton.y + BUTTON_HEIGHT / 2 - 10, 20, WHITE);

    // Display error message if any
    if (state.showError) {
        DrawText(state.errorMessage.c_str(),
            SCREEN_WIDTH / 2 - MeasureText(state.errorMessage.c_str(), 20) / 2,
            530, 20, RED);
    }
}


void RailwayGui::DrawRemoveTrainScreen()
{
    DrawText("Remove Train", 50, 50, 40, DARKBLUE);
    DrawText("Available Trains", 50, 120, 30, DARKBLUE);

    // Initialize static variables to store train data
    static vector<string> trains;
    static float lastUpdateTime = 0;
    float currentTime = GetTime();

    // Refresh train data every second
    if (currentTime - lastUpdateTime >= 1.0f || trains.empty())
    {
        trains.clear();
        ifstream trainFile("trains.txt");
        string train;

        if (trainFile.is_open())
        {
            while (getline(trainFile, train))
            {
                if (!train.empty())
                {
                    trains.push_back(train);
                }
            }
            trainFile.close();
            lastUpdateTime = currentTime;
        }
    }

    // Display trains and remove buttons
    for (size_t i = 0; i < trains.size(); i++)
    {
        Rectangle trainRect = { 50, 170.0f + i * 60, SCREEN_WIDTH - 300, 50 };
        Rectangle removeButton = { SCREEN_WIDTH - 220, 170.0f + i * 60, BUTTON_WIDTH, 50 };

        DrawRectangleRec(trainRect, LIGHTGRAY);
        DrawText(trains[i].c_str(), trainRect.x + 10, trainRect.y + 15, 20, DARKGRAY);

        DrawRectangleRec(removeButton, RED);
        DrawText("Remove", removeButton.x + BUTTON_WIDTH / 2 - MeasureText("Remove", 20) / 2,
            removeButton.y + 25 - 10, 20, WHITE);
    }

    // Back button
    Rectangle backButton = { 50, SCREEN_HEIGHT - 70, BUTTON_WIDTH, BUTTON_HEIGHT };
    DrawRectangleRec(backButton, RED);
    DrawText("Back", backButton.x + BUTTON_WIDTH / 2 - MeasureText("Back", 20) / 2,
        backButton.y + BUTTON_HEIGHT / 2 - 10, 20, WHITE);

    // Display message if no trains found
    if (trains.empty())
    {
        DrawText("No trains available", SCREEN_WIDTH / 2 - MeasureText("No trains available", 30) / 2,
            SCREEN_HEIGHT / 2, 30, DARKGRAY);
    }
}

void RailwayGui::UpdateGui()
{
    // Add other state updates here...

    Vector2 mousePoint = GetMousePosition();

    // Update in RailwayGui class
    if (state.showCustomerDetails)
    {
        // Handle all input boxes
        HandleInputBox(state.nameInput);
        HandleInputBox(state.ageInput);
        HandleInputBox(state.genderInput);
        HandleInputBox(state.phoneInput);
        HandleInputBox(state.birthPrefInput);

        // Handle submit button
        Rectangle submitButton = { SCREEN_WIDTH / 2 - BUTTON_WIDTH - 20, 500, BUTTON_WIDTH, BUTTON_HEIGHT };
        if (CheckCollisionPointRec(GetMousePosition(), submitButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            // Validate inputs
            if (strlen(state.nameInput.text) == 0 || strlen(state.ageInput.text) == 0 ||
                strlen(state.genderInput.text) == 0 || strlen(state.phoneInput.text) == 0) {
                state.errorMessage = "All fields are required";
                state.showError = true;
                return;
            }

            // Copy values to customer details
            strcpy(state.customerName, state.nameInput.text);
            strcpy(state.customerAge, state.ageInput.text);
            strcpy(state.customerGender, state.genderInput.text);
            strcpy(state.customerPhone, state.phoneInput.text);
            strcpy(state.customerBirthPref, state.birthPrefInput.text);

            // Save details and handle response
            if (details.saveToFile(state)) {
                // Clear all input boxes
                memset(state.nameInput.text, 0, sizeof(state.nameInput.text));
                memset(state.ageInput.text, 0, sizeof(state.ageInput.text));
                memset(state.genderInput.text, 0, sizeof(state.genderInput.text));
                memset(state.phoneInput.text, 0, sizeof(state.phoneInput.text));
                memset(state.birthPrefInput.text, 0, sizeof(state.birthPrefInput.text));

                state.showCustomerDetails = false;
                state.showMainMenu = true;
            }
            else {
                state.errorMessage = "Error saving details";
                state.showError = true;
            }
        }

        // Handle back button
        Rectangle backButton = { SCREEN_WIDTH / 2 + 20, 500, BUTTON_WIDTH, BUTTON_HEIGHT };
        if (CheckCollisionPointRec(GetMousePosition(), backButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            state.showCustomerDetails = false;
            state.showMainMenu = true;
        }
    }

    if (state.showLoginScreen)
    {
        // Login screen input handling
        if (CheckCollisionPointRec(mousePoint, state.usernameBox) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            state.usernameEditMode = true;
            state.passwordEditMode = false;
        }

        if (CheckCollisionPointRec(mousePoint, state.passwordBox) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            state.passwordEditMode = true;
            state.usernameEditMode = false;
        }

        // Handle text input for username and password
        if (state.usernameEditMode || state.passwordEditMode)
        {
            char* activeInput = state.usernameEditMode ? state.username : state.password;
            int key = GetCharPressed();
            while (key > 0)
            {
                if ((key >= 32) && (key <= 125) && (strlen(activeInput) < 49))
                {
                    activeInput[strlen(activeInput)] = (char)key;
                    activeInput[strlen(activeInput) + 1] = '\0';
                }
                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE) && strlen(activeInput) > 0)
            {
                activeInput[strlen(activeInput) - 1] = '\0';
            }
        }

        // Login button handling
        Rectangle loginButton = { SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, 450, BUTTON_WIDTH, BUTTON_HEIGHT };
        if (CheckCollisionPointRec(mousePoint, loginButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {

            cout << "Pressed";
            if (strcmp(state.username, "admin") == 0 && strcmp(state.password, "admin") == 0)
            {
                state.isAdmin = true;
                state.isLoggedIn = true;
                state.showLoginScreen = false;
                state.showMainMenu = true;
            }
        }
    }
    else if (state.showMainMenu)
    {
        // Main menu button handling
        vector<const char*> menuItems = {
            "Customer Details",
            "Train Booking",
            "Tickets and Charges",
            "Add Train",
            "Remove Train",
            "Exit" };

        for (size_t i = 0; i < menuItems.size(); i++)
        {
            Rectangle btnRect = { 50.0f, 150.0f + i * 60, BUTTON_WIDTH, BUTTON_HEIGHT };
            if (CheckCollisionPointRec(mousePoint, btnRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                switch (i)
                {
                case 0:
                    state.showMainMenu = false;
                    state.showCustomerDetails = true;
                    break;
                case 1:
                    state.showMainMenu = false;
                    state.showTrainBooking = true;
                    break;
                case 2:
                    state.showMainMenu = false;
                    state.showTickets = true;
                    break;
                case 3:
                    if (state.isAdmin)
                    {
                        state.showMainMenu = false;
                        state.showAddTrain = true;
                    }
                    break;
                case 4:
                    if (state.isAdmin)
                    {
                        state.showMainMenu = false;
                        state.showRemoveTrain = true;
                    }
                    break;
                case 5:
                    CloseWindow();  // This will close the window and end the program
                    exit(0);        // Ensure the program exits completely
                    break;
                }
            }
        }
    }
    else if (state.showCustomerDetails)
    {
        // Back button handling for Customer Details
        Rectangle backButton = { 280, 500, BUTTON_WIDTH, BUTTON_HEIGHT };
        if (CheckCollisionPointRec(mousePoint, backButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            state.showCustomerDetails = false;
            state.showMainMenu = true;
        }

        // Submit button handling
        Rectangle submitButton = { 50, 500, BUTTON_WIDTH, BUTTON_HEIGHT };
        if (CheckCollisionPointRec(mousePoint, submitButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            // Save customer details to file
            // You would implement the actual saving logic here

            state.showCustomerDetails = false;
            state.showMainMenu = true;
        }
    }
    else if (state.showTrainBooking)
    {
        Vector2 mousePoint = GetMousePosition();

        // Handle train selection
        ifstream trainFile("trains.txt");
        string line;
        int trainY = 210;
        while (getline(trainFile, line)) {
            Rectangle trainRect = { 50, trainY - 5, SCREEN_WIDTH - 100, 40 };

            if (CheckCollisionPointRec(mousePoint, trainRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                stringstream ss(line);
                vector<string> fields;
                string field;

                while (getline(ss, field, ',')) {
                    fields.push_back(field);
                }

                state.selectedTrain = fields[0];         // Train Name
                state.selectedTrainNumber = fields[1];   // Train Number
                state.selectedFare = fields[5];          // Fare
            }

            trainY += 40;
        }
        trainFile.close();

        // Back button handling
        Rectangle backButton = { SCREEN_WIDTH / 2 + 20, SCREEN_HEIGHT - 70, BUTTON_WIDTH, BUTTON_HEIGHT };
        if (CheckCollisionPointRec(mousePoint, backButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            state.selectedTrain.clear();
            state.showTrainBooking = false;
            state.showMainMenu = true;
        }

        // Book button handling
        Rectangle bookButton = { SCREEN_WIDTH / 2 - BUTTON_WIDTH - 20, SCREEN_HEIGHT - 70, BUTTON_WIDTH, BUTTON_HEIGHT };
        if (!state.selectedTrain.empty() &&
            CheckCollisionPointRec(mousePoint, bookButton) &&
            IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            state.showBookingConfirmation = true;
        }

        // Handle confirmation dialog
        if (state.showBookingConfirmation) {
            Rectangle confirmButton = {
                state.confirmationBox.x + 100,
                state.confirmationBox.y + 300,
                BUTTON_WIDTH,
                BUTTON_HEIGHT
            };
            Rectangle cancelButton = {
                state.confirmationBox.x + 300,
                state.confirmationBox.y + 300,
                BUTTON_WIDTH,
                BUTTON_HEIGHT
            };

            if (CheckCollisionPointRec(mousePoint, confirmButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                // Generate new PNR
                static int pnrCounter = 10010;  // Continue from our mock data
                pnrCounter++;

                // Save booking to tickets.txt
                ofstream ticketFile("tickets.txt", ios::app);
                if (ticketFile.is_open()) {
                    time_t now = time(0);
                    char dt[26];
                    strftime(dt, sizeof(dt), "%Y-%m-%d %H:%M", localtime(&now));

                    ticketFile << pnrCounter << ","
                        << state.customerName << ","
                        << state.customerAge << ","
                        << state.customerGender << ","
                        << state.customerBirthPref << ","
                        << state.selectedFare << ","
                        << dt << "\n";
                    ticketFile.close();

                    // Clear selection and move to tickets screen
                    state.selectedTrain.clear();
                    state.showBookingConfirmation = false;
                    state.showTrainBooking = false;
                    state.showTickets = true;

                    // Set the PNR in search box to show the new booking
                    sprintf(state.pnrSearchInput.text, "%d", pnrCounter);
                }
            }
            else if (CheckCollisionPointRec(mousePoint, cancelButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                state.showBookingConfirmation = false;
            }
        }
    }
    else if (state.showTickets)
    {
        // Handle PNR search input
        HandleInputBox(state.pnrSearchInput);

        // Back button handling
        Rectangle backButton = { SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT - 70, BUTTON_WIDTH, BUTTON_HEIGHT };
        if (CheckCollisionPointRec(mousePoint, backButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            // Clear PNR search when going back
            memset(state.pnrSearchInput.text, 0, sizeof(state.pnrSearchInput.text));
            state.showError = false;
            state.showTickets = false;
            state.showMainMenu = true;
        }

        // Search button handling
        Rectangle searchButton = { 50 + INPUT_BOX_WIDTH + 20, 120, BUTTON_WIDTH, BUTTON_HEIGHT };
        if (CheckCollisionPointRec(mousePoint, searchButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (strlen(state.pnrSearchInput.text) > 0) {
                try {
                    int pnr = stoi(state.pnrSearchInput.text);
                    state.showError = false;
                    // The actual search is handled in DrawTicketsScreen
                }
                catch (...) {
                    state.errorMessage = "Please enter a valid PNR number";
                    state.showError = true;
                }
            }
            else {
                state.errorMessage = "Please enter a PNR number";
                state.showError = true;
            }
        }
    }
    else if (state.showAddTrain)
    {
        // Handle all input boxes
        HandleInputBox(state.trainNameInput);
        HandleInputBox(state.trainNumberInput);
        HandleInputBox(state.sourceInput);
        HandleInputBox(state.destinationInput);
        HandleInputBox(state.departureInput);
        HandleInputBox(state.fareInput);

        // Back button handling
        Rectangle backButton = { SCREEN_WIDTH / 2 + 20, 570, BUTTON_WIDTH, BUTTON_HEIGHT };
        if (CheckCollisionPointRec(mousePoint, backButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            // Clear all inputs when going back
            memset(state.trainNameInput.text, 0, sizeof(state.trainNameInput.text));
            memset(state.trainNumberInput.text, 0, sizeof(state.trainNumberInput.text));
            memset(state.sourceInput.text, 0, sizeof(state.sourceInput.text));
            memset(state.destinationInput.text, 0, sizeof(state.destinationInput.text));
            memset(state.departureInput.text, 0, sizeof(state.departureInput.text));
            memset(state.fareInput.text, 0, sizeof(state.fareInput.text));

            state.showError = false;
            state.showAddTrain = false;
            state.showMainMenu = true;
        }

        // Add Train button handling
        Rectangle addButton = { SCREEN_WIDTH / 2 - BUTTON_WIDTH - 20, 570, BUTTON_WIDTH, BUTTON_HEIGHT };
        if (CheckCollisionPointRec(mousePoint, addButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            // Validate all fields are filled
            if (strlen(state.trainNameInput.text) == 0 || strlen(state.trainNumberInput.text) == 0 ||
                strlen(state.sourceInput.text) == 0 || strlen(state.destinationInput.text) == 0 ||
                strlen(state.departureInput.text) == 0 || strlen(state.fareInput.text) == 0) {
                state.errorMessage = "All fields are required";
                state.showError = true;
                return;
            }

            // Validate train number format
            try {
                int trainNumber = stoi(state.trainNumberInput.text);
                if (trainNumber <= 0) {
                    state.errorMessage = "Invalid train number";
                    state.showError = true;
                    return;
                }
            }
            catch (...) {
                state.errorMessage = "Train number must be numeric";
                state.showError = true;
                return;
            }

            // Validate fare amount
            try {
                float fare = stof(state.fareInput.text);
                if (fare <= 0) {
                    state.errorMessage = "Invalid fare amount";
                    state.showError = true;
                    return;
                }
            }
            catch (...) {
                state.errorMessage = "Fare must be numeric";
                state.showError = true;
                return;
            }

            // Save train to file
            ofstream trainFile("trains.txt", ios::app);
            if (trainFile.is_open()) {
                trainFile << state.trainNameInput.text << ","
                    << state.trainNumberInput.text << ","
                    << state.sourceInput.text << ","
                    << state.destinationInput.text << ","
                    << state.departureInput.text << ","
                    << state.fareInput.text << endl;
                trainFile.close();

                // Clear all inputs after successful save
                memset(state.trainNameInput.text, 0, sizeof(state.trainNameInput.text));
                memset(state.trainNumberInput.text, 0, sizeof(state.trainNumberInput.text));
                memset(state.sourceInput.text, 0, sizeof(state.sourceInput.text));
                memset(state.destinationInput.text, 0, sizeof(state.destinationInput.text));
                memset(state.departureInput.text, 0, sizeof(state.departureInput.text));
                memset(state.fareInput.text, 0, sizeof(state.fareInput.text));

                // Switch screen states
                state.showAddTrain = false;
                state.showMainMenu = true;
            }
            else {
                state.errorMessage = "Error saving train details";
                state.showError = true;
            }
        }
    }
    else if (state.showRemoveTrain)
    {
        // Back button handling
        Rectangle backButton = { 50, SCREEN_HEIGHT - 70, BUTTON_WIDTH, BUTTON_HEIGHT };
        if (CheckCollisionPointRec(mousePoint, backButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            state.showRemoveTrain = false;
            state.showMainMenu = true;
        }

        // Handle remove buttons for each train
        ifstream trainFile("trains.txt");
        vector<string> trains;
        string train;
        while (getline(trainFile, train))
        {
            trains.push_back(train);
        }
        trainFile.close();

        for (size_t i = 0; i < trains.size(); i++)
        {
            Rectangle removeButton = { SCREEN_WIDTH - 220, 170.0f + i * 60, BUTTON_WIDTH, 50 };
            if (CheckCollisionPointRec(mousePoint, removeButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {

                // In RemoveTrain screen handling:
                if (CheckCollisionPointRec(mousePoint, removeButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    // Read all trains
                    vector<string> updatedTrains;
                    ifstream readFile("trains.txt");
                    if (readFile.is_open())
                    {
                        string line;
                        size_t currentLine = 0;
                        while (getline(readFile, line))
                        {
                            if (currentLine != i)
                            { // Skip the train to be removed
                                updatedTrains.push_back(line);
                            }
                            currentLine++;
                        }
                        readFile.close();

                        // Write back updated trains
                        ofstream writeFile("trains.txt", ios::trunc);
                        if (writeFile.is_open())
                        {
                            for (const string& train : updatedTrains)
                            {
                                writeFile << train << endl;
                            }
                            writeFile.close();
                        }
                    }

                    // Reset display
                    state.showRemoveTrain = false;
                    state.showMainMenu = true;
                }
            }
        }
    }
}

int main()
{
    RailwayGui gui;
    gui.Run();
return 0;
}
