
#include <iostream>
#include <regex>
#include <stdexcept>
#include <map>
#include <bitset>

std::map<std::string, bool> valueMap;

struct Expr {
	std::string lhs;
	std::string op;
	std::string rhs;
	std::string res;
};

std::vector<Expr> exprList;

int main() {

	std::string line;

	const std::regex value_re("([0-9a-z]+): ([01])");
        while (std::getline(std::cin, line)) {
		if (line.size() == 0)
			break;

		std::smatch match;
		if (!std::regex_match(line, match, value_re) ||
		    match.size() != 3)
			throw std::runtime_error(line);

		valueMap.insert({match[1].str(),
				match[2].str()[0] == '0' ? false : true});
	}

	const std::regex expr_re("([a-z0-9]+) ([A-Z]+) ([a-z0-9]+) -> ([a-z0-9]+)");
	while (std::getline(std::cin, line)) {
		if (line.size() == 0)
			break;

		std::smatch match;
		if (!std::regex_match(line, match, expr_re) ||
		    match.size() != 5)
			throw std::runtime_error(line);

                Expr expr;
		expr.lhs = match[1].str();
		expr.op = match[2].str();
		expr.rhs = match[3].str();
		expr.res = match[4].str();
		exprList.push_back(expr);
	}

	size_t changes;
	do {
		changes = 0;

                for (auto const& expr: exprList) {
			// missing lhs
			if (valueMap.count(expr.lhs) == 0)
				continue;

			// missing rhs
			if (valueMap.count(expr.rhs) == 0)
				continue;

			// already have this value
			if (valueMap.count(expr.res) != 0)
				continue;

			changes++;
			bool val;
			if (expr.op == "AND")
				val = valueMap[expr.lhs] && valueMap[expr.rhs];
			else if (expr.op == "OR")
				val = valueMap[expr.lhs] || valueMap[expr.rhs];
			else if (expr.op == "XOR")
				val = valueMap[expr.lhs] ^ valueMap[expr.rhs];
			else
				throw std::runtime_error(expr.op);

			valueMap.insert({expr.res, val});
				
		}
	} while (changes != 0);

	size_t val = 0;
	size_t cnt = 0;
	for (auto const& i: valueMap) {
		std::cout << i.first << ": " << i.second << std::endl;
		if (i.first.starts_with("z")) {
			val <<= 1;
			val |= i.second ? 1 : 0;
			cnt++;
		}
	}
	std::cout << std::bitset<64>{val} << std::endl;

        size_t valx = 0;
	for (size_t i = 0; i < cnt; i++) {
		valx <<= 1;
		valx |= val & 1;
		val >>= 1;
	}
	std::cout << std::bitset<64>{valx} << std::endl;
	std::cout << valx << std::endl;
}
