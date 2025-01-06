
#include <iostream>
#include <regex>
#include <bitset>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    string line;
    const regex parseRe("^(turn off|turn on|toggle) ([0-9]+),([0-9]+) through ([0-9]+),([0-9]+)$");
    vector<vector<u_long>> leds;

    leds.reserve(1000);
    for (int i = 0; i < 1000; i++) {
        vector<u_long> vb(1000);
        for (size_t j = 0; j < 1000; j++)
            vb[j] = 0;
        leds.push_back(vb);
    }
    while (getline(cin, line)) {
        smatch match;
        if (!regex_match(line, match, parseRe))
            throw runtime_error(line);
        u_long x1 = stoul(match[2].str());
        u_long y1 = stoul(match[3].str());
        u_long x2 = stoul(match[4].str());
        u_long y2 = stoul(match[5].str());
        string type = match[1].str();

        for (size_t x = x1; x <= x2; x++) {
            for (size_t y = y1; y <= y2; y++) {
                if (type == "turn on")
                    leds[x][y]++;
                else if (type == "turn off")
                    leds[x][y] = leds[x][y] == 0 ? 0 : leds[x][y] - 1;
                else if (type == "toggle")
                    leds[x][y] += 2;
            }
        }
    }

    u_long sum = 0;
    for (auto const &v: leds) {
        for (auto n: v)
            sum += n;
    }
    cout << sum << endl;
}