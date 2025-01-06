
#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <regex>
#include <stdexcept>

#if 1
const size_t OFFSET = 10000000000000;
#else
const size_t OFFSET = 0;
#endif

size_t runIt(long ax, long ay, long bx, long by, long px, long py) {
	px += OFFSET;
	py += OFFSET;

	long divisor = (by * ax) - (bx * ay);
	if (divisor == 0) {
		// no simultaneous solutions
		// check to see if either equation is a solution
		std::cout << "DIVISOR" << std::endl;
		return -1;
	} else {
		// There's only one solution, let's find it.
		long a = ((by * px) - (bx * py)) / divisor;
		std::cout << a << std::endl;
		long b = (py - ay * a) / by;
		std::cout << "a,b: " << a << "," << b << "/" << divisor << std::endl;

		long x = a * ax + b * bx;
		long y = a * ay + b * by;
		std::cout << x << "=?" << px << std::endl << y << "=?" << py << std::endl;

		if (x == px && y == py)
			return (3 * a) + b;
		return 0;
	}
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
