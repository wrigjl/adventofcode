
#include <iostream>
#include <regex>
#include <string>
#include <stdexcept>
#include <vector>
#include <unordered_set>

const int NCOLS = 101;
const int NROWS = 103;

class Position {
public:
	int row, col;
	bool operator==(const Position&) const = default;
};

template<>
struct std::hash<Position>
{
	std::size_t operator()(const Position& p) const noexcept {
		return (p.row << 16) | p.col;
	}
};

bool testRobots(const std::vector<Position>& robots) {
	std::unordered_set<Position> pos;

	for (const auto &robot: robots) {
		if (pos.count(robot) == 0)
			pos.insert(robot);
		else
			return false;
	}
	return true;
}

int main() {
	std::string line;
	std::vector<Position> robots, velocities;

        const std::regex parseRe("p=(\\d+),(\\d+) v=(-?\\d+),(-?\\d+)");
	while (std::getline(std::cin, line)) {
		std::smatch m;
		if (!std::regex_match(line, m, parseRe) || m.size() != 5)
			throw std::runtime_error(line);
		Position p = { std::stoi(m[2].str()), std::stoi(m[1].str()) };
		Position v = { std::stoi(m[4].str()), std::stoi(m[3].str()) };
		robots.push_back(p);
		velocities.push_back(v);
	}

	for (int i = 0; true; i++) {
		for (size_t r = 0; r < robots.size(); r++) {
			robots[r].row = robots[r].row + velocities[r].row;
			while (robots[r].row >= NROWS)
				robots[r].row -= NROWS;
			if (robots[r].row < 0)
				robots[r].row = NROWS + robots[r].row;

                        robots[r].col = robots[r].col + velocities[r].col;
			while (robots[r].col >= NCOLS)
				robots[r].col -= NCOLS;
			if (robots[r].col < 0)
				robots[r].col = NCOLS + robots[r].col;
		}

		if (testRobots(robots))
			std::cout << (i + 1) << std::endl;
	}

	u_long q1 = 0, q2 = 0, q3 = 0, q4 = 0;
	for (const auto robot: robots) {
		if (robot.row == NROWS / 2 || robot.col == NCOLS / 2)
			continue;

                if (robot.row < NROWS / 2) {
			if (robot.col < NCOLS / 2)
				q1++;
			else
				q2++;
		} else {
			if (robot.col < NCOLS / 2)
				q3++;
			else
				q4++;
		}
	}

	std::cout << (q1 * q2 * q3 * q4) << std::endl;
}
