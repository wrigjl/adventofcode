#include <iostream>
#include <cctype>

int
main() {
        std::string str;
        char c1, c2;
        u_long sum = 0;

        while (std::getline(std::cin, str)) {
                auto pos = str.crbegin();

                for (; pos != str.crend(); ++pos)
                        if (isdigit(*pos)) {
                                c2 = c1 = *pos;
                                break;
                        }

                for (; pos != str.crend(); ++pos)
                        if (isdigit(*pos))
                                c2 = *pos;

                int N = ((c2 - '0') * 10) + (c1 - '0');
                std::cout << N << "--" << c2 << c1 << std::endl;
                sum += N;
        }

        std::cout << sum << std::endl;
}
