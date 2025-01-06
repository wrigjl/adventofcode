#include <iostream>
#include <unordered_set>
#include <string>
#include <sstream>
#include <algorithm>

int main() {
        std::string line;
        u_long score = 0;

        while (std::getline(std::cin, line)) {
                std::unordered_set<u_long> mynums;
                std::unordered_set<u_long> winningnums;
                std::stringstream ss(line);
                std::string discard;
                std::string s;
                bool firstNums = true;

                ss >> discard; // Card
                ss >> discard; // 1:
                while (ss >> s) {
                        if (s == "|")
                                firstNums = !firstNums;
                        else {
                                if (firstNums)
                                        winningnums.insert(std::stoul(s));
                                else
                                        mynums.insert(std::stoul(s));
                        }
                }
                std::unordered_set<int> intersect;

                for (auto s1: winningnums)
                        if (mynums.count(s1) > 0)
                                intersect.insert(s1);

                if (intersect.size() > 0)
                        score += 1 << (intersect.size() - 1);

                std::cout << "Winning:";
                for (auto x: winningnums)
                        std::cout << " " << x;
                std::cout << std::endl;

                std::cout << "MyNums:";
                for (auto x: mynums)
                        std::cout << " " << x;
                std::cout << std::endl;

                std::cout << "Intersect:";
                for (auto x: intersect)
                        std::cout << " " << x;
                std::cout << std::endl;
        }
        std::cout << "score: " << score << std::endl;
}
