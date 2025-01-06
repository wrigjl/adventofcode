
#include <iostream>

int
main() {
        std::string line;
        int pos = 0;
        bool found = false;

        std::cin >> line;
        for (size_t i = 0; i < line.size(); i++) {
                char c = line[i];
                if (c == '(')
                        pos++;
                else if (c == ')')
                        pos--;

                if (pos == -1 && found == false) {
                        std::cout << "floor: " << (i + 1) << std::endl;
                        found = !found;
                }
        }
        std::cout << pos << std::endl;
}
