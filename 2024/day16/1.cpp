
#include <iostream>
#include <stdexcept>
#include <vector>
#include <deque>
#include <unordered_set>

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

enum Direction {
	East = 0,
	North,
	South,
	West,
	InvalidDirection = -1,
};

struct PosDir {
	Position pos;
	Direction dir;

        bool operator==(const PosDir&) const = default;
};

template<>
struct std::hash<PosDir>
{
	std::size_t operator()(const PosDir& p) const noexcept {
		size_t h = std::hash<Position>{}(p.pos);
		return (h << 2) | (int)p.dir;
	}
};


struct WorkItem {
	Position pos;
	size_t dist;
	Direction dir;
};

std::vector<std::string> maze;

void printMaze(const std::vector<std::string>& maze, size_t row, size_t col) {
	for (size_t r = 0; r < maze.size(); r++) {
		if (r != row)
			std::cout << maze[r] << std::endl;
		else {
			auto x = maze[r];
			x[col] = 'O';
			std::cout << x << std::endl;
		}
	}
}

char getMaze(const Position& pos) {
	if (pos.row > maze.size() || pos.col > maze[pos.row].size())
		return '#';
	return maze[pos.row][pos.col];
}

bool isSafe(const Position& pos) {
	return getMaze(pos) == '.';
}

size_t newCost(Direction d1, Direction d2, size_t dist) {
	if (d1 == d2)
		return dist + 1;
	if (d1 == East || d1 == West) {
		if (d2 == North || d2 == South)
			return dist + 1001;
		throw std::runtime_error("180 degree");
		return dist + 2001;
	}
	// d1 == north or south
	if (d2 == East || d2 == West)
		return dist + 1001;
	throw std::runtime_error("180 degree");
	return dist + 2001;
}

// Keep the items sorted based on distance
void insertWorkItem2(std::deque<WorkItem> &work, const WorkItem &item) {
	for (auto iter = work.begin(); iter != work.end(); ++iter)
		if (item.dist < iter->dist) {
			work.insert(iter, item);
			return;
		}
	work.push_back(item);
}

void insertWorkItem(std::deque<WorkItem> &work, const WorkItem &item) {
	insertWorkItem2(work, item);
	auto iterl = work.begin();
	if (iterl == work.end())
		return;
	auto iterr = ++iterl;
	while (iterr != work.end()) {
		if (iterl->dist > iterr->dist)
			throw std::runtime_error("bad heap");
	}
}

Direction leftDir(Direction d) {
	if (d == East)
		return North;
	if (d == West)
		return South;
	if (d == North)
		return West;
	return East;
}

Direction rightDir(Direction d) {
	if (d == East)
		return South;
	if (d == West)
		return North;
	if (d == North)
		return East;
	return West;
}

void move(Position &pos, const Direction d) {
	if (d == East)
		pos.col++;
	if (d == West)
		pos.col--;
	if (d == North)
		pos.row--;
	if (d == South)
		pos.row++;
}

size_t solveIt(Position src, Position dst) {
	std::deque<WorkItem> todos = { {Position(src), 0, East} };
	std::unordered_set<PosDir> seen = { {src, East} };
	
	while (!todos.empty()) {
		WorkItem item = todos.front();
		todos.pop_front();

                Position npos;

		if (item.pos == dst)
			return item.dist;

		seen.insert({item.pos, item.dir});

		WorkItem xitem = {item.pos, item.dist + 1, item.dir};
		move(xitem.pos, xitem.dir);
		if (isSafe(xitem.pos) && seen.count({xitem.pos, xitem.dir}) == 0)
			insertWorkItem(todos, xitem);

		WorkItem litem = {item.pos, item.dist + 1001, leftDir(item.dir)};
		move(litem.pos, litem.dir);
		if (isSafe(litem.pos) && seen.count({litem.pos, litem.dir}) == 0)
			insertWorkItem(todos, litem);

		WorkItem ritem = {item.pos, item.dist + 1001, rightDir(item.dir)};
		move(ritem.pos, ritem.dir);
		if (isSafe(ritem.pos) && seen.count({ritem.pos, ritem.dir}) == 0)
			insertWorkItem(todos, ritem);
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

	printMaze(maze, dstrow, dstcol);

	std::cout << solveIt({srcrow, srccol}, {dstrow, dstcol}) << std::endl;
}