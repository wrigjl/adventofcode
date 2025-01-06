#include <iostream>
#include <unordered_set>
#include <vector>
#include <string>

using namespace std;

struct Position {
    int x, y;
    bool operator==(const Position&) const = default;
};

template<> struct std::hash<Position> {
    std::size_t operator()(const Position& s) const noexcept {
        return abs(s.x) << 16 | abs(s.y);
    }
};

int main() {
    unordered_set<Position> visited;
    unordered_set<Position> visited2;
    string moves = "^>v<";
    Position pos{};
    Position p2santa{};
    Position p2robo{};
    auto *p2p = &p2santa;

    getline(cin, moves);
    visited.insert(pos);
    visited2.insert(p2santa);
    visited2.insert(p2robo);

    for (auto c: moves) {
        if (c == '<') {
            pos.y--;
            p2p->y--;
        } else if (c == '>') {
            pos.y++;
            p2p->y++;
        } else if (c == '^') {
            pos.x--;
            p2p->x--;
        } else if (c == 'v') {
            pos.x++;
            p2p->x++;
        }

        visited.insert(pos);
        visited2.insert(*p2p);
        p2p = (p2p == &p2santa) ? &p2robo : &p2santa;
    }

    cout << "part1: " << visited.size() << endl;
    cout << "part2: " << visited2.size() << endl;
}