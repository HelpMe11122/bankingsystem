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
    string tp;
    while(getline(file, tp)) {
        cout << tp << endl;
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

    cout << "Welcome to realism banking - Entirely made in C++!" << endl;
    cout << "Do you already have an account? [Y/N]: ";

    cin >> accountLogic;

    if (accountLogic == "Y" || accountLogic == "y") {
        acceptedInput = true;
    } else if (accountLogic == "N" || accountLogic == "n") {
        acceptedInput = true;
        registration_acc();
    }
    return 0;
}
