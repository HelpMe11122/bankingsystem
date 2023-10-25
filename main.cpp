#include <iostream>
#include <string>

#include <cstring>
#include <filesystem>
#include <unistd.h>
#include <vector>
#include <cstdlib> // random
#include <ctime> // time.sleep ==
#include <set>
#include <bits/stdc++.h> // lambda
#include <sqlite3.h>




using namespace std;

string loginTokens[] = {
    "a", "b", "c", "d", "e", "f", "g",
    "h", "i", "j", "k", "l", "m", "n",
    "o", "p", "q", "s", "t", "u", "v",
    "w", "x", "y", "z", "1", "2", "3",
    "4", "5", "6", "7", "8", "9", "$",
    "#", "&", "@", "!"
};


bool isValidDate(const std::string& input) {
    // Regular expression to validate "YYYY-MM-DD" format
    std::regex datePattern(R"(^\d{2}-\d{2}-\d{4}$)");

    // Check if the input matches the pattern
    return std::regex_match(input, datePattern);
}


void login_suggestion(std::ifstream& file) {
    sqlite3* db;
    int rc = sqlite3_open("users.db", &db);

    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db); 
        return;
    } 

    // Read values from list 
    string attemptedLoginKey = "";

    cout << "Please enter the 12 character key for your account" << endl;
    cin >> attemptedLoginKey;

    // SQL Query Construction
    std::string sqlQuery = "SELECT Token FROM Users WHERE Token = ?";
    sqlite3_stmt* stmt;

    // Prepare the SQL statement
    rc = sqlite3_prepare_v2(db, sqlQuery.c_str(), -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    // Bind the input parameter to the SQL statement
    rc = sqlite3_bind_text(stmt, 1, attemptedLoginKey.c_str(), -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to bind parameter: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return;
    }

    // Execute the statement
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        std::cout << "Login successful!" << std::endl;
    } else {
        std::cout << "Login failed. Token not found in the database." << std::endl;
    }

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void insert_login_token(const std::string& loginToken) {
    sqlite3* db;
    int rc = sqlite3_open("users.db", &db);

    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    // Construct the SQL query to insert a new login token
    std::string sqlQuery = "INSERT INTO Users (Token) VALUES (?)";
    sqlite3_stmt* stmt;

    // Prepare the SQL statement
    rc = sqlite3_prepare_v2(db, sqlQuery.c_str(), -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    // Bind the input parameter (login token) to the SQL statement
    rc = sqlite3_bind_text(stmt, 1, loginToken.c_str(), -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to bind parameter: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return;
    }

    // Execute the statement to insert the login token
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Insert failed: " << sqlite3_errmsg(db) << std::endl;
    } else {
        std::cout << "Login token inserted successfully." << std::endl;
    }

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}


void registration_acc() {
    // Generate a pin for the user to login with
    string firstName;
    string lastName;
    string dob;


    cout << "Enter your first name: " << endl;
    cin >> firstName;
    cout << "Enter your last name (surname): " << endl;
    cin >> lastName;
    cout << "Enter Date of Birth (DD-MM-YYYY): " << endl;
    std::getline(std::cin, dob);

    if (isValidDate(dob)) {
        std::cout << "You entered a valid date of birth: " << dob << std::endl;
        // Further processing with the valid date of birth can be done here
    } else {
        std::cout << "Invalid date of birth format. Please use DD-MM-YYYY." << std::endl;
    }

    int identifier_max = 12;
    string fullToken = "";
    std::set<string> uniqueTokens;

    // Generation
    while (uniqueTokens.size() < static_cast<size_t>(identifier_max)) {
        int randomIndex = std::rand() % (sizeof(loginTokens) / sizeof(loginTokens[0]));
        string randomToken = loginTokens[randomIndex];
        uniqueTokens.insert(randomToken);
    }

    // Output
    for (const auto& token : uniqueTokens) {
        fullToken += token;
    }

    // Apply code to logintokens.txt
    std::ofstream outfile;
    outfile.open("logintokens.txt", std::ios_base::app); // Append instead of overwrite

    if (outfile.is_open()) {
        outfile << fullToken << endl;
        outfile.close(); // Close the file stream after writing
        cout << "Account created successfully. Your unique identifier code is: " << fullToken << endl;
        insert_login_token(fullToken);
    } else {
        cout << "Error: Unable to open file." << endl;
    }
}



int main() {
    string accountLogic = "";
    bool acceptedInput = false;

    cout << "Welcome to realism banking - Entirely made in C++!" << endl;
    cout << "Do you already have an account? [Y/N]: ";

    cin >> accountLogic;

    if (accountLogic == "Y" || accountLogic == "y") {
        acceptedInput = true;
        std::ifstream infile("logintokens.txt");
        login_suggestion(infile);
        infile.close(); // close after reading
    } else if (accountLogic == "N" || accountLogic == "n") {
        acceptedInput = true;
        registration_acc();
    }
    return 0;
}
