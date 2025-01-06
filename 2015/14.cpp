#include <iostream>
#include <regex>

using namespace std;

const u_long RUNTIME = 2503;


u_long calcDistance(u_long speed, u_long runtime, u_long resttime, u_long racetime) {
    u_long niters = racetime / (runtime + resttime);
    u_long dist = niters * speed * runtime;
    u_long remainder = racetime % (runtime + resttime);
    if (remainder >= runtime)
        return dist + (speed * runtime);
    return dist + (remainder * speed);
}

int main() {
    string line;
    u_long bestDist = 0;

    cout << "test1: " << calcDistance(14, 10, 127, 1000) << endl;
    cout << "test2: " << calcDistance(16, 11, 162, 1000) << endl;
    while (getline(cin, line)) {
        const regex parseRe("^[A-Z][a-z]+ can fly ([0-9]+) km/s for ([0-9]+) seconds, but then must rest for ([0-9]+) seconds.$");
        smatch match;
        if (!regex_match(line, match, parseRe))
            throw runtime_error(line);
        u_long speed = stoul(match[1].str());
        u_long runtime = stoul(match[2].str());
        u_long resttime = stoul(match[3].str());
        bestDist = max(bestDist, calcDistance(speed, runtime, resttime, RUNTIME));
    }
    cout << bestDist << endl;
}
