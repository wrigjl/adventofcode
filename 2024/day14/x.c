
#include <stdio.h>

int
main() {
	int vx=2, vy=-3;
	int x=2, y=4;

	for (int i = 0; i < 10; i++) {
		printf("t=%d: %d,%d\n", i, x, y);
		x = (x + vx) % 11;
		if (x < 0)
			x = 11 + x;
		if (x < 0) x = -x;
		y = (y + vy) % 7;
		if (y < 0)
			y = 7 + y;
	}
	return 0;
}
