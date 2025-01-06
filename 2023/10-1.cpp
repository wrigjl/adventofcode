#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <unordered_set>
#include <deque>

// The approach for part 2 doesn't quite work. I'm likely misunderstand the problem.

using namespace std;

struct Position {
    size_t row, col;
    bool operator<(const Position &other) const {
        return row < other.row || (row == other.row && col < other.col);
    }
    bool operator==(const Position &other) const = default;
};

template<> struct std::hash<Position> {
    std::size_t operator()(const Position& s) const noexcept {
        return (s.row << 16) | s.col;
    }
};

void readMaze(vector<string>& maze) {
    string line;

    while (getline(cin, line))
        maze.push_back(line);
}

void printMaze(const vector<string>& maze) {
    for (auto const& row: maze)
        cout << row << endl;
}

int main() {
    vector<string> maze;
    Position start = {string::npos, string::npos};

    readMaze(maze);
    for (auto row = 0; row < maze.size(); ++row) {
        auto pos = maze[row].find('S');
        if (pos == string::npos)
            continue;
        start.row = row;
        start.col = pos;
        break;
    }

    if (start.row == string::npos || start.col == string::npos)
        throw std::runtime_error("invalid start");

    // figure out what start should be:
    int dirmask = 0;
    if (start.col - 1 < maze[0].size()) {
        if (maze[start.row][start.col - 1] == '-' ||
            maze[start.row][start.col - 1] == 'L' ||
            maze[start.row][start.col - 1] == 'F')
            dirmask |= (1 << 0); // west
    }
    if (start.col + 1 < maze[0].size()) {
        if (maze[start.row][start.col + 1] == '-' ||
            maze[start.row][start.col + 1] == 'J' ||
            maze[start.row][start.col + 1] == '7')
            dirmask |= (1 << 1); // east
    }
    if (start.row + 1 < maze.size()) {
        if (maze[start.row + 1][start.col] == '|' ||
            maze[start.row + 1][start.col] == 'L' ||
            maze[start.row + 1][start.col] == 'J')
            dirmask |= (1 << 3); // north
    }
    if (start.row - 1 < maze.size()) {
        if (maze[start.row - 1][start.col] == '|' ||
            maze[start.row - 1][start.col] == '7' ||
            maze[start.row - 1][start.col] == 'F')
            dirmask |= (1 << 2); // south
    }

    char startchar;
    switch (dirmask) {
        //     SNEW
        case 0b0011: startchar = '-';
            break;
        case 0b0101: startchar = 'J';
            break;
        case 0b1001: startchar = '7';
            break;
        case 0b0110: startchar = 'L';
            break;
        case 0b1010: startchar = 'F';
            break;
        case 0b1100: startchar = '|';
            break;
        default: throw std::runtime_error("invalid dirmask");
    }
    maze[start.row][start.col] = startchar;

    unordered_set<Position> visited;
    deque<Position> workq;
    workq.push_front(start);
    while (!workq.empty()) {
        Position pos = workq.front();
        workq.pop_front();

        if (pos.row >= maze.size() || pos.col >= maze[pos.row].size())
            continue;
        if (visited.contains(pos))
            continue;
        visited.insert(pos);

        switch (maze[pos.row][pos.col]) {
            case '|':
                workq.push_back({pos.row - 1, pos.col + 0});
                workq.push_back({pos.row + 1, pos.col + 0});
                break;
            case '-':
                workq.push_back({pos.row + 0, pos.col + 1});
                workq.push_back({pos.row + 0, pos.col - 1});
                break;
            case 'L':
                workq.push_back({pos.row - 1, pos.col + 0});
                workq.push_back({pos.row + 0, pos.col + 1});
                break;
            case 'J':
                workq.push_back({pos.row - 1, pos.col + 0});
                workq.push_back({pos.row + 0, pos.col - 1});
                break;
            case '7':
                workq.push_back({pos.row + 1, pos.col + 0});
                workq.push_back({pos.row + 0, pos.col - 1});
                break;
            case 'F':
                workq.push_back({pos.row + 1, pos.col + 0});
                workq.push_back({pos.row + 0, pos.col + 1});
                break;
            default:
                throw std::runtime_error("invalid char");
        }
    }

    std::cout << "part1: " << visited.size()/2 << endl;

    // Ok, let's use ray casting to detect who's inside
    unordered_set<Position> inside;

    // SE -> NW ray cast
    unordered_set<Position> scanStarts;
    for (size_t row = 0; row < maze.size(); ++row)
        scanStarts.insert(Position{row, maze[row].size() - 1});
    for (size_t col = 0; col < maze[0].size(); ++col)
        scanStarts.insert(Position{maze.size() - 1, col});

    for (auto pos: scanStarts) {
        bool isInside = false;
        while (pos.row <= maze.size() && pos.col <= maze[0].size()) {
            if (visited.contains(pos)) {
                if (maze[pos.row][pos.col] == '|' ||
                    maze[pos.row][pos.col] == '-' ||
                    maze[pos.row][pos.col] == 'F' ||
                    maze[pos.row][pos.col] == 'J')
                    isInside = !isInside;
            } else {
                if (isInside)
                    inside.insert(pos);
            }
            pos.row--;
            pos.col--;
        }
    }

    for (auto const& pos: inside) {
        maze[pos.row][pos.col] = 'I';
    }

    cout << "part2: " << inside.size() << endl;
}