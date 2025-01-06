#include <iostream>
#include <map>
#include <regex>
#include <stdexcept>

int main() {
        std::map<std::string, std::pair<std::string, std::string>> graph;
        std::string prog;
        std::vector<std::string> ghosts;

        std::getline(std::cin, prog);

        std::regex parseRe("([0-9A-Z]+) = \\(([0-9A-Z]+), ([0-9A-Z]+)\\)");

        std::string line;
        while (std::getline(std::cin, line)) {
                if (line.size() == 0)
                        continue;
                std::smatch match;
                std::regex_match(line, match, parseRe);
                if (match.size() != 4)
                        throw std::runtime_error(line);
                graph.insert({match[1].str(), {match[2].str(), match[3].str()}});
                if (match[1].str()[2] == 'A')
                        ghosts.push_back(match[1].str());
        }

        u_long steps = 0;
        for (size_t i = 0; true; i = (i + 1) % prog.size()) {
                steps++;

                bool good = true;
                for (size_t idx = 0; idx < ghosts.size(); ++idx) {
                        std::string k = ghosts[idx];
                        std::string n = (prog[i] == 'R') ? graph[k].second : graph[k].first;
                        if (n[2] != 'Z')
                                good = false;
                        ghosts[idx] = n;
                }
                if (good)
                        goto out;
        }
out:
        std::cout << steps << std::endl;
}
