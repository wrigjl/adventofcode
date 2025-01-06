#include <iostream>
#include <map>
#include <regex>
#include <stdexcept>

int main() {
        std::map<std::string, std::pair<std::string, std::string>> graph;
        std::string prog;

        std::getline(std::cin, prog);

        std::regex parseRe("([A-Z]+) = \\(([A-Z]+), ([A-Z]+)\\)");

        std::string line;
        while (std::getline(std::cin, line)) {
                if (line.size() == 0)
                        continue;
                std::smatch match;
                std::regex_match(line, match, parseRe);
                if (match.size() != 4)
                        throw std::runtime_error(line);
                graph.insert({match[1].str(), {match[2].str(), match[3].str()}});
        }

        std::string x = "AAA";
        u_long steps = 0;
        for (size_t i = 0; true; i = (i + 1) % prog.size()) {
                steps++;
                if (prog[i] == 'R')
                        x = graph[x].second;
                else
                        x = graph[x].first;
                if (x == "ZZZ")
                        break;
        }
        std::cout << steps << std::endl;
}
