
#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <stdexcept>

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

int applyOp(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if (b == 0) throw std::runtime_error("Division by zero");
            return a / b;
    }
    return 0;
}

int evaluate(const std::string& expr) {
    std::stack<int> values;
    std::stack<char> ops;

    for (size_t i = 0; i < expr.length(); i++) {
        char c = expr[i];
        if (isspace(c)) continue;
        if (isdigit(c)) {
            int val = 0;
            while (i < expr.length() && isdigit(expr[i])) {
                val = val * 10 + (expr[i] - '0');
                i++;
            }
            values.push(val);
            i--;
        } else if (c == '(') {
            ops.push(c);
        } else if (c == ')') {
            while (!ops.empty() && ops.top() != '(') {
                int val2 = values.top(); values.pop();
                int val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            if (!ops.empty()) ops.pop();
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!ops.empty() && precedence(ops.top()) >= precedence(c)) {
                int val2 = values.top(); values.pop();
                int val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            ops.push(c);
        }
    }

    while (!ops.empty()) {
        int val2 = values.top(); values.pop();
        int val1 = values.top(); values.pop();
        char op = ops.top(); ops.pop();
        values.push(applyOp(val1, val2, op));
    }

    return values.top();
}

int main() {
    std::string input;
    std::cout << "Enter an arithmetic expression: ";
    std::getline(std::cin, input);

    try {
        int result = evaluate(input);
        std::cout << "Result: " << result << std::endl;
    } catch (const std::exception& ex) {
        std::cout << "Error: " << ex.what() << std::endl;
    }

    return 0;
}
