#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <string>

class Expression {
   public:
    Expression();

    Expression(std::string infix);

    void print();
    bool validate();

    void convertToPostfix();
    double evaluate();

   private:
    std::string infix;
    bool isValid;
    std::string postfix;

    bool isOperator(char c);

    int precedence(char op);
};

#endif  // !EXPRESSION_HPP
