#include <iostream>
#include <string>
#include <stdint.h>

u_long nextSecret(u_long secret) {
	u_long r;

	r = secret * 64;
	secret = r ^ secret;
	secret %= 16777216;

	r = secret / 32;
	secret ^= r;
	secret %= 16777216;
	
	r = secret * 2048;
	secret ^= r;
	secret %= 16777216;

	return secret;
}

int main() {
	u_long u;
	u_long sum = 0;

	while (std::cin >> u) {
		
		for (int i = 0; i < 2000; i++) {
			u = nextSecret(u);
		}
		sum += u;
	}
	std::cout << sum << std::endl;
}
