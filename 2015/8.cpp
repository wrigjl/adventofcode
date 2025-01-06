#include <iostream>
#include <string>

using namespace std;

u_long memLen(const string& line) {
    u_long sum = 0;

    bool inEscape = false;
    for (auto c: line) {
        sum += 1;
        if (inEscape) {
            if (c == '\'' || c == '"' || c == '\\')
                sum -= 1;
            else if (c == 'x')
                sum -= 3;

            inEscape = false;
        } else {
            if (c == '\\')
                inEscape = true;
        }
    }

    sum -= 2;
    return sum;
}

u_long encLen(const string& line) {
    u_long sum = line.size();
    for (auto c: line) {
        if (c == '"' || c == '\\' || c == '\'')
            sum++;
    }
    return sum + 2;
}

int main() {
    u_long sum = 0;
    string line;
    u_long part2sum = 0;

    while (getline(cin, line)) {
        u_long len = memLen(line);
        cout << line << ":" << len << endl;
        sum += line.size() - len;

        part2sum += encLen(line) - line.size();
    }
    cout << "part1 " << sum << endl;
    cout << "part2 " << part2sum << endl;
}