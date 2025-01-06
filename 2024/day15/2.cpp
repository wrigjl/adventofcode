
#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <regex>
#include <stdexcept>
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

std::vector<std::string> theMaze;

size_t computeGPS(const std::vector<std::string>& maze) {
	size_t sum = 0;

        for (size_t row = 0; row < maze.size(); row++)
		for (size_t col = 0; col < maze[row].size(); col++)
			if (maze[row][col] == '[')
				sum += (100 * row) + col;
	return sum;
}

void printMaze() {
	for (const auto& s: theMaze)
		std::cout << s << std::endl;
}

void maybeAddBox(const Position& pos,
		 std::unordered_set<Position>& found,
		 std::vector<Position>& row,
		 std::vector<Position>& all) {
	if (found.count(pos) > 0)
		return;
	found.insert(pos);
	row.push_back(pos);
	all.push_back(pos);
}

void doMove(std::vector<std::string> &maze, Position& robot, size_t drow, size_t dcol) {
	if (maze[robot.row + drow][robot.col + dcol] == '#') {
		// wall, do nothing
		return;
	}
	if (maze[robot.row + drow][robot.col + dcol] == '.') {
		// open space, move there
		maze[robot.row][robot.col] = '.';
		robot.row += drow;
		robot.col += dcol;
		maze[robot.row][robot.col] = '@';
		return;
	}

	// we've found a box, handle left/right
	if (dcol) {
		Position firstBox = {robot.row + drow, robot.col + dcol};
		Position pos = firstBox;
		Position endPos;
		char nextChar;

                while (maze[pos.row][pos.col] == '[' ||
		       maze[pos.row][pos.col] == ']') {
			pos.row += drow;
			pos.col += dcol;
		}
		endPos = pos;
		
		if (maze[pos.row][pos.col] == '#') {
			// wall, do nothing
			return;
		}

                nextChar = maze[firstBox.row][firstBox.col];
                maze[robot.row][robot.col] = '.';
		maze[firstBox.row][firstBox.col] = '@';
		robot = firstBox;

		pos.row = firstBox.row + drow;
		pos.col = firstBox.col + dcol;
		for (;;) {
			std::cout << "move " << pos.row << "," << pos.col
				  << "end " << endPos.row << "," << endPos.col
				  << std::endl ;
				
			maze[pos.row][pos.col] = nextChar;
			nextChar = (nextChar == '[') ? ']' : '[';
			if (pos == endPos)
				break;
			pos.row += drow;
			pos.col += dcol;
		}
		return;
	}

	// move up/down

        std::vector<Position> thisRow;
	std::vector<Position> allBoxes;
	std::unordered_set<Position> foundBoxes;

	maybeAddBox({robot.row + drow, robot.col + dcol},
		    foundBoxes, thisRow, allBoxes);
	if (maze[robot.row + drow][robot.col + dcol] == '[')
		maybeAddBox({robot.row + drow, robot.col + dcol + 1},
			    foundBoxes, thisRow, allBoxes);
	else
		maybeAddBox({robot.row + drow, robot.col + dcol - 1},
			    foundBoxes, thisRow, allBoxes);

        for (;;) {
		bool alldots = true;
		std::vector<Position> nextRow;

		std::cout << "Check this row:";
		for (const auto& pos: thisRow) {
			std::cout << " (" << pos.row << "," << pos.col
				  << ")";
		}
		std::cout << std::endl;

                for (auto pos: thisRow) {
			// see if we can stop...
			if (maze[pos.row + drow][pos.col + dcol] == '#')
				return;
			
			if (maze[pos.row + drow][pos.col + dcol] == '[') {
				alldots = false;
				maybeAddBox({pos.row + drow,
						pos.col + dcol},
					foundBoxes, nextRow, allBoxes);
				maybeAddBox({pos.row + drow,
						pos.col + dcol + 1},
					foundBoxes, nextRow, allBoxes);
			}

                        if (maze[pos.row + drow][pos.col + dcol] == ']') {
				alldots = false;
				maybeAddBox({pos.row + drow,
						pos.col + dcol},
					foundBoxes, nextRow, allBoxes);
				maybeAddBox({pos.row + drow,
						pos.col + dcol - 1},
					foundBoxes, nextRow, allBoxes);
			}
		}

		thisRow.clear();
		thisRow = nextRow;
		nextRow.clear();
		if (alldots)
			break;
	}

	for (auto box = allBoxes.crbegin();
	     box != allBoxes.crend(); ++box) {
		maze[box->row + drow][box->col + dcol] = maze[box->row][box->col + dcol];
		maze[box->row][box->col] = '.';
	}
	maze[robot.row][robot.col] = '.';
	robot.row += drow;
	robot.col += dcol;
	maze[robot.row][robot.col] = '@';
}

int main() {
	std::string line;
	std::string moves;
	int drow = 0, dcol = 0;

        // read the maze
        while (std::getline(std::cin, line)) {

                if (line.size() == 0)
			break;
		std::string xline;
		xline.reserve(line.size() * 2);
		for (auto const c: line) {
			std::string app(2, c);
			if (c == '@')
				app[1] = '.';
			if (c == 'O')
				app = "[]";
			xline += app;
		}
		theMaze.push_back(xline);
	}

	while (std::getline(std::cin, line)) {
		moves += line;
	}

	Position robot = {std::string::npos, std::string::npos};
	for (size_t row = 0; row < theMaze.size(); row++) {
		for (size_t col = 0; col < theMaze[row].size(); col++) {
			if (theMaze[row][col] == '@') {
				robot.row = row;
				robot.col = col;
			}
		}
	}

	for (auto const dir: moves) {
		// set the direction
		if (dir == '^') {
			drow = -1;
			dcol = 0;
		} else if (dir == '<') {
			drow = 0;
			dcol = -1;
		} else if (dir == '>') {
			drow = 0;
			dcol = 1;
		} else if (dir == 'v') {
			drow = 1;
			dcol = 0;
		}
		std::cout << "move: " << dir << std::endl;
		doMove(theMaze, robot, drow, dcol);
//		printMaze();
	}

	printMaze();

	std::cout << computeGPS(theMaze) << std::endl;
}
