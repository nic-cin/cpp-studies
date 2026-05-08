// 05-mini-projects/calculator/main.cpp
// terminal calculator with expression parsing and history
// compile: g++ -std=c++11 main.cpp -o calc && calc

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <stdexcept>
#include <iomanip>
using namespace std;

struct Entry {
    string expr;
    double result;
};

// ── recursive descent parser ──────────────────────────────────────────────────

class Parser {
    string src;
    size_t pos = 0;

    char peek() { return pos < src.size() ? src[pos] : '\0'; }
    char get()  { return pos < src.size() ? src[pos++] : '\0'; }
    void skipSpaces() { while (peek() == ' ') get(); }

    double number() {
        skipSpaces();
        bool neg = false;
        if (peek() == '-') { neg = true; get(); }
        if (peek() == '(') return neg ? -paren() : paren();

        string s;
        while (isdigit(peek()) || peek() == '.') s += get();
        if (s.empty()) throw runtime_error("expected number");
        return neg ? -stod(s) : stod(s);
    }

    double paren() {
        get(); // consume '('
        double val = expression();
        skipSpaces();
        if (peek() == ')') get();
        return val;
    }

    double power() {
        double base = number();
        skipSpaces();
        if (peek() == '^') { get(); return pow(base, power()); }
        return base;
    }

    double term() {
        double val = power();
        skipSpaces();
        while (peek() == '*' || peek() == '/') {
            char op = get();
            double rhs = power();
            if (op == '*') val *= rhs;
            else {
                if (rhs == 0) throw runtime_error("division by zero");
                val /= rhs;
            }
            skipSpaces();
        }
        return val;
    }

    double expression() {
        double val = term();
        skipSpaces();
        while (peek() == '+' || peek() == '-') {
            char op = get();
            val = (op == '+') ? val + term() : val - term();
            skipSpaces();
        }
        return val;
    }

public:
    double evaluate(const string &s) {
        src = s; pos = 0;
        double result = expression();
        skipSpaces();
        if (pos != src.size()) throw runtime_error("unexpected character");
        return result;
    }
};

// ── display ───────────────────────────────────────────────────────────────────

void printHistory(const vector<Entry> &history) {
    if (history.empty()) {
        cout << "  (no history)\n\n";
        return;
    }
    cout << "\n  -- history --\n";
    for (size_t i = 0; i < history.size(); i++) {
        cout << "  " << setw(2) << (i + 1) << ".  "
             << history[i].expr << " = "
             << setprecision(10) << history[i].result << "\n";
    }
    cout << "\n";
}

int main() {
    cout << "\n";
    cout << "  +-----------------------+\n";
    cout << "  |      calculator       |\n";
    cout << "  +-----------------------+\n";
    cout << "  ops:  + - * / ^ ()\n";
    cout << "  cmds: history | clear | ans | quit\n\n";

    Parser parser;
    vector<Entry> history;
    double ans = 0.0;
    string input;

    while (true) {
        cout << "  > ";
        getline(cin, input);
        if (input.empty()) continue;

        if (input == "quit" || input == "q" || input == "exit") {
            cout << "\n  bye!\n\n";
            break;
        }
        if (input == "history" || input == "h") { printHistory(history); continue; }
        if (input == "clear")  { history.clear(); cout << "  history cleared\n\n"; continue; }
        if (input == "ans")    { cout << "  ans = " << ans << "\n\n"; continue; }

        // replace "ans" in expression
        string expr = input;
        string ans_str = to_string(ans);
        size_t p = 0;
        while ((p = expr.find("ans", p)) != string::npos) {
            expr.replace(p, 3, ans_str);
            p += ans_str.size();
        }

        try {
            double result = parser.evaluate(expr);
            ans = result;
            history.push_back({input, result});
            cout << "  = " << setprecision(10) << result << "\n\n";
        } catch (const exception &e) {
            cout << "  error: " << e.what() << "\n\n";
        }
    }

    return 0;
}

// examples:
//   > 2 + 3 * 4        -> 14
//   > (2 + 3) * 4      -> 20
//   > 2^10             -> 1024
//   > ans / 2          -> 512
//   > 355 / 113        -> 3.14159292
