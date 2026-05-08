// 05-mini-projects/mini-shell/main.cpp
// minimal unix shell -- fork/exec/pipe
// compile (linux / mac only): g++ -std=c++11 main.cpp -o shell && ./shell
//
// NOTE: this project uses fork(), execvp(), unistd.h, sys/wait.h
// these are POSIX APIs and do NOT work on Windows (MSVC or MinGW).
// to run on Windows, use WSL (Windows Subsystem for Linux).

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

vector<string> cmd_history;

vector<string> tokenize(const string &line) {
    vector<string> tokens;
    istringstream ss(line);
    string tok;
    while (ss >> tok) tokens.push_back(tok);
    return tokens;
}

bool builtin_cd(const vector<string> &args) {
    if (args.size() < 2) chdir(getenv("HOME") ?: "/");
    else if (chdir(args[1].c_str()) != 0)
        cerr << "shell: cd: " << args[1] << ": no such directory\n";
    return true;
}

bool builtin_history(const vector<string> &) {
    for (size_t i = 0; i < cmd_history.size(); i++)
        cout << "  " << (i + 1) << "  " << cmd_history[i] << "\n";
    return true;
}

bool builtin_help(const vector<string> &) {
    cout << "  builtins: cd, history, help, exit\n";
    cout << "  everything else runs via execvp\n";
    return true;
}

bool builtin_exit(const vector<string> &) {
    cout << "\n  bye!\n\n";
    exit(0);
}

bool handleBuiltin(const vector<string> &args) {
    if (args.empty()) return false;
    if (args[0] == "cd")      return builtin_cd(args);
    if (args[0] == "history") return builtin_history(args);
    if (args[0] == "help")    return builtin_help(args);
    if (args[0] == "exit" || args[0] == "quit") return builtin_exit(args);
    return false;
}

void executeCommand(const vector<string> &args) {
    if (args.empty()) return;
    vector<char *> argv;
    for (auto &a : args) argv.push_back(const_cast<char *>(a.c_str()));
    argv.push_back(nullptr);

    pid_t pid = fork();
    if (pid < 0) { cerr << "shell: fork failed\n"; }
    else if (pid == 0) {
        execvp(argv[0], argv.data());
        cerr << "shell: " << args[0] << ": command not found\n";
        exit(1);
    } else {
        int status;
        waitpid(pid, &status, 0);
    }
}

bool hasPipe(const vector<string> &args) {
    for (auto &a : args) if (a == "|") return true;
    return false;
}

void executePipe(const vector<string> &args) {
    vector<string> left, right;
    bool seen = false;
    for (auto &a : args) {
        if (a == "|") { seen = true; continue; }
        (seen ? right : left).push_back(a);
    }

    int fd[2];
    pipe(fd);

    pid_t p1 = fork();
    if (p1 == 0) {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]); close(fd[1]);
        vector<char *> argv;
        for (auto &a : left) argv.push_back(const_cast<char *>(a.c_str()));
        argv.push_back(nullptr);
        execvp(argv[0], argv.data());
        exit(1);
    }

    pid_t p2 = fork();
    if (p2 == 0) {
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]); close(fd[1]);
        vector<char *> argv;
        for (auto &a : right) argv.push_back(const_cast<char *>(a.c_str()));
        argv.push_back(nullptr);
        execvp(argv[0], argv.data());
        exit(1);
    }

    close(fd[0]); close(fd[1]);
    waitpid(p1, nullptr, 0);
    waitpid(p2, nullptr, 0);
}

string getPrompt() {
    char cwd[256];
    if (!getcwd(cwd, sizeof(cwd))) return "? $ ";
    string path(cwd);
    size_t slash = path.rfind('/');
    if (slash != string::npos && slash > 0) {
        size_t prev = path.rfind('/', slash - 1);
        if (prev != string::npos) path = "..." + path.substr(prev);
    }
    return "\033[32m" + path + "\033[0m $ ";
}

int main() {
    cout << "\n  mini-shell  (type 'help' or 'exit')\n\n";

    string line;
    while (true) {
        cout << getPrompt() << flush;
        if (!getline(cin, line)) break;
        if (line.empty()) continue;
        cmd_history.push_back(line);

        auto args = tokenize(line);
        if (args.empty()) continue;

        if (!handleBuiltin(args)) {
            if (hasPipe(args)) executePipe(args);
            else               executeCommand(args);
        }
    }

    return 0;
}
