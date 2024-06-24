#include <stdio.h>

int fibb(int n) {
	if (n == 0) {
		return 0;
	} else if (n == 1) {
		return 1;
	} else {
		return fibb(n-2) + fibb(n-1);
	}
}

int main() {
	for (int i = 0; i < 10; i++) {
		printf("%d,", fibb(i));
	}
}