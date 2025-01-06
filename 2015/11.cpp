#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

bool hasStraight(const string& s) {
    for (size_t i = 2; i < s.size(); i++)
        if (s[i-2] + 2 == s[i-1] + 1 && s[i-1] + 1 == s[i])
            return true;
    return false;
}

bool noBadLetters(const string& s) {
    if (s.find('i') != string::npos)
        return false;
    if (s.find('o') != string::npos)
        return false;
    if (s.find('l') != string::npos)
        return false;
    return true;
}

bool hasTwoPairs(const string& s) {
    unordered_set<string> pairs;

    for (size_t i = 1; i < s.size(); i++) {
        if (s[i-1] == s[i]) {
            string key(1, s[i-1]);
            key.append(1, s[i]);
            pairs.insert(key);
        }
    }

    if (pairs.size() >= 2)
        return true;
    if (pairs.empty())
        return false;

    for (auto const& p: pairs)
        if (s.rfind(p) - s.find(p) >= 2)
            return true;

    return false;
}

void incr(string &s, size_t idx) {
    if (idx >= s.size())
        return;
    if (s[idx] == 'z') {
        s[idx] = 'a';
        incr(s, idx - 1);
    } else
        s[idx]++;
}

int main() {

    string pwd;
    getline(cin, pwd);

    for (;;) {
        if (hasStraight(pwd) && noBadLetters(pwd) && hasTwoPairs(pwd))
            break;
        incr(pwd, pwd.size() - 1);
    }
    cout << pwd << endl;

    incr(pwd, pwd.size() - 1);
    for (;;) {
        if (hasStraight(pwd) && noBadLetters(pwd) && hasTwoPairs(pwd))
            break;
        incr(pwd, pwd.size() - 1);
    }
    cout << pwd << endl;
}