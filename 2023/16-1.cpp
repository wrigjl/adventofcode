#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <unordered_set>
#include <deque>

using std::string;
using std::vector;
using std::cout, std::endl, std::cin, std::set, std::deque, std::unordered_set;

struct Position {
    size_t row, col;
    bool operator<(const Position &other) const {
        return row < other.row || (row == other.row && col < other.col);
    }
    bool operator==(const Position &other) const = default;
};

template<>
struct std::hash<Position>
{
    std::size_t operator()(const Position& s) const noexcept {
        return (s.row << 16) | s.col;
    }
};

enum Direction {
    North = '^',
    South = 'v',
    West = '<',
    East = '>',
};

struct PosDir {
    Position pos;
    Direction dir;
    bool operator==(const PosDir &other) const = default;
};

template<>
struct std::hash<PosDir>
{
    std::size_t operator()(const PosDir& s) const noexcept {
        return (std::hash<Position>{}(s.pos) << 8) | static_cast<int>(s.dir);
    }
};

void readMaze(vector<string>& maze) {
    string line;

    while (std::getline(cin, line)) {
        if (line.empty())
            break;
        maze.push_back(line);
    }
}

Position move(Position pos, Direction dir) {
    if (dir == Direction::North)
        pos.row--;
    else if (dir == Direction::South)
        pos.row++;
    else if (dir == Direction::West)
        pos.col--;
    else if (dir == Direction::East)
        pos.col++;
    return pos;
}

size_t walkMaze(const vector<string>& maze, PosDir start) {
    deque<PosDir> workq;
    unordered_set<PosDir> seen;
    unordered_set<Position> energized;

    workq.emplace_front(start);

    while (!workq.empty()) {
        PosDir current = workq.front();
        workq.pop_front();

        if (current.pos.row >= maze.size() ||
            current.pos.col >= maze[current.pos.row].size())
            continue;

        if (seen.contains(current))
            continue;

        seen.insert(current);
        energized.insert(current.pos);

        auto c = maze[current.pos.row][current.pos.col];
        if (c == '.') {
            workq.emplace_back(PosDir{move(current.pos, current.dir), current.dir});
        } else if (c == '|') {
            if (current.dir == Direction::North || current.dir == Direction::South) {
                workq.emplace_back(PosDir{move(current.pos, current.dir), current.dir});
            } else {
                workq.emplace_back(PosDir{move(current.pos, North), North});
                workq.emplace_back(PosDir{move(current.pos, South), South});
            }
        } else if (c == '-') {
            if (current.dir == Direction::West || current.dir == Direction::East) {
                workq.emplace_back(PosDir{move(current.pos, current.dir), current.dir});
            } else {
                workq.emplace_back(PosDir{move(current.pos, West), West});
                workq.emplace_back(PosDir{move(current.pos, East), East});
            }
        } else if (c == '/') {
            if (current.dir == Direction::East)
                workq.emplace_back(PosDir{move(current.pos, North), North});
            else if (current.dir == Direction::North)
                workq.emplace_back(PosDir{move(current.pos, East), East});
            else if (current.dir == Direction::West)
                workq.emplace_back(PosDir{move(current.pos, South), South});
            else if (current.dir == Direction::South)
                workq.emplace_back(PosDir{move(current.pos, West), West});
        } else if (c == '\\') {
            if (current.dir == Direction::East)
                workq.emplace_back(PosDir{move(current.pos, South), South});
            else if (current.dir == Direction::North)
                workq.emplace_back(PosDir{move(current.pos, West), West});
            else if (current.dir == Direction::West)
                workq.emplace_back(PosDir{move(current.pos, North), North});
            else if (current.dir == Direction::South)
                workq.emplace_back(PosDir{move(current.pos, East), East});
        }
    }

    return energized.size();
}

int main() {
    vector<string> maze;
    readMaze(maze);
    size_t part2 = 0;

    std::cout << "Part 1: " << walkMaze(maze, PosDir{{0, 0}, East}) << std::endl;

    for (size_t row = 0; row < maze.size(); ++row) {
        part2 = std::max(part2, walkMaze(maze, PosDir{{row, 0}, East}));
        part2 = std::max(part2, walkMaze(maze, PosDir{{row, maze[0].size()-1}, West}));
    }
    for (size_t col = 0; col < maze[0].size(); ++col) {
        part2 = std::max(part2, walkMaze(maze, PosDir{{0, col}, South}));
        part2 = std::max(part2, walkMaze(maze, PosDir{{maze.size()-1, col}, North}));
    }
    std::cout << "Part 2: " << part2 << std::endl;
}