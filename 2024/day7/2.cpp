#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <stdexcept>
#include <sstream>

bool evalVec(const std::vector<unsigned long> &vec, unsigned long target,
             size_t index, unsigned long sofar) {
	if (index == 0) {
		sofar = vec[index];
		if (evalVec(vec, target, index + 1, sofar))
		    return true;
		return false;
	}
	if (index == vec.size()) {
		return sofar == target;
	}
	if (evalVec(vec, target, index + 1, sofar + vec[index]))
		return true;
	if (evalVec(vec, target, index + 1, sofar * vec[index]))
		return true;

	std::stringstream ss;
	ss << sofar << vec[index];
	return evalVec(vec, target, index + 1, std::stoul(ss.str()));
}

int
main() {
	std::string line;
	std::vector<unsigned long> vec;
	unsigned long result = 0;

        while (std::getline(std::cin, line)) {
		if (line.size() == 0)
			break;

		vec.clear();

                size_t pos = line.find(':');
		if (pos == std::string::npos)
			throw std::runtime_error("missing delim");
		
		auto target = std::stoul(line.substr(0, pos));
		std::stringstream ss(line.substr(pos+1, std::string::npos));
		unsigned long v;
		while (ss >> v)
			vec.push_back(v);

		if (evalVec(vec, target, 0, 0))
			result += target;
	}
	std::cout << "result: " << result << std::endl;
}
