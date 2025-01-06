
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <stdexcept>
#include <unordered_set>

const int DIR_UP = 0;
const int DIR_RIGHT = 1;
const int DIR_DOWN = 2;
const int DIR_LEFT = 3;
const int DIR_END = 4;
int direction = DIR_UP;

std::vector<std::string> theMaze;
std::vector<std::string> origMaze;

const char MAZE_START = '^';
const char MAZE_OBSTACLE = '#';
const char MAZE_SPACE = '.';
const char MAZE_VISITED = 'X';
const char MAZE_OFFRAILS = 'Z';

class PosDir {
public:
	size_t row, col;
	int dir;
	bool operator==(const PosDir&) const = default;
};

template<>
struct std::hash<PosDir>
{
    std::size_t operator()(const PosDir& s) const noexcept
    {
	    return (s.row << 18) + (s.col << 2) + s.dir;
    }
};

std::unordered_set<PosDir> visitedPosDir;

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
	int result = 0;
	PosDir pd;

        while (std::getline(std::cin, line)) {
		if (line.size() == 0)
			continue;
		theMaze.push_back(line);
	}

        origMaze = theMaze;

	size_t obstactleRow, obstactleCol;
	for (obstactleRow = 0; obstactleRow < theMaze.size(); obstactleRow++) {
		for (obstactleCol = 0; obstactleCol < theMaze[obstactleRow].size(); obstactleCol++) {
			bool loopDetected = false;

                        if (origMaze[obstactleRow][obstactleCol] == MAZE_OBSTACLE)
				continue;
                        if (origMaze[obstactleRow][obstactleCol] == MAZE_START)
				continue;

			theMaze = origMaze;
			theMaze[obstactleRow][obstactleCol] = MAZE_OBSTACLE;
			direction = DIR_UP;
			visitedPosDir.clear();

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
					pd.row = row;
					pd.col = col;
					pd.dir = direction;
					if (visitedPosDir.count(pd) == 1) {
						loopDetected = true;
						goto done;
					} else
						visitedPosDir.insert(pd);
					break;
				default:
					throw std::runtime_error("bad space");
				}
			}
		done:
			if (loopDetected)
				result++;
		}
	}

	std::cout << result << std::endl;
}
