
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <stdexcept>
#include <sstream>
#include <unordered_set>

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

std::unordered_set<int> setDifference(const std::unordered_set<int> &big,
                                      const std::unordered_set<int> &ss) {
	std::unordered_set<int> res = big;
	for (const auto i: ss) {
		res.erase(i);
	}
	return res;
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

void sortIt(std::vector<int> &pages) {
	std::unordered_set<int> remainingItems;

	// set of all items for which we need to find a position
	for (const auto i: pages)
		remainingItems.insert(i);

	pages.clear();
	while (!remainingItems.empty()) {
		// now loop over the rules. we're looking for rules that say
		// X must be before Y where X and Y are in allItems

		std::unordered_set<int> rhs;
		for (const auto rule: rules) {
			if (remainingItems.count(rule.first) == 0)
				continue;
			if (remainingItems.count(rule.second) == 0)
				continue;
			rhs.insert(rule.second);
		}
		auto found = setDifference(remainingItems, rhs);

		std::cout << "found " << found.size() << " of " << pages.size() << std::endl;
		for (const auto i: found) {
			remainingItems.erase(i);
			pages.push_back(i);
		}
	}
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
			continue;
		sortIt(pages);
		sum += pages[pages.size() / 2];
	}
	std::cout << "Sum of mids: " << sum << std::endl;
	return 0;
}
