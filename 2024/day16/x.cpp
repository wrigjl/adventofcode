
#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>
#include <unistd.h>
#include <unordered_set>

enum Direction {
	InvalidDirection = -1,
	East = 0,
	North,
	South,
	West,
};

template<> struct std::hash<std::pair<size_t,size_t>>
{
	std::size_t operator()(const std::pair<size_t,size_t>& s)
		const noexcept {
		return (s.first << 16) | s.second;
	}
};

std::vector<std::string> maze;
std::vector<std::vector<size_t>> costpos;
std::vector<std::vector<Direction>> minCostDir;

char getMaze(const std::vector<std::string>& maze, size_t row, size_t col) {
	if (row > maze.size() || col > maze[row].size())
		return '#';
	return maze[row][col];
}

bool isSafe(size_t row, size_t col) {
	return getMaze(maze, row, col) == '.';
}

void findShortestPath(size_t row, size_t col,
		      size_t dstrow, size_t dstcol,
		      size_t &min_dist, size_t dist, Direction dir,
		      std::unordered_set<std::pair<size_t, size_t>>& retries) {
	if (dir == InvalidDirection) {
		std::cout << row << "," << col << std::endl;
		throw std::runtime_error("bad direction");
	}
	if (dist > costpos[row][col]) {
		// this path is worse, skip it
		return;
	}

	if (costpos[row][col] > dist) {
		costpos[row][col] = dist;
		minCostDir[row][col] = dir;
		retries.insert({row, col});
		std::cout << row << "," << col << std::endl;
		return;
	}

        if (row == dstrow && col == dstcol) {
		min_dist = std::min(dist, min_dist);
		std::cout << min_dist << std::endl;
		return;
	}

	size_t cost = 0;
	if (isSafe(row - 1, col)) {
		if (dir == North)
			cost = 1;
		else if (dir == South)
			cost = 2001;
		else
			cost = 1001;

		findShortestPath(row - 1, col, dstrow, dstcol,
				 min_dist, dist + cost, North, retries);
	}
	if (isSafe(row, col + 1)) {
		if (dir == East)
			cost = 1;
		else if (dir == West)
			cost = 2001;
		else
			cost = 1001;

                findShortestPath(row, col + 1, dstrow, dstcol,
				 min_dist, dist + cost, East, retries);
	}
        if (isSafe(row + 1, col)) {
		if (dir == South)
			cost = 1;
		else if (dir == North)
			cost = 2001;
		else
			cost = 1001;
		findShortestPath(row + 1, col, dstrow, dstcol,
				 min_dist, dist + cost, South, retries);
	}
	if (isSafe(row, col - 1)) {
		if (dir == West)
			cost = 1;
		else if (dir == East)
			cost = 2001;
		else
			cost = 1001;
		findShortestPath(row, col - 1, dstrow, dstcol,
				 min_dist, dist + cost, West, retries);
	}
}

size_t findShortestPathLength(size_t startrow, size_t startcol,
			      size_t dstrow, size_t dstcol) {
	if (getMaze(maze, startrow, startcol) == '#' ||
	    getMaze(maze, dstrow, dstcol) == '#')
		return std::string::npos - 4;
	
	std::vector<std::vector<bool>> visited;
	visited.resize(maze.size(), std::vector<bool>(maze[0].size()));
	size_t dist = std::string::npos;

	std::unordered_set<std::pair<size_t,size_t>> retries;
	retries.insert({startrow, startcol});
	minCostDir[startrow][startcol] = East;
	while (!retries.empty()) {
		auto pos = *retries.begin();
		retries.erase(pos);
		findShortestPath(pos.first, pos.second, dstrow, dstcol,
				 dist, costpos[pos.first][pos.second],
				 minCostDir[pos.first][pos.second],
				 retries);
	}

	return dist;
}

int main() {
	std::string line;

	while (std::getline(std::cin, line)) {
		if (line.size() == 0)
			break;
		maze.push_back(line);
		costpos.push_back(std::vector<size_t>(line.size(),
						      std::numeric_limits<size_t>::max()));
		minCostDir.push_back(std::vector<Direction>(line.size(),
							    InvalidDirection));
	}

	size_t srcrow = std::string::npos,
		srccol = std::string::npos,
		dstrow = std::string::npos,
		dstcol = std::string::npos;

        for (size_t row = 0; row < maze.size(); row++) {
		size_t pos = maze[row].find('S');
		if (pos != std::string::npos) {
			srcrow = row;
			srccol = pos;
			maze[row][pos] = '.';
		}
		pos = maze[row].find('E');
		if (pos != std::string::npos) {
			dstrow = row;
			dstcol = pos;
			maze[row][pos] = '.';
		}
	}

	costpos[srcrow][srccol] = 0;
	size_t x = findShortestPathLength(srcrow, srccol, dstrow, dstcol);
	
	std::cout << x << "---" << costpos[dstrow][dstcol] << std::endl;
}
