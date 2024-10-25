// Write program to convert infix to postfix

#include <bits/stdc++.h>


using namespace std;

class Stack {
private:
    int top;
    char* stackArray;
    int capacity;

public:
    Stack(int size) {
        capacity = size;
        stackArray = new char[capacity];
        top = -1;
    }

    ~Stack() {
        delete[] stackArray;
    }

    void push(char item) {
        if (isFull()) {
            cout << "Stack Overflow\n";
            return;
        }
        stackArray[++top] = item;
    }

    char pop() {
        if (isEmpty()) {
            cout << "Stack Underflow\n";
            return '\0';
        }
        return stackArray[top--];
    }

    char peek() {
        if (isEmpty()) {
            cout << "Stack is empty\n";
            return '\0';
        }
        return stackArray[top];
    }

    bool isEmpty() {
        return top == -1;
    }

    bool isFull() {
        return top == capacity - 1;
    }
};

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

string infixToPostfix(const string& infix) {
    Stack s(infix.size());
    string postfix = "";

    for (char c : infix) {
        if (isalnum(c)) {
            postfix += c;
        } else if (c == '(') {
            s.push(c);
        } else if (c == ')') {
            while (!s.isEmpty() && s.peek() != '(') {
                postfix += s.pop();
            }
            s.pop();
        } else if (isOperator(c)) {
            while (!s.isEmpty() && precedence(c) <= precedence(s.peek())) {
                postfix += s.pop();
            }
            s.push(c);
        }
    }

    while (!s.isEmpty()) {
        postfix += s.pop();
    }

    return postfix;
}

int main() {
    string expression;
    cout<<"Enter the infix expression:"<<endl;
    getline(cin,expression);
    cout << "Infix Expression: " << expression << endl;
    string postfix = infixToPostfix(expression);
    cout << "Postfix Expression: " << postfix << endl;
return 0;
}