// 03-structs/structs.cpp
// structs -- grouping data together
// compile: g++ structs.cpp -o structs && structs

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

struct Point {
    double x;
    double y;
};

struct Player {
    string name;
    int health;
    int score;
};

struct Team {
    string name;
    vector<Player> members;
};

struct Config {
    string host  = "localhost";
    int    port  = 8080;
    bool   debug = false;
};

double distance(Point a, Point b) {
    double dx = b.x - a.x;
    double dy = b.y - a.y;
    return sqrt(dx * dx + dy * dy);
}

void printPlayer(const Player &p) {
    cout << "  [" << p.name << "] hp=" << p.health
         << " score=" << p.score << "\n";
}

void heal(Player &p, int amount) {
    p.health += amount;
    if (p.health > 100) p.health = 100;
}

int main() {
    cout << "=== point ===\n";
    Point a = {0.0, 0.0};
    Point b = {3.0, 4.0};
    cout << "a = (" << a.x << ", " << a.y << ")\n";
    cout << "b = (" << b.x << ", " << b.y << ")\n";
    cout << "distance = " << distance(a, b) << "\n\n";

    cout << "=== player ===\n";
    Player p1 = {"archer", 40, 1500};
    Player p2 = {"mage",   80, 3200};
    printPlayer(p1);
    printPlayer(p2);

    heal(p1, 25);
    cout << "after heal -> ";
    printPlayer(p1);
    cout << "\n";

    cout << "=== team ===\n";
    Team team = {"shadow guild", {p1, p2}};
    cout << "team: " << team.name << "\n";
    for (auto &member : team.members)
        printPlayer(member);
    cout << "\n";

    cout << "=== struct pointer ===\n";
    Player *ptr = new Player{"rogue", 70, 900};
    cout << "via pointer: " << ptr->name << " hp=" << ptr->health << "\n";
    ptr->score += 100;
    cout << "score after bonus: " << ptr->score << "\n";
    delete ptr;
    cout << "\n";

    cout << "=== config (defaults) ===\n";
    Config cfg;
    cout << "host=" << cfg.host << " port=" << cfg.port
         << " debug=" << boolalpha << cfg.debug << "\n";

    Config custom = {"192.168.1.1", 3000, true};
    cout << "host=" << custom.host << " port=" << custom.port
         << " debug=" << custom.debug << "\n";

    return 0;
}
