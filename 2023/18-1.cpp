#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <map>

using namespace std;

struct DirLenColor {
    char dir;
    int len;
    uint32_t color;
};

vector<DirLenColor> dirs;

void scanFrom(vector<string> & maze, size_t row, int col) {
    bool inside = false;
    for (;;) {
        if (maze[row][col] == '|' || maze[row][col] == '-' ||
            maze[row][col] == 'F' || maze[row][col] == 'J')
            inside = !inside;
        else if (inside)
            maze[row][col] = 'X';

        row++; col++;
        if (row >= maze.size() || col >= maze[row].size())
            break;
    }
}

int main() {
    string line;
    vector<string> maze;
    int westmax = 0, eastmax = 0, northmax = 0, southmax = 0;
    int x = 0, y = 0;

    while (getline(cin, line)) {
        regex parseRe("([RUDL]) ([0-9]+) \\(#([0-9a-fA-F]+)\\)");
        smatch matches;
        if (!regex_match(line, matches, parseRe))
            throw runtime_error(line);

        DirLenColor dir{};
        dir.dir = matches[1].str()[0];
        dir.len = stoi(matches[2].str());
        dir.color = stoi(matches[3].str(), nullptr, 16);
        dirs.push_back(dir);

        if (dir.dir == 'R') {
            x += dir.len;
            eastmax = max(eastmax, x);
        } else if (dir.dir == 'L') {
            x -= dir.len;
            westmax = min(westmax, x);
        } else if (dir.dir == 'U') {
            y -= dir.len;
            northmax = min(northmax, y);
        } else if (dir.dir == 'D') {
            y += dir.len;
            southmax = max(southmax, y);
        } else
            throw runtime_error("Invalid direction");
    }
    cout << "hor: " << westmax << "," << eastmax << endl;
    cout << "ver: " << northmax << "," << southmax << endl;

    x = -westmax + 5;
    y = -northmax + 5;
    westmax -= 5;
    eastmax += 5;
    northmax -= 5;
    southmax += 5;

    for (int i = northmax; i <= southmax; i++) {
        string s(eastmax - westmax, '.');
        maze.push_back(s);
    }

    maze[y][x] = '#';
    map<string,char> turns = {
        {"RR", '-'}, {"RD", '7'}, {"RU", 'J'}, {"RL", '-'},
        {"LR", '-'}, {"LD", 'F'}, {"LU", 'L'}, {"RL", '-'},
        {"UR", 'F'}, {"UD", '|'}, {"UU", '|'}, {"UL", '7'},
        {"DR", 'L'}, {"DD", '|'}, {"DU", '|'}, {"DL", 'J'},
    };
    for (size_t diridx = 0; diridx < dirs.size(); diridx++) {
        auto const &dir = dirs[diridx];
        char c = 'X';
        for (size_t i = 0; i < dir.len; i++) {
            if (dir.dir == 'R') {
                ++x;
                c = '-';
            } else if (dir.dir == 'L') {
                --x;
                c = '-';
            } else if (dir.dir == 'U') {
                --y;
                c = '|';
            } else if (dir.dir == 'D') {
                ++y;
                c = '|';
            } else
                throw runtime_error("Invalid direction");

            maze[y][x] = c;
        }
        string key(1, dir.dir);
        key.append(1, dirs[(diridx + 1) % dirs.size()].dir);
        maze[y][x] = turns[key];
    }

    for (size_t i = 0; i < maze.size(); i++)
        scanFrom(maze, i, 0);
    for (size_t i = 0; i < maze[0].size(); i++)
        scanFrom(maze, 0, i);

    size_t area = maze.size() * maze[0].size();
    for (auto const& l: maze)
        area -= count_if(l.begin(), l.end(),
            [](char c) { return c == '.'; });

    for (auto const& l: maze)
        cout << l << endl;

    cout << area << endl;
}