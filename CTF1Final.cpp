#include <iostream>
#include <string>
#include <vector>

// Base64 encoding helper function
std::string base64Encode(const std::string& input) {
    static const std::string base64_chars = 
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";
    
    std::string encoded;
    int val = 0, valb = -6;
    for (unsigned char c : input) {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            encoded.push_back(base64_chars[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }
    if (valb > -6) {
        encoded.push_back(base64_chars[((val << 8) >> (valb + 8)) & 0x3F]);
    }
    while (encoded.size() % 4) {
        encoded.push_back('=');
    }
    return encoded;
}

int main() {
    std::string inputString;
    std::string numericString;
    std::string ctfKey = "CTF{C0ngr@ts_cr@(k3r}"; // CTF Key to be Base64 encoded

    // Input a string from the user
    std::cout << "Enter your name (at least 5 letters): ";
    std::cin >> inputString;

    // Check if the input string is at least 5 characters long
    if (inputString.length() < 5) {
        std::cout << "Input String should be at least 5 letters" << std::endl;
        return 1; // Return with an error code
    }

    // Initialize variables for multiplication and addition of ASCII values
    long long asciiProduct = 1;
    int asciiSum = 0;

    // Perform multiplication and addition of ASCII values of the characters
    for (char ch : inputString) {
        int asciiValue = static_cast<int>(ch);
        asciiProduct *= asciiValue;
        asciiSum += asciiValue;
    }

    // Check to avoid division by zero
    if (asciiSum == 0) {
        std::cout << "Invalid operation" << std::endl;
        return 1; // Return with an error code
    }

    // Perform division of the multiplication value by the addition value
    long long quotient = asciiProduct / asciiSum;

    // Input a numeric string from the user
    std::cout << "Enter the Valid key: ";
    std::cin >> numericString;

    // Compare the input value to the division quotient
    if (std::to_string(quotient) == numericString) {
        // Base64 encode the CTF key
        std::string base64EncodedCTFKey = base64Encode(ctfKey);
        std::cout << "Valid key - Congrats! " << base64EncodedCTFKey << std::endl;
    } else {
        std::cout << "Invalid key - Try harder!" << std::endl;
    }

    return 0;
}
