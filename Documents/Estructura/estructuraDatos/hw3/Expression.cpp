#include "Expression.hpp"
#include "Stack.hpp"

#include <cctype>
#include <cmath>
#include <string>

Expression::Expression() : infix(""), isValid(false) {}

Expression::Expression(std::string infix) : infix(infix) {
    isValid = validate();
    if (isValid) {
        convertToPostfix();
    } else {
        throw std::invalid_argument("Invalid expression");
    }
}

void Expression::print() {
    std::cout << "Infix: " << infix << std::endl;
    std::cout << "Postfix: " << postfix << std::endl;
}

int Expression::precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    if (op == '^')
        return 3;
    // if (op == 'sin' || op == 'cos' || op == 'tan' || op == 'log' || op ==
    // 'exp') {
    //    return 4; nope not enough time
    // } // char -> std::string
    return 0;
}

bool Expression::isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

void Expression::convertToPostfix() {
    Stack<char> opStack(10);
    postfix = "";
    for (int i = 0; i < infix.length(); i++) {
        char c = infix[i];

        if (std::isdigit(c)) {
            while (i < infix.length() && std::isdigit(infix[i])) {
                postfix += infix[i];
                i++;
            }
            postfix += " ";
            i--;
        } else if (isOperator(c)) {
            while (!opStack.isEmpty() && precedence(opStack.top()) >= precedence(c)) {
                postfix += opStack.top();
                postfix += " ";
                opStack.pop();
            }
            opStack.push(c);
        } else if (c == '(' || c == '{' || c == '[') {
            opStack.push(c);
        } else if (c == ')' || c == '}' || c == ']') {
            while (!opStack.isEmpty() && opStack.top() != '(' && opStack.top() != '{' &&
                   opStack.top() != '[') {
                postfix += opStack.top();
                postfix += " ";
                opStack.pop();
            }
            opStack.pop();
        }
        // std::cout << postfix << std::endl;
    }
    while (!opStack.isEmpty()) {
        // opStack.print();
        postfix += opStack.top();
        postfix += " ";
        opStack.pop();
    }
}

bool Expression::validate() {
    Stack<char> valStack(10);
    if (infix.length() == 0) {
        return false;
    }
    for (int i = 0; i < infix.length(); i++) {
        char c = infix[i];
        if (c == '(' || c == '{' || c == '[') {
            valStack.push(c);
        } else if (c == ')' || c == '}' || c == ']') {
            if (valStack.isEmpty()) {
                return false;
            }
            if (c == ')' && valStack.top() != '(' || c == '}' && valStack.top() != '{' ||
                c == ']' && valStack.top() != '[') {
                return false;
            }
            valStack.pop();
        } else if (isOperator(c)) {
            if (i == 0 || i == infix.length() - 1 || isOperator(infix[i - 1])) {
                return false;
            }
        }
    }
    return valStack.isEmpty();
}

double Expression::evaluate() {
    if (!isValid) {
        throw std::invalid_argument("This Expression isnt valid for evaluation");
    }
    Stack<double> evalStack(10);
    std::string num = "";

    for (int i = 0; i < postfix.length(); i++) {
        char c = postfix[i];
        if (std::isdigit(c) || c == '.') {
            num += c;
            // evalStack.push((double)c);
        } else if (c == ' ' && !num.empty()) {
            evalStack.push(std::stod(num));
            num = "";
        } else if (isOperator(c)) {
            double op2 = evalStack.top();
            evalStack.pop();

            double op1 = evalStack.top();
            evalStack.pop();

            switch (c) {
                case '+':
                    evalStack.push(op1 + op2);
                    break;
                case '-':
                    evalStack.push(op1 - op2);
                    break;
                case '*':
                    evalStack.push(op1 * op2);
                    break;
                case '/':
                    evalStack.push(op1 / op2);
                    break;
                case '^':
                    evalStack.push(std::pow(op1, op2));
                    break;
            }
        }
    }
    return evalStack.top();
}
