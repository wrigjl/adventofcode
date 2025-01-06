
#include <iostream>
#include <stdexcept>
#include <vector>
#include <stdexcept>

#if 0
int A = 729;
int B = 0;
int C = 0;

std::vector<int> program = { 0,1,5,4,3,0 };
#elif 1
int A = 34615120;
int B = 0;
int C = 0;

std::vector<int> program{2, 4, 1, 5, 7, 5, 1, 6, 0, 3, 4, 3, 5, 5, 3, 0};
#elif 0
int A = 0;
int B = 0;
int C = 9;

std::vector<int> program{2, 6};
#elif 0
int A = 10;
int B = 0;
int C = 0;

std::vector<int> program{5, 0, 5, 1, 5, 4};
#elif 0
int A = 2024;
int B = 0;
int C = 0;

std::vector<int> program{0,1,5,4,3,0};
#elif 0
int A = 0;
int B = 29;
int C = 0;

std::vector<int> program{1,7};
#elif 0
int A = 0;
int B = 2024;
int C = 43690;

std::vector<int> program{4,0};
#endif

std::vector<int> output;

int getCombo(int arg) {
	if (arg >= 0 && arg <= 3)
		return arg;
	if (arg == 4)
		return A;
	if (arg == 5)
		return B;
	if (arg == 6)
		return C;
	throw std::runtime_error("bad combo");
}

int main() {
	int pc = 0;

	for (;;) {
#if 1
		std::cout << "PC=" << pc << " A=" << A << " B=" << B
			  << " C=" << C << std::endl;
#endif
		if (pc < 0 || pc >= program.size())
			break;
		int operand = pc + 1;
		if (program[pc] == 0) {
			A >>= getCombo(program[operand]);
			pc += 2;
		} else if (program[pc] == 1) {
			B ^= program[operand];
			pc += 2;
		} else if (program[pc] == 2) {
			B = getCombo(program[operand]) % 8;
			pc += 2;
		} else if (program[pc] == 3) {
			if (A != 0)
				pc = program[pc + 1];
			else
				pc += 2;
		} else if (program[pc] == 4) {
			B ^= C;
			pc += 2;
		} else if (program[pc] == 5) {
			output.push_back(getCombo(program[pc + 1]) % 8);
			pc += 2;
		} else if (program[pc] == 6) {
			B = A >> getCombo(program[operand]);
			pc += 2;
		} else if (program[pc] == 7) {
			C = A >> getCombo(program[operand]);
			pc += 2;
		}
	}

	std::string sep;
	for (const auto i: output) {
		std::cout << sep << i;
		sep = ",";
	}
	std::cout << std::endl;
}
