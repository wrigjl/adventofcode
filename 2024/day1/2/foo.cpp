
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int
main() {
	vector<int> v1, v2;
	unordered_map<int, int> v2freq;

	const int N = 1000;
	
	v1.reserve(N);
	v2.reserve(N);

	for (int i = 0; i < N; i++) {
		int x, y;

		cin >> x >> y;
		v1.push_back(x);
		v2.push_back(y);
		if (v2freq.count(y) == 0)
			v2freq.insert({y, 0});
		v2freq.at(y) += 1;
	}

	int dist = 0;
	for (auto x: v1) {
		if (v2freq.count(x) == 0)
			continue;
		dist += v2freq.at(x) * x;
	}
	cout << dist << endl;
	
}
