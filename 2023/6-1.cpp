
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

void getLine(std::vector<u_long> &v, u_long &part2) {
        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        std::string discard;
        ss >> discard;
        u_long val;
        while (ss >> val)
                v.push_back(val);

        std::string x = line.substr(line.find(' '), std::string::npos);
        for (auto pos = x.find(' '); pos != std::string::npos; pos = x.find(' '))
                x.erase(pos, 1);
        part2 = std::stoul(x);
        std::cout << "Part2: " << part2 << std::endl;
}

u_long simulate(u_long rectime, u_long recdist) {
        u_long wins = 0;
        for (u_long i = 0; i <= rectime; i++) {
                u_long speed = i;
                u_long dist = (rectime - i) * speed;
                wins += (dist > recdist) ? 1 : 0;
        }
        std::cout << rectime << "/" << recdist << "=" << wins << std::endl;
        return wins;
}

int main() {
        std::vector<u_long> rec_times;
        std::vector<u_long> rec_distances;
        u_long ways = 1, part2time, part2dist;

        getLine(rec_times, part2time);
        getLine(rec_distances, part2dist);

        for (size_t i = 0; i < rec_times.size(); i++)
                ways *= simulate(rec_times.at(i), rec_distances.at(i));
        std::cout << ways << std::endl;

        ways = simulate(part2time, part2dist);
        std::cout << ways << std::endl;
}
