
#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <regex>
#include <stdexcept>
#include <unordered_set>
#include <unordered_map>

std::unordered_map<std::string, std::unordered_set<std::string>> theGraph;
size_t count = 0;

void maybeSet(const std::string &a,
	      const std::string &b,
	      const std::string &c,
	      std::unordered_set<std::string>& found) {
	std::vector<std::string> v = {a, b, c};
	std::sort(v.begin(), v.end());
	std::string s = v[0] + v[1] + v[2];
	if (found.count(s) == 0) {
		std::cout << s << std::endl;
		if (s[0] == 't' || s[2] == 't' || s[4] == 't')
			count++;
	}
	found.insert(s);
}
	
void traverse(const std::string &node,
              std::unordered_set<std::string> &visited,
	      std::unordered_set<std::string> &theSet) {
	if (visited.count(node) > 0)
		return;
	visited.insert(node);
	if (visited.size() == 3) {
		std::vector<std::string> v;
		for (const auto &x: visited)
			v.push_back(x);
		std::sort(v.begin(), v.end());

		std::string key = v[0] + v[1] + v[2];
		if (theSet.count(key) == 0)
			std::cout << key << std::endl;
		theSet.insert(key);
	} else {
		if (theGraph.count(node) == 0)
			return;
		for (const auto& x: theGraph[node]) {
			traverse(x, visited, theSet);
		}
		visited.erase(node);
	}
}	

void maybeInsert(const std::string &src, const std::string &dst) {
	if (theGraph.count(src) == 0) {
		std::unordered_set<std::string> x;
		theGraph.insert({src, x});
	}
	theGraph[src].insert(dst);
}

void buildSubGraph(const std::string &start) {
	std::unordered_set<std::string> visited;
	std::unordered_set<std::string> toVisit;

	toVisit.insert(start);
	while (!toVisit.empty()) {
		auto x = *toVisit.begin();
		toVisit.erase(x);

		visited.insert(x);
		for (const auto &node: theGraph[x]) {
			if (visited.count(node) == 0)
				toVisit.insert(node);
		}
	}

	std::string sep = "";
	for (auto const& node: visited) {
		std::cout << sep << node;
		sep = ",";
		theGraph.erase(node);
	}
	std::cout << std::endl;
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

	std::unordered_set<std::string> all;
	while (!theGraph.empty()) {
		std::string a = theGraph.begin()->first;
		for (auto const &b: theGraph[a]) {
			for (auto const &c: theGraph[b]) {
				if (theGraph[a].count(c) > 0) {
					maybeSet(a, b, c, all);
				}
			}
		}
		theGraph.erase(a);
	}

	std::cout << count << std::endl;
}
