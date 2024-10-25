// check whether grammar is ll1 or not 
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <sstream>

using namespace std;

// Function to input grammar
void inputGrammar(vector<string> &grammar) {
    int numRules;
    cout << "Enter the number of production rules: ";
    cin >> numRules;
    cin.ignore();  // Ignore the newline character after number input

    grammar.resize(numRules);

    for (int i = 0; i < numRules; ++i) {
        cout << "Enter production rule " << i + 1 << " (e.g., A->aB|b): ";
        getline(cin, grammar[i]);
    }
}

// Function to parse grammar into a map of productions
unordered_map<string, vector<string>> parseGrammar(const vector<string> &grammar) {
    unordered_map<string, vector<string>> productions;

    for (const string &rule : grammar) {
        size_t pos = rule.find("->");
        if (pos == string::npos) {
            cerr << "Invalid production rule: " << rule << endl;
            continue;
        }
        
        string nonTerminal = rule.substr(0, pos);
        string production = rule.substr(pos + 2);

        stringstream ss(production);
        string token;
        while (getline(ss, token, '|')) {
            productions[nonTerminal].push_back(token);
        }
    }

    return productions;
}

// Function to compute FIRST sets
unordered_map<string, unordered_set<string>> computeFirst(const unordered_map<string, vector<string>> &productions) {
    unordered_map<string, unordered_set<string>> first;
    bool changed;

    // Initialize FIRST sets
    for (const auto &entry : productions) {
        first[entry.first] = unordered_set<string>();
    }

    do {
        changed = false;
        for (const auto &entry : productions) {
            const string &nonTerminal = entry.first;
            unordered_set<string> oldFirstSet = first[nonTerminal];

            for (const string &production : entry.second) {
                if (!production.empty()) {
                    char firstSymbol = production[0];
                    if (isupper(firstSymbol)) {
                        string nonTerminalStr(1, firstSymbol);
                        for (const string &symbol : first[nonTerminalStr]) {
                            if (symbol != "ε") {
                                first[nonTerminal].insert(symbol);
                            }
                        }
                        if (first[nonTerminalStr].count("ε") != 0 && production.length() > 1) {
                            for (size_t i = 1; i < production.length(); ++i) {
                                char nextSymbol = production[i];
                                if (isupper(nextSymbol)) {
                                    string nextNonTerminal(1, nextSymbol);
                                    for (const string &symbol : first[nextNonTerminal]) {
                                        if (symbol != "ε") {
                                            first[nonTerminal].insert(symbol);
                                        }
                                    }
                                    if (first[nextNonTerminal].count("ε") == 0) {
                                        break;
                                    }
                                } else {
                                    first[nonTerminal].insert(string(1, nextSymbol));
                                    break;
                                }
                            }
                        }
                    } else {
                        first[nonTerminal].insert(string(1, firstSymbol));
                    }
                }
            }

            if (first[nonTerminal] != oldFirstSet) {
                changed = true;
            }
        }
    } while (changed);

    return first;
}

// Function to compute FOLLOW sets
unordered_map<string, unordered_set<string>> computeFollow(
    const unordered_map<string, vector<string>> &productions,
    const unordered_map<string, unordered_set<string>> &first) {
    
    unordered_map<string, unordered_set<string>> follow;
    unordered_set<string> nonTerminals;

    for (const auto &entry : productions) {
        nonTerminals.insert(entry.first);
    }

    // Initialize FOLLOW sets
    for (const auto &entry : nonTerminals) {
        follow[entry] = unordered_set<string>();
    }

    // Assume the first non-terminal is the start symbol and add $ to its FOLLOW set
    follow[*nonTerminals.begin()].insert("$");

    bool changed;
    do {
        changed = false;
        for (const auto &entry : productions) {
            const string &nonTerminal = entry.first;
            for (const string &production : entry.second) {
                size_t length = production.length();
                for (size_t i = 0; i < length; ++i) {
                    if (isupper(production[i])) {
                        string currSymbol(1, production[i]);
                        if (i + 1 < length) {
                            char nextSymbol = production[i + 1];
                            if (isupper(nextSymbol)) {
                                string nextNonTerminal(1, nextSymbol);
                                unordered_set<string> nextFirst = first.at(nextNonTerminal);
                                for (const string &symbol : nextFirst) {
                                    if (symbol != "ε") {
                                        if (follow[currSymbol].insert(symbol).second) {
                                            changed = true;
                                        }
                                    }
                                }
                                if (nextFirst.count("ε") != 0) {
                                    for (const string &symbol : follow[nonTerminal]) {
                                        if (follow[currSymbol].insert(symbol).second) {
                                            changed = true;
                                        }
                                    }
                                }
                            } else {
                                if (follow[currSymbol].insert(string(1, nextSymbol)).second) {
                                    changed = true;
                                }
                            }
                        } else {
                            for (const string &symbol : follow[nonTerminal]) {
                                if (follow[currSymbol].insert(symbol).second) {
                                    changed = true;
                                }
                            }
                        }
                    }
                }
            }
        }
    } while (changed);

    return follow;
}

// Function to check if the grammar is LL(1)
bool isLL1(const unordered_map<string, vector<string>> &productions, const unordered_map<string, unordered_set<string>> &first) {
    for (const auto &entry : productions) {
        const string &nonTerminal = entry.first;
        unordered_set<string> allFirsts;

        for (const string &production : entry.second) {
            unordered_set<string> productionFirsts;
            for (char symbol : production) {
                if (isupper(symbol)) {
                    const string nonTerminalStr(1, symbol);
                    productionFirsts.insert(first.at(nonTerminalStr).begin(), first.at(nonTerminalStr).end());
                    if (first.at(nonTerminalStr).count("ε") == 0) {
                        break; // Stop at the first symbol that isn't ε
                    }
                } else {
                    productionFirsts.insert(string(1, symbol));
                    break; // Stop on terminal
                }
            }

            // Check for intersections
            for (const auto &f : productionFirsts) {
                if (f != "ε" && allFirsts.count(f)) {
                    return false; // Not LL(1) if there's an intersection
                }
                allFirsts.insert(f);
            }
        }
    }

    return true; // If all checks pass, it is LL(1)
}

// Function to print sets
void printSets(const unordered_map<string, unordered_set<string>> &sets, const string &name) {
    cout << name << " sets:" << endl;
    for (const auto &entry : sets) {
        cout << entry.first << " -> { ";
        for (const auto &symbol : entry.second) {
            cout << symbol << " ";
        }
        cout << "}" << endl;
    }
}

int main() {
    vector<string> grammar;
    inputGrammar(grammar);

    // Parse grammar and compute FIRST and FOLLOW sets
    auto productions = parseGrammar(grammar);

    // Compute FIRST sets
    auto first = computeFirst(productions);
    printSets(first, "FIRST");

    // Compute FOLLOW sets
    auto follow = computeFollow(productions, first);
    printSets(follow, "FOLLOW");

    // Check if the grammar is LL(1)
    if (isLL1(productions, first)) {
        cout << "The given grammar is LL(1)." << endl;
    } else {
        cout << "The given grammar is not LL(1)." << endl;
    }

    return 0;
}
