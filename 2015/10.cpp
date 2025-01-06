#include <iostream>
#include <string>
#include <sstream>

using namespace std;

string crank(string input) {
    ostringstream oss("");

    while (!input.empty()) {
        auto c = input[0];
        size_t i;
        for (i = 1; i < input.size(); ++i)
            if (c != input[i])
                break;
        oss << i << c;
        input = input.substr(i, string::npos);
    }
    return oss.str();
}

int main() {
    string digits;

    getline(cin, digits);

    for (int i = 0; i < 50; i++) {
        cout << "  " << i << endl;
        if (i == 40)
            cout << digits.size() << endl;
        digits = crank(digits);
    }
    cout << digits.size() << endl;
}