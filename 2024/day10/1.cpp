#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

template<>
struct std::hash<std::pair<size_t, size_t>>
{
    std::size_t operator()(const std::pair<size_t, size_t>& s) const noexcept {
	    return (s.first << 16) + s.second;
    }
};

char getMaze(const std::vector<std::string> &maze, const std::pair<size_t, size_t>& pos) {
	if (pos.first > maze.size())
		return '.';
	if (pos.second > maze[pos.first].size())
		return '.';
	return maze[pos.first][pos.second];
}

void followTrail(char c, const std::pair<size_t, size_t> &th,
		 const std::vector<std::string> &maze,
		 std::unordered_set<std::pair<size_t, size_t>> &maxes, size_t& rating ) {
//	std::cout << c << " (" << th.first << "," << th.second << ")" << std::endl;
	if (c != getMaze(maze, th))
		return;
	
	if (c == '9') {
		maxes.insert(th);
		rating++;
		return;
	}
	followTrail(c + 1, {th.first + 1, th.second + 0}, maze, maxes, rating);
	followTrail(c + 1, {th.first - 1, th.second + 0}, maze, maxes, rating);
	followTrail(c + 1, {th.first + 0, th.second + 1}, maze, maxes, rating);
	followTrail(c + 1, {th.first + 0, th.second - 1}, maze, maxes, rating);
}


int main() {
	std::string line;
	std::vector<std::string> pathways;
	std::vector<std::pair<size_t, size_t>> trailheads;
	size_t score = 0, rating = 0;

        while (std::getline(std::cin, line)) {
		if (line.size() == 0)
			break;
		pathways.push_back(line);
	}

	for (size_t row = 0; row < pathways.size(); row++) {
		for (size_t col = 0; col < pathways[row].size(); col++) {
			if (pathways[row][col] != '0')
				continue;
			trailheads.push_back({row, col});
		}
	}

	while (!trailheads.empty()) {
		auto th = trailheads.back();
		trailheads.pop_back();

                std::unordered_set<std::pair<size_t, size_t>> maxes;

		followTrail('0', th, pathways, maxes, rating);
		score += maxes.size();
	}

	std::cout << "score: " << score << std::endl;
	std::cout << "rating: " << rating << std::endl;
}
