
#include <iostream>
#include <stdexcept>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <deque>

class Position {
public:
	size_t row, col;
	bool operator==(const Position&) const = default;

        bool operator<(const Position & rhs) const {
		if (row < rhs.row)
			return true;
		if (row > rhs.row)
			return false;
		return (col < rhs.col);
	}

	size_t distance(const Position &rhs) const {
		size_t d = 0;
		d += std::max(row, rhs.row) - std::min(row, rhs.row);
		d += std::max(col, rhs.col) - std::min(col, rhs.col);
		return d;
	}
};

template<>
struct std::hash<Position>
{
	std::size_t operator()(const Position& p) const noexcept {
		return (p.row << 16) | p.col;
	}
};

std::vector<std::string> maze;

char getMaze(const Position &pos) {
	if (pos.row > maze.size() || pos.col > maze[pos.row].size())
		return '#';
	return maze[pos.row][pos.col];
}

bool isSafe(const Position& pos) {
	return getMaze(pos) == '.';
}

void visit(const Position &pos, size_t dist, std::deque<Position> &todo,
           std::unordered_map<Position, size_t> &seen) {}

size_t solveIt(Position src, Position dst) {
	std::deque<Position> todos = { Position(src) };
	std::deque<size_t> dists = { 0 };
	std::unordered_set<Position> seen = { src };
	
	while (!todos.empty()) {
		Position pos = todos.front();
		todos.pop_front();

		size_t dist = dists.front();
		dists.pop_front();

                Position npos;

		if (pos == dst)
			return dist;

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

	throw std::runtime_error("Fuck, no solve.");
}

int main() {
	std::string line;
	while (std::getline(std::cin, line)) {
		if (line.size() == 0)
			break;
		maze.push_back(line);
	}

	Position src(std::string::npos, std::string::npos);
	Position dst(std::string::npos, std::string::npos);
	std::vector<Position> walls;
	for (size_t row = 0; row < maze.size(); row++) {
		for (size_t col = 0; col < maze[row].size(); col++) {

			if (row > 0 && row < maze.size() - 1 &&
			    col > 0 && col < maze[row].size() - 1 &&
			    maze[row][col] == '#')
				walls.push_back({row, col});
			
			if (maze[row][col] == 'S') {
				src.row = row;
				src.col = col;
			}
			if (maze[row][col] == 'E') {
				dst.row = row;
				dst.col = col;
			}
		}
	}

        maze[src.row][src.col] = '.';
	maze[dst.row][dst.col] = '.';
	size_t baseTime = solveIt(src, dst);
	std::cout << "base: " << baseTime << std::endl;

	std::map<size_t,size_t> counts;

        for (auto const &pos1: walls) {
		maze[pos1.row][pos1.col] = '.';

                size_t base1 = solveIt(src, dst);

		if (base1 > baseTime)
			std::runtime_error("How the fuck?");

		size_t k1 = baseTime - base1;
		if (counts.count(k1) == 0)
			counts.insert({k1, 1});
		else
			counts[k1]++;

                maze[pos1.row][pos1.col] = '#';
	}

	size_t sum = 0;
        for (auto const &k: counts) {
		if (k.first == 0)
			continue;
		std::cout << "There are " << k.second
			  << " that save " << k.first << std::endl;
		if (k.first >= 100)
			sum += k.second;
	}
	std::cout << sum << std::endl;
}
