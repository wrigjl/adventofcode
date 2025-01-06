
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <deque>

const size_t GRID_SIZE = 71;
const size_t NBYTES = 1024;

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

std::vector<std::string> maze;
std::vector<std::string> xmaze;

char getMaze(const Position &pos) {
	if (pos.row > maze.size() || pos.col > maze[pos.row].size())
		return '#';
	return maze[pos.row][pos.col];
}

bool isSafe(const Position& pos) {
	return getMaze(pos) == '.';
}

void visit(const Position& pos, size_t dist, std::deque<Position>& todo, 
	   std::unordered_map<Position, size_t>& seen) {
}
int main() {
	for (size_t i = 0; i < GRID_SIZE; i++) {
		std::string s(GRID_SIZE, '.');
		maze.push_back(s);
	}

	for (size_t i = 0; i < NBYTES; i++) {
		std::string line;
		std::getline(std::cin, line);
		auto pos = line.find(',');
		size_t col = std::stoul(line.substr(0, pos));
		size_t row = std::stoul(line.substr(pos + 1,
						    std::string::npos));
		maze[row][col] = '#';
	}

	std::deque<Position> todos = { Position(0, 0) };
	std::deque<size_t> dists = { 0 };
	std::unordered_set<Position> seen = { Position(0, 0) };
	
	while (!todos.empty()) {
		Position pos = todos.front();
		todos.pop_front();

		size_t dist = dists.front();
		dists.pop_front();

                Position npos;

		std::cout << "(" << pos.row << "," << pos.col << ")"
			  << "->" << dist << std::endl;

                npos.row = pos.row + 1; npos.col = pos.col + 0;
		if (seen.count(npos) == 0 && isSafe(npos)) {
			todos.push_back(npos);
			dists.push_back(dist + 1);
			seen.insert(npos);
		}

                npos.row = pos.row - 1; npos.col = pos.col + 0;
		if (seen.count(npos) == 0 && isSafe(npos)) {
			todos.push_back(npos);
			dists.push_back(dist + 1);
			seen.insert(npos);
		}

                npos.row = pos.row + 0; npos.col = pos.col + 1;
		if (seen.count(npos) == 0 && isSafe(npos)) {
			todos.push_back(npos);
			dists.push_back(dist + 1);
			seen.insert(npos);
		}

                npos.row = pos.row + 0; npos.col = pos.col - 1;
		if (seen.count(npos) == 0 && isSafe(npos)) {
			todos.push_back(npos);
			dists.push_back(dist + 1);
			seen.insert(npos);
		}
	}
}
