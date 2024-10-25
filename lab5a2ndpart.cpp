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

class ParseNode {
public:
    char symbol;
    vector<ParseNode*> children;

    ParseNode(char symbol) {
        this->symbol = symbol;
    }

    // Helper function to print the parse tree
    void print(string prefix) {
        cout << prefix << symbol << endl;
        for (ParseNode* child : children) {
            child->print(prefix + "  ");
        }
    }
};

bool belongsToGrammar(const string& input, const vector<Grammar>& grammar, char startSymbol);
int match(const string& input, int pos, char symbol, const vector<Grammar>& grammar, ParseNode* node);

bool belongsToGrammar(const string& input, const vector<Grammar>& grammar, char startSymbol) {
    ParseNode* parseTree = new ParseNode(startSymbol); // Root of the parse tree
    bool result = match(input, 0, startSymbol, grammar, parseTree) == input.length();
    
    if (result) {
        cout << "Parse tree:" << endl;
        parseTree->print(""); // Print the parse tree
    }
    
    // Clean up the allocated parse tree
    delete parseTree;
    
    return result;
}

int match(const string& input, int pos, char symbol, const vector<Grammar>& grammar, ParseNode* node) {
    if (pos >= input.length()) {
        return -1;  // No match
    }

    for (const Grammar& rule : grammar) {
        if (rule.nonTerminal == symbol) {
            if (rule.production == "ab") {
                if (input.substr(pos, 2) == "ab") {
                    // Add children for 'a' and 'b'
                    node->children.push_back(new ParseNode('a'));
                    node->children.push_back(new ParseNode('b'));
                    return pos + 2; // Move forward by 2 positions
                }
            } else if (rule.production == "aSb") {
                // Recursive match for 'aSb'
                if (input[pos] == 'a' && input[input.length() - 1] == 'b') {
                    node->children.push_back(new ParseNode('a')); // Add 'a' as a child
                    ParseNode* subTree = new ParseNode('S'); // Create a subtree for 'S'
                    node->children.push_back(subTree);
                    int newPos = match(input, pos + 1, 'S', grammar, subTree); // Recursively match 'S'
                    if (newPos != -1 && newPos < input.length() && input[newPos] == 'b') {
                        node->children.push_back(new ParseNode('b')); // Add 'b' as a child
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