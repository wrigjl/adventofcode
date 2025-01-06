
#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <algorithm>

// +---+---+---+
// | 7 | 8 | 9 |
// +---+---+---+
// | 4 | 5 | 6 |
// +---+---+---+
// | 1 | 2 | 3 |
// +---+---+---+
//     | 0 | A |
//     +---+---+

//     +---+---+
//     | ^ | A |
// +---+---+---+
// | < | v | > |
// +---+---+---+

class Position {
public:
        size_t row, col;
        bool operator==(const Position &x) const {
                return row == x.row && col == x.col;
        }
};
                
template<> struct std::hash<Position> {
    std::size_t operator()(const Position& s) const noexcept {
            std::size_t h1 = s.row;
            std::size_t h2 = s.col;
            return (h1 << 16) | h2;
    }
};

struct ButtonPath {
        char src;
        char dst;
        bool operator==(const ButtonPath &x) const {
                return src == x.src && dst == x.dst;
        }
};

template<> struct std::hash<ButtonPath> {
    std::size_t operator()(const ButtonPath& s) const noexcept {
            std::size_t h1 = s.src;
            std::size_t h2 = s.dst;
            return (h1 << 16) | h2;
    }
};

const std::vector<std::string> numericPad = {
    "789",
    "456",
    "123",
    "_0A",
};

const std::vector<std::string> directionalPad = {
    "_^A",
    "<v>",
};

bool pathOk(const std::vector<std::string>& pad, const Position& pos, const std::string& path) {
        Position npos = pos;
        for (auto c: path) {
                if (c == '^')
                        npos.row--;
                else if (c == '<')
                        npos.col--;
                else if (c == '>')
                        npos.col++;
                else if (c == 'v')
                        npos.row++;
                else
                        throw std::runtime_error("invalid direction");

                if (npos.row >= pad.size())
                        throw std::runtime_error("invalid row");
                if (npos.col >= pad[npos.row].size())
                        throw std::runtime_error("invalid col");
                if (pad[npos.row][npos.col] == '_')
                        return false;
        }

        return true;
}

void findPath(const std::vector<std::string>& pad, std::unordered_map<ButtonPath, std::vector<std::string>>& paths, const Position& srcpos, const Position& dstpos) {
        char src_c = pad[srcpos.row][srcpos.col];
        char dst_c = pad[dstpos.row][dstpos.col];

        if (srcpos == dstpos) {
                paths.insert({{src_c, dst_c}, { "" }});
                return;
        }

        char vertchar = (srcpos.row < dstpos.row) ? 'v' : '^';
        char horzchar = (srcpos.col < dstpos.col) ? '>' : '<';
        std::string mychars;
        mychars.append(std::max(srcpos.row, dstpos.row) -
                       std::min(srcpos.row, dstpos.row), vertchar);
        mychars.append(std::max(srcpos.col, dstpos.col) -
                       std::min(srcpos.col, dstpos.col), horzchar);
        std::sort(mychars.begin(), mychars.end());
        do {
                if (pathOk(pad, srcpos, mychars)) {
                        if (paths.count({src_c, dst_c}) == 0)
                                paths.insert({{src_c, dst_c}, {}});
                        paths[{src_c, dst_c}].push_back(mychars);
                }
        } while ( std::next_permutation(mychars.begin(), mychars.end()) );
        
}

void findPaths(const std::vector<std::string>& pad, std::unordered_map<ButtonPath, std::vector<std::string>>& paths) {
        for (size_t row = 0; row < pad.size(); ++row) {
                for (size_t col = 0; col < pad[row].size(); col++) {
                        if (pad[row][col] == '_')
                                continue;
                        for (size_t rowdst = 0; rowdst < pad.size(); ++rowdst) {
                                for (size_t dstcol = 0; dstcol < pad[rowdst].size(); dstcol++) {
                                        if (pad[rowdst][dstcol] == '_')
                                                continue;
                                        findPath(pad, paths, {row, col}, {rowdst, dstcol});
                                }
                        }
                }
        }
}

void showPath(std::vector<std::string>& results, std::string baseStr,
              char src, const std::string path,
              std::unordered_map<ButtonPath, std::vector<std::string>>& paths) {
        if (path.size() == 0) {
                results.push_back(baseStr);
                return;
        }
        for (const auto str: paths[{src, path.front()}]) {
                showPath(results, baseStr + str + "A", path.front(),
                         path.substr(1, std::string::npos), paths);
        }
}

size_t getCode(std::string s) {
        size_t id;

        std::string xs = s.substr(0, 3);
        while (xs.size() > 1 && xs.front() == '0')
                xs = xs.substr(1, std::string::npos);
        id = std::stoul(xs);

        std::unordered_map<ButtonPath, std::vector<std::string>> numPaths, dirPaths;
        std::vector<std::string> foundPaths;
        findPaths(numericPad, numPaths);
        findPaths(directionalPad, dirPaths);

        showPath(foundPaths, "", 'A', "029A", numPaths);

        std::vector<std::string> nextFoundPaths;
        for (auto const &x: foundPaths) {
                showPath(nextFoundPaths, "", 'A', x, dirPaths);
        }

        foundPaths = nextFoundPaths;
        nextFoundPaths.clear();
        for (auto const &x: foundPaths) {
                showPath(nextFoundPaths, "", 'A', x, dirPaths);
        }
        size_t minpathlen = std::string::npos;
        for (auto const &x: nextFoundPaths)
                minpathlen = std::min(minpathlen, x.size());

        std::cout << s << ": " << minpathlen << " * " << id << std::endl;
        return id * minpathlen;
}

int main () {
        size_t sum = 0;

        sum += getCode("029A");
        sum += getCode("980A");
        sum += getCode("179A");
        sum += getCode("456A");
        sum += getCode("379A");
        std::cout << "sum: " << sum << std::endl;
}
