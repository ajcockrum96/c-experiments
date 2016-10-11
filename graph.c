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
	if (argc <= 4) {
		printf("Error.  Too few arguments\n");
		return EXIT_FAILURE;
	}
	struct iPoint* min   = malloc(sizeof(*min));
	struct iPoint* max   = malloc(sizeof(*max));
	struct iPoint* range = malloc(sizeof(*range));
	sscanf(argv[1], "%d", &(min -> x));
	sscanf(argv[2], "%d", &(min -> y));
	sscanf(argv[3], "%d", &(max -> x));
	sscanf(argv[4], "%d", &(max -> y));
	range -> x = (max -> x) - (min -> x);
	range -> y = (max -> y) - (min -> y);
	print_iPoint(min);
	print_iPoint(max);
	print_iPoint(range);
	if (range -> x < 0 || range -> y < 0) {
		printf("Error, silly arguments.\n");
		free(min);
		free(max);
		free(range);
		return EXIT_FAILURE;
	}

	int** graph = malloc(sizeof(*graph) * (range -> y + 1));
	for (int i = 0; i < (range -> y + 1); ++i) {
		graph[i] = malloc(sizeof(*graph[i]) * (range -> x + 1));
		for (int j = 0; j < (range -> x + 1); ++j) {
			graph[i][j] = 0;
		}
	}
	free(min);
	free(max);
	free(range);
	free(graph);
	return EXIT_SUCCESS;
}
