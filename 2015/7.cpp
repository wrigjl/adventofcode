
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <regex>

using namespace std;

map<string,u_int16_t> values;

void setValue(const string& key, const u_int16_t val, bool part2) {
    if (part2 && key == "b")
        return;
    values[key] = val;
}

bool eval(const string& str, bool part2) {
    smatch match;

    const regex notRe("^NOT ([a-z]+) -> ([a-z]+)$");
    if (regex_match(str, match, notRe)) {
        if (values.count(match[1].str()) == 0)
            return false;
        u_int16_t val = values[match[1].str()];
        val ^= 0xffff;
        setValue(match[2].str(), val, part2);
        return true;
    }

    const regex orRe("^([a-z]+) OR ([a-z]+) -> ([a-z]+)$");
    if (regex_match(str, match, orRe)) {
        if (values.count(match[1].str()) == 0 || values.count(match[2].str()) == 0)
            return false;
        setValue(match[3].str(), values[match[1].str()] | values[match[2].str()], part2);
        return true;
    }

    const regex constRe("^([0-9]+) -> ([a-z]+)$");
    if (regex_match(str, match, constRe)) {
        setValue(match[2].str(), stoul(match[1].str()), part2);
        return true;
    }

    const regex andRe("^([a-z]+) AND ([a-z]+) -> ([a-z]+)$");
    if (regex_match(str, match, andRe)) {
        if (values.count(match[1].str()) == 0 || values.count(match[2].str()) == 0)
            return false;
        setValue(match[3].str(), values[match[1].str()] & values[match[2].str()], part2);
        return true;
    }

    const regex varRe("^([a-z]+) -> ([a-z]+)$");
    if (regex_match(str, match, varRe)) {
        if (values.count(match[1].str()) == 0)
            return false;
        setValue(match[2].str(), values[match[1].str()], part2);
        return true;
    }

    const regex andConstRe("^([0-9]+) AND ([a-z]+) -> ([a-z]+)$");
    if (regex_match(str, match, andConstRe)) {
        if (values.count(match[2].str()) == 0)
            return false;
        setValue(match[3].str(), stoul(match[1].str()) & values[match[2].str()], part2);
        return true;
    }

    const regex rshiftRe("^([a-z]+) RSHIFT ([0-9]+) -> ([a-z]+)$");
    if (regex_match(str, match, rshiftRe)) {
        if (values.count(match[1].str()) == 0)
            return false;
        setValue(match[3].str(), values[match[1].str()] >> stoul(match[2].str()), part2);
        return true;
    }

    const regex lshiftRe("^([a-z]+) LSHIFT ([0-9]+) -> ([a-z]+)$");
    if (regex_match(str, match, lshiftRe)) {
        if (values.count(match[1].str()) == 0)
            return false;
        setValue(match[3].str(), values[match[1].str()] << stoul(match[2].str()), part2);
        return true;
    }

    throw runtime_error(str);
    return false;
}

int main() {
    string line;
    vector<string> exprsorig;
    vector<string> exprs;

    while (getline(cin, line))
        exprs.push_back(line);

    exprsorig = exprs;

    while (values.count("a") == 0) {
        for (auto it = exprs.begin(); it != exprs.end(); it++) {
            if (eval(*it, false)) {
                exprs.erase(it);
                break;
            }
        }
    }

    cout << "part1: " << values["a"] << endl;

    u_int16_t val = values["a"];
    values.clear();
    values["b"] = val;

    exprs = exprsorig;
    while (values.count("a") == 0) {
        for (auto it = exprs.begin(); it != exprs.end(); it++) {
            if (eval(*it, true)) {
                exprs.erase(it);
                break;
            }
        }
    }
    cout << "part2: " << values["a"] << endl;
}