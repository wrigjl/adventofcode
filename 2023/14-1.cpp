
#include <iostream>
#include <vector>
#include <string>

char getMaze(const std::vector<std::string>&maze, size_t row, size_t col) {
        if (row >= maze.size() || col >= maze[row].size())
                return '#';
        return maze[row][col];
}

int rollit(std::vector<std::string>& maze) {
        int cnt = 0;
        for (size_t row = 0; row < maze.size(); ++row) {
                for (size_t col = 0; col < maze[row].size(); ++col) {
                        if (maze[row][col] == 'O' && maze[row - 1][col] == '.') {
                                maze[row][col] = '.';
                                maze[row - 1][col] = 'O';
                                cnt++;
                        }
                }
        }
        return cnt;
}

u_long countit(std::vector<std::string>& maze) {
        u_long cnt = 0;
        for (size_t row = 0; row < maze.size(); ++row)
                for (size_t col = 0; col < maze[row].size(); ++col)
                        if (maze[row][col] == 'O')
                                cnt += maze.size() - row;
        return cnt;
}

int main() {
        std::string line;
        std::vector<std::string> maze;

        while (std::getline(std::cin, line)) {
                if (line.size() == 0)
                        break;

                maze.push_back(line);
        }

        while (rollit(maze) != 0)
                /* EMPTY */;

        std::cout << countit(maze) << std::endl;
}
