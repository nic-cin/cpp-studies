// 05-mini-projects/task-manager/main.cpp
// terminal task manager with file persistence
// compile: g++ -std=c++11 main.cpp -o tasks && tasks

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>
#include <algorithm>

#ifdef _WIN32
#include <windows.h>
void enableAnsi() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hOut, &mode);
    SetConsoleMode(hOut, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}
#else
void enableAnsi() {}
#endif

using namespace std;

struct Task {
    int    id;
    string text;
    bool   done;
    string created_at;
};

const string FILE_PATH = "tasks.dat";

string now() {
    time_t t = time(nullptr);
    tm tm_info{};

#ifdef _WIN32
    localtime_s(&tm_info, &t);
#else
    localtime_r(&t, &tm_info);
#endif

    char buf[20];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M", &tm_info);

    return string(buf);
}

void saveTasks(const vector<Task>& tasks) {
    ofstream f(FILE_PATH);
    for (auto& t : tasks)
        f << t.id << "|" << (t.done ? 1 : 0) << "|" << t.created_at << "|" << t.text << "\n";
}

vector<Task> loadTasks() {
    vector<Task> tasks;
    ifstream f(FILE_PATH);
    if (!f.is_open()) return tasks;
    string line;
    while (getline(f, line)) {
        istringstream ss(line);
        string id_s, done_s, created, text;
        if (getline(ss, id_s, '|') &&
            getline(ss, done_s, '|') &&
            getline(ss, created, '|') &&
            getline(ss, text)) {
            tasks.push_back({ stoi(id_s), text, done_s == "1", created });
        }
    }
    return tasks;
}

int nextId(const vector<Task>& tasks) {
    int max = 0;
    for (auto& t : tasks) if (t.id > max) max = t.id;
    return max + 1;
}

void listTasks(const vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "  (no tasks yet)\n\n";
        return;
    }

    int done_count = 0;
    for (auto& t : tasks) if (t.done) done_count++;

    cout << "  tasks: " << tasks.size()
        << "  done: " << done_count
        << "  pending: " << (tasks.size() - done_count) << "\n";
    cout << "  --------------------------------------------------\n";

    for (auto& t : tasks) {
        string mark = t.done ? "[x]" : "[ ]";
        // dim color for done tasks
        if (t.done) cout << "\033[90m";
        cout << "  " << mark
            << " #" << setw(2) << t.id << "  "
            << t.text;
        cout << "  (" << t.created_at << ")";
        if (t.done) cout << "\033[0m";
        cout << "\n";
    }
    cout << "\n";
}

void addTask(vector<Task>& tasks) {
    cout << "  task text: ";
    string text;
    cin.ignore();
    getline(cin, text);
    if (text.empty()) { cout << "  (empty, skipped)\n\n"; return; }
    tasks.push_back({ nextId(tasks), text, false, now() });
    saveTasks(tasks);
    cout << "  added!\n\n";
}

void markDone(vector<Task>& tasks) {
    cout << "  task id: ";
    int id; cin >> id;
    for (auto& t : tasks) {
        if (t.id == id) {
            t.done = true;
            saveTasks(tasks);
            cout << "  marked done!\n\n";
            return;
        }
    }
    cout << "  id not found\n\n";
}

void removeTask(vector<Task>& tasks) {
    cout << "  task id: ";
    int id; cin >> id;
    auto it = remove_if(tasks.begin(), tasks.end(),
        [id](const Task& t) { return t.id == id; });
    if (it != tasks.end()) {
        tasks.erase(it, tasks.end());
        saveTasks(tasks);
        cout << "  removed!\n\n";
    }
    else {
        cout << "  id not found\n\n";
    }
}

void clearDone(vector<Task>& tasks) {
    tasks.erase(remove_if(tasks.begin(), tasks.end(),
        [](const Task& t) { return t.done; }),
        tasks.end());
    saveTasks(tasks);
    cout << "  cleared completed tasks\n\n";
}

int main() {
    enableAnsi();
    auto tasks = loadTasks();

    cout << "\n";
    cout << "  +--------------------------------------------------+\n";
    cout << "  |                  task manager                    |\n";
    cout << "  +--------------------------------------------------+\n\n";

    char cmd;
    while (true) {
        listTasks(tasks);
        cout << "  [a] add  [d] done  [r] remove  [c] clear done  [q] quit\n";
        cout << "  -> ";
        cin >> cmd;

        switch (cmd) {
        case 'a': addTask(tasks);    break;
        case 'd': markDone(tasks);   break;
        case 'r': removeTask(tasks); break;
        case 'c': clearDone(tasks);  break;
        case 'q': cout << "\n  bye!\n\n"; return 0;
        default:  cout << "  unknown command\n\n";
        }
    }
}
