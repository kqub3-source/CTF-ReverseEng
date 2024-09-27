#include <iostream>
#include <string>

int main() {
    std::string inputString;
    std::string numericString;

    // Input a string from the user
    std::cout << "Enter your name: ";
    std::cin >> inputString;

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
        std::cout << "Valid key - [ctf_key]" << std::endl;
    } else {
        std::cout << "Invalid key - Try harder!" << std::endl;
    }

    return 0;
}
