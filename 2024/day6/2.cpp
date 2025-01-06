
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <stdexcept>

const int DIR_UP = 0;
const int DIR_RIGHT = 1;
const int DIR_DOWN = 2;
const int DIR_LEFT = 3;
const int DIR_END = 4;
int direction = DIR_UP;

std::vector<std::string> theMaze;

const char MAZE_START = '^';
const char MAZE_OBSTACLE = '#';
const char MAZE_SPACE = '.';
const char MAZE_VISITED = 'X';
const char MAZE_OFFRAILS = 'Z';

void turnRight() {
	direction = (direction + 1) % DIR_END;
}

char getMazeChar(size_t row, size_t col) {
	if (row >= theMaze.size())
		return MAZE_OFFRAILS;
	if (col >= theMaze[row].size())
		return MAZE_OFFRAILS;
	return theMaze[row][col];
}

int
main() {
	std::string line;

	while (std::getline(std::cin, line)) {
		if (line.size() == 0)
			continue;
		theMaze.push_back(line);
	}

	// find the start position
	size_t row, col = std::string::npos;
	for (row = 0; row < theMaze.size(); row++) {
		col = theMaze[row].find(MAZE_START);
		if (col != std::string::npos)
			break;
	}
	if (col == std::string::npos)
		throw std::runtime_error("start position not found");

	theMaze[row][col] = MAZE_VISITED;

        for (;;) {
		size_t nextrow = row, nextcol = col;

		switch (direction) {
		case DIR_UP: nextrow--; break;
		case DIR_DOWN: nextrow++; break;
		case DIR_LEFT: nextcol--; break;
		case DIR_RIGHT: nextcol++; break;
		default:
			throw std::runtime_error("bad direction");
		}

		char nextmarker = getMazeChar(nextrow, nextcol);
		switch (nextmarker) {
		case MAZE_OBSTACLE:
			turnRight();
			break;
		case MAZE_OFFRAILS:
			theMaze[row][col] = MAZE_VISITED;
			goto done;
		case MAZE_VISITED:
		case MAZE_SPACE:
			theMaze[row][col] = MAZE_VISITED;
			row = nextrow;
			col = nextcol;
			break;
		default:
			throw std::runtime_error("bad space");
		}
	}
done:
	int result = 0;
	for (row = 0; row < theMaze.size(); row++) {
		std::cout << theMaze[row] << std::endl;
		for (col = 0; col < theMaze[row].size(); col++)
			if (theMaze[row][col] == MAZE_VISITED)
				result++;
	}

	std::cout << result << std::endl;
}
