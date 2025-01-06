#include <iostream>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <stdint.h>

std::unordered_map<u_long, u_long> memo;

std::vector<u_long> blinkStone(u_long stone) {
	if (stone == 0)
		return {1};


	std::stringstream ss;
	ss << stone;
	size_t len = ss.str().size();

	if ((len % 2) == 1)
		return {stone * 2024};

        std::vector<u_long> ret;
        
	ret.push_back(std::stoul(ss.str().substr(0, len / 2)));
	auto rhs = ss.str().substr(len / 2, len / 2);
	while (rhs.size() > 1) {
		if (rhs[0] != '0')
			break;
		rhs = rhs.substr(1, std::string::npos);
	}
	ret.push_back(std::stoul(rhs));
	return ret;
}

std::unordered_map<u_long, u_long> blinkArrangement(std::unordered_map<u_long, u_long> a) {
	std::unordered_map<u_long, u_long> result;

	for (auto const &stone: a) {
		auto newStones = blinkStone(stone.first);
		for (auto const v: newStones) {
			if (result.count(v) == 0)
				result.insert({v, 0});
			result[v] += stone.second;
		}
	}
	return result;
}

int main() {
#if 0
	std::vector<unsigned long> stonesList = { 125, 17 };
#else
	std::vector<unsigned long> stonesList = { 872027, 227, 18, 9760, 0, 4, 67716, 9245696 };
#endif
            std::unordered_map<u_long, u_long> arrangement;

	for (auto x: stonesList)
		arrangement.insert({x, 1});


	for (int i = 0; i < 75; i++) {
		arrangement = blinkArrangement(arrangement);

		u_long sum = 0;
		for (auto const& a: arrangement)
			sum += a.second;
		std::cout << i+1 << ": " << sum << std::endl;
	}
}
