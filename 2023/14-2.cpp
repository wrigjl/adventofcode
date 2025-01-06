
#include <iostream>
#include <limits>
#include <vector>
#include <string>
#include <unordered_map>

#define BITSET_SIZE (100 * 100)

char getMaze(const std::vector<std::string>&maze, size_t row, size_t col) {
        if (row >= maze.size() || col >= maze[row].size())
                return '#';
        return maze[row][col];
}

void rollit_n(std::vector<std::string>& maze) {
        for (size_t row = 0; row < maze.size(); ++row) {
                for (size_t col = 0; col < maze[row].size(); ++col) {
                        size_t r = row, c = col;
                        while (maze[r][c] == 'O' && maze[r - 1][c] == '.') {
                                maze[r][c] = '.';
                                maze[r - 1][c] = 'O';
                                --r;
                        }
                }
        }
}

void rollit_e(std::vector<std::string>& maze) {
        for (size_t col = maze[0].size() - 1; col != std::numeric_limits<size_t>::max(); --col) {
                for (size_t row = 0; row < maze.size(); ++row) {
                        size_t r = row, c = col;
                        while (maze[r][c] == 'O' && maze[r][c + 1] == '.') {
                                maze[r][c] = '.';
                                maze[r][c + 1] = 'O';
                                ++c;
                        }
                }
        }
}

void rollit_s(std::vector<std::string>& maze) {
        for (size_t row = maze.size() - 1; row != std::numeric_limits<size_t>::max(); --row) {
                for (size_t col = 0; col < maze[row].size(); ++col) {
                        size_t r = row, c = col;
                        while (maze[r][c] == 'O' && maze[r + 1][c] == '.') {
                                maze[r][c] = '.';
                                maze[r + 1][c] = 'O';
                                ++r;
                        }
                }
        }
}

void rollit_w(std::vector<std::string>& maze) {
        for (size_t col = 0; col < maze[0].size(); ++col) {
                for (size_t row = 0; row < maze.size(); ++row) {
                        size_t r = row, c = col;
                        while (maze[r][c] == 'O' && maze[r][c - 1] == '.') {
                                maze[r][c] = '.';
                                maze[r][c - 1] = 'O';
                                --c;
                        }
                }
        }
}

u_long countit(std::vector<std::string>& maze) {
        u_long cnt = 0;
        for (size_t row = 0; row < maze.size(); ++row)
                for (size_t col = 0; col < maze[row].size(); ++col)
                        if (maze[row][col] == 'O')
                                cnt += maze.size() - row;
        return cnt;
}

void setit(const std::vector<std::string>& maze, std::bitset<BITSET_SIZE>& bits) {
        bits.reset();
        for (size_t row = 0; row < maze.size(); ++row)
                for (size_t col = 0; col < maze[row].size(); ++col)
                        if (maze[row][col] == 'O')
                                bits.set(row * maze.size() + col);
}
        
void spincycle(std::vector<std::string>& maze) {
        rollit_n(maze);
        rollit_w(maze);
        rollit_s(maze);
        rollit_e(maze);
}

void printmaze(const std::vector<std::string>& maze) {
        for (auto const& s: maze)
                std::cout << s << std::endl;
}

int main() {
        std::string line;
        std::vector<std::string> maze;
        std::bitset<BITSET_SIZE> bits;
        std::unordered_map<std::bitset<BITSET_SIZE>, std::vector<int>> seen;

        while (std::getline(std::cin, line)) {
                if (line.size() == 0)
                        break;

                maze.push_back(line);
        }

        // Why 150? Well, once the initial values settle,
        // the period is 59. 
        for (int i = 1; i <= 1000; i++) {
                spincycle(maze);
                setit(maze, bits);
                if (seen.count(bits) == 0)
                        seen.insert({bits, {}});
                seen[bits].push_back(i);
        }

        int VAL = 0;
        for (auto const& x: seen) {
                for (auto y: x.second)
                        std::cout << y << " ";
                std::cout << std::endl << std::endl;
                if (x.second.size() == 1)
                        VAL = std::max(VAL, x.second[0]);
        }
        std::cout << "biggest unique: " << VAL << std::endl;
        std::cout << countit(maze) << std::endl;
}
