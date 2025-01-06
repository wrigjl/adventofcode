
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;
map<string,char> gateType;
map<string, vector<string>> gateConns;
map<string,bool> gateState; // true for on

struct Pulse {
    string name;
    bool high;
};
deque<Pulse> pulses;

size_t highPulses = 0;
size_t lowPulses = 0;

void addPulse(string name, bool high) {
    if (high)
        highPulses++;
    else
        lowPulses++;

    pulses.push_back({name, high});
}

void simulate() {
    while (!pulses.empty()) {
        auto pulse = pulses.front();
        pulses.pop_front();

        if (pulse.name == "broadaster") {
            for (auto const& gate: gateConns[pulse.name])
                addPulse(gate, pulse.high);
        } else if (gateType[pulse.name] == '%') {
            if (pulse.high) {
                // nothing to do
            } else {
                bool sendPulse = gateState[pulse.name] ? false : true;
                gateState[pulse.name] = !gateState[pulse.name];
                for (auto const& gate: gateConns[pulse.name])
                    addPulse(gate, sendPulse);
            }
        }
    }

}
int main() {

}
