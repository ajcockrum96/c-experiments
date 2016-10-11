#include <stdio.h>
#include <stdlib.h>

struct iPoint {
	int x;
	int y;
};

void print_iPoint(struct iPoint* point) {
	printf("(%d, %d)\n", point -> x, point -> y);
}

int main(int argc, char* argv[]) {
	struct iPoint* min = malloc(sizeof(*min));
	struct iPoint* max = malloc(sizeof(*max));
	sscanf(argv[1], "%d", &(min -> x));
	sscanf(argv[2], "%d", &(min -> y));
	sscanf(argv[3], "%d", &(max -> x));
	sscanf(argv[4], "%d", &(max -> y));
	print_iPoint(min);
	print_iPoint(max);
	free(min);
	free(max);
	return EXIT_SUCCESS;
}
