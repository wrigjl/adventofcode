
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

#define MODE_FILE  0
#define MODE_EMPTY 1
#define MODE_MAX (MODE_EMPTY + 1)

void printDisk(const std::vector<int>& d) {
	for (auto i: d) {
		if (i == -1)
			std::cout << '.';
		else
			std::cout << i;
	}
	std::cout << std::endl;
}

int main() {
	std::string data;
	std::vector<int> disk;
	int fileid = 0;
	int mode = MODE_FILE;
	unsigned long csum;

        std::getline(std::cin, data);
	for (auto c: data) {
		int cnt = c - '0';
		for (int i = 0; i < cnt; i++)
			disk.push_back(mode == MODE_FILE ? fileid : -1);

		if (mode == MODE_FILE)
			fileid++;
		mode = (mode + 1) % MODE_MAX;
	}

	while (disk.size() > 0 && disk.back() == -1)
		disk.pop_back();
	
	for (size_t i = 0; i < disk.size(); i++) {
		if (disk.at(i) == -1) {
			disk.at(i) = disk.back();
			disk.pop_back();
			
			while (disk.size() > 0 && disk.back() == -1)
				disk.pop_back();
		}
	}

	csum = 0;
	for (auto i = 0; i < disk.size(); i++) {
		if (disk[i] == -1)
			std::runtime_error("bad block");
//		std::cout << i << "*" << disk.at(i) << std::endl;
		csum += i * disk.at(i);;
	}

	std::cout << csum << std::endl;
}
