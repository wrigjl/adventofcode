
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <stdexcept>
#include <sstream>

std::vector<std::pair<int, int> > rules;

bool checkEntry(const std::vector<int> &pages, size_t cur, size_t tst) {
	if (cur == tst)
		return true;
	for (const auto rule: rules) {
		if (cur > tst && rule.first == pages[cur] && rule.second == pages[tst])
			return false;
		else if (cur < tst && rule.first == pages[tst] && rule.second == pages[cur])
			return false;
	}
	return true;
}

bool checkIt(const std::vector<int> &pages) {
	for (size_t i = 0; i < pages.size(); i++) {
		for (size_t j = 0; j < pages.size(); j++) {
			if (!checkEntry(pages, i, j))
				return false;
		}
	}
	return true;
}

int
main() {
	std::string line;
	int sum = 0;

        while (std::getline(std::cin, line)) {
		if (line.size() == 0)
			break;
		size_t pos = line.find('|');
		if (pos == std::string::npos)
			throw std::runtime_error("missing delim |");
		auto lhs = std::stoi(line.substr(0, pos));
		auto rhs = std::stoi(line.substr(pos + 1, std::string::npos));
		rules.push_back({lhs,rhs});
		std::cout << lhs << ".." << rhs << std::endl;
	}

	while (std::getline(std::cin, line)) {
		std::vector<int> pages;
		std::stringstream ss(line);
		std::string str;
		while (std::getline(ss, str, ',')) {
			pages.push_back(std::stoi(str));
		}
		std::cout << "read(" << pages[0] << ".." << pages[pages.size()-1] << std::endl;
		if (checkIt(pages))
			sum += pages[pages.size() / 2];
	}
	std::cout << "Sum of mids: " << sum << std::endl;
	return 0;
}
