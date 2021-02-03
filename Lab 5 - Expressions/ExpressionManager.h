#ifndef ExpressionManager_h
#define ExpressionManager_h
#include <stdio.h>
#include <sstream>
#include <vector>
#include <stack>
#include "ExpressionManagerInterface.h"

class ExpressionManager : public ExpressionManagerInterface {
    private:
        string operators = "([{ -+  */% }])", postfix_;
        std::vector<string> infix_;
    
        /** Get Operator Precedence */
        int precedence(string op) const {
            int index = (int) operators.find(op);
            return index == -1 ? -1 : index / 4;
        }
        /** Determine if token is a number */
        bool isNum(string token) const {
            for (unsigned int i = 0; i < token.size(); ++i) {
                if (!isdigit(token.at(i))) return false;
            }
            return true;
        }
        /** Determine if token is a parenthesis */
        bool isParen(string token) const {
            string parens = "({[]})";
            return parens.find(token) == -1 ? false : true;
        }
        /** Determine if opening brace matches closing brace */
        bool matchingParen(string token, string match) const {
            if ((token == "(" && match == ")")
                || (token == "{" && match == "}")
                || (token == "[" && match == "]")) return true;
            return false;
        }
        /** Determine if token is an operator */
        bool isOp(string token) const {
            string ops = "-+*/%";
            return ops.find(token) == -1 ? false : true;
        }
        /* Get reverse of parenthesis for use in prefix */
        string reverseParen(string token) const {
            string parens = "({[)}]", out = "";
            if (token == "(" || token == "{" || token == "[") out.push_back(parens.at(parens.find(token) + 3));
            else out.push_back(parens.at(parens.find(token) - 3));
            return out;
        }
        /** Overload insertion operator to print infix */
        friend std::ostream& operator<<(std::ostream& os, ExpressionManager exp) {
            os << exp.toString();
            return os;
        }
    public:
        /** Construct class and store expression when class is created */
        ExpressionManager(string expr) {
            std::istringstream in(expr);
            for (string segment; getline(in, segment, ' ');) {
                infix_.push_back(segment);
            }
        }
        /** Return the infix vector'd expression items */
        string toString() const {
            std::ostringstream out;
            for (unsigned int i = 0; i < infix_.size(); ++i) {
                out << infix_[i] << " ";
            }
            return out.str();
        }
        /** Return the integer value of the infix expression */
        virtual int value(void);
        /** Return the infix items from the expression */
        string infix(void);
        /** Return a postfix representation of the infix expression */
        string postfix(void);
        /** (BONUS) Return a prefix representation of the infix expression */
        virtual string prefix(void);
};

#endif
