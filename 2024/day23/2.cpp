
#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <stdexcept>
#include <unordered_set>
#include <unordered_map>

std::unordered_map<std::string, std::unordered_set<std::string>> theGraph;

void maybeInsert(const std::string &src, const std::string &dst) {
	if (theGraph.count(src) == 0) {
		std::unordered_set<std::string> x;
		theGraph.insert({src, x});
	}
	theGraph[src].insert(dst);
}

void showIt(const std::unordered_set<std::string> &nodes) {
	std::vector<std::string> x;
	std::string sep = "";
	for (auto n: nodes)
		x.push_back(n);
	std::sort(x.begin(), x.end());
	for (auto n: x) {
		std::cout << sep << n;
		sep = ",";
	}
	std::cout << std::endl;
}

void printGraph() {
        for (auto const &i: theGraph) {
		std::cout << i.first << ":";
		for (auto const &j: i.second)
			std::cout << " " << j;
		std::cout << std::endl;
	}
}

bool testSubgraph(const std::unordered_set<std::string>& nodes) {
	std::unordered_map<std::string, std::unordered_set<std::string>> subgraph;
	for (auto const& n1: nodes) {
		for (auto const& n2: nodes) {
			if (theGraph.count(n1) == 0)
				continue;
			if (theGraph[n1].count(n2) == 0)
				continue;
			if (subgraph.count(n1) == 0)
				subgraph.insert({n1, {}});
			subgraph[n1].insert(n2);
		}
	}

        if (subgraph.size() != nodes.size())
		return false;

        for (auto const &i: subgraph) {
		if (subgraph[i.first].size() != nodes.size() - 1)
			return false;
	}

	showIt(nodes);

        return true;
}

bool testSubgraph1(const std::unordered_set<std::string>& nodex) {
	const size_t K = 13;
	std::vector<std::string> names;

	for (auto x: nodex)
		names.push_back(x);

	std::string bitmask(K, 1); // K ones
	bitmask.resize(names.size(), 0); // N - K zeros

	do {
		std::unordered_set<std::string> nodes;
		for (size_t i = 0; i < names.size(); i++)
			if (bitmask[i])
				nodes.insert(names[i]);
		if (testSubgraph(nodes))
			return true;
	} while (std::prev_permutation(bitmask.begin(), bitmask.end()));

	return false;
}

void testSubgraphs() {
	for (auto x: theGraph) {
		auto z = x.second;
		z.insert(x.first);
		if (testSubgraph1(z))
			return;
	}
}

int main() {
	std::string line;

	while (std::getline(std::cin, line)) {

		if (line.size() == 0)
			break;
		size_t pos = line.find('-');
		if (pos == std::string::npos)
			std::runtime_error("missing hyphen");
		std::string lhs = line.substr(0, pos);
		std::string rhs = line.substr(pos+1, std::string::npos);

		maybeInsert(lhs, rhs);
		maybeInsert(rhs, lhs);
	}

	testSubgraphs();
}
