
#include <iostream>
#include <string>
#include <regex>
#include <iterator>
#include <stdexcept>

using namespace std;

int product(const string& str) {
	regex mulregex("^mul\\((\\d+),(\\d+)\\)$");
	smatch argsmatch;
	if (!regex_match(str, argsmatch, mulregex))
		throw runtime_error("no match?");
	cout << str << "->" << argsmatch[1].str() << "," << argsmatch[2].str() << endl;
	return stoi(argsmatch[1].str()) * stoi(argsmatch[2].str());
}

int
main() {
	string s;
	int sum = 0;
	int lineno = 1;
	while (getline(cin, s)) {
		cout << "line " << lineno << endl;
		lineno++;

		regex word_regex("(mul\\(\\d+,\\d+\\))|(do\\(\\))|(don't\\(\\))");
		auto words_begin = sregex_iterator(s.begin(), s.end(), word_regex);
		auto words_end = sregex_iterator();

		for (auto i = words_begin; i != words_end; ++i) {
			auto match = *i;
			auto match_str = match.str();
			cout << match_str << endl;
			sum += product(match_str);
		}
	}
	cout << "sum: " << sum << endl;
}
