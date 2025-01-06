
#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <regex>
#include <stdexcept>

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

void printMaze() {
	for (const auto& s: theMaze)
		std::cout << s << std::endl;
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
	if (maze[robot.row + drow][robot.col + dcol] == 'O') {
		// box, see if we can move it
		Position firstBox = {robot.row + drow, robot.col + dcol};
		Position pos = firstBox;

		// keep moving as long as we have a line of boxes
		while (maze[pos.row][pos.col] == 'O') {
			pos.row += drow;
			pos.col += dcol;
		}

		// at this pojnt the end of the line (pos) is not a box
		if (maze[pos.row][pos.col] == '#') {
			// wall, do nothing
			return;
		}
		if (maze[pos.row][pos.col] == '.') {
			maze[pos.row][pos.col] = 'O';
			maze[robot.row][robot.col] = '.';
			maze[firstBox.row][firstBox.col] = '@';
			robot = firstBox;
		}
	}
}

int main() {
	std::string line;
	std::string moves;
	int drow = 0, dcol = 0;

        // read the maze
        while (std::getline(std::cin, line)) {
		if (line.size() == 0)
			break;
		theMaze.push_back(line);
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
		doMove(theMaze, robot, drow, dcol);

		printMaze();
	}
}
