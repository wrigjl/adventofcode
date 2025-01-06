#include <cctype>
#include <iostream>
#include <string>
#include <unordered_set>
#include <utility>

template<>
struct std::hash<std::pair<size_t, size_t>>
{
    std::size_t operator()(const std::pair<size_t, size_t>& s) const noexcept {
	    return (s.first << 16) | (s.second);
    }
};

void plotAnti(std::unordered_set<std::pair<size_t, size_t>>& antinodes,
	      const std::vector<std::pair<size_t, size_t>>& ants,
	      const std::pair<size_t, size_t> maxes) {
	
	for (const auto &p1: ants) {
		for (const auto &p2: ants) {
			// same location, skip
			if (p1.first == p2.first && p1.second == p2.second)
				continue;

                        size_t row = p1.first + (p1.first - p2.first);
			size_t col = p1.second + (p1.second - p2.second);
			if (row >= maxes.first || col >= maxes.second) {
				// off the map
			} else
				antinodes.insert({row, col});
		}
	}
}

int
main() {
	std::vector<std::string> theMap;
	std::unordered_map<char, std::vector<std::pair<size_t, size_t>>> antennas;
	std::unordered_set<std::pair<size_t, size_t>> antinodes;
        std::string line;
	size_t row = 0, col;

        while (getline(std::cin, line)) {
		if (line.size() == 0)
			break;
		col = 0;
		for (auto const c: line) {
			if (std::isalnum(c)) {
				if (antennas.count(c) == 0) {
					std::vector<std::pair<size_t,size_t>> v;
					antennas.insert({c, v});
				}
				antennas[c].push_back({row, col});
			}
			col++;
		}
		row++;
	}

	std::cout << "unique freqs: " << antennas.size() << std::endl;

	std::pair<size_t, size_t> bounds = {row,col};

        for (const auto &a: antennas) {
		plotAnti(antinodes, a.second, bounds);
	}

	std::cout << antinodes.size() << std::endl;
}
