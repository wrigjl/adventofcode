#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <regex>
#include <ranges>

using namespace std;

unordered_map<string, unordered_map<string, unsigned>> map;

void addmap(const string& n1, const string& n2, const unsigned val) {
    map[n1][n2] = val;
    map[n2][n1] = val;
}

unsigned findMin(const string&from, const unordered_set<string>& cities, unsigned soFar) {
    if (cities.empty())
        return soFar;

    unsigned val = numeric_limits<unsigned>::max();
    for (const auto& city : cities) {
        auto newCities = cities;
        newCities.erase(city);
        val = min(val, findMin(city, newCities, soFar + map[from][city]));
    }
    return val;
}

unsigned findMinHelper(const unordered_set<string>& cities) {
    if (cities.empty())
        return 0;
    unsigned val = numeric_limits<unsigned>::max();
    for (const auto& city : cities) {
        auto newCities = cities;
        newCities.erase(city);
        val = min(val, findMin(city, newCities, 0));
    }
    return val;
}

unsigned findMax(const string&from, const unordered_set<string>& cities, unsigned soFar) {
    if (cities.empty())
        return soFar;

    unsigned val = numeric_limits<unsigned>::min();
    for (const auto& city : cities) {
        auto newCities = cities;
        newCities.erase(city);
        val = max(val, findMax(city, newCities, soFar + map[from][city]));
    }
    return val;
}

unsigned findMaxHelper(const unordered_set<string>& cities) {
    if (cities.empty())
        return 0;
    unsigned val = numeric_limits<unsigned>::min();
    for (const auto& city : cities) {
        auto newCities = cities;
        newCities.erase(city);
        val = max(val, findMax(city, newCities, 0));
    }
    return val;
}

int main() {
    string line;

    const regex parseRe("^([a-zA-Z ]+) to ([a-zA-Z ]+) = ([0-9]+)$");
    while (getline(cin, line)) {
        smatch match;
        if (!regex_match(line, match, parseRe))
            throw runtime_error(line);
        addmap(match[1].str(), match[2].str(), stoul(match[3].str()));
    }

    unordered_set<string> cities;
    for (const auto& city: views::keys(map))
        cities.insert(city);

    cout << "part1: " << findMinHelper(cities) << endl;
    cout << "part2: " << findMaxHelper(cities) << endl;
}