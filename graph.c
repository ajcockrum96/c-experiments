#include <stdio.h>
#include <stdlib.h>

struct iPoint {
	int x;
	int y;
};

struct dPoint {
	double x;
	double y;
};

void print_iPoint(struct iPoint* point) {
	printf("(%d, %d)\n", point -> x, point -> y);
}

void print_dPoint(struct dPoint* point) {
	printf("(%.2lf, %.2lf)\n", point->x, point->y);
}

void print_graph(int** graph, struct iPoint* range) {
	for (int i = range -> y; i >= 0; --i) {
		for (int j = 0; j < (range -> x + 1); ++j) {
			switch (graph[i][j]) {
				case(0):
					printf(" ");
					break;
				case(1):
					printf("+");
					break;
				case(2):
					printf("-");
					break;
				case(3):
					printf("|");
					break;
			}
		}
		printf("\n");
	}
}

int** _blank_graph(struct iPoint* range) {
	int** graph = malloc(sizeof(*graph) * (range->y + 1));
	for (int i = 0; i < (range->y + 1); ++i) {
		graph[i] = malloc(sizeof(*graph[i]) * (range->x + 1));
		for (int j = 0; j < (range->x + 1); ++j) {
			graph[i][j] = 0;
		}
	}
	return graph;
}

void _draw_axes(int** graph, struct iPoint* range, struct iPoint* min) {
	for (int i = 0; i < (range->y + 1); ++i) {
		for (int j = 0; j < (range->x + 1); ++j) {
			if ((i == -(min->y)) && (j == -(min->x))) {
				graph[i][j] = 1;
			}
			else if (i == -(min->y)) {
				graph[i][j] = 2;
			}
			else if (j == -(min->x)) {
				graph[i][j] = 3;
			}
		}
	}
}

int main(int argc, char* argv[]) {
	if (argc <= 6) {
		printf("Error.  Too few arguments\n");
		return EXIT_FAILURE;
	}
	struct iPoint* min   = malloc(sizeof(*min));
	struct iPoint* max   = malloc(sizeof(*max));
	struct iPoint* range = malloc(sizeof(*range));
	struct dPoint* delta = malloc(sizeof(*delta));
	sscanf(argv[1], "%d",  &(min->x));
	sscanf(argv[2], "%d",  &(min->y));
	sscanf(argv[3], "%d",  &(max->x));
	sscanf(argv[4], "%d",  &(max->y));
	sscanf(argv[5], "%lf", &(delta->x));
	sscanf(argv[6], "%lf", &(delta->y));

	range -> x = (max -> x) - (min -> x);
	range -> y = (max -> y) - (min -> y);

	print_iPoint(min);
	print_iPoint(max);
	print_iPoint(range);
	print_dPoint(delta);
	if (range -> x < 0 || range -> y < 0) {
		printf("Error, silly arguments.\n");
		free(min);
		free(max);
		free(range);
		return EXIT_FAILURE;
	}

	int** graph = _blank_graph(range);
	_draw_axes(graph, range, min);

	print_graph(graph, range);
	free(min);
	free(max);
	free(range);
	free(delta);
	free(graph);
	return EXIT_SUCCESS;
}
