// 05-mini-projects/password-generator/main.cpp
// terminal password generator
// compile: g++ main.cpp -o passgen && passgen

#include <iostream>
#include <string>
#include <random>
#include <algorithm>
using namespace std;

const string LOWER   = "abcdefghijklmnopqrstuvwxyz";
const string UPPER   = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string DIGITS  = "0123456789";
const string SYMBOLS = "!@#$%^&*()-_=+[]{}|;:,.<>?";

struct Options {
    int  length  = 16;
    bool lower   = true;
    bool upper   = true;
    bool digits  = true;
    bool symbols = true;
    int  count   = 1;
};

string generatePassword(const Options &opts, mt19937 &rng) {
    string pool;
    if (opts.lower)   pool += LOWER;
    if (opts.upper)   pool += UPPER;
    if (opts.digits)  pool += DIGITS;
    if (opts.symbols) pool += SYMBOLS;

    if (pool.empty()) return "error: no charset selected";

    uniform_int_distribution<int> dist(0, (int)pool.size() - 1);
    string password;

    auto pick = [&](const string &set) {
        uniform_int_distribution<int> d(0, (int)set.size() - 1);
        password += set[d(rng)];
    };
    if (opts.lower)   pick(LOWER);
    if (opts.upper)   pick(UPPER);
    if (opts.digits)  pick(DIGITS);
    if (opts.symbols) pick(SYMBOLS);

    while ((int)password.size() < opts.length)
        password += pool[dist(rng)];

    shuffle(password.begin(), password.end(), rng);
    return password;
}

int estimateEntropy(const Options &opts) {
    int poolSize = 0;
    if (opts.lower)   poolSize += 26;
    if (opts.upper)   poolSize += 26;
    if (opts.digits)  poolSize += 10;
    if (opts.symbols) poolSize += (int)SYMBOLS.size();
    double log2pool = 0;
    int p = poolSize;
    while (p > 1) { log2pool++; p >>= 1; }
    return (int)(opts.length * log2pool);
}

string strengthLabel(int bits) {
    if (bits < 40) return "weak";
    if (bits < 60) return "fair";
    if (bits < 80) return "strong";
    return "very strong";
}

Options interactiveMode() {
    Options opts;
    string input;

    cout << "  length [16]: ";
    getline(cin, input);
    if (!input.empty()) opts.length = stoi(input);

    cout << "  count  [1]:  ";
    getline(cin, input);
    if (!input.empty()) opts.count = stoi(input);

    cout << "  include uppercase? [Y/n]: ";
    getline(cin, input);
    if (!input.empty() && (input[0] == 'n' || input[0] == 'N')) opts.upper = false;

    cout << "  include digits?    [Y/n]: ";
    getline(cin, input);
    if (!input.empty() && (input[0] == 'n' || input[0] == 'N')) opts.digits = false;

    cout << "  include symbols?   [Y/n]: ";
    getline(cin, input);
    if (!input.empty() && (input[0] == 'n' || input[0] == 'N')) opts.symbols = false;

    return opts;
}

int main(int argc, char *argv[]) {
    cout << "\n";
    cout << "  +-----------------------------+\n";
    cout << "  |     password generator      |\n";
    cout << "  +-----------------------------+\n\n";

    Options opts;

    if (argc >= 2) {
        opts.length = stoi(argv[1]);
        if (argc >= 3) opts.count = stoi(argv[2]);
    } else {
        opts = interactiveMode();
    }

    if (opts.length < 4 || opts.length > 256) {
        cerr << "  error: length must be 4-256\n";
        return 1;
    }

    random_device rd;
    mt19937 rng(rd());

    int entropy = estimateEntropy(opts);
    cout << "\n  entropy : ~" << entropy << " bits (" << strengthLabel(entropy) << ")\n";
    cout << "  --------------------------------\n";

    for (int i = 0; i < opts.count; i++) {
        cout << "  " << generatePassword(opts, rng) << "\n";
    }

    cout << "  --------------------------------\n\n";
    return 0;
}

// examples:
//   passgen          (interactive)
//   passgen 24       (length 24)
//   passgen 24 5     (length 24, 5 passwords)
