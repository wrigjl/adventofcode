#include <iostream>
#include <vector>
#include <string>

using namespace std;

void printMaze(const vector<string>& maze) {
    for (auto const& x: maze)
        cout << x << endl;
}

char getMaze(const vector<string>& maze, size_t row, size_t col) {
    if (row >= maze.size() || col >= maze[row].size())
        return '.';
    return maze[row][col];
}

unsigned aliveNeighbors(const vector<string>& maze, size_t row, size_t col) {
    vector<pair<int, int>> neighbors = {{-1, -1}, {-1, 0}, {-1, 1},
                                        {0, -1}, {0, 1},
                                        {1, -1}, {1, 0}, {1, 1}};
    unsigned count = 0;
    for (auto n: neighbors)
        if (getMaze(maze, row + n.first, col + n.second) == '#')
            count++;
    return count;
}

vector<string> step(const vector<string> &maze) {
    vector<string> newMaze;
    for (size_t row = 0; row < maze.size(); row++) {
        newMaze.push_back("");
        for (size_t col = 0; col < maze[row].size(); col++) {
            char c = '.';
            auto cnt = aliveNeighbors(maze, row, col);
            if (maze[row][col] == '#' && (cnt == 2 || cnt == 3))
                c = '#';
            else if (maze[row][col] == '.' && cnt == 3)
                c = '#';

            // override: corners are always on
            if ((row == 0 || row == maze.size() - 1) &&
                (col == 0 || col == maze[row].size() - 1))
                c = '#';

            newMaze[row].push_back(c);
        }
    }
    return newMaze;
}

int main() {
    string line;
    vector<string> maze;

    while (getline(cin, line)) {
        if (line.empty())
            break;
        maze.push_back(line);
    }

    //printMaze(maze);

    maze[0][0] = '#';
    maze[maze.size() - 1][0] = '#';
    maze[0][maze[0].size() - 1] = '#';
    maze[maze.size() - 1][maze[0].size() - 1] = '#';

    for (int i = 1; i <= 100; i++) {
        // cout << endl << "  " << i << endl;
        maze = step(maze);
        //printMaze(maze);
    }

    u_long cnt = 0;
    for (size_t row = 0; row < maze.size(); row++)
        for (size_t col = 0; col < maze[row].size(); col++)
            if (maze[row][col] == '#')
                cnt++;

    cout << cnt << endl;
}
