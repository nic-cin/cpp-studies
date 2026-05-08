// 04-files/files.cpp
// reading and writing files in c++
// compile: g++ files.cpp -o files && files

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct Record {
    string name;
    int    score;
};

void writeFile(const string &path) {
    ofstream file(path);
    if (!file.is_open()) {
        cerr << "error: could not open " << path << "\n";
        return;
    }
    file << "alice,1500\n";
    file << "bob,2300\n";
    file << "carol,980\n";
    file.close();
    cout << "wrote -> " << path << "\n";
}

void readFile(const string &path) {
    ifstream file(path);
    if (!file.is_open()) {
        cerr << "error: could not open " << path << "\n";
        return;
    }
    string line;
    cout << "reading " << path << ":\n";
    while (getline(file, line)) {
        cout << "  " << line << "\n";
    }
    file.close();
}

vector<Record> parseCsv(const string &path) {
    vector<Record> records;
    ifstream file(path);
    string line;
    while (getline(file, line)) {
        istringstream ss(line);
        string name, score_str;
        if (getline(ss, name, ',') && getline(ss, score_str)) {
            records.push_back({name, stoi(score_str)});
        }
    }
    return records;
}

void appendFile(const string &path, const string &entry) {
    ofstream file(path, ios::app);
    if (!file.is_open()) return;
    file << entry << "\n";
    cout << "appended -> " << entry << "\n";
}

bool fileExists(const string &path) {
    ifstream f(path);
    return f.good();
}

int countLines(const string &path) {
    ifstream file(path);
    int count = 0;
    string line;
    while (getline(file, line)) count++;
    return count;
}

int main() {
    const string path = "scores.csv";

    cout << "=== write ===\n";
    writeFile(path);
    cout << "\n";

    cout << "=== read raw ===\n";
    readFile(path);
    cout << "\n";

    cout << "=== parsed records ===\n";
    auto records = parseCsv(path);
    for (auto &r : records)
        cout << "  name=" << r.name << " score=" << r.score << "\n";
    cout << "\n";

    cout << "=== append ===\n";
    appendFile(path, "dave,4100");
    cout << "\n";

    cout << "=== verify ===\n";
    cout << "file exists? " << boolalpha << fileExists(path) << "\n";
    cout << "line count:  " << countLines(path) << "\n";

    return 0;
}
