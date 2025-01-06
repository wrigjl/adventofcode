
#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <sstream>

std::unordered_map<std::string,size_t> memo;

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

size_t makeIt(const std::string& s, const std::vector<std::string>& frags) {
	if (s.empty())
		return 1;

	size_t sum = 0;

	if (memo.count(s) > 0)
		return memo[s];

        for (const auto& frag: frags) {
		if (s.starts_with(frag))
			sum += makeIt(s.substr(frag.size(),
					       std::string::npos), frags);
	}

	memo.insert({s, sum});
	return sum;
}

int
main() {
	std::vector<std::string> fragments;
	std::string line;
	size_t possible = 0;
	size_t sum = 0;

        std::getline(std::cin, line);
	fragments = parseFragments(line);
	std::cout << "Frags: " << fragments[0] << " ... " << fragments[fragments.size() - 1] << std::endl;
	
	std::getline(std::cin, line);
	if (line.size() != 0)
		throw std::runtime_error(line);

	while (std::getline(std::cin, line)) {
		std::cout << line << std::endl;
		size_t x = makeIt(line, fragments);
		if (x > 0)
			possible++;
		sum += x;
	}

	std::cout << "Possible: " << possible << std::endl;
	std::cout << "Sum: " << sum << std::endl;
}
