
#include <iostream>
#include <regex>
#include <bitset>
#include <vector>
#include <string>

using namespace std;

int main() {
    string line;
    const regex parseRe("^(turn off|turn on|toggle) ([0-9]+),([0-9]+) through ([0-9]+),([0-9]+)$");
    vector<bitset<1000>> leds;

    leds.reserve(1000);
    for (int i = 0; i < 1000; i++)
        leds.emplace_back();

    while (getline(cin, line)) {
        smatch match;
        if (!regex_match(line, match, parseRe))
            throw runtime_error(line);
        u_long x1 = stoul(match[2].str());
        u_long y1 = stoul(match[3].str());
        u_long x2 = stoul(match[4].str());
        u_long y2 = stoul(match[5].str());
        string type = match[1].str();
        bitset<1000> buf;
        for (size_t i = x1; i <= x2; i++)
            buf.set(i, true);

        if (type == "turn off")
            buf.flip();

        for (size_t i = y1; i <= y2; i++) {
            if (type == "toggle")
                leds[i] ^= buf;
            else if (type == "turn on")
                leds[i] |= buf;
            else if (type == "turn off")
                leds[i] &= buf;
        }
    }

    size_t sum = 0;
    for (auto const &led : leds)
        sum += led.count();
    cout << sum << endl;
}