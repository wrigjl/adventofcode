#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

#define NRED 12
#define NGREEN 13
#define NBLUE 14

std::vector<std::string> split(const std::string &str, char c) {
        std::stringstream ss(str);
        std::vector<std::string> vec;
        std::string s;

        while (std::getline(ss, s, c))
                vec.push_back(s);
        return vec;
}

std::string strip(std::string s) {
        while (s.size() > 0 && s.front() == ' ')
                s = s.substr(1, std::string::npos);
        while (s.size() > 0 && s.back() == ' ')
                s.pop_back();
        return s;
}

int main() {
        std::string line;
        size_t sum = 0, powsum = 0;

        while (std::getline(std::cin, line)) {
                bool possible = true;
                auto gameLine = split(line, ':');
                auto gameId = gameLine.at(0), game = gameLine.at(1);
                std::map<std::string, size_t> needs = {{"blue", 0}, {"red", 0}, {"green", 0}};
                std::stringstream gameStream(gameId);
                std::string gameWord;
                int id;

                gameStream >> gameWord >> id;

                for (auto turn: split(game, ';')) {
                        turn = strip(turn);
                        std::cout << id << ": " << turn << std::endl;
                        for (auto colornum: split(turn, ',')) {
                                std::stringstream ss(colornum);
                                std::string color;
                                size_t num;

                                ss >> num;
                                ss >> color;

                                needs[color] = std::max(needs[color], num);
                                if (color == "blue" && num > NBLUE)
                                        possible = false;
                                if (color == "red" && num > NRED)
                                        possible = false;
                                if (color == "green" && num > NGREEN)
                                        possible = false;
                        }
                }

                if (possible)
                        sum += id;

                powsum += needs["red"] * needs["green"] * needs["blue"];
        }

        std::cout << sum << std::endl;
        std::cout << "powersum: " << powsum << std::endl;
}
