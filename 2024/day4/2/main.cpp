#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> theLetters = {
    "MMMSXXMASM",
    "MSAMXMSMSA",
    "AMXSXMAAMM",
    "MSAMASMSMX",
    "XMASAMXAMM",
    "XXAMMXXAMA",
    "SMSMSASXSS",
    "SAXAMASAAA",
    "MAMMMXMMMM",
    "MXMXAXMASX",
};

bool doesItMatch(const string &str1, const string &str2) {
    if ((str1 == "MAS" || str1 == "SAM") && (str2 == "MAS" || str2 == "SAM"))
        return true;
    return false;
}

char getChar(const vector<string>& letters, size_t row, size_t col) {
    if (row >= letters.size() || col >= letters[row].size())
        return '.';
    return letters[row][col];
}

int foundAt(const vector<string>& letters, size_t row, size_t col) {
    int cfound = 0;
    int found = 0;
    string pattern("MAS");

    if (getChar(letters, row, col) != 'A')
        return 0;

    // horizontal/vertical
    string s1 = "XXX", s2 = "XXX";
#if 0
    s1[0] = getChar(letters, row - 1, col);
    s1[1] = getChar(letters, row, col);
    s1[2] = getChar(letters, row + 1, col);
    s2[0] = getChar(letters, row, col - 1);
    s2[1] = getChar(letters, row, col);
    s2[2] = getChar(letters, row, col + 1);
    if (doesItMatch(s1, s2))
        found++;
#endif

    // diagonal
#if 1
    s1[0] = getChar(letters, row - 1, col - 1);
    s1[1] = getChar(letters, row, col);
    s1[2] = getChar(letters, row + 1, col + 1);
    s2[0] = getChar(letters, row - 1, col + 1);
    s2[1] = getChar(letters, row, col);
    s2[2] = getChar(letters, row + 1, col - 1);
    if (doesItMatch(s1, s2))
        found++;
#endif
    return found;
}
int main() {
    int nfound = 0;
    string s;
    theLetters.clear();

    while (getline(cin, s)) {
        if (!s.empty()) {
            theLetters.push_back(s);
        }
    }

    for (size_t i = 0; i < theLetters.size(); i++) {
        for (size_t j = 0; j < theLetters[i].size(); j++) {
            nfound += foundAt(theLetters, i, j);
        }
    }

    cout << nfound << endl;
    return 0;
}
