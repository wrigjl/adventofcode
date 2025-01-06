#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

class Position {
public:
        size_t row, col;
        bool operator==(const Position& x) const = default;
};

template<> struct std::hash<Position> {
        std::size_t operator()(const Position &pos) const noexcept {
                return (pos.row << 16) | pos.col;
        }
};

std::unordered_map<Position, std::string> numberMap;

char getMaze(const std::vector<std::string>& maze, size_t row, size_t col) {
        if (row >= maze.size())
                return '.';
        if (col >= maze[row].size())
                return '.';
        return maze[row][col];
}

bool checkSymbol(const std::vector<std::string>& maze, size_t row, size_t col) {
        for (auto r: std::vector<int>{-1, 0, 1}) {
                for (auto c: std::vector<int>{-1, 0, 1}) {
                        if (r == c && r == 0)
                                continue;
                        char ch = getMaze(maze, row + r, col + c);
                        if (!isdigit(ch) && ch != '.')
                                return true;
                }
        }
        return false;
}

size_t checkStar(const std::vector<std::string>&maze, size_t row, size_t col) {
        std::vector<std::string> vs;

        std::cout << "Checking " << row << "," << col << std::endl;

        for (const auto numStr: numberMap) {
                Position pos = numStr.first;
                std::string ns = numStr.second;

                // is it to this string's left?
                if (pos.row == row && pos.col - 1 == col) {
                        std::cout << ns << ": left match" << std::endl;
                        vs.push_back(ns);
                }

                // is it to this string's right?
                else if (pos.row == row && pos.col + ns.size() == col) {
                        std::cout << ns << ": right match" << std::endl;
                        vs.push_back(ns);
                }

                // is it on the row directly above or below this number?
                else if ((pos.row > 0 && row == pos.row - 1) || row == pos.row + 1) {
                        std::cout << ns << ": check row" << std::endl;
                        size_t lcol = (pos.col > 1) ? pos.col - 1 : 0;
                        if (col >= lcol && col <= pos.col + ns.size()) {
                                std::cout << ns << ": line match" << std::endl;
                                vs.push_back(ns);
                        }
                }
        }

        if (vs.size() != 2)
                return 0;
        std::cout << vs[0] << "," << vs[1] << std::endl;
        return std::stoul(vs[0]) * std::stoul(vs[1]);
}

int main() {
        std::string line;
        std::vector<std::string> maze;
        u_long sum = 0;

        while (std::getline(std::cin, line)) {
                if (line.size() == 0)
                        break;
                maze.push_back(line);
        }

        for (size_t row = 0; row < maze.size(); ++row) {
                bool inNumber = false;
                bool foundSymbol = false;
                Position pos = {std::string::npos, std::string::npos};
                std::string numStr;

                for (size_t col = 0; col < maze[row].size(); ++col) {
                        char c = getMaze(maze, row, col);
                        if (isdigit(c)) {
                                if (!inNumber) {
                                        numStr.clear();
                                        inNumber = true;
                                        foundSymbol = false;
                                        pos = {row, col};
                                }
                                numStr += getMaze(maze, row, col);

                                foundSymbol = foundSymbol || checkSymbol(maze, row, col);
                        } else {
                                if (inNumber && foundSymbol) {
                                        sum += std::stoul(numStr);
                                        numberMap.insert({pos, numStr});
                                }
                                inNumber = false;
                                foundSymbol = false;
                                numStr.clear();
                        }
                }
                if (inNumber && foundSymbol) {
                        numberMap.insert({pos, numStr});
                        sum += std::stoul(numStr);
                }
        }
        std::cout << sum << std::endl;

        size_t starSum = 0;
        for (size_t row = 0; row < maze.size(); ++row) {
                for (size_t col = 0; col < maze[row].size(); ++col) {
                        char c = getMaze(maze, row, col);
                        if (c != '*')
                                continue;
                        starSum += checkStar(maze, row, col);
                }

        }
        std::cout << "gearsum" << starSum << std::endl;
}
