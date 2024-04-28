#include <iostream>
#include <string>
#include <stack>
#include <cmath>

using namespace std;

int precedence(char);
void inToPost(const string&, string&);
int post_eval(const string&);

int main() {
    string infix, postfix;
    cout << "Enter the infix expression (Nhập tên biểu thức trung tố vào : )";
    getline(cin, infix);

    inToPost(infix, postfix);
    int result = post_eval(postfix);
    cout << "The postfix expression: (Biểu thức hậu tố: )" << postfix << endl;
    cout << "The result: (kết quả: )" << result << endl;

    return 0;
}

int precedence(char symbol) {
    switch(symbol) {
        case '^':
            return 3;
        case '/':
        case '*':
            return 2;
        case '+':
        case '-':
            return 1;
        default:
            return 0;
    }
}

void inToPost(const string& infix, string& postfix) {
    stack<char> op_stack;
    postfix = "";
    for(char symbol : infix) {
        if (symbol == ' ' || symbol == '\t') {
            continue; // Skip whitespace
        } else if (symbol == '(') {
            op_stack.push(symbol);
        } else if (symbol == ')') {
            while (!op_stack.empty() && op_stack.top() != '(') {
                postfix += op_stack.top();
                op_stack.pop();
            }
            op_stack.pop(); // Pop '('
        } else if (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '^') {
            while (!op_stack.empty() && precedence(op_stack.top()) >= precedence(symbol)) {
                postfix += op_stack.top();
                op_stack.pop();
            }
            op_stack.push(symbol);
        } else {
            postfix += symbol;
        }
    }
    while (!op_stack.empty()) {
        postfix += op_stack.top();
        op_stack.pop();
    }
}

int post_eval(const string& postfix) {
    stack<int> operand_stack;
    for(char symbol : postfix) {
        if (symbol >= '0' && symbol <= '9') {
            operand_stack.push(symbol - '0');
        } else {
            int a = operand_stack.top();
            operand_stack.pop();
            int b = operand_stack.top();
            operand_stack.pop();
            switch (symbol) {
                case '+':
                    operand_stack.push(b + a); break;
                case '-':
                    operand_stack.push(b - a); break;
                case '*':
                    operand_stack.push(b * a); break;
                case '/':
                    operand_stack.push(b / a); break;
                case '^':
                    operand_stack.push(pow(b, a)); break;
            }
        }
    }
    return operand_stack.top();
}
