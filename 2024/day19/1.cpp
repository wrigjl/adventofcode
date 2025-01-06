
#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <sstream>

std::vector<std::string> parseFragments(const std::string &line) {
	std::string str;
	std::string frag;
	std::vector<std::string> frags;
	
	for (auto c: line)
		if (c != ' ')
			str += c;
	std::stringstream ss(str);
	while (std::getline(ss, frag, ','))
		frags.push_back(frag);
	return frags;
}

bool makeIt(const std::string& s, const std::vector<std::string>& frags) {
	if (s.empty())
		return true;

	for (const auto& frag: frags) {
		if (s.starts_with(frag)) {
			if (makeIt(s.substr(frag.size(), std::string::npos), frags))
				return true;
		}
	}

	return false;
}

int
main() {
	std::vector<std::string> fragments;
	std::string line;
	size_t possible = 0;

        std::getline(std::cin, line);
	fragments = parseFragments(line);
	std::cout << "Frags: " << fragments[0] << " ... " << fragments[fragments.size() - 1] << std::endl;
	
	std::getline(std::cin, line);
	if (line.size() != 0)
		throw std::runtime_error(line);

	while (std::getline(std::cin, line)) {
		if (makeIt(line, fragments))
			possible++;
	}

	std::cout << "Possible: " << possible << std::endl;
}
