#include "ExpressionManager.h"
/** Return a postfix representation of the infix expression */
string ExpressionManager::postfix() {
    std::stack<string> operators;
    // For each element in infix either add to string or stack and process the operators
    for (unsigned int i = 0; i < infix_.size(); ++i) {
        string token = infix_.at(i);
        if (isNum(token)) postfix_.append(" " + token);
        else if (precedence(token) == 0) operators.push(token);
        else if (precedence(token) == 3) {
            while (!operators.empty() && !matchingParen(operators.top(), token)) {
                postfix_.append(" " + operators.top());
                operators.pop();
            }
            if (!operators.empty()) operators.pop();
        }
        else if (operators.empty() || precedence(token) > precedence(operators.top())) operators.push(token);
        else {
            while (!operators.empty() && precedence(token) <= precedence(operators.top())) {
                postfix_.append(" " + operators.top());
                operators.pop();
            }
            operators.push(token);
        }
    }
    // Add remaining operators in stack to string
    while (!operators.empty()) {
        postfix_.append(" " + operators.top());
        operators.pop();
    }
    postfix_ = postfix_.substr(1);
    return postfix_;
}
/** Return the integer value of the infix expression */
int ExpressionManager::value(void) {
    // Create postfix if it doesn't already exist
    if (postfix_.empty()) postfix();
    std::stack<string> stack;
    std::istringstream out(postfix_);
    // For each element in postfix, if it's a number push to stack otherwise evaluate operator with top 2 elements on stack
    for (string token; getline(out, token, ' ');) {
        if (isNum(token)) stack.push(token);
        else if (!stack.empty()) {
            int b = stoi(stack.top());
            stack.pop();
            int a = stoi(stack.top());
            stack.pop();
            if (token == "+") stack.push(std::to_string(a + b));
            else if (token == "-") stack.push(std::to_string(a - b));
            else if (token == "*") stack.push(std::to_string(a * b));
            else if (token == "/") stack.push(std::to_string(a / b));
            else if (token == "%") stack.push(std::to_string(a % b));
        }
    }
    return stoi(stack.top());
}
/** Return the infix items from the expression */
string ExpressionManager::infix(void) {
    if (infix_.empty()) throw "Invalid Expression";
    std::stack<string> stack;
    string out, lastToken;
    int numInts = 0, numOps = 0;
    // Detect if infix is balanced (Only in separate for loop because it needs to have higher priority :| )
    for (unsigned int i = 0; i < infix_.size(); ++i) {
        string token = infix_[i];
        if (precedence(token) == 0) stack.push(token);
        else if (!stack.empty() && precedence(token) == 3 && matchingParen(stack.top(), token)) stack.pop();
        else if (!stack.empty() && precedence(token) == 3 && !matchingParen(stack.top(), token)) throw "Unbalanced";
    }
    if (!stack.empty()) throw "Unbalanced";
    else if (isOp(infix_[0])) throw "Missing Operand";
    // Count numbers and operators in infix and determine if operators / operands are missing
    for (unsigned int i = 0; i < infix_.size(); ++i) {
        string token = infix_[i];
        if (!lastToken.empty() && isNum(token) && isNum(lastToken)) throw "Missing Operator";
        else if (!lastToken.empty() && isOp(token) && isOp(lastToken)) throw "Missing Operand";
        else if (isNum(token)) ++numInts;
        else if (isOp(token)) ++numOps;
        else if (!isParen(token)) throw "Illegal Operator";
        out.append(" " + token);
        lastToken = token;
    }
    if (numInts <= numOps) throw "Missing Operand";
    return out.substr(1);
}
/** (BONUS) Return a prefix representation of the infix expression */
string ExpressionManager::prefix(void) {
    std::stack<string> operators;
    std::vector<string> invert;
    string postfix;
    // Store reversed infix in invert vector
    for (int i = (int) infix_.size() - 1; i >= 0; --i) {
        string token = infix_[i];
        if (isParen(token)) token = reverseParen(token);
        invert.push_back(token);
    }
    // Convert invert to postfix with a few condition changes, insert output to beginning of postfix to reverse it
    for (unsigned int i = 0; i < invert.size(); ++i) {
        string token = invert.at(i);
        if (isNum(token)) postfix.insert(0, " " + token);
        else if (precedence(token) == 0) operators.push(token);
        else if (precedence(token) == 3) {
            while (!operators.empty() && !matchingParen(operators.top(), token)) {
                postfix.insert(0, " " + operators.top());
                operators.pop();
            }
            if (!operators.empty()) operators.pop();
        }
        else if (operators.empty() || precedence(token) >= precedence(operators.top())) operators.push(token);
        else {
            while (!operators.empty() && precedence(token) < precedence(operators.top())) {
                postfix.insert(0, " " + operators.top());
                operators.pop();
            }
            operators.push(token);
        }
    }
    while (!operators.empty()) {
        postfix.insert(0, " " + operators.top());
        operators.pop();
    }
    return postfix.substr(1);
}
