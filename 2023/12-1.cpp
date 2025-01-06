
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

vector<unsigned> makeNums(const string& s) {
    vector<unsigned> v;
    unsigned len = 0;
    for (auto c: s) {
        if (c == '#') {
            len++;
        } else if (c == '.') {
            if (len > 0) {
                v.push_back(len);
                len = 0;
            }
        }
    }
    if (len > 0)
        v.push_back(len);
    return v;
}

u_long tryLine(string pattern, const vector<unsigned> nums) {
    vector<size_t> locs;
    u_long combs = 0;
    for (size_t i = 0; i < pattern.size(); i++) {
        if (pattern[i] == '?')
            locs.push_back(i);
    }

    uint64_t bits = 0;
    for (uint64_t i = 0; i < (1 << locs.size()); i++) {
        for (size_t l = 0; l < locs.size(); l++)
            pattern[locs[l]] = (i & (1 << l)) ? '#' : '.';
        if (nums == makeNums(pattern)) {
            cout << pattern << endl;
            ++combs;
        }
    }
    cout << combs << endl;
    return combs;
}
int main() {
    string line;
    u_long sum = 0;
    while (getline(cin, line)) {
        vector<unsigned> nums;
        unsigned num = 0;
        string pattern = line.substr(0, line.find(" "));
        string numberStr = line.substr(line.find(" ") + 1, string::npos);
        istringstream iss(numberStr);
        string numStr;
        while (getline(iss, numStr, ','))
            nums.push_back(stoi(numStr));
        sum += tryLine(pattern, nums);
    }
    cout << sum << endl;
}