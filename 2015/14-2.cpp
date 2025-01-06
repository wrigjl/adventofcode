#include <iostream>
#include <regex>

using namespace std;

const u_long RACETIME = 2503;

struct Reindeer {
    u_long speed;
    u_long runtime;
    u_long resttime;
    u_long points;
    vector<u_long> race;
};

void runRace(Reindeer& r, u_long racetime) {
    u_long dist = 0;
    for (u_long t = 0; t < racetime; t++) {
        u_long dt = t % (r.runtime + r.resttime);
        if (dt < r.runtime)
            dist += r.speed;
        r.race.push_back(dist);
    }
}

vector<Reindeer> reindeers;

void addReindeer(u_long speed, u_long runtime, u_long resttime) {
    Reindeer r;
    r.speed = speed;
    r.runtime = runtime;
    r.resttime = resttime;
    r.points = 0;
    runRace(r, RACETIME);
    reindeers.push_back(r);
}

u_long getPoints(u_long racetime) {
    vector<u_long> maxes;
    for (u_long t = 0; t < racetime; t++) {
        u_long m = 0;
        for (const auto &r : reindeers)
            m = max(m, r.race[t]);
        maxes.push_back(m);
    }
    for (u_long t = 0; t < racetime; t++) {
        for (auto &r : reindeers)
            if (r.race[t] == maxes[t])
                r.points++;
    }
    u_long m = 0;
    for (const auto &r : reindeers)
        m = max(m, r.points);
    return m;
}

int main() {
    string line;
    u_long bestDist = 0;

    while (getline(cin, line)) {
        const regex parseRe("^[A-Z][a-z]+ can fly ([0-9]+) km/s for ([0-9]+) seconds, but then must rest for ([0-9]+) seconds.$");
        smatch match;
        if (!regex_match(line, match, parseRe))
            throw runtime_error(line);
        u_long speed = stoul(match[1].str());
        u_long runtime = stoul(match[2].str());
        u_long resttime = stoul(match[3].str());
        addReindeer(speed, runtime, resttime);
    }
    cout << getPoints(RACETIME) << endl;
}
