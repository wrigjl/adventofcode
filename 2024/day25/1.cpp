
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

std::vector<std::vector<int>> locks;
std::vector<std::vector<int>> keys;

bool testKeyLock(const std::vector<int>& key,
		 const std::vector<int>& lock) {
	if (key.size() != lock.size())
		throw std::runtime_error("mismatch size");
	for (size_t i = 0; i < key.size(); i++)
		if (key[i] + lock[i] > 5)
			return false;
	return true;
}

void printIt(const std::vector<int>& vec) {
	std::string sep = "";

	for (auto v: vec) {
		std::cout << sep << v;
		sep = ",";
	}
	std::cout << std::endl;
}

void parseThing(const std::vector<std::string> &thing) {
	std::vector<int> hashes;

        for (size_t col = 0; col < thing[0].size(); col++) {
		int cnt = 0;
		for (size_t row = 0; row < thing.size(); row++)
			if (thing[row][col] == '#')
				cnt++;
		hashes.push_back(cnt - 1);
	}

	if (thing[0][0] == '#') {
		locks.push_back(hashes);
		std::cout << "lock: ";
		printIt(locks.back());
	} else {
		keys.push_back(hashes);
		std::cout << "key:  ";
		printIt(keys.back());
	}
}

int main() {
	std::string line;
	std::vector<std::string> thing;

        while (std::getline(std::cin, line)) {
		if (line.size() == 0) {
			parseThing(thing);
			thing.clear();
			continue;
		}
		thing.push_back(line);
	}
	if (thing.size() > 0) {
		parseThing(thing);
		thing.clear();
	}

        size_t fits = 0;
	for (const auto &lock: locks) {
		bool overlap = false;
		for (const auto &key: keys) {
			if (testKeyLock(key, lock))
				fits++;
		}
	}

        std::cout << fits << std::endl;
}
