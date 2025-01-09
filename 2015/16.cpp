#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <string>
#include <vector>
#include <regex>
#include <stdexcept>

using namespace std;

unordered_map<string, u_long> props = {
    {"children", 3},
    {"cats", 7},
    {"samoyeds", 2},
    {"pomeranians", 3},
    {"akitas", 0},
    {"vizslas", 0},
    {"goldfish", 5},
    {"trees", 3},
    {"cars", 2},
    {"perfumes", 1},
};

bool matchProp(const string &name, u_long num) { return props[name] == num; }

bool matchProp2(const string &name, u_long num) {
        if (name == "cats" || name == "trees")
                return num > props[name];
        if (name == "pomeranians" || name == "goldfish")
                return num < props[name];
        return props[name] == num; }

int main() {
        const regex parseRe("^Sue ([0-9]+): "
                      "([a-z]+): ([0-9]+), "
                      "([a-z]+): ([0-9]+), "
                      "([a-z]+): ([0-9]+)$");
        smatch match;
        string line;

        while (getline(cin, line)) {
                if (line.size() == 0)
                        break;
                if (!regex_match(line, match, parseRe))
                        throw runtime_error(line);

                const u_long sueNo = stoul(match[1].str());
                if (matchProp(match[2].str(), stoul(match[3].str())) &&
                    matchProp(match[4].str(), stoul(match[5].str())) &&
                    matchProp(match[6].str(), stoul(match[7].str())))
                        cout << "part1: " << sueNo << endl;

                if (matchProp2(match[2].str(), stoul(match[3].str())) &&
                    matchProp2(match[4].str(), stoul(match[5].str())) &&
                    matchProp2(match[6].str(), stoul(match[7].str())))
                        cout << "part2: " << sueNo << endl;
        }
}
