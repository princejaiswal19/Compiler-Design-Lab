#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;


bool isLeftRecursive(const std::string& nonTerminal, const std::vector<std::string>& productions) {
    for (const std::string& production : productions) {
        if (production.find(nonTerminal) == 0) {
            return true;
        }
    }
    return false;
}

bool needsLeftFactoring(const std::vector<std::string>& productions) {
    for (size_t i = 0; i < productions.size(); ++i) {
        for (size_t j = i + 1; j < productions.size(); ++j) {
            size_t minLength = std::min(productions[i].length(), productions[j].length());
            size_t k = 0;
            while (k < minLength && productions[i][k] == productions[j][k]) {
                ++k;
            }
            if (k > 0) { 
                return true;
            }
        }
    }
    return false;
}

int main() {
    int numNonTerminals;
    std::cout << "Enter the number of non-terminals: ";
    std::cin >> numNonTerminals;

    std::cin.ignore(); 

    for (int i = 0; i < numNonTerminals; ++i) {
        std::string nonTerminal;
        std::cout << "\nEnter non-terminal: ";
        std::getline(std::cin, nonTerminal);

        std::string productionInput;
        std::cout << "Enter productions (separated by '|'): ";
        std::getline(std::cin, productionInput);

        std::vector<std::string> productions;
        std::stringstream ss(productionInput);
        std::string production;
        while (std::getline(ss, production, '|')) {
            productions.push_back(production);
        }

        if (isLeftRecursive(nonTerminal, productions)) {
            std::cout << nonTerminal << " has left recursion.\n";
        } else {
            std::cout << nonTerminal << " does not have left recursion.\n";
        }

        if (needsLeftFactoring(productions)) {
            std::cout << nonTerminal << " needs left factoring.\n";
        } else {
            std::cout << nonTerminal << " does not need left factoring.\n";
        }
    }


return 0;
}