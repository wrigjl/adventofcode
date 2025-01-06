#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

bool issafe(const vector<int>& v) {
	if (v.size() < 2)
		return true;

	bool ascending = true;
	if (v[0] == v[1])
		return false;
	if (v[0] > v[1])
		ascending = false;

	for (size_t i = 1; i < v.size(); i++) {
		int diff = v[i - 1] - v[i];
		if (abs(diff) < 1 || abs(diff) > 3)
			return false;
		if (ascending && diff > 0)
			return false;
		if (!ascending && diff < 0)
			return false;
	}
	return true;
}

bool dampenedsafe(const vector<int>&orig) {
	if (issafe(orig))
		return true;
	for (size_t i = 0; i < orig.size(); i++) {
		vector v = orig;
		v.erase(v.begin() + i);
		if (issafe(v))
			return true;
	}
	return false;
}

int main() {
	string s;
	int nsafe = 0;
	while (getline(cin, s)) {
		vector<int> v;
		stringstream ss(s);
		int x;
		while (ss >> x) {
			v.push_back(x);
		}
		if (v.size() > 0 && dampenedsafe(v))
			nsafe++;
	}
	cout << "safe: " << nsafe << endl;
}
