#include <iostream>
#include <regex>

using namespace std;

int main() {
    u_long sum = 0;
    u_long ribbon = 0;

    regex parseRe("([0-9]+)x([0-9]+)x([0-9]+)");
    string line;
    while (getline(cin, line)) {
        if (line.empty())
            break;
        smatch match;
        if (!regex_search(line, match, parseRe))
            throw runtime_error(line);
        u_long l = stoul(match[1].str());
        u_long w = stoul(match[2].str());
        u_long h = stoul(match[3].str());
        sum += 2 * l * w;
        sum += 2 * l * h;
        sum += 2 * w * h;
        sum += min(l*w, min(l * h, h*w));

        ribbon += min(l + l + w + w, min(l + l + h + h, h + h + w + w));
        ribbon += l * w * h; // bow
    }
    cout << sum << endl;
    cout << ribbon << endl;
}