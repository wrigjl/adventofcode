
#include <iostream>
#include <string>
#include <sstream>

u_int hash(const std::string& s) {
    u_int h = 0;
    for (u_char c: s) {
        h += c;
        h *= 17U;
        h %= 256;
    }
    return h;
}

int main() {
    u_long sum = 0;
    std::vector<std::string> words;
    std::string line;

    while (std::getline(std::cin, line)) {
        std::string word;
        std::istringstream iss(line);
        while (std::getline(iss, word, ',')) {
            words.push_back(word);
        }
    }

    for (const auto& word: words) {
        auto h = hash(word);
        std::cout << word << " " << h << std::endl;
        sum += h;
    }

    std::cout << sum << std::endl;
}