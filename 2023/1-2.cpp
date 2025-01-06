#include <iostream>
#include <cctype>
#include <vector>
#include <string>

int
main() {
        std::string str;
        u_long sum = 0;

        std::vector<std::string> vec = {
                "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
                "zero", "one", "two", "three", "four",
                "five", "six", "seven", "eight", "nine" };

        while (std::getline(std::cin, str)) {
                size_t minindex = std::string::npos;
                size_t maxindex = 0;
                size_t minpos = std::string::npos;
                size_t maxpos = 0;

                for (size_t idx = 0; idx < vec.size(); idx++) {
                        auto pos = str.find(vec[idx]);
                        if (pos != std::string::npos && pos < minpos) {
                                minpos = pos;
                                minindex = idx;
                        }

                        pos = str.rfind(vec[idx]);
                        if (pos != std::string::npos && pos >= maxpos) {
                                maxpos = pos;
                                maxindex = idx;
                        }
                }

                int N = ((minindex % 10) * 10) + (maxindex % 10);

                std::cout << str << ":" << N << "--" << (minindex % 10) << ","
                          << (maxindex % 10) << std::endl;
                sum += N;
        }

        std::cout << sum << std::endl;
}
