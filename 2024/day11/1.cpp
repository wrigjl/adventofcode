#include <iostream>
#include <vector>
#include <sstream>
#include <stdint.h>

std::unordered_map<u_long, u_long> memo;

u_long blinker(u_long a) {
	auto stones = new std::vector<u_long>();
	stones->push_back(a);

        for (int i = 0; i < 75; i++) {
		auto newStones = new std::vector<unsigned long>();

                for (auto stone: *stones) {
			std::stringstream ss;
			ss << stone;
			size_t len = ss.str().size();

                        if (stone == 0) {
				newStones->push_back(1);
			} else if (len % 2 == 0) {
				newStones->push_back(std::stoul(ss.str().substr(0, len / 2)));
				auto rhs = ss.str().substr(len / 2, len / 2);
				while (rhs.size() > 1) {
					if (rhs[0] != '0')
						break;
					rhs = rhs.substr(1, std::string::npos);
				}
				newStones->push_back(std::stoul(rhs));
			} else {
				newStones->push_back(stone * 2024);
			}
		}
		delete stones;
		stones = newStones;
	}
	u_long x = stones->size();
	delete stones;
	return x;
}

int main() {
#if 1
	std::vector<unsigned long> stones = { 125, 17 };
#else
	std::vector<unsigned long> stones = { 872027, 227, 18, 9760, 0, 4, 67716, 9245696 };
#endif

	u_long score = 0;
	for (auto stone: stones) {
		std::cout << "W(" << stone << ")" << std::endl;
		if (memo.count(stone) == 0)
			memo.insert({stone, blinker(stone)});
		score += memo.at(stone);
	}
	std::cout << score << std::endl;
}
