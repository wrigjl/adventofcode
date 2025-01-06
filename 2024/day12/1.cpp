
#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <unordered_set>

class Position {
public:
	size_t row, col;
	bool operator==(const Position&) const = default;
};

template<>
struct std::hash<Position>
{
	std::size_t operator()(const Position& p) const noexcept {
		return (p.row << 16) | p.col;
	}
};

char getMaze(const std::vector<std::string> &maze, size_t row, size_t col) {
	if (row > maze.size())
		return '.';
	if (col > maze[row].size())
		return '.';
	return maze[row][col];
}

char getMaze(const std::vector<std::string> &maze, const Position& pos) {
	if (pos.row > maze.size())
		return '.';
	if (pos.col > maze[pos.row].size())
		return '.';
	return maze[pos.row][pos.col];
}

void setMaze(std::vector<std::string> &maze, size_t row, size_t col, char x) {
	if (row > maze.size())
		return;
	if (col > maze[row].size())
		return;
	maze[row][col] = x;
}

void setMaze(std::vector<std::string> &maze, const Position& pos, char x) {
	if (pos.row > maze.size())
		return;
	if (pos.col > maze[pos.row].size())
		return;
	maze[pos.row][pos.col] = x;
}

void buildRegion(std::vector<std::string>& maze, char c, const Position &pos, std::unordered_set<Position>& region) {
	if (getMaze(maze, pos) != c)
		return;
	region.insert(pos);
	setMaze(maze, pos, '.');
	buildRegion(maze, c, {pos.row + 1, pos.col + 0}, region);
	buildRegion(maze, c, {pos.row - 1, pos.col + 0}, region);
	buildRegion(maze, c, {pos.row + 0, pos.col + 1}, region);
	buildRegion(maze, c, {pos.row + 0, pos.col - 1}, region);
}

size_t regionArea(const std::unordered_set<Position> &region) {
	return region.size();
}

size_t regionPerimeter(const std::unordered_set<Position>& region) {
	size_t perimeter = 0;
	for (const auto block: region) {
		if (region.count({block.row + 1, block.col + 0}) == 0)
			perimeter++;
		if (region.count({block.row - 1, block.col + 0}) == 0)
			perimeter++;
		if (region.count({block.row + 0, block.col + 1}) == 0)
			perimeter++;
		if (region.count({block.row + 0, block.col - 1}) == 0)
			perimeter++;
	}
	return perimeter;
}
int main() {
	std::string line;
	std::vector<std::string> maze;
	size_t sum = 0;

        while (std::getline(std::cin, line)) {
		if (line.size() == 0)
			break;
		maze.push_back(line);
	}

	for (size_t row = 0; row < maze.size(); row++) {
		for (size_t col = 0; col < maze[row].size(); col++) {
			char c = getMaze(maze, row, col);
			if (isalpha(c)) {
				std::unordered_set<Position> region;
				buildRegion(maze, c, {row, col}, region);

				size_t area = regionArea(region);
				size_t perimeter = regionPerimeter(region);
				sum += area * perimeter;
				std::cout << c << ": area=" << area << " perimeter=" << perimeter << std::endl;
			}
		}
	}
	std::cout << "sum " << sum << std::endl;
}
