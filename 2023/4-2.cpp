#include <iostream>
#include <unordered_set>
#include <string>
#include <sstream>
#include <map>

int main() {
        std::string line;
        u_long score = 0;
        std::map<int, u_long> copies;

        while (std::getline(std::cin, line)) {
                std::unordered_set<u_long> mynums;
                std::unordered_set<u_long> winningnums;
                std::stringstream ss(line);
                std::string discard;
                std::string s;
                bool firstNums = true;
                int cardId;

                ss >> discard; // Card
                ss >> cardId;  // 1
                ss >> discard; // :

                if (copies.count(cardId) == 0)
                        copies.insert({cardId, 1});
                else
                        copies[cardId]++;

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

                for (int i = 1; i <= intersect.size(); i++) {
                        if (copies.count(cardId + i) == 0)
                                copies.insert({cardId + i, copies[cardId]});
                        else
                                copies[cardId + i] += copies[cardId];
                }

                std::cout << "after " << cardId << std::endl;
                for (auto x: copies)
                        std::cout << x.first << ": " << x.second << std::endl;
        }
        std::cout << "score: " << score << std::endl;

        u_long ncards = 0;
        for (const auto& x: copies)
                ncards += x.second;
        std::cout << "ncards: " << ncards << std::endl;
}
