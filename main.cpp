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

void login_suggestion(std::ifstream& file) {
    string attemptedLoginKey = "";

    cout << "Please enter the 12 character key for your account" << endl;
    cin >> attemptedLoginKey;


    string tp;
    while(getline(file, tp)) {
        if (attemptedLoginKey == tp) {
            cout << "Attempted: " << attemptedLoginKey << endl <<
            "Actual: " << tp;
        }
    }
}

void registration_acc() {
    // Generate a pin for the user to login with
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
    } else {
        cout << "Error: Unable to open file." << endl;
    }
}



int main() {
    string accountLogic = "";
    bool acceptedInput = false;

    cout << "Please wait... Connecting to database.....";
    sqlite3* db;
    int rc = sqlite3_open("users.db", &db);

    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db); 
        return rc;
    }


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
