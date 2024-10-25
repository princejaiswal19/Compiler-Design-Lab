#include<bits/stdc++.h>

using namespace std;

map<char, set<char>> firstSets, followSets;  
map<char, vector<string>> grammarRules;      
set<char> nonTerminals, terminals;           

void calculateFirst(char symbol);
void calculateFollow(char symbol);
bool isTerminal(char symbol);
void displaySet(map<char, set<char>> &sets, string setName);

int main() {
    int n;
    cout << "Enter number of grammar rules: ";
    cin >> n;
    cout << "Enter the grammar rules (e.g., S->ABc, where S is the non-terminal and ABc is the production):\n";

    for (int i = 0; i < n; i++) {
        char nonTerminal;
        string production;
        cin >> nonTerminal >> production;  
        
        production = production.substr(2); 
        grammarRules[nonTerminal].push_back(production);
        nonTerminals.insert(nonTerminal);
        
        for (char symbol : production) {
            if (!isupper(symbol) && symbol != '$') {
                terminals.insert(symbol);
            }
        }
    }

   
    for (char nonTerminal : nonTerminals) {
        calculateFirst(nonTerminal);
    }

    
    followSets[*(nonTerminals.begin())].insert('$');  // Start symbol gets '$'
    for (char nonTerminal : nonTerminals) {
        calculateFollow(nonTerminal);
    }

   
    displaySet(firstSets, "First");
    displaySet(followSets, "Follow");

    return 0;
}

bool isTerminal(char symbol) {
    return !isupper(symbol); 
}

void calculateFirst(char symbol) {
    if (isTerminal(symbol)) {
        firstSets[symbol].insert(symbol);
        return;
    }

    if (!firstSets[symbol].empty()) return;  

    for (string production : grammarRules[symbol]) {
        for (char prodSymbol : production) {
            if (isTerminal(prodSymbol)) {
                firstSets[symbol].insert(prodSymbol);
                break;
            } else {
                calculateFirst(prodSymbol);
                set<char> &firstSetOfProdSymbol = firstSets[prodSymbol];

                firstSets[symbol].insert(firstSetOfProdSymbol.begin(), firstSetOfProdSymbol.end());
                
                if (firstSetOfProdSymbol.find('$') == firstSetOfProdSymbol.end()) {
                    break;  
                }
            }
        }
    }
}

void calculateFollow(char symbol) {
    for (auto &rule : grammarRules) {
        char lhs = rule.first;
        for (string production : rule.second) {
            for (size_t i = 0; i < production.length(); i++) {
                if (production[i] == symbol) {
                    if (i + 1 < production.length()) {
                        char nextSymbol = production[i + 1];
                        if (isTerminal(nextSymbol)) {
                            followSets[symbol].insert(nextSymbol);
                        } else {
                            set<char> firstNextSymbol = firstSets[nextSymbol];
                            followSets[symbol].insert(firstNextSymbol.begin(), firstNextSymbol.end());
                            followSets[symbol].erase('$');

                            if (firstNextSymbol.find('$') != firstNextSymbol.end()) {
                                calculateFollow(lhs);
                                followSets[symbol].insert(followSets[lhs].begin(), followSets[lhs].end());
                            }
                        }
                    } else {
                        if (symbol != lhs) {
                            calculateFollow(lhs);
                            followSets[symbol].insert(followSets[lhs].begin(), followSets[lhs].end());
                        }
                    }
                }
            }
        }
    }
}

void displaySet(map<char, set<char>> &sets, string setName) {
    for (auto &entry : sets) {
        cout << setName << "(" << entry.first << ") = { ";
        for (char ch : entry.second) {
            cout << ch << " ";
        }
        cout << "}\n";
    }
}
