#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <sstream>

using namespace std;
struct rule {
    char ch;    // which character to match
    char comp;  // comparison operator, = means no match needed
    int num;
    string dst;
};

map<string, vector<rule>> rules;

vector<rule> parseRuleList(const string& list) {
    vector<rule> rules;
    string str;
    istringstream iss(list);
    regex defaultRe("[0-9a-zA-Z]+");
    regex ruleRe("([xmas])([<>])([0-9]+):([0-9a-zA-Z]+)");
    smatch match;
    while (getline(iss, str, ',')) {
        if (regex_match(str, defaultRe)) {
            rules.push_back({'=', '=', 0, str});
        } else if (regex_match(str, match, ruleRe)) {
            rule r;
            r.ch = match[1].str()[0];
            r.comp = match[2].str()[0];
            r.num = stoi(match[3].str());
            r.dst = match[4].str();
            rules.push_back(r);
        } else
            throw runtime_error(str);
    }
    return rules;
}

void parseRules() {
    string line;
    regex parseRe("([a-z0-9A-Z]+)\\{(.*)\\}");

    while (getline(cin, line)) {
        if (line.size() == 0)
            break;

        smatch match;
        if (!regex_match(line, match, parseRe))
            throw runtime_error(line);

        string name = match[1].str();
        rules.insert({name, parseRuleList(match[2].str())});
    }
}

size_t evalMachine(const map<char, int> & machine, const map<string, vector<rule>> & pairs) {
    string state = "in";
    cout << state << " ";

    for (;;) {
        if (!rules.contains(state))
            break;
        for (auto const &rule: rules[state]) {
            if (rule.comp == '=') {
                state = rule.dst;
                break;
            }
            if (rule.comp == '<' && machine.at(rule.ch) < rule.num) {
                state = rule.dst;
                break;
            }
            if (rule.comp == '>' && machine.at(rule.ch) > rule.num) {
                state = rule.dst;
                break;
            }
        }
        cout << state << " ";
    }
    cout << endl;
    if (state != "A")
        return 0;
    return machine.at('x') + machine.at('m')+ machine.at('a') + machine.at('s');
}

size_t handleMachines() {
    string line;
    regex parseRe("\\{x=([0-9]+),m=([0-9]+),a=([0-9]+),s=([0-9]+)\\}");
    size_t sum = 0;
    while (getline(cin, line)) {
        if (line.size() == 0)
            return 0;

        smatch match;
        if (!regex_match(line, match, parseRe))
            throw runtime_error(line);
        map<char, int> machine;
        machine.emplace('x', stoi(match[1].str()));
        machine.emplace('m', stoi(match[2].str()));
        machine.emplace('a', stoi(match[3].str()));
        machine.emplace('s', stoi(match[4].str()));
        sum += evalMachine(machine, rules);
    }
    return sum;
}
int main() {
    parseRules();

    cout << handleMachines() << endl;
}