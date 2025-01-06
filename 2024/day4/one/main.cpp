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

char getChar(const vector<string>& letters, size_t row, size_t col) {
    if (row >= letters.size() || col >= letters[row].size())
        return '.';
    return letters[row][col];
}

int foundAt(const vector<string>& letters, size_t row, size_t col) {
    int cfound = 0;
    int found = 0;
    string pattern("XMAS");

    // down
    cfound = 0;
    for (size_t i = 0; i < pattern.size(); i++)
        if (getChar(letters, row + i, col) == pattern[i])
            cfound++;
    if (cfound == pattern.size())
        found++;

    // up
    cfound = 0;
    for (size_t i = 0; i < pattern.size(); i++)
        if (getChar(letters, row - i, col) == pattern[i])
            cfound++;
    if (cfound == pattern.size())
        found++;

    // right
    cfound = 0;
    for (size_t i = 0; i < pattern.size(); i++)
        if (getChar(letters, row, col + i) == pattern[i])
            cfound++;
    if (cfound == pattern.size())
        found++;

    // left
    cfound = 0;
    for (size_t i = 0; i < pattern.size(); i++)
        if (getChar(letters, row, col - i) == pattern[i])
            cfound++;
    if (cfound == pattern.size())
        found++;

    // down
    cfound = 0;
    for (size_t i = 0; i < pattern.size(); i++)
        if (getChar(letters, row + i, col + i) == pattern[i])
            cfound++;
    if (cfound == pattern.size())
        found++;

    // up
    cfound = 0;
    for (size_t i = 0; i < pattern.size(); i++)
        if (getChar(letters, row - i, col + i) == pattern[i])
            cfound++;
    if (cfound == pattern.size())
        found++;

    // right
    cfound = 0;
    for (size_t i = 0; i < pattern.size(); i++)
        if (getChar(letters, row + i, col - i) == pattern[i])
            cfound++;
    if (cfound == pattern.size())
        found++;

    // left
    cfound = 0;
    for (size_t i = 0; i < pattern.size(); i++)
        if (getChar(letters, row - i, col - i) == pattern[i])
            cfound++;
    if (cfound == pattern.size())
        found++;

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