// Write a C/C++ program to find the number of occurrences of any word in a file and replace that with another word.
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

// Function to replace all occurrences of a word in a string
std::string replaceWordInString(const std::string& text, const std::string& oldWord, const std::string& newWord) {
    std::string result = text;
    size_t pos = 0;
    while ((pos = result.find(oldWord, pos)) != std::string::npos) {
        result.replace(pos, oldWord.length(), newWord);
        pos += newWord.length();
    }
    return result;
}

// Function to count occurrences of a word in a string
int countOccurrences(const std::string& text, const std::string& word) {
    int count = 0;
    size_t pos = text.find(word);
    while (pos != std::string::npos) {
        count++;
        pos = text.find(word, pos + word.length());
    }
    return count;
}

int main() {
    std::string filename, oldWord, newWord;

    // Input the filename and the words
    std::cout << "Enter the filename: ";
    std::getline(std::cin, filename);

    std::cout << "Enter the word to find: ";
    std::getline(std::cin, oldWord);

    std::cout << "Enter the word to replace with: ";
    std::getline(std::cin, newWord);

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return 1;
    }

    // Read the entire file into a string
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string fileContent = buffer.str();
    file.close();

    // Count occurrences of the old word
    int count = countOccurrences(fileContent, oldWord);

    // Replace the old word with the new word
    std::string newContent = replaceWordInString(fileContent, oldWord, newWord);

    // Write the new content back to the file
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return 1;
    }
    outFile << newContent;
    outFile.close();

    // Output the number of occurrences
    std::cout << "The word '" << oldWord << "' occurred " << count << " times." << std::endl;

   return 0;
}

