#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Grammar {
public:
    char nonTerminal;
    string production;

    Grammar(char nonTerminal, string production) {
        this->nonTerminal = nonTerminal;
        this->production = production;
    }
};

bool belongsToGrammar(const string& input, const vector<Grammar>& grammar, char startSymbol);
int match(const string& input, int pos, char symbol, const vector<Grammar>& grammar);

bool belongsToGrammar(const string& input, const vector<Grammar>& grammar, char startSymbol) {
    return match(input, 0, startSymbol, grammar) == input.length();
}

int match(const string& input, int pos, char symbol, const vector<Grammar>& grammar) {
    if (pos >= input.length()) {
        return -1;  // No match
    }

    for (const Grammar& rule : grammar) {
        if (rule.nonTerminal == symbol) {
            if (rule.production == "ab") {
                if (input.substr(pos, 2) == "ab") {  // Direct match for 'ab'
                    return pos + 2; // Move forward by 2 positions
                }
            } else if (rule.production == "aSb") {
                // Check for recursive rule 'aSb'
                if (input[pos] == 'a' && input[input.length() - 1] == 'b') {
                    // Recursively match the middle part for 'S'
                    int newPos = match(input, pos + 1, 'S', grammar);
                    if (newPos != -1 && newPos < input.length() && input[newPos] == 'b') {
                        return newPos + 1; // Move past 'b'
                    }
                }
            }
        }
    }

    return -1; // No valid match found
}

int main() {
    vector<Grammar> grammar = {
        Grammar('S', "ab"),
        Grammar('S', "aSb")
    };

    string input;
    cout << "Enter a string: ";
    cin >> input;

    if (belongsToGrammar(input, grammar, 'S')) {
        cout << "The string belongs to the grammar." << endl;
    } else {
        cout << "The string does not belong to the grammar." << endl;
    }
return 0;
}