
#include <iostream>
#include <vector>

using namespace std;

int
main() {
	vector<int> v1, v2;

	const int N = 1000;
	
	v1.reserve(N);
	v2.reserve(N);

	for (int i = 0; i < N; i++) {
		int x, y;

		cin >> x >> y;
		v1.push_back(x);
		v2.push_back(y);
	}
	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());

	int dist = 0;
	for (int i = 0; i < N; i++) {
		dist += abs(v1[i] - v2[i]);
	}
	cout << dist << endl;
	
}
