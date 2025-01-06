
#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <regex>
#include <stdexcept>


size_t runIt(size_t ax, size_t ay, size_t bx, size_t by, size_t px, size_t py) {
	std::vector<std::pair<size_t, size_t>> matches;

        for (size_t a = 0; a < 100; a++)
		for (size_t b = 0; b < 100; b++) {
			size_t x = (a * ax) + (b * bx);
			size_t y = (a * ay) + (b * by);
			if (x == px && y == py) {
				matches.push_back({a, b});
			}
		}

	if (matches.size() == 0)
		return 0;

	std::pair<size_t, size_t> cur = matches.front();
	for (const auto& p: matches) {
		size_t curcost = (3 * cur.first) + cur.second;
		size_t pcost = (3 * p.first) * p.second;
		if (pcost < curcost)
			cur = p;
	}
	
	return (3 * cur.first) + cur.second;
}

int main() {
	std::string line;
	size_t ax, bx, ay, by, px, py;
	const std::regex button_re("Button (.): X\\+(\\d+), Y\\+(\\d+)");
	const std::regex prize_re("Prize: X=(\\d+), Y=(\\d+)");
	size_t sum;

        while (std::getline(std::cin, line)) {
		std::smatch match;
		if (!std::regex_match(line, match, button_re) || match.size() != 4)
			throw std::runtime_error(line);
		ax = std::stoul(match[2].str());
		ay = std::stoul(match[3].str());

		std::getline(std::cin, line);
		if (!std::regex_match(line, match, button_re) || match.size() != 4)
			throw std::runtime_error(line);
		bx = std::stoul(match[2].str());
		by = std::stoul(match[3].str());

                std::getline(std::cin, line);
		if (!std::regex_match(line, match, prize_re) || match.size() != 3)
			throw std::runtime_error(line);
		px = std::stoul(match[1].str());
		py = std::stoul(match[2].str());

		size_t val = runIt(ax, ay, bx, by, px, py);
		sum += val;
		std::cout << "VAL " << val << std::endl;
		std::getline(std::cin, line);
	}

	std::cout << "sum: " << sum << std::endl;
}
