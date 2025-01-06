
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <unordered_map>

#define MODE_FILE  0
#define MODE_EMPTY 1
#define MODE_MAX (MODE_EMPTY + 1)

std::unordered_map<int, size_t> fileLengths;
std::unordered_map<int, size_t> fileOffsets;

void tryMoveFile(std::vector<int>& disk,
		 const std::vector<std::pair<size_t, size_t>>& extents,
		 int fileid, size_t len, size_t off) {
	for (const auto &ex: extents) {
		if (ex.first >= off)
			return;
		if (len > ex.second)
			continue;

		for (size_t i = 0; i < len; i++) {
			disk[ex.first + i] = fileid;
			disk[off + i] = -1;
		}
		return;
	}
}

void buildExtents(const std::vector<int>& disk, std::vector<std::pair<size_t, size_t>>& extents) {
	extents.clear();

	for (size_t pos = 0; pos < disk.size(); pos++) {
		if (disk[pos] != -1)
			continue;
		if (extents.size() == 0)
			extents.push_back({pos, 1});
		else {
			if (extents.back().first + extents.back().second == pos)
				extents.back().second++;
			else
				extents.push_back({pos, 1});
		}
	}

#if 0
	for (size_t i = 0; i < extents.size(); i++)
		std::cout << "E(off=" << extents[i].first << ",len=" << extents[i].second << ")" << std::endl;
#endif
}


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
	std::vector<int> fileIdList;

        std::getline(std::cin, data);
	for (auto c: data) {
		int cnt = c - '0';
		size_t off = disk.size();
		for (int i = 0; i < cnt; i++)
			disk.push_back(mode == MODE_FILE ? fileid : -1);

		
		if (mode == MODE_FILE) {
			fileLengths.insert({fileid, cnt});
			fileOffsets.insert({fileid, off});
			fileIdList.push_back(fileid);
			fileid++;
		}
		mode = (mode + 1) % MODE_MAX;
	}

#if 0
	printDisk(disk);
#endif
        while (!fileIdList.empty()) {
		int fileid = fileIdList.back();
		fileIdList.pop_back();

                std::vector<std::pair<size_t, size_t>> extents;
		buildExtents(disk, extents);
		size_t fileLen = fileLengths.at(fileid);
		size_t fileOff = fileOffsets.at(fileid);
		tryMoveFile(disk, extents, fileid, fileLen, fileOff);
#if 0
		
		printDisk(disk);
#endif
	}

	csum = 0;
	for (size_t i = 0; i < disk.size(); i++) {
		if (disk[i] != -1)
			csum += i * disk[i];
	}
	std::cout << csum << std::endl;
}
