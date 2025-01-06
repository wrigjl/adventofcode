
#include <iostream>
#include <vector>
#include <sstream>
#include <limits>

struct mapping {
        u_long src;
        u_long dst;
        u_long len;
};

std::vector<u_long> getSeeds(const std::string& line) {
        std::vector<u_long> seeds;
        std::string discard;

        std::stringstream sstr(line);
        sstr >> discard; // seeds:
        u_long seed;

        while (sstr >> seed)
                seeds.push_back(seed);
        return seeds;
}

std::vector<mapping> readMapping() {
        std::vector<mapping> map;
        std::string name;
        std::getline(std::cin, name);
        std::cout << name << std::endl;
        while (std::getline(std::cin, name)) {
                mapping m;
                if (name.size() == 0)
                        break;
                std::stringstream ss(name);
                ss >> m.dst >> m.src >> m.len;
                map.push_back(m);
        }
        return map;
}

u_long doOneMap(u_long start, const std::vector<mapping> &map) {
        for (auto const &m: map)
                if (start >= m.src && start < m.src + m.len)
                        return (start - m.src) + m.dst;
        return start;
}

u_long doMapping(u_long start, const std::vector<std::vector<mapping>>& maps) {
        for (auto const &map: maps) {
                start = doOneMap(start, map);
        }
        return start;
}

int main() {
        std::vector<std::vector<mapping>> maps;
        std::string line, discard;
        std::getline(std::cin, line);
        auto seeds = getSeeds(line);

        std::getline(std::cin, line); // empty line

        for (int i = 0; i < 7; i++)
                maps.push_back(readMapping());

        auto minloc = std::numeric_limits<u_long>::max();
        for (auto seed: seeds)
                minloc = std::min(doMapping(seed, maps), minloc);
        std::cout << "minloc: " << minloc << std::endl;
}
