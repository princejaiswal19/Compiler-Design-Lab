#include <iostream>
#include <cctype>

using namespace std;

bool isValidIdentifier(char ch) {
    return (isalpha(ch) || ch == '_');
}

bool isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=');
}

bool isValidExpression(const string &expression) {
    int n = expression.length();
    bool expectOperator = false;

    for (int i = 0; i < n; ++i) {
        char ch = expression[i];
        if (isspace(ch)) continue;

        if (isValidIdentifier(ch)) {
            expectOperator = true;
            while (i + 1 < n && (isalnum(expression[i + 1]) || expression[i + 1] == '_')) {
                i++;
            }
        } else if (isdigit(ch)) {
            expectOperator = true;
            while (i + 1 < n && isdigit(expression[i + 1])) {
                i++;
            }
        } else if (isOperator(ch)) {
            if (!expectOperator) return false;
            expectOperator = false;
        } else {
            return false; 
        }
    }

    return expectOperator;
}

int main() {
    string expression;
    
    cout << "Enter an arithmetic expression: ";
    getline(cin, expression);

    if (!isValidExpression(expression)) {
        cout << "Invalid arithmetic expression!" << endl;
        return 1;
    }

    cout << "Valid arithmetic expression." << endl;

    cout << "Identifiers: ";
    for (int i = 0; i < expression.length(); ++i) {
        char ch = expression[i];
        if (isValidIdentifier(ch)) {
            while (i < expression.length() && (isalnum(expression[i]) || expression[i] == '_')) {
                cout << expression[i];
                i++;
            }
            cout << " ";
        }
    }
    cout << endl;

    cout << "Operators: ";
    for (char ch : expression) {
        if (isOperator(ch)) {
            cout << ch << " ";
        }
    }
    cout << endl;

    return 0;
}
