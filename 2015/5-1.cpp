#include <iostream>
#include <string>

using namespace std;

bool isNice(const string &s) {
    vector<string> notNice = { "ab", "cd", "pq", "xy" };
    size_t nvowels = 0;

    for (auto const &nn: notNice)
        if (s.find(nn) != string::npos)
            return false;

    for (auto c: s)
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
            ++nvowels;

    if (nvowels < 3)
        return false;

    for (size_t i = 1; i < s.size(); ++i)
        if (s[i-1] == s[i])
            return true;
    return false;
}

bool checkit(const string &s) {
    bool found = false;
    for (size_t i = 1; i < s.size() && !found; ++i) {
        string sub(1, s[i-1]);
        sub.append(1, s[i]);
        auto pos = s.rfind(sub);
        if (pos == string::npos)
            continue;
        if (pos >= i + 1)
            found = true;
    }

    if (!found)
        return false;
    return true;
}

bool isNice2(const string &s) {
    bool found = false;
    for (size_t i = 1; i < s.size() && !found; ++i) {
        string sub(1, s[i-1]);
        sub.append(1, s[i]);
        auto pos = s.rfind(sub);
        if (pos == string::npos)
            continue;
        if (pos >= i + 1)
            found = true;
    }

    if (!found)
        return false;

    for (size_t i = 2; i < s.size(); ++i)
        if (s[i-2] == s[i])
            return true;
    return false;
}

void testPart2(const string& s, bool expected) {
    bool t = isNice2(s);
    cout << s << " " << boolalpha << " " << ((expected == t) ? "PASS" : "FAIL") << endl;
}

int main() {
    u_long niceStrings = 0;
    u_long nice2 = 0;
    string line;

    while (getline(cin, line)) {
        niceStrings += isNice(line) ? 1 : 0;
        nice2 += isNice2(line) ? 1 : 0;
    }
    cout << "part1 " << niceStrings << endl;
    cout << "part2 " << nice2 << endl;
    checkit("xyxy");

    testPart2("qjhvhtzxzqqjkmpb", true);
    testPart2("xxyxx", true);
    testPart2("uurcxstgmygtbstg", false);
    testPart2("ieodomkazucvgmuy", false);
}